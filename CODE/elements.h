/*
 * elements.h
 *
 *  Created on: 2022.7.20
 *      Author: Cyfarwydd
 */

#ifndef CODE_ELEMENTS_H_
#define CODE_ELEMENTS_H_

#include "common.h"
#include "headfile.h"

#define P_CROSSING 0
#define DIVERGENCE 1
#define ROUNDABOUT 2
#define GARAGE     3
#define cutCOL 187
#define Button_row 119
#define TRIP 0
#define STRAIGHT 1
#define CROSSING_DOWN 2
#define CROSSING_ABOVE 3
#define BottomRow 119
#define CenterLine 0
#define LeftLine 1
#define RightLine 2
#define StartCoL 0
#define EndCoL 187

extern short P_Crossing_LCounter;
extern short P_Crossing_RCounter;
extern short StartLine_Counter;
extern short Divergence_Counter;
extern short Upslope_Counter;
extern short Downslope_Counter;
extern short Rounding_LCounter;
extern short Rounding_RCounter;
extern short RoundAbout_LCounter;
extern short RoundAbout_RCounter;
extern short Charging_Counter;
extern short Outing_Counter;
extern unsigned char Present_RoundAbout_PointFlagL;
extern unsigned char Present_RoundAbout_PointFlagR;
extern unsigned char ChargingParking_PointFlag;

typedef struct{
    unsigned char changepoint_start;
    unsigned char changepoint_end;
    unsigned char changepoint_row;
    unsigned char changepoint_col;
    unsigned char changepoint_flag;
}changepoint;

extern unsigned char Divergence_point_flag;
extern unsigned char P_Crossing_PointFlag_L, P_Crossing_PointFlag_R;
extern unsigned char StartLine_PointFlag;
extern unsigned char RoundAbout_PointFlag_L;
extern unsigned char RoundAbout_PointFlag_R;
extern unsigned char Upslope_PointFlag;
extern unsigned char Downslope_PointFlag;
extern unsigned char Parking_PointFlag;
extern unsigned char CurrentCharging_PointFlag;
extern unsigned char WireNum;
extern unsigned char Outing_Flag;

extern changepoint TripChangepointL, TripChangepointR, StraightChangepointL, StraightChangepointR;
extern changepoint Changepoint_Down_L, Changepoint_Down_R, Changepoint_Above_L, Changepoint_Above_R;
extern changepoint Parking_L, Parking_R;
extern changepoint RoundAbout_LeftDown, RoundAbout_LeftAbove, RoundAbout_RightDown, RoundAbout_RightAbove;




int absolute(int var);

int minimum(int var1, int var2);

void Findchangepoint_L(changepoint *prt, unsigned char Start, unsigned char End, unsigned char (*binary_array)[188], unsigned char mode);

void Findchangepoint_R(changepoint *prt, unsigned char Start, unsigned char End, unsigned char (*binary_array)[188], unsigned char mode);

void Judging_Divergence(unsigned char (*binary_array)[188]);

// void Judging_Divergence_ver2(unsigned char (*binary_array)[188]);

unsigned char Leftline_Lost_Sum(unsigned char Start_Row, unsigned char End_row);

unsigned char Rightline_Lost_Sum(unsigned char Start_Row, unsigned char End_row);

void Judging_P_Crossing_ver2(unsigned char (*binary_array)[188]);

void Judging_StartLine(unsigned char (*binary_array)[188]);

void Judging_RoundAbout(unsigned char (*binary_array)[188]);

void Judging_Slope(void);

void Pokemon_Go(void);

#endif /* CODE_ELEMENTS_H_ */
