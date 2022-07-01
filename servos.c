int curr_ang[15] = <READ>; //current servo's angles
int angle[15] = <WRITE>; //needed angles

int incr; //increment

while (curr_angs != angles) {
     for (i in curr_angs) {
          if (angles[i] < curr_angs[i]) {
               incr = -1;
          } else {
               incr = 1;
          }
          angles[i] += incr;
          angle_15 = set_angle (angles[15]);
          angle_15 = set_angle (angles[15]);
          angle_15 = set_angle (angles[15]);
          angle_14 = set_angle (angles[14]);
          angle_13 = set_angle (angles[13]);
          angle_12 = set_angle (angles[12]);
          angle_11 = set_angle (angles[11]);
          angle_10 = set_angle (angles[10]);
          angle_9 = set_angle (angles[9]);
          angle_8 = set_angle (angles[8]);
          angle_7 = set_angle (angles[7]);
          angle_6 = set_angle (angles[6]);
          angle_5 = set_angle (angles[5]);
          angle_4 = set_angle (angles[4]);
          angle_3 = set_angle (angles[3]);
          angle_2 = set_angle (angles[2]);
          angle_1 = set_angle (angles[1]);
          angle_0 = set_angle (angles[0]);
          }
}
