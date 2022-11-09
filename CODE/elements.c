/*
 * elements.c
 *
 *  Created on: 2022.7.20
 *      Author: Cyfarwydd
 */

#include "elements.h"
#include "image.h"
#include "gyro.h"
#include "cycle.h"
#include "control.h"
#include "pid.h"


changepoint TripChangepointL, TripChangepointR, StraightChangepointL, StraightChangepointR;         // 定义三岔拐点结构体
changepoint Changepoint_Down_L, Changepoint_Down_R, Changepoint_Above_L, Changepoint_Above_R;       // 定义十字回环结构体                           
changepoint Parking_L, Parking_R;                                                                   // 定义车库拐点结构体
changepoint RoundAbout_LeftDown, RoundAbout_LeftAbove, RoundAbout_RightDown, RoundAbout_RightAbove; // 环岛拐点结构体

short P_Crossing_LCounter = 0;  
short P_Crossing_RCounter = 0;  
short StartLine_Counter = 0;    // 斑马线识别计时器
short Divergence_Counter = 0;   // 三岔识别计时器
short Upslope_Counter = 0;      // 上坡识别计时器
short Downslope_Counter = 0;    // 下坡识别计时器
short Rounding_LCounter = 0;    // 左环岛识别计时器
short Rounding_RCounter = 0;    // 右环岛识别计时器
short RoundAbout_LCounter = 0;  // 左十字回环识别计时器
short RoundAbout_RCounter = 0;  // 右十字回环识别计时器
short Charging_Counter = 0;     // 充电线圈识别计时器
short Outing_Counter = 0;       

unsigned char Present_RoundAbout_PointFlagL = 1;    /*********************/
unsigned char Present_RoundAbout_PointFlagR = 1;

/*-------三岔特殊点坐标数据---------*/
float Divergence_startrow;
float Divergence_startcol;
float Divergence_button_X;
float Divergence_button_Y;
unsigned char Divergence_TopPoint_X;
unsigned char Divergence_TopPoint_Y;
short sum_lost_line;
float Divergence_k;
float Divergence_b;
double Divergence_k1;
double Divergence_k2;
unsigned char Divergnce_TopLeftPoint_X, Divergnce_TopLeftPoint_Y;
unsigned char Divergence_TopRightPoint_X, Divergence_TopRightPoint_Y;

unsigned char StartLine_PointFlag = 0;      // 斑马线标志位
unsigned char RoundAbout_PointFlag_L = 0;   // 左环岛标志位
unsigned char RoundAbout_PointFlag_R = 0;   // 右环岛标志位
unsigned char Upslope_PointFlag = 0;        // 上坡标志位
unsigned char Downslope_PointFlag = 0;      // 下坡标志位
unsigned char P_Crossing_PointFlag_L = 0;   // 左十字回环标志位
unsigned char P_Crossing_PointFlag_R = 0;   // 右十字回环标志位
unsigned char Divergence_point_flag = 0;    // 三岔标志位
unsigned char Parking_PointFlag = 0;        // 停车标志位
unsigned char ChargingParking_PointFlag = 0;// 充电停车标志位
unsigned char CurrentCharging_PointFlag = 0;// 充电标志位
unsigned char WireNum = 0;                  // 线圈计数
unsigned char Outing_Flag = 1;              // 不知道什么玩意






/*
    以下为电赛~B~题的各种变量及标志位
*/

unsigned char LengthwaysGarage_PointFlag = 0;       // 纵向车库识别标志位，1为识别到第一个车库，2为识别到第二个车库，以此类推
unsigned char CrosswiseGarage_PointFlag = 0;        // 横向车库识别标志位，与上通
unsigned char left_distance = 0;                    // 从中线向左边界累加的距离
unsigned char right_distance = 0;                   // 从中线向右边界累加的距离
unsigned char SearchingBoundaries_PointFlag = 0;    // 寻找角点函数中的标志位，如果标志位为3，则判断为找到车库




/*
    绝对值计算函数
*/
int absolute(int var){
    if(var < 0)
        return -var;
    else
        return var;
}

/*
    最小值计算函数
*/
int minimum(int var1, int var2){
    if(var1 > var2)
        return var1;
    else
        return var2;
}

