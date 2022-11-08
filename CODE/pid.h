/*
 * pid.h
 *
 *  Created on: 2022.5.18
 *      Author: Cyfarwydd
 */

#ifndef CODE_PID_H_
#define CODE_PID_H_


#include "common.h"
#include "headfile.h"

#define KP 0  //pid���ò���
#define KI 1
#define KD 2
#define KT 3
#define KB 4
#define KF 5

typedef struct
{
    float SumError;
    int32 LastError;
    int32 PrevError;
    int32 LastData;
}PID;

typedef struct{
    float Set;             //设定值
    float Actual;          //实际值
    float err;             //当前误差
    float err_last;        //上一次误差
    float last_derivative; //上次误差与上上次误差之差

    float Kp,Ki,Kd,Kout;
    float voltage;         //计算值
    float integral;        //误差积分值
}PID_2;

extern PID Lmotor_PID, Rmotor_PID, Direct_PID, Prospect_PID, Bottom_PID, Turn_PID, Motor_PID;
extern PID_2 pid;
extern PID Steer_PID;
extern float Lmotor[3], Rmotor[3];
extern float Direct[4], Prospect[4], Bottom[4], Motor[4], Prospect_ForPCrossing[4], Bottom_ForPCrossing[4];
extern float Turn[5][4];
extern float Steer[3];



int32 PlacePID_Control(PID *sprt, float *PID, int32 NowPiont, int32 SetPoint);

int32 PID_Realize(PID *sptr, float *PID, int32 NowData, int32 Point);

int16 PID_Increase(PID *sptr, float *PID, int32 NowData, int32 Point);

int PD_control(float *PID);

void PID_Parameter_Init(PID *sptr);

int16 range_protect(int16 duty, int16 min, int16 max);

short PID_Increase_for_ProspectErr(PID *sptr, float *PID);

short PID_Increase_for_BottomErr(PID *sptr, float *PID);

short PID_Realize_for_ProspectErr(PID *sptr, float *PID);

short PID_Realize_for_BottomErr(PID *sptr, float *PID);

void PID_Init(void);

int calculate_pid(float a);


#endif /* CODE_PID_H_ */
