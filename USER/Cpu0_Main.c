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


/*
    以下为电赛~B~题奇奇怪怪的代码
*/


int core0_main(void)
{
    get_clk();

    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
    enableInterrupts();

    // mt9v03x_init();
    // seekfree_wireless_init();
    // lcd_showstr(0, 0, "hello world");

    pit_interrupt_ms(CCU6_0, PIT_CH0, 5);
    pit_interrupt_ms(CCU6_0, PIT_CH1, 4);
    pit_interrupt_ms(CCU6_1, PIT_CH0, 5);
    // eru_init(ERU_CH5_REQ1_P15_8, RISING);

    gtm_pwm_init(ATOM0_CH7_P02_7, 17 * 1000, 0);
    gtm_pwm_init(ATOM0_CH5_P02_5, 17 * 1000, 0);
    gtm_pwm_init(ATOM0_CH6_P02_6, 17 * 1000, 0);
    gtm_pwm_init(ATOM0_CH3_P21_5, 17 * 1000, 0);

    gpt12_init(GPT12_T6, GPT12_T6INA_P20_3, GPT12_T6EUDA_P20_0);
    gpt12_init(GPT12_T2, GPT12_T2INB_P33_7, GPT12_T2EUDB_P33_6);
    uart_init(UART_0, 115200, UART0_TX_P14_0, UART0_RX_P14_1);
    gpio_init(P22_0, GPI, 0, PULLDOWN);
    gpio_init(P22_1, GPI, 0, PULLDOWN);
    // gpio_init(P22_0, GPI, 0, PULLDOWN);

    gpio_init(P33_10, GPO, 0, PUSHPULL);   // 蜂鸣器初始化

    steering_init(0);
    lcd_init();
    Motor_Init();

    systick_delay_ms(STM0, 1000);
    while (TRUE)
    {
        lcd_showint16(0, 1, 1043 + Steer_Increase);
        steering_test();

        Motor_Set(3500);
        Get_UartBuffer();
    
        if(data_array[2] == 2){
            Motor_Set(3500);
            systick_delay_ms(STM0, 10);
            encoder_data = 0;
            while(encoder_data < 1300){
				steering_angl(230);
				Motor_Set(4000);
            }
            Buzzer_ctrl(1000);
            while(encoder_data > -300){
                steering_angl(-160);
				Motor_Set(-4000);
            }
            while(encoder_data > -1300){
                steering_angl(0);
                Motor_Set(-4500);
            }
            Motor_Set(0);
            // 此处入库停车，蜂鸣器响应，编码器累加清零
            encoder_data = 0;
            Buzzer_ctrl(1000);
            
             systick_delay_ms(STM0, 5000);
             while(encoder_data < 1200){
                 Motor_Set(4500);
                 steering_angl(0);
             }
             while(encoder_data < 5800){
                 Motor_Set(5500);
                 steering_angl(-230);
             }
             while(1){
                 steering_angl(0);
             }
        }
        
    }
    
}


#pragma section all restore


