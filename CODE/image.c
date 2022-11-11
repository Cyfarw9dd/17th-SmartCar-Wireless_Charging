/*
    ���������ͼ��ʱ��Ҫע��һ�㣬�����ԭʼͼ���С��120 * 188�ġ������XYƽ������ϵ��ʾԭʼͼ��Ļ��������ͼ�������ԭ��
    λ�����Ϸ������У�x��������Ϊ��ֱ���£�y��������Ϊˮƽ���ҡ�
    ����֮��X�����ʾ����ͼ���������Y�����ʾͼ���е�������

    mt9v03x_image[120][188]Ϊ���������ͷ�ɼ�����ԭʼ�Ҷ�ͼ��

    �ڻҶ�ͼ���У�ÿ�����ص���������ԵĻҶ�ֵ�ģ���Щ�Ҷ�ֵ����Ϊ30������Ϊ90������Խ����ɫԽǳ������ԽС����ɫԽ��һ�
    ��ֵ�ķ�ΧΪ0~255�����ԣ��Ҷ�ֵΪ0�ᱻ���Ϊ��ɫ��Ϊ255�Ļ���Ϊ��ɫ��
    0~255ǡ��Ϊ�޷��Ų������(unsigned char)������ֵ�ķ�Χ����ADS��д��unsigned char�������й���ͼ����ͼ������ı������Ὣ����
    ��Ϊunsigned char���͡�


    //-----------------------------------------------------------------//
    �������һ���������͵Ĳο���
    unsigned char           unsigned char
    int16                   short
    int32                   int
    �����ADS��Ĺ��õ�д�������ǲ�������C��׼���ұ���C�����е�д��������ADS����ʱ������Ļ�������ߵ�������ʽ
*/

#include "image.h"
#include "gyro.h"
#include "elements.h"
#include "cycle.h"
#include "pid.h"
#include "control.h"

unsigned char centerline[120];                  //�����������飬��������ĺ�������ڣ����ߺ�����+���ߺ����꣩/ 2
unsigned char leftline[120];                    //�������������
unsigned char rightline[120];                   //�����ұ�������
unsigned char image_deal[MT9V03X_H][MT9V03X_W]; //����һ����ά���飬���ڴ�Ŷ�ֵ�����ͼ�����У��±�MT9V03X_H��MT9V03X_W��ʾ�����ͼ��ĸߺͿ�
unsigned char image_deal2[MT9V03X_H][MT9V03X_W];
unsigned char Left_RoadWidth[120];              //��������������ȣ������ߵ�����ߵľ���
unsigned char Right_RoadWidth[120];             //�����Ұ���������
short image_threshold = 0;                      //����ͼ������ֵ

/*�������������ڼ������ߵ�ƫ��̶ȣ�����������Ľ������ת�򻷼���*/

int Prospect_Err = 0;                   //����ǰհƫ�ǰհƫ���ȡֵΪʵ�������������Ⱦ�ĵ�ֱ�������������Ĳ�
int Bottom_Err = 0;                     //���峵�����ƫ�������ͷ�ĵ�ͼ�����׶�һ������������ֵ�������������Ĳ�
int further, middle, near;              //ͼ���е�Զ�㣬�е�ͽ���

/*
    ����ͷ���е����庯������򷨣�ɨ�ߵȶ���������������
*/
void Camera(void){
    if(mt9v03x_finish_flag){                              //mt9v03x_finish_flagΪͼ��������ı�־λ������ɿ���������ϸ����
        image_threshold = GetOSTU(mt9v03x_image[0]);      //ͨ��������õ�ԭʼ�Ҷ�ͼ�����ֵ
        lcd_binaryzation032_zoom(mt9v03x_image[0], image_deal[0], MT9V03X_W , MT9V03X_H, image_threshold); //����ֵ�����ͼ���ŵ�image_deal[120][188]��
        Get_IcmData();                                    //��ȡ����������

        Searching_for_boundaries(&image_deal[0]);         //Ѱ�������߽� 
        Deal_Road_Characteristics(&image_deal[0]);        //����������������������Ұ��������ȵ�       
        Turn_cycle_ver2(1800);                            //ת�򻷣�����1800��pwm
        lcd_displayimage032(mt9v03x_image[0], 188, 120);
        Pokemon_Go();                                     //Ԫ���ж�
        Hightlight_Lines(&image_deal[0]);                 //�������ұ߽��Լ�����
        mt9v03x_finish_flag = 0;                          //��־λ��0��һ��Ҫ��0������0�Ļ�ͼ��ֻ������ʼ֡
    }
}


