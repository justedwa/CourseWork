#ifndef info_H
#define info_H

struct info{
  int humidity;
  int temp;
  int accel;
  int gear;
  float speed;
  int hr;
  float x;
  float y;
  float lean;
  int crash;
};

void populate(info*);
//void printInfo(info*);

#endif
