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

/*��������ȫ�ֱ������ֱ�Ϊ���޷����ֵ���������ֵ���޷���Сֵ*/
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
        pwm_duty(ATOM0_CH1_P21_3, Lmotor); //��ת
        pwm_duty(ATOM0_CH0_P21_2, 0);
    }
    else{
        Lmotor = range_protect(-Lmotor, DUTY_MIN, DUTY_MAX);
        pwm_duty(ATOM0_CH1_P21_3, 0);      //��ת
        pwm_duty(ATOM0_CH0_P21_2, Lmotor);
    }
    if(Rmotor >= 0){
        Rmotor = range_protect(Rmotor, DUTY_MIN, DUTY_MAX);
        pwm_duty(ATOM0_CH3_P21_5, Rmotor); //��ת
        pwm_duty(ATOM0_CH2_P21_4, 0);
    }
    else{
        Rmotor = range_protect(-Rmotor, DUTY_MIN, DUTY_MAX);
        pwm_duty(ATOM0_CH3_P21_5, 0);      //��ת
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


void Motor_Init(void){
    //unsigned short motor_duty;
    gtm_pwm_init(ATOM0_CH6_P02_6, 50, 0);
    gtm_pwm_init(ATOM0_CH7_P02_7, 50, 0);
}


void Motor_Set(int16 speed){
    int16 motor_duty;
    motor_duty = speed;
    if(motor_duty > 0 && motor_duty<=10000){//�޷�
        pwm_duty(ATOM0_CH6_P02_6, 0);
        pwm_duty(ATOM0_CH7_P02_7, motor_duty);
    }
    else if(motor_duty == 0){
        pwm_duty(ATOM0_CH6_P02_6, 0);
        pwm_duty(ATOM0_CH7_P02_7, 0);        
    }
    else if(motor_duty < 0 && motor_duty >= -10000){
        pwm_duty(ATOM0_CH6_P02_6, -motor_duty);
        pwm_duty(ATOM0_CH7_P02_7, 0);
    }
    
}


void steering_init(int16 angl){//�����ʼ���� �����ֵΪ1000�����޷�Ϊ1230�����޷�Ϊ730��
    unsigned short steer_duty;
    if(angl > 230){//��������޷�
        angl = 230;
    }
    else if(angl < -270){
        angl = -270;
    }
    steer_duty = 1043 + angl;
    gtm_pwm_init(ATOM1_CH1_P33_9, 50, steer_duty);
}

/***********�����Ǻ���***********
 * @param angl ����Ƕ�pwm_duty����
 * @return ��
 * @since      v1.0
   Sample usage: steering_angl(int16 angl)��
   */
void steering_angl(int16 angl){
    unsigned short steer_duty;//��������޷�
    if(angl > 230){
        angl = 230;
    }
    else if(angl < -270){
        angl = -270;
    }
    steer_duty = 1043 - angl;
    pwm_duty(ATOM1_CH1_P33_9, steer_duty);
}

void steering_test(void){
    if(gpio_get(P22_0)){
        steering_angl(Steer_Increase);
        Steer_Increase += 5;
    }
    if(gpio_get(P22_1)){
        steering_angl(Steer_Increase);
        Steer_Increase -= 5;
    }
}

void Buzzer_ctrl(unsigned time){
    gpio_set(P33_10, 1);
    systick_delay_ms(STM0, time); // time * 1000000
    gpio_set(P33_10, 0);
}