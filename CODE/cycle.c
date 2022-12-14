/*
 * cycle.c
 *
 *  Created on: 2022.7.2
 *      Author: Cyfarwydd
 */

#include "cycle.h"
#include "control.h"
#include "pid.h"
#include "image.h"
#include "gyro.h"
#include "led.h"

#define MOTOR_MAX 1500
#define DUTY_EXPECTATION 4000

short Left_Increase = 0;
short Right_Increase = 0;
short LDuty = 0, RDuty = 0, motor1 = 0, motor2 = 0;
int Direct_Last = 0;
short LMotor_Duty = 0;
short RMotor_Duty = 0;
unsigned char Speed_Parameter = 0;
float CurrentVoltage, PresentVoltage, TempVoltage;


int num = 0;
unsigned char data_array[4];
unsigned char truth;

// unsigned short adc_result;
// float voltage_result;
// float voltage_cap;

void Speed_cycle(short expect){
    get_motor_speed();
    short Expect = 0;
    Expect = expect;
    Left_Increase = PID_Increase(&Lmotor_PID, Lmotor, speed1, Expect);
    Right_Increase = PID_Increase(&Rmotor_PID, Rmotor, speed2, Expect);

    LDuty = LDuty + Left_Increase;
    RDuty = RDuty + Right_Increase;
    lcd_showint16(0, 3, Left_Increase);
    lcd_showint16(0, 4, Right_Increase);

    motor_ctrl(LDuty, RDuty);
}


int32 Speed_deal(void){
    //get_motor_speed();
    int32 speed_now = (speed1 + speed2) / 2;
    int32 speed_set = 100;
    int32 Theory_Duty = PID_Realize(&Motor_PID, Motor, speed_now, speed_set);
    return Theory_Duty;
}

void Turn_cycle_ver2(short theory_duty){ //1600
    cal_curvature();
    short Prospect_Parameter = PID_Realize_for_ProspectErr(&Prospect_PID, Prospect);
    short Bottom_Parameter = PID_Realize_for_BottomErr(&Bottom_PID, Bottom);
    short Union_result = Prospect_Parameter + Bottom_Parameter;
    // short Direct_Parameter = -PID_Realize(&Direct_PID, Direct, (int32)(Real_Gyro_Z * 10),(int32)Union_result);

    Direct_Last = Direct_Last * 0.2 + Union_result * 0.8;
    LMotor_Duty = (theory_duty + Direct_Last * 3) * 6 / voltage_cap;
    RMotor_Duty = (theory_duty - Direct_Last * 3) * 6 / voltage_cap;
    motor_ctrl(LMotor_Duty, RMotor_Duty);
}


void Turn_cycle_ver3(void){
    short Direct_Parameter = calculate_pid((one_curvature(centerline[105], 105))*100);
    Direct_Last = Direct_Last * 0.2 + Direct_Parameter * 0.8;
    LMotor_Duty = DUTY_MAX + Direct_Last * 10000;
    RMotor_Duty = DUTY_MAX - Direct_Last * 10000;

    motor_ctrl(LMotor_Duty, RMotor_Duty);
}


void Turn_cycle_ForPCrossing(short theory_duty){ //1600
    cal_curvature();
    short Prospect_Parameter = PID_Realize_for_ProspectErr(&Prospect_PID, Prospect);
    short Bottom_Parameter = PID_Realize_for_BottomErr(&Bottom_PID, Bottom);
    short Union_result = Prospect_Parameter + Bottom_Parameter;
    // short Direct_Parameter = -PID_Realize(&Direct_PID, Direct, (int32)(Real_Gyro_Z * 10),(int32)Union_result);

    Direct_Last = Direct_Last * 0.2 + Union_result * 0.8;
    LMotor_Duty = theory_duty + Direct_Last * 4;
    RMotor_Duty = theory_duty - Direct_Last * 4;

    motor_ctrl(LMotor_Duty, RMotor_Duty);
}


