/*
 * control.h
 *
 *  Created on: 2022.5.18
 *      Author: Cyfarwydd
 */

#ifndef CODE_CONTROL_H_
#define CODE_CONTROL_H_

#include "common.h"
#include "headfile.h"

#define STEER_MID 1042

extern int16 speed1, speed2;
extern short DUTY_MIN, DUTY_MAX;

extern int Steer_Increase;
extern short encoder_chaser2;
extern short encoder_data;

void motor_ctrl(int16 Lmotor, int16 Rmotor);

void get_motor_speed(void);

void Quick_Break(void);

void Motor_Init(void);

void Motor_Set(int16 speed);

void steering_init(int16 angl);

void steering_angl(int16 angl);

void steering_test(void);

void Buzzer_ctrl(unsigned time);

#endif /* CODE_CONTROL_H_ */
