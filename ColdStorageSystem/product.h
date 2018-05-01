#ifndef product_H
#define product_H

//Product structure
struct product
{
    char pname[50];
    unsigned int pid[4];
    unsigned int count;
    float priceper;
    float weight;

    struct product *next;

};


#endif

