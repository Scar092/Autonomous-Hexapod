#include <wiringPiI2C.h>
#include <iostream>

#define BOARD_ID_1 0x40 //first board adress
#define BOARD_ID_2 0x60 //second board adress (check!)

#define LED0_ON_L  0x06 
#define LED0_ON_H  0x07 
#define LED0_OFF_L 0x08 
#define LED0_OFF_H 0x09

int get_board_addr (int num) {

     /* This function have no return in "else". Also I would test it with 
        another board, when it will be possible
        
        TESTED! NOT ALL! */

     if (num == 1) {
          return wiringPiI2CSetup (BOARD_ID_1);
     } else if (num == 2) {
          return wiringPiI2CSetup (BOARD_ID_2);
     } else {
          std::cout << "Invalid board number!\n";
          break;
     }
}

void board_init(int board) {

     /* This function set the PCA9685 board to normal mode and also set the chip
        frequency to a suitable for this project
        Also operation of this function depends from previous.
        
        TESTED! NOT ALL! */ 

     int adrr {get_board_addr(board)};
     wiringPiI2CWriteReg8 (adrr, 0x00, 0x11);
     wiringPiI2CWriteReg8 (adrr, 0xFE, 0x79);
     wiringPiI2CWriteReg8 (adrr, 0x00, 0x01);
}   

void set_servo_angle (int channel, int ang) {
    
     /* This function is designed to use into the endless cycle, special for HEXY V1.0
        smart house hexapod. Therefore it consists "break" keyword in some cases */

     int pwm {}, val_l {}, val_h {};

     if (ang>=0 & ang<=180) {

          /* Note: this my own practical test results:
             0°     =   129   pwm;
             90°    =   309   pwm;
             180°   =   489   pwm;
             step   =   2     pwm.
          */
              
          pwm = ang*2+129;     //transform angle value to corresponding PWM
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

     int board {};
     if (channel>=0 & channel<=15) {
          board = get_board_adrr(1);
     } else if (channel>=16 & channel<=19) {
          board = get_board_adrr(2);
          channel -= 16;
     } else {
          std::cout << "Impossible channel value!\n";
          break;
     }

     //Start condition (is default)
     wiringPiI2CWriteReg8 (board, LED0_ON_L + channel*4, 0x00);
     wiringPiI2CWriteReg8 (board, LED0_ON_H + channel*4, 0x00);

     //Stop condition
     wiringPiI2CWriteReg8 (board, LED0_OFF_L + channel*4, val_l);
     wiringPiI2CWriteReg8 (board, LED0_OFF_H + channel*4, val_h);
}

int read_servo_angle (int channel) {
     int reg_on_h {}, reg_on_l {}, reg_off_h {}, reg_off_l {};
     int board {};

     if (channel>=0 & channel<=15) {
          board = get_board_adrr(1);
     } else if (channel>=16 & channel<=19) {
          board = get_board_adrr(2);
          channel -= 16;
     } else {
          std::cout << "Invalid channel value!\n";
          break;
     }

     reg_on_h  = wiringPiI2CReadReg8 (board, LED0_ON_H + channel*4);
     reg_on_l  = wiringPiI2CReadReg8 (board, LED0_ON_L + channel*4);
     reg_off_h = wiringPiI2CReadReg8 (board, LED0_OFF_H + channel*4);
     reg_off_l = wiringPiI2CReadReg8 (board, LED0_OFF_L + channel*4);

     if (reg_on_l!=0 | reg_on_h!=0) {
          std::"Fatal error!\n";
          break;
     }

     return (((reg_off_h << 8)+reg_off_l)-129)/2;
}