/*
    �������ƣ���򷨻�ȡ��ֵ����
    �������ܣ�ͨ������ԭʼ�Ҷ�ͼ���еĻҶ�ֱ��ͼ���Զ��������ǰ�Ҷ�ͼ���е���ֵ
    ��򷨵ľ���ʵ�ֹ��̿��Բ����ر��˽�
*/
unsigned char otsuThreshold(unsigned char *image, unsigned short col, unsigned short row)
{
    #define GrayScale 256
    unsigned short width = col;
    unsigned short height = row;
    int pixelCount[GrayScale];
    float pixelPro[GrayScale];
    int i, j, pixelSum = width * height;
    unsigned char threshold = 0;
    unsigned char* data = image;  //ָ���������ݵ�ָ��
    for (i = 0; i < GrayScale; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }

    //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            pixelCount[(int)data[i * width + j]]++;  //������ֵ��Ϊ����������±�
        }
    }

    //����ÿ������������ͼ���еı���
    float maxPro = 0.0;
    for (i = 0; i < GrayScale; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;
        if (pixelPro[i] > maxPro)
        {
            maxPro = pixelPro[i];
        }
    }

    //�����Ҷȼ�[0,255]
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
    for (i = 0; i < GrayScale; i++)     // i��Ϊ��ֵ
    {
        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
        for (j = 0; j < GrayScale; j++)
        {
            if (j <= i)   //��������
            {
                w0 += pixelPro[j];
                u0tmp += j * pixelPro[j];
            }
            else   //ǰ������
            {
                w1 += pixelPro[j];
                u1tmp += j * pixelPro[j];
            }
        }
        u0 = u0tmp / w0;
        u1 = u1tmp / w1;
        u = u0tmp + u1tmp;
        deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
        if (deltaTmp > deltaMax)
        {
            deltaMax = deltaTmp;
            threshold = (unsigned char)i;
        }
    }

    return threshold;
}

/*
    ͼ��ɨ�裬��ɨ�ߺ���������һ�����������������Ϊ��ֵ�����ͼ���ָ��
    ͨ����ͼ���м��������������α���Ѱ�ҵ���ɫ�߽�
    ������Щ��ɫ�߽�ĺ�����ֱ��ŵ��߽�������
    �������꼴�ñ��ߵļ������
*/
void Searching_for_boundaries(unsigned char (*binary_array)[188]){
    unsigned char Row = 0;
    unsigned char Left_Col = 0;
    unsigned char Right_Col = 0;
    for(Row=119;Row>0;Row--){
        for(Left_Col=93;Left_Col<188;Left_Col++){
            if(Left_Col == EndCoL){
                rightline[Row] = EndCoL;
                break;
            }
            if((binary_array[Row][Left_Col-2]==255)&&(binary_array[Row][Left_Col-1]==0)&&(binary_array[Row][Left_Col]==0)){
                rightline[Row]=Left_Col;
                break;
            }
        }

        for(Right_Col=93;Right_Col>1;Right_Col--){
            if(Right_Col == StartCoL){
                leftline[Row] = StartCoL;
                break;
            }
            if((binary_array[Row][Right_Col]==0)&&(binary_array[Row][Right_Col+1]==0)&&(binary_array[Row][Right_Col+2]==255)){
                leftline[Row]=Right_Col;
                break;
            }
        }
    }
}


void Deal_Road_Characteristics(unsigned char (*binary_array)[188]){
    for(unsigned char i = BottomRow; i > 0; i--){
        centerline[i] = (rightline[i] + leftline[i]) / 2;
        Left_RoadWidth[i] = absolute(93 - leftline[i]);
        Right_RoadWidth[i] = absolute(rightline[i] - 93);
    }
}

void Hightlight_Lines(unsigned char (*binary_array)[188]){
    for(unsigned char i = BottomRow; i > 0; i--){
        binary_array[i][centerline[i]] = 120;
        binary_array[i][rightline[i]] = 120;
        binary_array[i][leftline[i]] = 120;
    }
}

