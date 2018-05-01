#ifndef functions_H
#define functions_H

#include "HX711.h"

struct product* addproduct(struct product *head);
struct product* sortlist(struct product *head);
struct product* displaylist(struct product *head);
void freelist(struct product *head);
void savelist(struct product *head);
struct product* loadlist();
struct product* findbyname(char name[50], struct product *head);
struct product* findbyid(int id[10], struct product *head);
struct product* checkin(struct product *head);
struct product* checkout(struct product *head, HX711 scale1);
float scale(HX711 scale);
void timer_temp_hum_isr();
void getstatus();
void setmax();
struct product* findrfid(int rfid[4], struct product *head);


#endif