/*
    函数名称：寻找左拐点
    函数参数：一个changepoint类型的结构体，拐点寻找的起始行，结束行，二值化后的原始数组，不同拐点的模式参数
    为了方便寻找不同类型的拐点，预先设置了不同的模式（mode），一一对应不同类型的拐点。大体上，将拐点分为上下拐点两类，在下拐点又细分
    角拐点和平拐点，比如三岔入口底部左右两侧的角拐点以及十字路口出入口底部左右两侧的平拐点。
*/
void Findchangepoint_L(changepoint *prt, unsigned char Start, unsigned char End, unsigned char (*binary_array)[188], unsigned char mode){
    // 角拐点
    if(mode == TRIP){
        prt->changepoint_start = Start;     // 拐点寻找的起始行
        prt->changepoint_end = End;         // 拐点寻找的结束行
        prt->changepoint_row = 0;
        prt->changepoint_col = 0;
        prt->changepoint_flag = 0;

        for (unsigned char i = prt->changepoint_start; i > prt->changepoint_end; i--){
            if (leftline[i] != 0 && leftline[i - 1] != 0 && leftline[i + 1] != 0
            && leftline[i - 2] != 0
            && leftline[i] < 178 && leftline[i - 1] < 178 && leftline[i + 1] < 178
            && leftline[i - 2] < 178)
            {

                if ((leftline[i] - leftline[i - 1] >= 0) && (leftline[i] - leftline[i - 2] >= 0)
                && (leftline[i] - leftline[i - 3] >= 2)
                && (leftline[i] - leftline[i + 1] >= 0)
                && (leftline[i] - leftline[i + 2] >= 0)
                && (leftline[i] - leftline[i + 3] >= 0))
                {
                    prt->changepoint_row = i;
                    prt->changepoint_col = leftline[i];
                    prt->changepoint_flag = 1;
                    break;
                }
            }
        }
        if(prt->changepoint_flag == 0){
            prt->changepoint_row = 119;
            prt->changepoint_col = 0;
        }
    }
    // 平拐点，但是没用
    if(mode == STRAIGHT){

        prt->changepoint_start = Start;
        prt->changepoint_end = End;
        prt->changepoint_row = 0;
        prt->changepoint_col = 0;
        prt->changepoint_flag = 0;

        unsigned char Temp_Left_X, Temp_Left_Y, A;
        A = 0;
        Temp_Left_X = 95;
        for(unsigned char i = 93; i >= 5; i--){
            if(binary_array[Temp_Left_X][i] == 0 && binary_array[Temp_Left_X][i + 1] == 255){
                Temp_Left_Y = i;
                A = 1;
                break;
            }
        }

        if(A){
            Temp_Left_X = Temp_Left_X - 1;
            for(unsigned char i = Temp_Left_X; i > 0; i--){
                for(unsigned char j = Temp_Left_Y; j < 185; j++){
                    if(binary_array[i][j] == 255){
                        prt->changepoint_col = j - 1;
                        break;
                    }
                }
                if(binary_array[i - 1][prt->changepoint_col] == 255){
                    prt->changepoint_row = i ;
                    prt->changepoint_flag = 1;
                    break;
                }
            }
        }
    }
    // 下平拐点
    if(mode == CROSSING_DOWN){
        prt->changepoint_start = Start;
        prt->changepoint_end = End;
        prt->changepoint_row = 0;
        prt->changepoint_col = 0;
        prt->changepoint_flag = 0;

        for (unsigned char i = prt->changepoint_start; i > prt->changepoint_end; i--){
            if ((leftline[i] - leftline[i - 1] >= 0) && (leftline[i] - leftline[i - 2] >= 0)
                && (leftline[i] - leftline[i - 3] >= 8)
                && (leftline[i] - leftline[i + 1] >= 0)
                && (leftline[i] - leftline[i + 2] >= 0)
                && (leftline[i] - leftline[i + 3] >= 3))
            {
                prt->changepoint_row = i - 1;
                prt->changepoint_col = leftline[i];
                prt->changepoint_flag = 1;
                break;
            }
        }
    }
    // 上平拐点
    if(mode == CROSSING_ABOVE){

        prt->changepoint_start = Start;
        prt->changepoint_end = End;
        prt->changepoint_row = 0;
        prt->changepoint_col = 0;
        prt->changepoint_flag = 0;

        for(unsigned char i = prt->changepoint_start; i > prt->changepoint_end; i--){
            if(leftline[i] - leftline[i - 1] <= 0 && leftline[i] - leftline[i - 2] <= 0 && leftline[i] - leftline[i - 3] <= -2
            && leftline[i] - leftline[i + 1] >= 0 && leftline[i] - leftline[i + 2] >= 0 && leftline[i] - leftline[i + 3] >= 10){
                prt->changepoint_row = i + 1;
                prt->changepoint_col = leftline[i];
                prt->changepoint_flag = 1;
                break;
            }
        }
    }
}


