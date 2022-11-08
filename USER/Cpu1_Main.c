/*
 * gyro.c
 *
 *  Created on: 2022.7.6
 *      Author: Cyfarwydd
*/

#include "headfile.h"
#pragma section all "cpu1_dsram"
#include "pid.h"
#include "image.h"
#include "cycle.h"
#include "gyro.h"
#include "elements.h"
#include "led.h"
#include "control.h"

void core1_main(void)
{
    get_clk();//获取时钟频率  务必保留
    //用户在此处调用各种初始化函数等
    adc_init(ADC_0, ADC0_CH0_A0);//初始化ADC0 通道0 使用A10引脚
    adc_init(ADC_1, ADC1_CH9_A25);
    //等待所有核心初始化完毕
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
    enableInterrupts();
    
    while (TRUE)
    {
        
    }
}

                          

#pragma section all restore