/*
    ��ֵ������
    *p          ԭʼͼ������ָ��
    *q          ��ͼ������ָ��
    width       ԭʼͼ��Ŀ�
    height      ԭʼͼ��ĸ�
    threshold   ��ֵ������Ϊ��򷨼������ͼ����ֵ
*/

void lcd_binaryzation032_zoom(unsigned char *p, unsigned char *q, unsigned short width, unsigned short height, unsigned char threshold)//����һ�����������ָ�룬Ȼ������޸���������
{
    unsigned i,j;
    unsigned short temp = 0;

    for(j=0;j<height;j++)
    {
        for(i=0;i<width;i++)
        {
            temp = *p;
            if(temp>threshold)
                *q = 255;
            else
                *q  = 0;
            ++q;
            ++p;
        }
    }
}

/*
    �������˲�
*/
void Four_neighbourhood_Filter(unsigned char (*binary_array)[188]){
    short row; //��
    short col; //��

    for (col = 1; col < MT9V03X_H - 1; col++)
    {
        for (row = 1; row < MT9V03X_W - 1; row++)
        {
            if ((binary_array[col][row] == 0)
                    && (binary_array[col - 1][row] + binary_array[col + 1][row] + binary_array[col][row + 1] + binary_array[col][row - 1] > 550))
            {
                binary_array[col][row] = 255;
            }
            else if ((binary_array[col][row] == 1)
                    && (binary_array[col - 1][row] + binary_array[col + 1][row] + binary_array[col][row + 1] + binary_array[col][row - 1] < 550))
            {
                binary_array[col][row] = 0;
            }
        }
    }
}

float one_curvature(int x1, int y1) // one_curvature(centerline[30], 30)
{
    float K;
    int l = x1 - 63;
    int h = y1 - 59;
    K = (float)2 * l / (l * l + h * h);
    return K;
}

/*
    �������ƣ���������ƫ��
    ����ֵ����
    ��������
    ���ù��̣�
    �Զ���ǰհ������Ĭ����15��ǰհ����ֵԽ�󣬴����Ų���ƫ������������Խ�࣬ǰհ����ֵԽС������ƫ������������ԽС������Ӧ
    �͸����������Զ���Զ�㣬�е㣬���㣬ʵ�ʵ�����ƫ��������������ʵ��������������á����ң��������������ȡ���ٽ���������
    ��Ӳ����ֵ�������ܵع��˵��쳣���ݡ�
*/

void cal_curvature(void){
    int prospect = 15;            //�Զ���ǰհ���� 15

    near = (centerline[119] + centerline[119 - 1] + centerline[119 - 2]) / 3;
    middle = (centerline[119 - prospect] + centerline[119 - prospect - 1] + centerline[119 - prospect - 2]) / 3;
    further = (centerline[119 - prospect * 2] + centerline[119 - prospect * 2 - 1] + centerline[119 - prospect * 2 - 2]) / 3;

    if(further < middle && middle < near){
        Prospect_Err = ((middle - further)  + (near - middle)) / 2;
    }
    else if(further < middle && middle >= near){
        Prospect_Err = near - middle;
    }
    else if(further >= middle && middle < near){
        Prospect_Err = near - middle;
    }
    else{
        Prospect_Err = ((middle - further) + (near - middle)) / 2;
    }
    Bottom_Err = near - 94;
}