/*
    函数名称：寻找右拐点
    函数参数：一个changepoint类型的结构体，拐点寻找的起始行，结束行，二值化后的原始数组，不同拐点的模式参数
    为了方便寻找不同类型的拐点，预先设置了不同的模式（mode），一一对应不同类型的拐点。大体上，将拐点分为上下拐点两类，在下拐点又细分
    角拐点和平拐点，比如三岔入口底部左右两侧的角拐点以及十字路口出入口底部左右两侧的平拐点。
*/
void Findchangepoint_R(changepoint *prt, unsigned char Start, unsigned char End, unsigned char (*binary_array)[188], unsigned char mode){
    // 角拐点
    if(mode == TRIP){
        prt->changepoint_start = Start;
        prt->changepoint_end = End;
        prt->changepoint_row = 0;
        prt->changepoint_col = 0;
        prt->changepoint_flag = 0;

        for (unsigned char i = prt->changepoint_start; i >= prt->changepoint_end; i--){
            if((rightline[i] != (cutCOL - 1) && rightline[i - 1] != (cutCOL - 1)
            && rightline[i - 2] != (cutCOL - 1)
            && rightline[i - 3] != (cutCOL - 1))
            && (rightline[i] > 10 && rightline[i - 1] > 10
            && rightline[i + 1] > 10 && rightline[i - 2] > 10))
            {
                if ((rightline[i] - rightline[i + 1] <= 0)
                && (rightline[i] - rightline[i + 2]) <= 0
                && (rightline[i] - rightline[i + 3]) <= 0
                && (rightline[i] - rightline[i - 1] <= 0)
                && (rightline[i] - rightline[i - 2] <= 0)
                && (rightline[i] - rightline[i - 3] <= -2))
                {
                    prt->changepoint_row = i;
                    prt->changepoint_col = rightline[i];
                    prt->changepoint_flag = 1;
                    break;
                }
            }
        }
        if(prt->changepoint_flag == 0){
            prt->changepoint_row = 119;
            prt->changepoint_col = 187;
        }
    }

    // 平拐点，但是没用
    if(mode == STRAIGHT){
        prt->changepoint_start = Start;
        prt->changepoint_end = End;
        prt->changepoint_row = 0;
        prt->changepoint_col = 0;
        prt->changepoint_flag = 0;

        unsigned char Temp_Right_X, Temp_Right_Y, B;
        Temp_Right_X = 95;
        for(unsigned char i = 93; i < cutCOL; i++){
            if(binary_array[Temp_Right_X][i] == 0 && binary_array[Temp_Right_X][i - 1] == 255){
                Temp_Right_Y = i;
                B = 1;
                break;
            }
        }

        if(B){
            Temp_Right_X = Temp_Right_X - 1;
            for(unsigned char i = Temp_Right_X; i > 0; i--){
                for(unsigned char j = Temp_Right_Y; j > 5; j--){
                    if(binary_array[i][j] == 255){
                        prt->changepoint_col = j + 1;
                        break;
                    }
                }
                if(binary_array[i - 1][prt->changepoint_col] == 255){
                    prt->changepoint_row = i;
                    prt->changepoint_flag = 1;
                    break;
                }
            }
        }
    }

    // 下平拐点
    if(mode == CROSSING_DOWN){
        prt->changepoint_start = Start;
        prt->changepoint_end = End;
        prt->changepoint_row = 0;
        prt->changepoint_col = 0;
        prt->changepoint_flag = 0;

        for (unsigned char i = prt->changepoint_start; i >= prt->changepoint_end; i--){
            if ((rightline[i] - rightline[i + 1] <= 0)
                && (rightline[i] - rightline[i + 2]) <= 0
                && (rightline[i] - rightline[i + 3]) <= -3
                && (rightline[i] - rightline[i - 1] <= 0)
                && (rightline[i] - rightline[i - 2] <= 0)
                && (rightline[i] - rightline[i - 3] <= -3))
            {
                prt->changepoint_row = i - 1;
                prt->changepoint_col = rightline[i];
                prt->changepoint_flag = 1;
                break;
            }
        }
    }

    // 上平拐点
    if(mode == CROSSING_ABOVE){

        prt->changepoint_start = Start;
        prt->changepoint_end = End;
        prt->changepoint_row = 0;
        prt->changepoint_col = 0;
        prt->changepoint_flag = 0;

        for(unsigned char i = prt->changepoint_start; i >= prt->changepoint_end; i--){
            if(rightline[i] - rightline[i - 1] >= 0 && rightline[i] - rightline[i - 2] >= 0 && rightline[i] - rightline[i - 3] >= 0
            && rightline[i] - rightline[i + 1] <= 0 && rightline[i] - rightline[i + 2] <= 0 && rightline[i] - rightline[i + 3] <= -10){
                prt->changepoint_row = i + 1;
                prt->changepoint_col = rightline[i];
                prt->changepoint_flag = 1;
                break;
            }
        }
    }
}



void Judging_Divergence(unsigned char (*binary_array)[188]){
    if(!P_Crossing_PointFlag_L && !P_Crossing_PointFlag_R){
        // Divergence_point_flag = 0;     
        unsigned char distance = 0;
        Divergence_button_X = 0;
        Divergence_button_Y = 0;
        unsigned char leftline_lost_sum = Leftline_Lost_Sum(BottomRow, BottomRow - 60);
        unsigned char rightline_lost_sum = Rightline_Lost_Sum(BottomRow, BottomRow - 60);
        Findchangepoint_L(&TripChangepointL, 119, 70, &image_deal[0], TRIP);
        Findchangepoint_R(&TripChangepointR, 119, 70, &image_deal[0], TRIP);
        if((TripChangepointL.changepoint_flag && TripChangepointR.changepoint_flag && absolute(TripChangepointL.changepoint_row - TripChangepointR.changepoint_row) <= 10) || (TripChangepointL.changepoint_flag && TripChangepointR.changepoint_row == 119)){
            Divergence_startrow = (TripChangepointL.changepoint_row + TripChangepointR.changepoint_row) / 2;
            Divergence_startcol = (TripChangepointL.changepoint_col + TripChangepointR.changepoint_col) / 2;
            for(unsigned char i = (int)Divergence_startrow; i > 1; i--){
                if((image_deal[i][(int)Divergence_startcol] == 0) && (image_deal[i + 1][(int)Divergence_startcol] == 255) && image_deal[i + 2][(int)Divergence_startcol] == 255){
                    Divergence_button_X = i;
                    Divergence_button_Y = Divergence_startcol;
                    distance = Divergence_startrow - Divergence_button_X;
                    break;
                }
            }
        }
        if(distance > 0 && distance <= 90 && Divergence_button_X > 40){
            Divergence_k = (TripChangepointR.changepoint_col - Divergence_button_Y) / (TripChangepointR.changepoint_row - Divergence_button_X);
            Divergence_point_flag = 1;
            for(unsigned char i = (int)TripChangepointR.changepoint_row; i > Divergence_button_X; i--){
                rightline[i] = (int)(Divergence_k * (i - Divergence_button_X) + Divergence_button_Y);
            }
        }
    }
}


unsigned char Leftline_Lost_Sum(unsigned char Start_Row, unsigned char End_row){
    unsigned char leftline_lost_sum = 0;
    for(int i = Start_Row; i > End_row; i--){
        if(leftline[i] < 5){
            leftline_lost_sum++;
        }
    }
    return leftline_lost_sum;
}


unsigned char Rightline_Lost_Sum(unsigned char Start_Row, unsigned char End_row){
    unsigned char rightline_lost_sum = 0;
    for(int i = Start_Row; i > End_row; i--){
        if(rightline[i] > 182){
            rightline_lost_sum++;
        }
    }
    return rightline_lost_sum;
}



