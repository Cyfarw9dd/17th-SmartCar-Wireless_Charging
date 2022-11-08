/*
 * led.c
 *
 *  Created on: 2022��7��27��
 *      Author: Cyfarwydd
 */

#include "zf_gpio.h"
#include "led.h"
#include "zf_stm_systick.h"
#include "SEEKFREE_18TFT.h"
#include "zf_vadc.h"
// #include "gyro.h"
#define SP 50
unsigned short voltage=0;
unsigned short adc_result;
unsigned short adc_react;
float voltage_result;
float voltage_cap;
float voltage_ret;

void LED_bar_Init(void)
{       gpio_init(A, GPO, 0, PUSHPULL);
        gpio_init(B, GPO, 0, PUSHPULL);
        gpio_init(C, GPO, 0, PUSHPULL);
        gpio_init(D, GPO, 0, PUSHPULL);
        gpio_init(E, GPO, 0, PUSHPULL);
        gpio_init(L1, GPO, 1, PUSHPULL);
        gpio_init(L2, GPO, 1, PUSHPULL);
        gpio_init(L3, GPO, 1, PUSHPULL);

}
void LED_bar_All(void)
{       gpio_init(A, GPO, 1, PUSHPULL);
        gpio_init(B, GPO, 1, PUSHPULL);
        gpio_init(C, GPO, 1, PUSHPULL);
        gpio_init(D, GPO, 1, PUSHPULL);
        gpio_init(E, GPO, 1, PUSHPULL);
        gpio_init(L1, GPO, 0, PUSHPULL);
        gpio_init(L2, GPO, 0, PUSHPULL);
        gpio_init(L3, GPO, 0, PUSHPULL);

}

void LED_bar0(void)
{
    LED_bar_Init();
}

void LED_bar1(void)
{
    //while(1)
    for(int a=0;a<SP;a++)
    {
         gpio_set(L3,0);
         gpio_set(E,1);
    }
    for(int a=0;a<SP;a++)
    {
        //  systick_delay_ms(STM0,SPEED);
         LED_bar_Init();
        //  systick_delay_ms(STM0,SPEED);
    }
}

void LED_bar2(void)
{
    //while(1)
    for(int a=0;a<SP;a++)
    {
         gpio_set(L2,0);
         gpio_set(L3,0);
         gpio_set(E,1);
    }
    for(int a=0;a<SP;a++)
    {
        //  systick_delay_ms(STM0,SPEED);
         LED_bar_Init();
        //  systick_delay_ms(STM0,SPEED);
    }
}

void LED_bar3(void)
{
    //while(1)
    for(int a=0;a<SP;a++)
    {
         gpio_set(L1,0);
         gpio_set(L2,0);
         gpio_set(L3,0);
         gpio_set(E,1);
    }
    for(int a=0;a<SP;a++)
    {
        //  systick_delay_ms(STM0,SPEED);
         LED_bar_Init();
        //  systick_delay_ms(STM0,SPEED);
    }
}

void LED_bar4(void)
{
    //while(1)
    for(int a=0;a<SP;a++)
    {
         gpio_set(L1,0);
         gpio_set(L2,0);
         gpio_set(L3,0);
         gpio_set(E,1);
    }
    for(int a=0;a<SP;a++)
    {
        //  systick_delay_ms(STM0,SPEED);
         LED_bar_Init();
    }
    for(int a=0;a<SP;a++)
    {
        //  systick_delay_ms(STM0,SPEED);
         gpio_set(L3,0);
         gpio_set(C,1);
    }
    for(int a=0;a<SP;a++)
    {
        //  systick_delay_ms(STM0,SPEED);
         LED_bar_Init();
        //  systick_delay_ms(STM0,SPEED);
    }
}

void LED_bar5(void)
{
    //while(1)
    for(int a=0;a<SP;a++)
    {
         gpio_set(L1,0);
         gpio_set(L2,0);
         gpio_set(L3,0);
         gpio_set(E,1);
    }
    for(int a=0;a<SP;a++)
    {
        //  systick_delay_ms(STM0,SPEED);
         LED_bar_Init();
    }
    for(int a=0;a<SP;a++)
    { 
        //  systick_delay_ms(STM0,SPEED);
         gpio_set(L2,0);
         gpio_set(L3,0);
         gpio_set(C,1);
    }for(int a=0;a<SP;a++)
    {
        //  systick_delay_ms(STM0,SPEED);
         LED_bar_Init();
    }
}

