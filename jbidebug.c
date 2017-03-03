
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "ports.h"


int jtag_hardware_initialized = 0;


void initialize_jtag_hardware()
{
	setupPort ();
}

void close_jtag_hardware()
{
	unstallPort();
}

void jtagPinTest(int pin)
{
    setPort (pin, 1);
    setPort (pin, 0);
}

void jtagPinReadTest(void)
{
    int readValue;

    readValue = readTDOBit();

    printf ("TDO: %d\r\n", readValue);
}
/************************************************************************
*
*	Customized interface functions for Jam STAPL ByteCode Player I/O:
*
*	jbi_jtag_io()
*	jbi_message()
*	jbi_delay()
*/
int jbi_jtag_io(int tms, int tdi, int read_tdo)
{
    int tdoValue = 0;

	if (!jtag_hardware_initialized)
	{
		initialize_jtag_hardware();
		jtag_hardware_initialized = 1;
	}

	setPort(TDI_PIN,tdi);
    setPort(TMS_PIN, tms);

	if (read_tdo)
	{
	    tdoValue = readTDOBit();
	}

    setPort(TCK_PIN, 1);
	setPort(TCK_PIN, 0);
		
	return tdoValue;
}

int main (void)
{
    int i = 0;
    int retValue = 0;

    close_jtag_hardware();
#if 1
    for (i = 0;;i++)
    {
        jbi_jtag_io(1,1,0);
        retValue = jbi_jtag_io(0,0,0);
        if (i % 40000 == 0)
        {
            retValue = jbi_jtag_io(0,0,1);
            printf ("TDO:%d\r\n", retValue);
        }
    }
#else
    for (;;)
    {
        //jtagPinTest(TDI_PIN);  
        jtagPinReadTest();
        sleep(1);
    }
#endif
    return 0;
}