/*
    ����������
*/
void sobel(unsigned char (*imageIn)[188], unsigned char (*imageOut)[188], unsigned char Threshold)
{
    /** ����˴�С */
    //short KERNEL_SIZE = 3;
    short xStart = 1;
    short xEnd = MT9V03X_W - 2;
    short yStart = 1;
    short yEnd = MT9V03X_H - 1;
    short i, j, k;
    short temp[4];
    for (i = yStart; i < yEnd; i++)
    {
        for (j = xStart; j < xEnd; j++)
        {
            /* ���㲻ͬ�����ݶȷ�ֵ  */
            temp[0] = -(short) imageIn[i - 1][j - 1] + (short) imageIn[i - 1][j + 1]     //{{-1, 0, 1},
            - (short) imageIn[i][j - 1] + (short) imageIn[i][j + 1]        // {-1, 0, 1},
            - (short) imageIn[i + 1][j - 1] + (short) imageIn[i + 1][j + 1];    // {-1, 0, 1}};

            temp[1] = -(short) imageIn[i - 1][j - 1] + (short) imageIn[i + 1][j - 1]     //{{-1, -1, -1},
            - (short) imageIn[i - 1][j] + (short) imageIn[i + 1][j]       // { 0,  0,  0},
            - (short) imageIn[i - 1][j + 1] + (short) imageIn[i + 1][j + 1];    // { 1,  1,  1}};

            temp[2] = -(short) imageIn[i - 1][j] + (short) imageIn[i][j - 1]       //  0, -1, -1
            - (short) imageIn[i][j + 1] + (short) imageIn[i + 1][j]       //  1,  0, -1
            - (short) imageIn[i - 1][j + 1] + (short) imageIn[i + 1][j - 1];    //  1,  1,  0

            temp[3] = -(short) imageIn[i - 1][j] + (short) imageIn[i][j + 1]       // -1, -1,  0
            - (short) imageIn[i][j - 1] + (short) imageIn[i + 1][j]       // -1,  0,  1
            - (short) imageIn[i - 1][j - 1] + (short) imageIn[i + 1][j + 1];    //  0,  1,  1

            temp[0] = abs(temp[0]);
            temp[1] = abs(temp[1]);
            temp[2] = abs(temp[2]);
            temp[3] = abs(temp[3]);

            /* �ҳ��ݶȷ�ֵ���ֵ  */
            for (k = 1; k < 4; k++)
            {
                if (temp[0] < temp[k])
                {
                    temp[0] = temp[k];
                }
            }

            if (temp[0] > Threshold)
            {
                imageOut[i][j] = 255;
            }
            else
            {
                imageOut[i][j] = 0;
            }
        }
    }
}

/*
    ���°��˹����Ĵ��
    �ٶ�Ӧ�ñ����д��Ҫ��һЩ��Ŀǰ�õ������
*/
short GetOSTU(unsigned char tmImage[MT9V03X_H][MT9V03X_W])
{
    signed short i, j;
    unsigned long Amount = 0;
    unsigned long PixelBack = 0;
    unsigned long PixelshortegralBack = 0;
    unsigned long Pixelshortegral = 0;
    signed long PixelshortegralFore = 0;
    signed long PixelFore = 0;
    float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // ��䷽��;
    signed short MinValue, MaxValue;
    signed short Threshold = 0;
    unsigned char HistoGram[256];              

    for (j = 0; j < 256; j++)
        HistoGram[j] = 0; //��ʼ���Ҷ�ֱ��ͼ

    for (j = 0; j < MT9V03X_H; j++)
    {
        for (i = 0; i < MT9V03X_W; i++)
        {
            HistoGram[tmImage[j][i]]++; //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
        }
    }

    for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++);        //��ȡ��С�Ҷȵ�ֵ
    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--); //��ȡ���Ҷȵ�ֵ

    if (MaxValue == MinValue)
        return MaxValue;         // ͼ����ֻ��һ����ɫ
    if (MinValue + 1 == MaxValue)
        return MinValue;        // ͼ����ֻ�ж�����ɫ

    for (j = MinValue; j <= MaxValue; j++)
        Amount += HistoGram[j];        //  ��������

    Pixelshortegral = 0;
    for (j = MinValue; j <= MaxValue; j++)
    {
        Pixelshortegral += HistoGram[j] * j;        //�Ҷ�ֵ����
    }
    SigmaB = -1;
    for (j = MinValue; j < MaxValue; j++)
    {
        PixelBack = PixelBack + HistoGram[j];     //ǰ�����ص���
        PixelFore = Amount - PixelBack;           //�������ص���
        OmegaBack = (float) PixelBack / Amount;   //ǰ�����ذٷֱ�
        OmegaFore = (float) PixelFore / Amount;   //�������ذٷֱ�
        PixelshortegralBack += HistoGram[j] * j;  //ǰ���Ҷ�ֵ
        PixelshortegralFore = Pixelshortegral - PixelshortegralBack;  //�����Ҷ�ֵ
        MicroBack = (float) PixelshortegralBack / PixelBack;   //ǰ���ҶȰٷֱ�
        MicroFore = (float) PixelshortegralFore / PixelFore;   //�����ҶȰٷֱ�
        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);   //������䷽��
        if (Sigma > SigmaB)                    //����������䷽��g //�ҳ������䷽���Լ���Ӧ����ֵ
        {
            SigmaB = Sigma;
            Threshold = j;
        }
    }
    return Threshold;                        //���������ֵ;
}

