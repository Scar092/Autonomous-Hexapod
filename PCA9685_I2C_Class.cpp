#include "PCA9685_I2C.h"

/*Board initialisation
----------------------*/

Board::Board()
{

}

Board::Board(int num)
{
	board = num;
}

void Board::board_init() 
{

	 /* This function set the PCA9685 board to normal mode and also set the chip
	    frequency to a suitable for this project
	    Also operation of this function depends from previous.

	    TESTED! NOT ALL! */

	int addr{ get_board_addr(board) };
	wiringPiI2CWriteReg8(addr, 0x00, 0x11);
	wiringPiI2CWriteReg8(addr, 0xFE, 0x79);
	wiringPiI2CWriteReg8(addr, 0x00, 0x01);
	std::cout << "Intialisation succesful!\t" << addr << std::endl;
}

int Board::get_board_addr(int num) 
{

	/* This function have no return in "else". Also I would test it with
	   another board, when it will be possible

	   TESTED! NOT ALL! */

	if (num == 1) 
	{
		return wiringPiI2CSetup(BOARD_ID_1);
	}
	else if (num == 2) 
	{
		return wiringPiI2CSetup(BOARD_ID_2);
	}
	else 
	{
		std::cout << "Invalid board number!\n";
		//break;
	}
}





/*Servo initialisation
----------------------*/

Servo::Servo(int ch)
{
	channel = ch;
}

void Servo::set_servo_angle(int ang)
{

	/* This function is designed to use into the endless cycle, special for HEXY V1.0
	   smart house hexapod. Therefore it consists "break" keyword in some cases */

	if (ang >= 0 & ang <= 180)
	{

		/* Note: this my own practical test results:
		   0°     =   129   pwm;
		   90°    =   309   pwm;
		   180°   =   489   pwm;
		   step   =   2     pwm.
		*/

		pwm = ang * 2 + 129; //transform angle value to corresponding PWM
		val_h = pwm >> 8;    //high 4 bits of PWM
		val_l = pwm & 0xFF;  //low 8 bits of PWM
	}
	else
	{
		std::cout << "Impossible angle value!\n";
		//break;
	}

	/* Each Servo (LED) output have two 12-bit words, that indicates
	front and rear moments of every pulse (called ON and OFF moments).
	There are 4096 repeating parts of time. Every 10 part we will have
	start condition. And the pulse width will be identified by end
	moment. Every word is devided between 2 registers. So we have 8 low
	bits and 4 high bits. Also have additional bits in  High register.
	Please, look to PCA9685 datasheet. And be attentive. */

	if (channel >= 0 & channel <= 15)
	{
		board = get_board_addr(1);
	}
	else if (channel >= 16 & channel <= 19)
	{
		board = get_board_addr(2);
		channel -= 16;
	}
	else
	{
		std::cout << "Impossible channel value!\n";
		//break;
	}

	//Start condition (is default)
	wiringPiI2CWriteReg8(board, LED0_ON_L + channel * 4, 0x00);
	wiringPiI2CWriteReg8(board, LED0_ON_H + channel * 4, 0x00);

	//Stop condition
	wiringPiI2CWriteReg8(board, LED0_OFF_L + channel * 4, val_l);
	wiringPiI2CWriteReg8(board, LED0_OFF_H + channel * 4, val_h);
}

int Servo::read_servo_angle() {

	if (channel >= 0 & channel <= 15) {
		board = get_board_addr(1);
	}
	else if (channel >= 16 & channel <= 19) {
		board = get_board_addr(2);
		channel -= 16;
	}
	else {
		std::cout << "Invalid channel value!\n";
		//break;
	}

	reg_on_h = wiringPiI2CReadReg8(board, LED0_ON_H + channel * 4);
	reg_on_l = wiringPiI2CReadReg8(board, LED0_ON_L + channel * 4);
	reg_off_h = wiringPiI2CReadReg8(board, LED0_OFF_H + channel * 4);
	reg_off_l = wiringPiI2CReadReg8(board, LED0_OFF_L + channel * 4);

	if (reg_on_l != 0 | reg_on_h != 0) {
		std::cout << "Fatal error!\n";
		//break;
	}

	return (((reg_off_h << 8) + reg_off_l) - 129) / 2;
}
