

#include "fastgpio.h"
#include "ports.h"


void setupPort (void)
{
    fastgpio_export(JTAG_TMS);
   	fastgpio_export(JTAG_TDI);
   	fastgpio_export(JTAG_TCK);
   	fastgpio_export(JTAG_TDO);

	fastgpio_set_dir(JTAG_TMS, OUT);
   	fastgpio_set_dir(JTAG_TDI, OUT);
   	fastgpio_set_dir(JTAG_TCK, OUT);
   	fastgpio_set_dir(JTAG_TDO, IN);
    setPort(TMS_PIN, 0);
    setPort(TDI_PIN, 0);
    setPort(TCK_PIN, 0);
}

void unstallPort(void)
{
    fastgpio_unexport(JTAG_TCK);
	fastgpio_unexport(JTAG_TDI);
	fastgpio_unexport(JTAG_TMS);
	fastgpio_unexport(JTAG_TDO);
}

void setPort(short p,short val)
{
    if (p==TMS_PIN)
       fastgpio_set_value(JTAG_TMS, val);
    else if (p==TDI_PIN)
       fastgpio_set_value(JTAG_TDI, val);
    else if (p==TCK_PIN)
       fastgpio_set_value(JTAG_TCK, val);
}

unsigned char readTDOBit()
{
    /* You must return the current value of the JTAG TDO signal. */
   unsigned int val;
   /* gpio_get_value(GPIO_TDO, &val); */
   fastgpio_get_value(JTAG_TDO, &val);
  
   return(val);
}
