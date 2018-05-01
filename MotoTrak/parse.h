#ifndef parse_H
#define parse_H
struct info{
    int accel;
    int lean;
    float x;
    float y;
    int hr;
    float speed;
    int temp;
    int humidity;
    int gear;
};
int parse(char*,info*);
void initializeStruct(info*);
#endif