void LED_bar6(void)
{
    //while(1)
    for(int a=0;a<SP;a++)
    {
         gpio_set(L1,0);
         gpio_set(L2,0);
         gpio_set(L3,0);
         gpio_set(C,1);
         gpio_set(E,1);
    }
    for(int a=0;a<SP;a++)
    {
        //  systick_delay_ms(STM0,SPEED);
         LED_bar_Init();
        //  systick_delay_ms(STM0,SPEED);
    }
}

void LED_bar7(void)
{
    //while(1)
    for(int a=0;a<SP;a++)
    {
         gpio_set(L1,0);
         gpio_set(L2,0);
         gpio_set(L3,0);
         gpio_set(C,1);
         gpio_set(E,1);
    }
    for(int a=0;a<SP;a++)
    {
        //  systick_delay_ms(STM0,SPEED);
         LED_bar_Init();
    }
    for(int a=0;a<SP;a++)
    {
        //  systick_delay_ms(STM0,SPEED);
         gpio_set(L3,0);
         gpio_set(D,1);
    }
    for(int a=0;a<SP;a++)
    {
        //  systick_delay_ms(STM0,SPEED);
         LED_bar_Init();
    }
}

void LED_bar8(void)
{
    //while(1)
    for(int a=0;a<SP;a++)
    {
        gpio_set(L1,0);
        gpio_set(L2,0);
        gpio_set(L3,0);
        gpio_set(C,1);
        gpio_set(E,1);
    }
    for(int a=0;a<SP;a++)
    {
        // systick_delay_ms(STM0,SPEED);
        LED_bar_Init();
    }
    for(int a=0;a<SP;a++)
    {
        // systick_delay_ms(STM0,SPEED);
        gpio_set(L2,0);
        gpio_set(L3,0);
        gpio_set(D,1);
    }
    for(int a=0;a<SP;a++)
    {
        // systick_delay_ms(STM0,SPEED);
        LED_bar_Init();
    }
}

void LED_bar9(void)
{
    //while(1)
    for(int a=0;a<SP;a++)
    {
         gpio_set(L1,0);
         gpio_set(L2,0);
         gpio_set(L3,0);
         gpio_set(D,1);
         gpio_set(C,1);
         gpio_set(E,1);
    }
    for(int a=0;a<SP;a++)
    {
        //  systick_delay_ms(STM0,SPEED);
         LED_bar_Init();
        //  systick_delay_ms(STM0,SPEED);
    }
}

void LED_bar10(void)
{
    //while(1)
    for(int a=0;a<SP;a++)
    {
        gpio_set(L1,0);
        gpio_set(L2,0);
        gpio_set(L3,0);
        gpio_set(D,1);
        gpio_set(C,1);
        gpio_set(E,1);
    }
    for(int a=0;a<SP;a++)
    {
    //    systick_delay_ms(STM0,SPEED);
        LED_bar_Init();
    }
    for(int a=0;a<SP;a++)
    {
    //    systick_delay_ms(STM0,SPEED);
        gpio_set(L3,0);
        gpio_set(B,1);
    }
    //    systick_delay_ms(STM0,SPEED);
    for(int a=0;a<SP;a++)
    {  
        LED_bar_Init();
    }
}

void LED_bar11(void)
{
    //while(1)
    for(int a=0;a<SP;a++)
    {   gpio_set(L1,0);
        gpio_set(L2,0);
        gpio_set(L3,0);
        gpio_set(D,1);
        gpio_set(C,1);
        gpio_set(E,1);
    }
    for(int a=0;a<SP;a++)
    {
        // systick_delay_ms(STM0,SPEED);
        LED_bar_Init();
    }
    for(int a=0;a<SP;a++)
    {
        // systick_delay_ms(STM0,SPEED);
        gpio_set(L2,0);
        gpio_set(L3,0);
        gpio_set(B,1);
    }
    for(int a=0;a<SP;a++)
    {
        // systick_delay_ms(STM0,SPEED);
        LED_bar_Init();
    }
}

void LED_bar12(void)
{
    //while(1)
    for(int a=0;a<SP;a++)
    {
         gpio_set(L1,0);
         gpio_set(L2,0);
         gpio_set(L3,0);
         gpio_set(B,1);
         gpio_set(D,1);
         gpio_set(C,1);
         gpio_set(E,1);
    }
    for(int a=0;a<SP;a++)
    {
        //  systick_delay_ms(STM0,SPEED);
         LED_bar_Init();
        //  systick_delay_ms(STM0,SPEED);
    }
}

