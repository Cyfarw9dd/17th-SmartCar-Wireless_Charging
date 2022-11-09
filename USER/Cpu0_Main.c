/*
 * gyro.c
 *
 *  Created on: 2022.7.6
 *      Author: Cyfarwydd
*/


#include "headfile.h"
#pragma section all "cpu0_dsram"

#include "pid.h"
#include "control.h"
#include "image.h"
#include "cycle.h"
#include "gyro.h"
#include "elements.h"
#include "led.h"

#define STEER_MAX 1273
#define STEER_MIN 813

#define PHASE1 740
#define PHASE2 -1770


int core0_main(void)
{
    get_clk();

    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
    enableInterrupts();

    mt9v03x_init();
    seekfree_wireless_init();
    lcd_init();
    lcd_showstr(0, 0, "hello world");

    pit_interrupt_ms(CCU6_0, PIT_CH0, 5);
    pit_interrupt_ms(CCU6_0, PIT_CH1, 4);
    pit_interrupt_ms(CCU6_1, PIT_CH0, 5);
    eru_init(ERU_CH5_REQ1_P15_8, RISING);

    gtm_pwm_init(ATOM0_CH7_P02_7, 17 * 1000, 0);
    gtm_pwm_init(ATOM0_CH5_P02_5, 17 * 1000, 0);
    gtm_pwm_init(ATOM0_CH6_P02_6, 17 * 1000, 0);
    gtm_pwm_init(ATOM0_CH3_P21_5, 17 * 1000, 0);

    gpt12_init(GPT12_T6, GPT12_T6INA_P20_3, GPT12_T6EUDA_P20_0);
    gpt12_init(GPT12_T2, GPT12_T2INB_P33_7, GPT12_T2EUDB_P33_6);

    systick_delay_ms(STM0, 1000);
    while (TRUE)
    {
        Camera();
    }
    
}


#pragma section all restore