void Judging_P_Crossing_ver2(unsigned char (*binary_array)[188]){
    unsigned char leftline_lost_sum = Leftline_Lost_Sum(119, 1);
    unsigned char rightline_lost_sum = Rightline_Lost_Sum(119, 1);
    Findchangepoint_L(&Changepoint_Down_L, 119, 75, &image_deal[0], CROSSING_DOWN);
    Findchangepoint_R(&Changepoint_Down_R, 119, 75, &image_deal[0], CROSSING_DOWN);
    Findchangepoint_L(&Changepoint_Above_L, 65, 35, &image_deal[0], CROSSING_ABOVE);
    Findchangepoint_R(&Changepoint_Above_R, 65, 35, &image_deal[0], CROSSING_ABOVE); // 65 20
    
    if(Changepoint_Down_L.changepoint_flag && Changepoint_Above_L.changepoint_flag && /*!Changepoint_Down_R.changepoint_flag && !Changepoint_Above_R.changepoint_flag
    && */rightline_lost_sum <= 20 && Changepoint_Down_L.changepoint_col < 90 && Changepoint_Above_L.changepoint_col < 90 && P_Crossing_PointFlag_L <= 1)
    {
        P_Crossing_PointFlag_L = 1;
    }
    
    if(!Changepoint_Down_L.changepoint_flag && Changepoint_Above_L.changepoint_flag && /*!Changepoint_Down_R.changepoint_flag && !Changepoint_Above_R.changepoint_flag
    && */rightline_lost_sum <= 10 && Changepoint_Above_L.changepoint_col < 93 && Changepoint_Above_L.changepoint_row > 40 && (P_Crossing_PointFlag_L == 1 || P_Crossing_PointFlag_L == 2))
    {
        P_Crossing_PointFlag_L = 2;
    }
    
    if(Changepoint_Down_R.changepoint_flag && Changepoint_Down_R.changepoint_row >= 75 &&  Changepoint_Down_R.changepoint_col > 110 && P_Crossing_PointFlag_L >= 1 && P_Crossing_PointFlag_L <= 3)
    {
        P_Crossing_PointFlag_L = 3;
        // P_Crossing_PointFlag_R = 0;
        unsigned char TempPoint_row, TempPoint_col;
        float TempK;
        TempPoint_col = 100;
        for(unsigned char i = BottomRow; i > 2; i--){
            if(binary_array[i + 1][TempPoint_col] == 255 && binary_array[i][TempPoint_col] == 0 && binary_array[i - 1][TempPoint_col] == 0){
                TempPoint_row = i;
                break;
            }
        }
        TempK = (float)(TempPoint_col - 0) / (float)(TempPoint_row - BottomRow);
        for(unsigned char i = BottomRow; i > TempPoint_row; i--){
            leftline[i] = (int)(TempK * (i - TempPoint_row) + TempPoint_col);
        }
    }

    
    if(Changepoint_Down_L.changepoint_flag && Changepoint_Down_R.changepoint_flag && Changepoint_Down_L.changepoint_row >= 100 && Changepoint_Down_R.changepoint_row >=100
    && P_Crossing_PointFlag_L >= 1 && P_Crossing_PointFlag_L <= 4){
        P_Crossing_PointFlag_L = 4;
        unsigned char TempPoint_row, TempPoint_col;
        float TempK;
        TempPoint_col = (Changepoint_Down_L.changepoint_col + Changepoint_Down_R.changepoint_col) / 2 + 10;
        TempPoint_row = (Changepoint_Down_L.changepoint_row + Changepoint_Down_R.changepoint_row) / 2;
        for(unsigned char i = TempPoint_row; i > 1; i--){
            if(binary_array[i + 1][TempPoint_col] == 255 && binary_array[i][TempPoint_col] == 0 && binary_array[i - 1][TempPoint_col] == 0){
                TempPoint_row = i;
                break;
            }
        }
        TempK = (float)(TempPoint_col - StartCoL) / (float)(TempPoint_row - BottomRow);
        for(unsigned char i = Changepoint_Down_L.changepoint_row; i > TempPoint_row; i--){
            leftline[i] = (int)(TempK * (i - TempPoint_row) + TempPoint_col);
        }

    }

    /*
    
    if(P_Crossing_PointFlag_L >= 3){  // || P_Crossing_PointFlag_L ==2 || P_Crossing_PointFlag_L == 1
        Findchangepoint_L(&Changepoint_Down_L, 119, 100, &image_deal[0], CROSSING_DOWN);
        Findchangepoint_L(&Changepoint_Down_R, 119, 100, &image_deal[0], CROSSING_DOWN);
        unsigned char TempRow;
        for(unsigned char i = 119; i > 99; i--){
            if(binary_array[i + 1][93] == 255 && binary_array[i][93] == 0 && binary_array[i - 1][93] == 0 && binary_array[i - 2][93] == 0){
                break;
            }
            else{
                TempRow++;
            }
        }
        if(P_Crossing_PointFlag_L >= 3 && TempRow >= 15 && !Changepoint_Down_L.changepoint_flag && !Changepoint_Down_R.changepoint_flag){
            P_Crossing_PointFlag_L = 5;
            unsigned char TempPoint_row, TempPoint_col;
            float TempK;
            TempPoint_col = 100;
            for(unsigned char i = BottomRow; i > 2; i--){
                if(binary_array[i + 1][TempPoint_col] == 255 && binary_array[i][TempPoint_col] == 0 && binary_array[i - 1][TempPoint_col] == 0){
                    TempPoint_row = i;
                    break;
                }
            }
            TempK = (float)(TempPoint_col - 0) / (float)(TempPoint_row - BottomRow);
            for(unsigned char i = BottomRow; i > TempPoint_row; i--){
                leftline[i] = (int)(TempK * (i - TempPoint_row) + TempPoint_col);
            }
        }
    }
    */


    
    if(Changepoint_Down_R.changepoint_flag && Changepoint_Above_R.changepoint_flag && /*!Changepoint_Down_L.changepoint_flag && !Changepoint_Above_L.changepoint_flag
    && */leftline_lost_sum <= 10 && Changepoint_Down_R.changepoint_col > 93 && Changepoint_Above_R.changepoint_col > 93 && P_Crossing_PointFlag_R <= 1)
    {
        P_Crossing_PointFlag_R = 1;
    }
    
    if(!Changepoint_Down_R.changepoint_flag && Changepoint_Above_R.changepoint_flag && /*!Changepoint_Down_L.changepoint_flag && !Changepoint_Above_L.changepoint_flag
    && */leftline_lost_sum <= 10 && Changepoint_Above_R.changepoint_col > 93 && Changepoint_Above_R.changepoint_row > 40 && P_Crossing_PointFlag_R >= 1 && P_Crossing_PointFlag_R <=2)
    {
        P_Crossing_PointFlag_R = 2;
    }
    
    if(Changepoint_Down_L.changepoint_flag && Changepoint_Down_L.changepoint_row >= 74 && Changepoint_Down_L.changepoint_row <= 107 && Changepoint_Down_L.changepoint_col <= 47
    && P_Crossing_PointFlag_R >= 1 && P_Crossing_PointFlag_R <= 3 && Changepoint_Down_R.changepoint_flag)
    {
        P_Crossing_PointFlag_R = 3;
        // P_Crossing_PointFlag_L = 0;
        unsigned char TempPoint_row, TempPoint_col;
        float TempK;
        TempPoint_col = cutCOL - 100;
        for(unsigned char i = BottomRow; i > 2; i--){
            if(binary_array[i + 1][TempPoint_col] == 255 && binary_array[i][TempPoint_col] == 0 && binary_array[i - 1][TempPoint_col] == 0){
                TempPoint_row = i;
                break;
            }
        }
        TempK = (float)(TempPoint_col - cutCOL) / (float)(TempPoint_row - BottomRow);
        for(unsigned char i = BottomRow; i > TempPoint_row; i--){
            rightline[i] = (int)(TempK * (i - TempPoint_row) + TempPoint_col);
        }
    }
    
    if(Changepoint_Down_L.changepoint_flag && Changepoint_Down_R.changepoint_flag && Changepoint_Down_L.changepoint_row >= 100 && Changepoint_Down_R.changepoint_row >=100
    && P_Crossing_PointFlag_R >= 1 && P_Crossing_PointFlag_R <= 4){
        P_Crossing_PointFlag_R = 4;
        unsigned char TempPoint_row, TempPoint_col;
        float TempK;
        TempPoint_col = (Changepoint_Down_L.changepoint_col + Changepoint_Down_R.changepoint_col) / 2 - 10;
        TempPoint_row = (Changepoint_Down_L.changepoint_row + Changepoint_Down_R.changepoint_row) / 2;
        for(unsigned char i = TempPoint_row; i > 1; i--){
            if(binary_array[i + 1][TempPoint_col] == 255 && binary_array[i][TempPoint_col] == 0 && binary_array[i - 1][TempPoint_col] == 0){
                TempPoint_row = i;
                break;
            }
        }
        TempK = (float)(TempPoint_col - Changepoint_Down_R.changepoint_col) / (float)(TempPoint_row - Changepoint_Down_R.changepoint_row);
        for(unsigned char i = Changepoint_Down_R.changepoint_row; i > TempPoint_row; i--){
            rightline[i] = (int)(TempK * (i - TempPoint_row) + TempPoint_col);
        }

    }
    /*
    
    if(P_Crossing_PointFlag_R >= 3){    //  || P_Crossing_PointFlag_R ==2 || P_Crossing_PointFlag_R == 1
        Findchangepoint_L(&Changepoint_Down_L, 119, 100, &image_deal[0], CROSSING_DOWN);
        Findchangepoint_L(&Changepoint_Down_R, 119, 100, &image_deal[0], CROSSING_DOWN);
        unsigned char TempRow;
        for(unsigned char i = 119; i > 99; i--){
            if(binary_array[i + 1][93] == 255 && binary_array[i][93] == 0 && binary_array[i - 1][93] == 0 && binary_array[i - 2][93] == 0){
                break;
            }
            else{
                TempRow++;
            }
        }
        if(P_Crossing_PointFlag_R >= 1 && P_Crossing_PointFlag_R <= 3 && TempRow >= 15 && !Changepoint_Down_L.changepoint_flag && !Changepoint_Down_R.changepoint_flag){
            P_Crossing_PointFlag_R = 5;
            unsigned char TempPoint_row, TempPoint_col;
            float TempK;
            TempPoint_col = cutCOL - 90;
            for(unsigned char i = BottomRow; i > 2; i--){
                if(binary_array[i + 1][TempPoint_col] == 255 && binary_array[i][TempPoint_col] == 0 && binary_array[i - 1][TempPoint_col] == 0){
                    TempPoint_row = i;
                    break;
                }
            }
            TempK = (float)(TempPoint_col - 0) / (float)(TempPoint_row - BottomRow);
            for(unsigned char i = BottomRow; i > TempPoint_row; i--){
                rightline[i] = (int)(TempK * (i - TempPoint_row) + TempPoint_col);
            }
        }
    }
    */
}


