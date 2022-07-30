#ifndef PCA9685_H
#define PCA9685_H

#include <wiringPiI2C.h>
#include <iostream>

#define BOARD_ID_1 0x40 //first board adress
#define BOARD_ID_2 0x60 //second board adress (check!)

#define LED0_ON_L  0x06 
#define LED0_ON_H  0x07 
#define LED0_OFF_L 0x08 
#define LED0_OFF_H 0x09

class Board
{
public:
	Board(int num);
	void board_init();

private:
	int board;

protected:
	Board();
	int get_board_addr(int num);
};

class Servo : protected Board
{
public:
	Servo(int ch);
	void set_servo_angle(int ang);
	int read_servo_angle();

private:
	int pwm{}, val_l{}, val_h{};
	int channel{}, board{};
	int reg_on_h{}, reg_on_l{}, reg_off_h{}, reg_off_l{};
};

#endif
