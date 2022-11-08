/*
 * cycle.h
 *
 *  Created on: 2022��5��18��
 *      Author: Cyfarwydd
 */

#ifndef CODE_CYCLE_H_
#define CODE_CYCLE_H_


#include "common.h"
#include "headfile.h"

extern short Left_Increase;
extern short Right_Increase;
extern int Direct_Last;

extern short LMotor_Duty;
extern short RMotor_Duty;
extern float CurrentVoltage, PresentVoltage, TempVoltage;

extern unsigned char data_array[4];

void Speed_cycle(short expect);

int32 Speed_deal(void);

void Turn_cycle_ver2(short theory_duty);

void Turn_cycle_ver3(void);

void Turn_cycle_ForPCrossing(short theory_duty);

void Get_UartBuffer(void);

#endif /* CODE_CYCLE_H_ */