void Judging_StartLine(unsigned char (*binary_array)[188]){
    Findchangepoint_L(&Parking_L, 70, 40, &image_deal[0], CROSSING_ABOVE);
    Findchangepoint_R(&Parking_R, 70, 40, &image_deal[0], CROSSING_ABOVE);
    unsigned char times = 0;
    for (unsigned char i = BottomRow - 18; i >= BottomRow - 23; i--)
    {
        unsigned char black_blocks = 0;
        unsigned char cursor = 0;
        for(unsigned char j = 0; j <= 186; j++)
        {
            if(binary_array[i][j] == 0)
            {
                if(cursor >= 20)
                {

                }
                else
                {
                    cursor++;
                }
            }
            else
            {
                if(cursor >= 4 && cursor <= 8)
                {
                    black_blocks++;
                    cursor = 0;
                }
                else
                {
                    cursor = 0;
                }
            }
        }
        if(black_blocks >= 6 && black_blocks <= 12) times++;
    }
    if(times >= 3 /*&& times <= 5*/)
    {
        StartLine_PointFlag = 1;
    }
    else
    {
        StartLine_PointFlag = 0;
    }
    
    if(StartLine_PointFlag && Parking_L.changepoint_flag){
        Parking_PointFlag = 1;
        for(unsigned char i = BottomRow; i > 60; i--){
            centerline[i] = 93;
        }
    }
    
    if(StartLine_PointFlag && Parking_R.changepoint_flag && leftline[119] != StartCoL && StartLine_Counter >= 1000){
        Parking_PointFlag = 2;
        float TempK;
        TempK = (float)(Parking_R.changepoint_col - 0) / (float)(Parking_R.changepoint_row - 119);
        for(unsigned char i = BottomRow; i > Parking_R.changepoint_row; i--){
            leftline[i] = (int)(TempK * (i - Parking_R.changepoint_row) + Parking_R.changepoint_col);
            rightline[i] = 187;
        }
    }

}