void LED_bar13(void)
{
    //while(1)
    for(int a=0;a<SP;a++)
    {
         gpio_set(L1,0);
         gpio_set(L2,0);
         gpio_set(L3,0);
         gpio_set(B,1);
         gpio_set(D,1);
         gpio_set(C,1);
         gpio_set(E,1);
    }
    for(int a=0;a<SP;a++)
    {
        //  systick_delay_ms(STM0,SPEED);
         LED_bar_Init();
    }
    for(int a=0;a<SP;a++)
    {
         //systick_delay_ms(STM0,SPEED);
         gpio_set(L3,0);
         gpio_set(A,1);
    }
    for(int a=0;a<SP;a++)
    {
        //  systick_delay_ms(STM0,SPEED);
         LED_bar_Init();
    }
}

void LED_bar14(void)
{
    //while(1)
    for(int a=0;a<SP;a++)
    {
         gpio_set(L1,0);
         gpio_set(L2,0);
         gpio_set(L3,0);
         gpio_set(B,1);
         gpio_set(D,1);
         gpio_set(C,1);
         gpio_set(E,1);
    }
    for(int a=0;a<SP;a++)
    {
        //  systick_delay_ms(STM0,SPEED);
         LED_bar_Init();
    }
    for(int a=0;a<SP;a++)
    {
        //  systick_delay_ms(STM0,SPEED);
         gpio_set(L2,0);
         gpio_set(L3,0);
         gpio_set(A,1);
    }
    for(int a=0;a<SP;a++)
    {
        //  systick_delay_ms(STM0,SPEED);
         LED_bar_Init();
    }
}

void LED_bar15(void)
{      
        for(int a=0;a<SP;a++)
    {   LED_bar_All();
        // systick_delay_ms(STM0,SPEED);
    }
    for(int a=0;a<SP;a++)
    {
        LED_bar_Init();
        // systick_delay_ms(STM0,SPEED);
    }
}

void LED_bar(float voltage)
{   unsigned char a;
    a = (int)voltage;
    //lcd_showuint8(0,0,a);
    switch(a)
    {
        case 0: LED_bar0();break;
        case 1:LED_bar1();break;
        case 2:LED_bar2();break;
        case 3:LED_bar3();break;
        case 4:LED_bar4();break;
        case 5:LED_bar5();break;
        case 6:LED_bar6();break;
        case 7:LED_bar7();break;
        case 8:LED_bar8();break;
        case 9:LED_bar9();break;
        case 10:LED_bar10();break;
        case 11:LED_bar11();break;
        case 12:LED_bar12();break;
        case 13:LED_bar13();break;
        case 14:LED_bar14();break;
        case 15:LED_bar15();break;
        default:LED_bar0();break;
    }
}

 void ADC_VoltageCapture(void){
     adc_result = adc_mean_filter(ADC_0, ADC0_CH0_A0, ADC_12BIT, 10);//采集10次求平均  分辨率12位
     //voltage_result=adc_result*1.0/1242.10;
     voltage_result = adc_result * 1.0 * 0.000758;
     voltage_cap = voltage_result * 5.0;
     voltage_cap = Get_fitter_distance(voltage_cap);
    //  LED_bar(voltage_cap);
 }


#define xianfu 100
unsigned short Get_fitter_distance(unsigned short real_distance)

{

  unsigned char i;
  static unsigned short Data[10];//13
  static unsigned short Last_distance=0;
  unsigned short Value;
  unsigned short Sum=0;
 unsigned short Max,Min;
 if(abs(Last_distance-real_distance)>xianfu){        //丢弃和上一次数据差值太大的数据
           if(Last_distance<real_distance){
       real_distance=Last_distance+xianfu;  
      }else{
        real_distance=Last_distance-xianfu;    
      }
 }
  Data[9] =real_distance;//采集数据放到数组最高位

  for(i=0;i<9;i++)
  {

  Data[i]= Data[i+ 1]; //所有数据左移,低位扔掉

  }
                            //中位值均值滤波
        Max =Data[0];
        Min = Max;
        for( i=0;i<10;i++)
        {
                 Sum += Data[i];//求和
            if(Data[i]>Max)
            {
                Max = Data[i];  
            }

            if(Data[i]<Min)
            {
                Min =Data[i];   
            }
        }
      Sum= Sum-Max-Min; 
      
 
       Value = Sum/8;
       Last_distance=real_distance;
       return Value;//求平均

}


