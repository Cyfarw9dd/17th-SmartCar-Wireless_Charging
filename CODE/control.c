/*
 * control.c
 *
 *  Created on: 2022.7.4
 *      Author: Cyfarwydd
 */

#include "headfile.h"
#include "control.h"
#include "pid.h"
#include "cycle.h"


short DUTY_MAX = 4000;  // 4000
short DUTY_MIN = 0;
int16 speed1 = 0, speed2 = 0;

int main_motor;
int Steer_Increase;
short encoder_chaser2;
short encoder_data;

void motor_ctrl(int16 Lmotor, int16 Rmotor){
    if(Lmotor >= 0){
        Lmotor = range_protect(Lmotor, DUTY_MIN, DUTY_MAX);
        pwm_duty(ATOM0_CH1_P21_3, Lmotor); 
        pwm_duty(ATOM0_CH0_P21_2, 0);
    }
    else{
        Lmotor = range_protect(-Lmotor, DUTY_MIN, DUTY_MAX);
        pwm_duty(ATOM0_CH1_P21_3, 0);      
        pwm_duty(ATOM0_CH0_P21_2, Lmotor);
    }
    if(Rmotor >= 0){
        Rmotor = range_protect(Rmotor, DUTY_MIN, DUTY_MAX);
        pwm_duty(ATOM0_CH3_P21_5, Rmotor); 
        pwm_duty(ATOM0_CH2_P21_4, 0);
    }
    else{
        Rmotor = range_protect(-Rmotor, DUTY_MIN, DUTY_MAX);
        pwm_duty(ATOM0_CH3_P21_5, 0);      
        pwm_duty(ATOM0_CH2_P21_4, Rmotor);
    }
}

void get_motor_speed(void){
    speed1 = gpt12_get(GPT12_T6);
    speed2 = -gpt12_get(GPT12_T2);

    gpt12_clear(GPT12_T6);
    gpt12_clear(GPT12_T2);
    lcd_showint16(0, 1, speed1);
    lcd_showint16(0, 2, speed2);
    // systick_delay_ms(STM0, 100);
}

void Quick_Break(void)
{
    int16 speed_now = (speed1 + speed2) / 2;
    if(speed_now > 50)
        motor_ctrl(-2000,-2000);
    else
        motor_ctrl(0,0);
}