void Judging_RoundAbout(unsigned char (*binary_array)[188]){
    // Judging right roundabout point flag 1st
    for(unsigned char i = BottomRow - 10; i > 60; i--){
        if(leftline[BottomRow] != StartCoL && rightline[BottomRow] != EndCoL && absolute(Right_RoadWidth[i + 10] - Right_RoadWidth[i] > 7)
        && absolute(Right_RoadWidth[i - 10] - Right_RoadWidth[i]) > 35 && RoundAbout_PointFlag_R <= 1 && Rounding_RCounter < 300)
        {
            RoundAbout_PointFlag_R = 1;
            break;
        }
    }
    // Judging right roundabout point flag 2nd
    if(RoundAbout_PointFlag_R > 0 && RoundAbout_PointFlag_R <= 2 && Right_RoadWidth[BottomRow - 10] - Left_RoadWidth[BottomRow - 10] > 5 && Right_RoadWidth[BottomRow - 111] - Left_RoadWidth[BottomRow - 11] > 6
    && Right_RoadWidth[BottomRow - 12] - Left_RoadWidth[BottomRow - 12] > 8 && Right_RoadWidth[BottomRow - 13] - Left_RoadWidth[BottomRow - 13] > 8
    && Right_RoadWidth[BottomRow - 14] - Left_RoadWidth[BottomRow - 14] > 8 && Right_RoadWidth[BottomRow - 15] - Left_RoadWidth[BottomRow-  15] > 8 && RoundAbout_PointFlag_R <= 2 && Rounding_RCounter < 300)
    {
        RoundAbout_PointFlag_R = 2;
    }
    // Judging right roundabout point flag 3rd
    for(unsigned char i = BottomRow - 10; i > 60; i--){
        if(leftline[BottomRow] != StartCoL && rightline != EndCoL && Right_RoadWidth[i + 10] - Right_RoadWidth[i + 5] > 3 && Right_RoadWidth[i + 5] - Right_RoadWidth[i] > 2
        && Right_RoadWidth[i] - Right_RoadWidth[i + 10] < -5 && Right_RoadWidth[i] - Right_RoadWidth[i - 5] < -2 && Right_RoadWidth[i - 5] - Right_RoadWidth[i - 10] < -3
        && Right_RoadWidth[i - 10] - Right_RoadWidth[i] > 5 && RoundAbout_PointFlag_R >= 2 && RoundAbout_PointFlag_R <= 3 && Rounding_RCounter < 300)
        {
            RoundAbout_PointFlag_R = 3;
            break;
        }
    }
    // Judging right roundabout point flag 4th, Entering the roundabout
    if(RoundAbout_PointFlag_R >= 3 && RoundAbout_PointFlag_R <= 4 && rightline[BottomRow] > 180 && rightline[BottomRow - 1] > 180 && rightline[BottomRow - 2] > 180
    && rightline[BottomRow - 3] > 180 && rightline[BottomRow - 4] > 180 && rightline[BottomRow - 5] > 180 && Rounding_RCounter < 300)
    {
        Findchangepoint_R(&RoundAbout_RightAbove, 119, 40, &image_deal[0], CROSSING_ABOVE);
        if(RoundAbout_RightAbove.changepoint_flag && RoundAbout_RightAbove.changepoint_col > 100){
            RoundAbout_PointFlag_R = 4;
            unsigned char TempPoint_Row, TempPoint_Col;
            TempPoint_Row = BottomRow;
            TempPoint_Col = leftline[BottomRow];
            float TempK;
            TempK = (float)(TempPoint_Col - RoundAbout_RightAbove.changepoint_col) / (float)(TempPoint_Row - RoundAbout_RightAbove.changepoint_row);
            for(unsigned char i = TempPoint_Row; i > RoundAbout_RightAbove.changepoint_row; i--){
                leftline[i] = (int)(TempK * (i - TempPoint_Row) + TempPoint_Col);
            }
        }
    }
    // Judging right roundabout point flag 5th, running in the roundabout
    if(Rounding_RCounter >= 200 && RoundAbout_PointFlag_R >= 4){
        RoundAbout_PointFlag_R = 5;
    }
    // Judging right roundabout point flag 6th, prepare to leave the roundabout
    if(RoundAbout_PointFlag_R >= 5 && RoundAbout_PointFlag_R <= 6 && Rounding_RCounter >= 300){
        Findchangepoint_R(&RoundAbout_LeftDown, 119, 40, &image_deal[0], TRIP);
        if(RoundAbout_LeftDown.changepoint_flag && RoundAbout_LeftDown.changepoint_col < 93 && RoundAbout_LeftDown.changepoint_col >= 20){
            RoundAbout_PointFlag_R = 6;
        }
        if(RoundAbout_PointFlag_R == 6){
            unsigned char TempPoint_Row, TempPoint_Col;
            float TempK;
            TempPoint_Col = 93;
            for(unsigned char i = BottomRow; i > 20; i--){
                if(binary_array[i + 1][TempPoint_Col] == 255 && binary_array[i][TempPoint_Col] == 0 && binary_array[i - 1][TempPoint_Col] == 0){
                    TempPoint_Row = i;
                    break;
                }
            }
            TempK = (float)(TempPoint_Col - RoundAbout_LeftDown.changepoint_col) / (float)(TempPoint_Row - RoundAbout_LeftDown.changepoint_row);
            for(unsigned char i = RoundAbout_LeftDown.changepoint_row; i > TempPoint_Row; i--){
                leftline[i] = (int)(TempK * (i - TempPoint_Row) + TempPoint_Col);
            }
        }
    }


    // Judging the left roundabout point flag 1st
    for(unsigned char i = BottomRow - 10; i > 60; i--){
        if(leftline[BottomRow] != StartCoL && rightline[BottomRow] != EndCoL && absolute(Right_RoadWidth[i + 10] - Left_RoadWidth[i + 10] < 10)
        && absolute(Right_RoadWidth[i - 10] - Left_RoadWidth[i - 10]) > 35 && RoundAbout_PointFlag_L <= 1)
        {
            RoundAbout_PointFlag_L = 1;
            break;
        }
    }
    // Judging the left roundabout point flag 2nd
    if(RoundAbout_PointFlag_L > 0 && RoundAbout_PointFlag_L <= 2 && leftline[BottomRow] > 180 && leftline[BottomRow - 1] > 180 && leftline[BottomRow - 2] > 180
    && leftline[BottomRow - 3] > 180 && leftline[BottomRow - 4] > 180 && leftline[BottomRow - 5] > 180 && RoundAbout_PointFlag_L <= 2)
    {
        RoundAbout_PointFlag_L = 2;
    }
    // Judging the left roundabout point flag 3rd
    for(unsigned char i = BottomRow - 10; i > 60; i--){
        if(rightline[BottomRow] != StartCoL && Left_RoadWidth[i + 10] - Left_RoadWidth[i] < -10 && Left_RoadWidth[i - 10] - Left_RoadWidth[i] < -10
        && RoundAbout_PointFlag_L >= 2 && RoundAbout_PointFlag_L <= 3)
        {
            RoundAbout_PointFlag_L = 3;
            break;
        }
    }
    // Judging the left roundabout point flag 4th, Entering the roundabout
    if(RoundAbout_PointFlag_L >= 3 && RoundAbout_PointFlag_L <= 4 && leftline[BottomRow] > 180 && leftline[BottomRow - 1] > 180 && leftline[BottomRow - 2] > 180
    && leftline[BottomRow - 3] > 180 && leftline[BottomRow - 4] > 180 && leftline[BottomRow - 5] > 180)
    {
        Findchangepoint_L(&RoundAbout_LeftAbove, 119, 40, &image_deal[0], CROSSING_ABOVE);
        if(RoundAbout_LeftAbove.changepoint_flag && RoundAbout_LeftAbove.changepoint_col > 100){
            RoundAbout_PointFlag_L = 4;
            unsigned char TempPoint_Row, TempPoint_Col;
            TempPoint_Row = BottomRow;
            TempPoint_Col = rightline[BottomRow];
            float TempK;
            TempK = (float)(TempPoint_Col - RoundAbout_LeftAbove.changepoint_col) / (float)(TempPoint_Row - RoundAbout_LeftAbove.changepoint_row);
            for(unsigned char i = TempPoint_Row; i > RoundAbout_LeftAbove.changepoint_row; i--){
                rightline[i] = (int)(TempK * (i - TempPoint_Row) + TempPoint_Col);
            }
        }
    }
    // Judging the left roundabout point flag 5th, running in the roundabout
    if(Rounding_LCounter >= 200 && RoundAbout_PointFlag_L >= 4){
        RoundAbout_PointFlag_L = 5;
    }
    // Judging the left roundabout point flag 6th, prepare to leave the roundabout
    if(RoundAbout_PointFlag_L >= 5 && RoundAbout_PointFlag_L <= 6 && Rounding_RCounter <= 300){
        Findchangepoint_R(&RoundAbout_RightDown, 119, 40, &image_deal[0], TRIP);
        if(RoundAbout_RightDown.changepoint_flag && RoundAbout_RightDown.changepoint_col < 93 && RoundAbout_RightDown.changepoint_col >= 20){
            RoundAbout_PointFlag_L = 6;
        }
        if(RoundAbout_PointFlag_L == 6){
            unsigned char TempPoint_Row, TempPoint_Col;
            float TempK;
            TempPoint_Col = 93;
            for(unsigned char i = BottomRow; i > 20; i--){
                if(binary_array[i + 1][TempPoint_Col] == 255 && binary_array[i][TempPoint_Col] == 0 && binary_array[i - 1][TempPoint_Col] == 0){
                    TempPoint_Row = i;
                    break;
                }
            }
            TempK = (float)(TempPoint_Col - RoundAbout_RightDown.changepoint_col) / (float)(TempPoint_Row - RoundAbout_RightDown.changepoint_row);
            for(unsigned char i = RoundAbout_RightDown.changepoint_row; i > TempPoint_Row; i--){
                rightline[i] = (int)(TempK * (i - TempPoint_Row) + TempPoint_Col);
            }
        }
    }
}


