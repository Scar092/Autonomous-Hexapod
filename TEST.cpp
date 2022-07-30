#include "PCA9685_I2C.h"

int main()
{
	Board board(1);
	board.board_init();

	Servo servo(10);
	servo.set_servo_angle(0);
}
