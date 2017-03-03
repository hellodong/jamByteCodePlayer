

#ifndef PORTS_H
#define PORTS_H

#define TMS_PIN     0
#define TDI_PIN     1
#define TCK_PIN     2

void setupPort (void);

void unstallPort(void);

void setPort(short p,short val);

unsigned char readTDOBit(void);


#endif