#include <wiringPiI2C.h>

#define BOARD_ID 0x60 //device adress
#define LED13_ON_L 0x3A
#define LED13_ON_H 0x3B
#define LED13_OFF_L 0x3C
#define LED13_OFF_H 0x3D

int board, default_1, default_2, result_1, result_2;
int ang
char pwm, val_l, val_h;

ang = ; //angle defined early 
pwm = angle/180*4095; //Angle to PWM
val_h = pwm >> 4;

board = wiringPiI2CSetup (BOARD_ID);
default_1 = wiringPiI2CWriteReg8 (BOARD_ID, LED13_ON_L, 0xA);
default_2 = wiringPiI2CWriteReg8 (BOARD_ID, LED13_ON_H, 0x0);

result_1 = wiringPiI2CWriteReg8 (BOARD_ID, LED13_OFF_L, val_l);
result_1 = wiringPiI2CWriteReg8 (BOARD_ID, LED13_OFF_H, val_h);
