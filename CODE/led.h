/*
 * led.h
 *
 *  Created on: 2022��7��27��
 *      Author: Cyfarwydd
 */

#ifndef CODE_LED_H_
#define CODE_LED_H_


#define A P20_7
#define B P21_7
#define C P23_1
#define D P32_4
#define E P33_10
#define L1 P33_12
#define L2 P33_13
#define L3 P33_5

extern unsigned short adc_result;
extern unsigned short adc_react;
extern float voltage_result;
extern float voltage_cap;
extern float voltage_ret;
//#define SPEED 100
void LED_bar_Init(void);//初始化（全灭）
void LED_bar(float voltage);//通过ADC跑灯
void LED_bar_All(void);//LED全亮

void LED_bar0(void);
void LED_bar1(void);
void LED_bar2(void);
void LED_bar3(void);
void LED_bar4(void);
void LED_bar5(void);
void LED_bar6(void);
void LED_bar7(void);
void LED_bar8(void);
void LED_bar9(void);
void LED_bar10(void);
void LED_bar11(void);
void LED_bar12(void);
void LED_bar13(void);
void LED_bar14(void);
void LED_bar15(void);

void ADC_VoltageCapture(void);

unsigned short Get_fitter_distance(unsigned short real_distance);


#endif /* CODE_LED_H_ */
