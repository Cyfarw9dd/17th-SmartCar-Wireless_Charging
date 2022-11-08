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
    get_clk();//��ȡʱ��Ƶ��  ��ر���
    //�û��ڴ˴����ø��ֳ�ʼ��������
    adc_init(ADC_0, ADC0_CH0_A0);//��ʼ��ADC0 ͨ��0 ʹ��A10����
    adc_init(ADC_1, ADC1_CH9_A25);
    //�ȴ����к��ĳ�ʼ�����
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
    enableInterrupts();
    
    while (TRUE)
    {
        
    }
}

                          

#pragma section all restore
