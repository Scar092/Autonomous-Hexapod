#include <wiringPiI2C.h>

#define BOARD_ID 0x60 //device adress
#define LED13_ON_L 0x3A //low ON register date 
#define LED13_ON_H 0x3B //high ON register date
#define LED13_OFF_L 0x3C //low OFF register date
#define LED13_OFF_H 0x3D //high OFF register date

int board, default_1, default_2, result_1, result_2;
int ang, pwm
char val_l, val_h;

ang = ; //angle defined early 
pwm = angle/180*4095; //angle to PWM
val_h = pwm & 0xF00; //high 4 bits of PWM
val_l = pwm & 0xFF; //low 8 bits of PWM

board = wiringPiI2CSetup (BOARD_ID); //initialisation

/* Each Servo (LED) output have two 12-bit words, that indicates
front and rear moments of every pulse (called ON and OFF moments).
There are 4096 repeating parts of time. Every 10 part we will have
start condition. And the pulse width will be identified by end moment. */ 

default_1 = wiringPiI2CWriteReg8 (BOARD_ID, LED13_ON_L, 0xA);
default_2 = wiringPiI2CWriteReg8 (BOARD_ID, LED13_ON_H, 0x0);

result_1 = wiringPiI2CWriteReg8 (BOARD_ID, LED13_OFF_L, val_l);
result_1 = wiringPiI2CWriteReg8 (BOARD_ID, LED13_OFF_H, val_h);
