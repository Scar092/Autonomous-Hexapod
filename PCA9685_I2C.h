#ifndef PCA9685_H
#define PCA9685_H

int get_board_addr (int board);
void board_init (int board);
void set_servo_angle (int channel, int ang);
int read_servo_angle (int channel);

#endif