void Judging_Slope(void){
    if(Real_Gyro_Y <= -35){
        Upslope_PointFlag = 1;
    }
    if(Real_Gyro_Y >= 35){
        Downslope_PointFlag = 1;
    }
}

void RoundingCounter_Supporting(void){
    if(Present_RoundAbout_PointFlagR == RoundAbout_PointFlag_R){
        Rounding_RCounter++;
    }
    else{
        Rounding_RCounter = 0;
        if(Present_RoundAbout_PointFlagR + 1 == RoundAbout_PointFlag_R){
            Present_RoundAbout_PointFlagR = RoundAbout_PointFlag_R;
        }
    }

}

// void Go_forwardL(void){
//     Findchangepoint_L(&Changepoint_Down_L, 119, 75, &image_deal[0], CROSSING_DOWN);
//     Findchangepoint_R(&Changepoint_Down_R, 119, 75, &image_deal[0], CROSSING_DOWN);
//     if(Changepoint_Down_L.changepoint_flag && Changepoint_Down_R.cahnge)
// }

// void Go_forwardR(void){

// }


void Pokemon_Go(void){
    short Slow_Down = 1500;
    // if(WireNum == 3){
    //     while(1){
    //         motor_ctrl(1900, 1900);
    //         systick_delay_ms(STM0, 100);
    //         break;
    //     }

    // }
    Judging_Divergence(&image_deal[0]);
    Judging_P_Crossing_ver2(&image_deal[0]);
    // Judging_StartLine(&image_deal[0]);
    // Judging_Slope();
    // Judging_RoundAbout(&image_deal[0]);
    if(Divergence_point_flag){
        Deal_Road_Characteristics(&image_deal[0]);
        DUTY_MAX = 1600;
        Turn_cycle_ver2(Slow_Down);
    }
    // else if(P_Crossing_PointFlag_L >= 3 || P_Crossing_PointFlag_R >= 3){
    //     Deal_Road_Characteristics(&image_deal[0]);
    //     DUTY_MAX = 2000;
    //     Turn_cycle_ver2(Slow_Down);
    // }
    else if(!P_Crossing_PointFlag_L || !P_Crossing_PointFlag_R || !RoundAbout_PointFlag_R){
        Deal_Road_Characteristics(&image_deal[0]);
        DUTY_MAX = 1600;
        Turn_cycle_ver2(Slow_Down);
    }
    else if(Upslope_PointFlag){
        // DUTY_MAX = 5000;
        // motor_ctrl(DUTY_MAX, DUTY_MAX);
    }
    else if(Downslope_PointFlag){
        // motor_ctrl(0, 0);
    }
    else{
        DUTY_MAX = 1900;
        Turn_cycle_ver2(DUTY_MAX);
    }
}

