#include "PCA9685_I2C.h"
#include <iostream>

class Leg
{
public:
	/*Leg(int num)
	{
		if (num == 1)
		{
			Servo servo_root (1);
			Servo servo_middle (2);
			Servo servo_end (3);
		}
		else if (num == 2)
		{
			Servo servo_root(4);
			Servo servo_middle(5);
			Servo servo_end(6);
		}
		else if (num == 3)
		{
			Servo servo_root(7);
			Servo servo_middle(8);
			Servo servo_end(9);
		}
		else if (num == 4)
		{
			Servo servo_root(10);
			Servo servo_middle(11);
			Servo servo_end(12);
		}
		else if (num == 5)
		{
			Servo servo_root(13);
			Servo servo_middle(14);
			Servo servo_end(15);
		}
		else if (num == 6)
		{
			Servo servo_root(16);
			Servo servo_middle(17);
			Servo servo_end(18);
		}
		else
		{
			std::cout << "Wrong leg number! Init failed!" << std::endl;
		}
	}
	*/
	void set_point(int x, int y, int z)
	{
		double root_ang{ atan2(x,y) };

		double xy{ sqrt(pow(x,2) + pow(y,2)) };
		int x_y = (int)xy;
		double r1{ sqrt(pow(x_y + delta_len,2) + pow(z,2)) };
		int r = (int)r1;
		
		if (r > len_1 + len_2)
		{
			std::cout << "Cannot touch!" << std::endl;
		}

		double middle_ang{ atan2(z,xy) + acos((pow(len_1, 2) + pow(r, 2) - pow(len_2, 2)) / (2 * len_1*r)) };

		double end_ang{ acos((pow(len_2, 2) + pow(len_1, 2) - pow(r, 2)) / (2 * len_1*len_2)) };

		root_ang = root_ang * 180 / 3.14;
		int root = (int)root_ang;

		middle_ang = middle_ang * 180 / 3.14;
		int middle = (int)middle_ang;

		end_ang = end_ang * 180 / 3.14;
		int end = (int)end_ang;

		std::cout << "Root: " << root << "\nMiddle: " << middle << "\nEnd: " << end << std::endl;
		std::cout << "Radius: " << r << std::endl;
	}

private:
	int len_1{ 65 }, len_2{ 123 }, delta_len{ 50 };

	// len_1 - плечо от оси средней сервы до оси концевой
	// len_2 - плечо от оси концевой сервы до кончика ноги
	// delta_len - это плечо от оси корневой сервы до оси средней. Оно не поднимается вверх, а потому
	// не участвует в кинематике следующих двух плеч. Оно двигается только в плоскости ху.
	// Ноль координат х и у будет в точке оси корневой сервы, а по оси z на уровне оси средней сервы.

};
