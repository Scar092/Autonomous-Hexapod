#include <wiringPiI2C.h>
#include <iostream>

#define BOARD_ID_1 0x40 //first board adress
#define BOARD_ID_2 0x60 //second board adress (check!)

#define LED0_ON_L 0x3A // CHECK!!!!!!!
#define LED0_ON_H 0x3B 
#define LED0_OFF_L 0x3C 
#define LED0_OFF_H 0x3D // AND THIS ALL!!!!!

void set_servo_angle (int channel, int ang) {
    
     /* This function is designed to use into the endless cycle, special for HEXY V1.0
     smart house hexapod. Therefore it consists "break" keyword in some cases */

     int pwm {}, val_l {}, val_h {};

     if (0<=ang<=180) {
          pwm = ang/180*4095;  //transform angle value to corresponding PWM
          val_h = pwm >> 8;    //high 4 bits of PWM
          val_l = pwm & 0xFF;  //low 8 bits of PWM
     } else {
          std::cout << "Impossible angle value!\n";
          break;
     }

     /* Each Servo (LED) output have two 12-bit words, that indicates
     front and rear moments of every pulse (called ON and OFF moments).
     There are 4096 repeating parts of time. Every 10 part we will have
     start condition. And the pulse width will be identified by end
     moment. Every word is devided between 2 registers. So we have 8 low
     bits and 4 high bits. Also have additional bits in  High register.
     Please, look to PCA9685 datasheet. And be attentive. */ 
     
     int board {}, board_1 {}, board_2 {};

     board_1 = wiringPiI2CSetup (BOARD_ID_1); //initialisation first board
     board_2 = wiringPiI2CSetup (BOARD_ID_2); //initialisation second board

     if (0<=channel<=15) {
          board = board_1;
     } else if (16<=channel<=19) {
          board = board_2;
          channel -= 16;
     } else {
          std::cout << "Impossible channel value!\n";
          break;
     }

     //Start condition (is default)
     wiringPiI2CWriteReg8 (board, LED0_ON_L + channel, 0xA);
     wiringPiI2CWriteReg8 (board, LED0_ON_H + channel, 0x0);

     //Stop condition
     wiringPiI2CWriteReg8 (board, LED0_OFF_L + channel, val_l);
     wiringPiI2CWriteReg8 (board, LED0_OFF_H + channel, val_h);
}

int read_servo_angle() {