/*
    以下是电赛B题识别泊车代码，电赛采用积分制，先按一个任务一个任务来踩分完成
    对于使用侧视摄像头，最重要的设定标志位，识别到了标志位，再做倒车的判断
    现在对于倒车有几个不同的方案，每个都……各有特点，但也都各有各的缺点，其一就是识别度最高且最准确的用k210后视，用边框拟合或者颜色识别
    其二就是使用固定输出，面向结果，其三或许可以使用超声波模块，来确定与左右车模之间的距离

    mt9v03x_image[][]为总钻风原始数组
    image_deal[][]为经过处理以后的图像数组
    93图像的中间列数
*/

/*
    这里先完成第一个任务，右侧垂直倒车，库1库3均有车辆，倒车时间越短越好，倒车时间大于30s成绩，停车到位5s后，沿车头方向右转出库，出库时
    间不超过15s
*/

void Searching_For_GarageBoundaries(unsigned char (*binary_array)[188]){
    SearchingBoundaries_PointFlag = 0;
    unsigned char temp_row; 
    
    for(unsigned char i = MT9V03X_H - 1; i > 0; i--){
        if(image_deal[i][93] == 255 && image_deal[i - 1][93] == 0 && image_deal[i - 2][93] == 0){
            temp_row = i - 1;
            SearchingBoundaries_PointFlag = 1;
            break;
        }
    }
    if(SearchingBoundaries_PointFlag == 1){
        for(unsigned char i = temp_row; i > 0; i--){
            if(image_deal[i][93] == 0 && image_deal[i - 1][93] == 255 && image_deal[i - 2][93] == 255){
                temp_row = i - 1;
                SearchingBoundaries_PointFlag = 2;
                break;
            }
        }
    }
    if(SearchingBoundaries_PointFlag == 2){
        /*
            已经找到黑线上缘的第一条空白行，此处向左遍历
        */
        for(unsigned char i  = 93; i > 0; i--){
            if(image_deal[i][temp_row] == 255 && image_deal[i - 1][temp_row] == 0 && image_deal[i - 2][temp_row] == 0){
                left_distance++;
                break;
            }
        }
        /*
            已经找到黑线上缘的第一条空白行，此处向右遍历
        */
        for(unsigned char i = 93; i > 0; i++){
            if(image_deal[i][temp_row] == 255 && image_deal[i + 1][temp_row] == 0 && image_deal[i + 2][temp_row] == 0){
                right_distance++;
                break;
            }
        }
        if(absolute(left_distance - right_distance) < 3){
            SearchingBoundaries_PointFlag = 3;
        }
    }
}

void Judging_Garage(unsigned char (*binary_array)[188]){
    if(SearchingBoundaries_PointFlag == 3){
        LengthwaysGarage_PointFlag++;
    }
    if(LengthwaysGarage_PointFlag == 3){
        // 执行倒车
    }
}