void regression(int type, int startline, int endline){
    int i = 0;
    int sumlines = endline - startline;
    int sumX = 0;
    int sumY = 0;
    float averageX = 0;
    float averageY = 0;
    float sumUp = 0;
    float sumDown = 0;
    float parameterA, parameterB;
    if (type == 0)      //�������
    {
        for (i = startline; i < endline; i++)
        {
            sumX += i;
            sumY += centerline[i];
        }
        if (sumlines != 0)
        {
            averageX = sumX / sumlines;     //x��ƽ��ֵ
            averageY = sumY / sumlines;     //y��ƽ��ֵ
        }
        else
        {
            averageX = 0;     //x��ƽ��ֵ
            averageY = 0;     //y��ƽ��ֵ
        }
        for (i = startline; i < endline; i++)
        {
            sumUp += (centerline[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        if (sumDown == 0) parameterB = 0;
        else parameterB = sumUp / sumDown;
        parameterA = averageY - parameterB * averageX;
    }
    else if (type == 1)//�������
    {
        for (i = startline; i < endline; i++)
        {
            sumX += i;
            sumY += leftline[i];
        }
        if (sumlines == 0) sumlines = 1;
        averageX = sumX / sumlines;     //x��ƽ��ֵ
        averageY = sumY / sumlines;     //y��ƽ��ֵ
        for (i = startline; i < endline; i++)
        {
            //SetText("lefetline"+i+" " +lefetline[i] + " averageY" +" "+ averageY);
            sumUp += (leftline[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        if (sumDown == 0) parameterB = 0;
        else parameterB = sumUp / sumDown;
        parameterA = averageY - parameterB * averageX;
    }
    else if (type == 2)//�������
    {
        for (i = startline; i < endline; i++)
        {
            sumX += i;
            sumY += rightline[i];
        }
        if (sumlines == 0) sumlines = 1;
        averageX = sumX / sumlines;     //x��ƽ��ֵ
        averageY = sumY / sumlines;     //y��ƽ��ֵ
        for (i = startline; i < endline; i++)
        {
            sumUp += (rightline[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        if (sumDown == 0) parameterB = 0;
        else parameterB = sumUp / sumDown;
        parameterA = averageY - parameterB * averageX;

    }
}


/*
    �������ƣ��ڵ����
    ������������ֵ����ͼ���ԭʼ��ά���飬��ʼ������������������������
    ����ʵ����Cal_BlackPoints(&image_deal[0], 119, 0);
*/
short Cal_BlackPoints(unsigned char (*binary_array)[188], unsigned char Start_Row, unsigned char End_Row){
    short blackpoint;
    blackpoint = 0;
    for(unsigned char i = Start_Row; i > End_Row; i--){
        for(unsigned char j = 0; j < 186; i++){
            if(binary_array[i][j] == 0){
                blackpoint++;
            }
        }
    }
    return blackpoint;
}


/************************************************************
���������ơ�Eight_neighborhood
����    �ܡ��������㷨��߽�
����    ����Ѱ���ӷ�ʽ
���� �� ֵ����
��ʵ    ����Eight_neighborhood(0);
��ע�����
    1*���㷨��Ҫ�㴫��Ķ�ֵ�����飬�Ǿ�����ֵ��֮������飬��ɫΪ1  ��ɫΪ0
    2*���㷨�����ͼ����Ҫ���Լ�����һ�����ֵ������ߴ���ͬ�Ķ�ά����
    3*����ĺ궨����뻻���Լ�ʵ�ʵ�ͼ������ߴ�Ͷ�ά������
    4*�ǵ������ú���
************************************************************/

//���ﻻ�����ֵ��֮���ͼ������
//#define User_Image    image
//�����ǰ��������������Ҫ�Լ�����һ����ԭͼ����ͬ�ߴ�Ķ�ά����
//#define Edge_arr  image
#define User_Image image_deal
#define Edge_arr image_deal2

void Eight_neighborhood(unsigned char flag){
    unsigned char i,j;
    //������������  ��ʼ�����ʼΪ6
    unsigned char core_x,core_y,start;
    //����
    char direction;
    unsigned length = 0;
    //��ձ߽�����
    for(i=0;i<USER_SIZE_H;i++)
        for(j=0;j<USER_SIZE_W;j++)
            Edge_arr[i][j]=0;
    if(flag==0)//��������������
    {
        start = 6;
        //����м�Ϊ��
        if(User_Image[USER_SIZE_H-1][USER_SIZE_W/2]==255)
        {
            for(i=USER_SIZE_W/2;i>=1;i--)
            {
                if(User_Image[USER_SIZE_H-1][i-1]==0||i==0)
                {//�����µ�һ���߽����Ϊ����
                    core_x = i;
                    core_y = USER_SIZE_H-1;
                    break;
                }
            }
        }//����м�Ϊ����ȥ������
        else if(User_Image[USER_SIZE_H-1][USER_SIZE_W/2]==0)
        {
            if(User_Image[USER_SIZE_H-1][5]==255)
                for(i=5;i>=1;i--)
                {
                    if(User_Image[USER_SIZE_H-1][i-1]==0||i==0)
                    {//�����µ�һ���߽����Ϊ����
                        core_x = i;
                        core_y = USER_SIZE_H-1;
                        break;
                    }
                }
            else if(User_Image[USER_SIZE_H-1][USER_SIZE_W-5]==255)
                for(i=USER_SIZE_W-5;i>=1;i--)
                {
                    if(User_Image[USER_SIZE_H-1][i-1]==0||i==0)
                    {//�����µ�һ���߽����Ϊ����
                        core_x = i;
                        core_y = USER_SIZE_H-1;
                        break;
                    }
                }
            else//������Ϊ��Чͼ��������
                return;
        }
    }
    else if(flag==1)
    {
        start = 6;
        for(i=0;i<USER_SIZE_W;i++)
        {
            if(User_Image[USER_SIZE_H-1][i]==255||i==USER_SIZE_W-1)
            {//�����µ�һ���߽����Ϊ����
                core_x = i;
                core_y = USER_SIZE_H-1;
                break;
            }
        }
    }
    else if(flag==2)
    {
        start = 2;
        //����м�Ϊ��
        if(User_Image[USER_SIZE_H-1][USER_SIZE_W/2]==255)
        {
            for(i=USER_SIZE_W/2;i<USER_SIZE_W;i++)
            {
                if(User_Image[USER_SIZE_H-1][i+1]==0||i==USER_SIZE_W-1)
                {
                    //�����µ�һ���߽����Ϊ����
                    core_x = i;
                    core_y = USER_SIZE_H-1;
                    break;
                }
            }
        }//����м�Ϊ����ȥ������
        else if(User_Image[USER_SIZE_H-1][USER_SIZE_W/2]==0)
        {
            if(User_Image[USER_SIZE_H-1][5]==255)
                for(i=5;i<USER_SIZE_W;i++)
                {
                    if(User_Image[USER_SIZE_H-1][i+1]==0||i==USER_SIZE_W-1)
                    {//�����µ�һ���߽����Ϊ����
                        core_x = i;
                        core_y = USER_SIZE_H-1;
                        break;
                    }
                }
            else if(User_Image[USER_SIZE_H-1][USER_SIZE_W-5]==255)
                for(i=USER_SIZE_W-5;i<USER_SIZE_W;i++)
                {
                    if(User_Image[USER_SIZE_H-1][i+1]==0||i==USER_SIZE_W-1)
                    {//�����µ�һ���߽����Ϊ����
                        core_x = i;
                        core_y = USER_SIZE_H-1;
                        break;
                    }
                }
            else//������Ϊ��Чͼ��������
                return;
        }
    }
    else if(flag==3)
    {
        start = 2;
        for(i=USER_SIZE_W-1;i>=0;i--)
        {
            if(User_Image[USER_SIZE_H-1][i]==255||i==0)
            {//�����µ�һ���߽����Ϊ����
                core_x = i;
                core_y = USER_SIZE_H-1;
                break;
            }
        }
    }
    //Ѱ�ұ�Ե
  while(1)
    {
        direction = start;
        Edge_arr[core_y][core_x]=255;
        if(flag == 0||flag == 1)
        {
            for(i=0;i<8;i++)
            {
                if(direction == 0) {if(core_y!=0)                                                                               {if(User_Image[core_y-1][core_x]==255)      {core_y--;                      start=6;    break;}}}
                if(direction == 1) {if(core_y!=0&&core_x!=USER_SIZE_W-1)                                {if(User_Image[core_y-1][core_x+1]==255)    {core_y--; core_x++;    start=6;    break;}}}
                if(direction == 2) {if(core_x!=USER_SIZE_W-1)                                                       {if(User_Image[core_y][core_x+1]==255)      {core_x++;                      start=0;    break;}}}
                if(direction == 3) {if(core_y!=USER_SIZE_H-1&&core_x!=USER_SIZE_W-1)        {if(User_Image[core_y+1][core_x+1]==255)    {core_y++; core_x++;    start=0;    break;}}}
                if(direction == 4) {if(core_y!=USER_SIZE_H-1)                                                       {if(User_Image[core_y+1][core_x]==255)      {core_y++;                      start=2;    break;}}}
                if(direction == 5) {if(core_y!=USER_SIZE_H-1&&core_x!=0)                                {if(User_Image[core_y+1][core_x-1]==255)    {core_y++; core_x--;    start=2;    break;}}}
                if(direction == 6) {if(core_x!=0)                                                                               {if(User_Image[core_y][core_x-1]==255)      {core_x--;                      start=4;    break;}}}
                if(direction == 7) {if(core_y!=0&&core_x!=0)                                                        {if(User_Image[core_y-1][core_x-1]==255)    {core_y--; core_x--;    start=4;    break;}}}
                direction++;    if(direction>7) direction=0;
            }
        }
        else if(flag == 2||flag == 3)
        {
            for(i=0;i<8;i++)
            {
                if(direction == 0) {if(core_y!=0)                                                                               {if(User_Image[core_y-1][core_x]==255)      {core_y--;                      start=2;    break;}}}
                if(direction == 1) {if(core_y!=0&&core_x!=USER_SIZE_W-1)                                {if(User_Image[core_y-1][core_x+1]==255)    {core_y--; core_x++;    start=4;    break;}}}
                if(direction == 2) {if(core_x!=USER_SIZE_W-1)                                                       {if(User_Image[core_y][core_x+1]==1)        {core_x++;                      start=4;    break;}}}
                if(direction == 3) {if(core_y!=USER_SIZE_H-1&&core_x!=USER_SIZE_W-1)        {if(User_Image[core_y+1][core_x+1]==255)    {core_y++; core_x++;    start=6;    break;}}}
                if(direction == 4) {if(core_y!=USER_SIZE_H-1)                                                       {if(User_Image[core_y+1][core_x]==255)      {core_y++;                      start=6;    break;}}}
                if(direction == 5) {if(core_y!=USER_SIZE_H-1&&core_x!=0)                                {if(User_Image[core_y+1][core_x-1]==255)    {core_y++; core_x--;    start=0;    break;}}}
                if(direction == 6) {if(core_x!=0)                                                                               {if(User_Image[core_y][core_x-1]==255)      {core_x--;                      start=0;    break;}}}
                if(direction == 7) {if(core_y!=0&&core_x!=0)                                                        {if(User_Image[core_y-1][core_x-1]==255)    {core_y--; core_x--;    start=2;    break;}}}
                direction--;    if(direction==-1)   direction=7;
            }
        }
        if(core_y==USER_SIZE_H-1&&length>5)
        {
            Edge_arr[core_y][core_x]=255;
            break;
        }
        length++;
    }
    if(flag==0&&length<80)
    {
        Eight_neighborhood(1);
    }
    if(flag==1&&length<80)
    {
        Eight_neighborhood(2);
    }
    if(flag==2&&length<80)
    {
        Eight_neighborhood(3);
    }
}


