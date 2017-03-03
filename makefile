OBJ=jbistub.o jbimain.o jbicomp.o jbijtag.o ports.o fastgpio.o gpio.o
ADDOBJ=jbiDebug.o
WFLAG=-Wall -v

#CC=gcc
CC=arm-arago-linux-gnueabi-gcc

EXE=jbiExe jbiDebug
all:$(EXE)

jbiExe:$(OBJ)
	$(CC) -g -o $@ $^
jbiDebug:jbiDebug.o ports.o fastgpio.o gpio.o
	$(CC) -g -o $@ $^
jbiDebug.o:jbiDebug.c
	$(CC) -g -c $<
jbistub.o:jbistub.c jbiport.h jbiexprt.h ports.h
	$(CC) -g -c $<
jbimain.o:jbimain.c jbiport.h jbiexprt.h jbijtag.h jbicomp.h
	$(CC) -g -c $<
jbicomp.o:jbicomp.c jbiport.h jbiexprt.h jbicomp.h
	$(CC) -g -c $<
jbijtag.o:jbijtag.c jbiport.h jbiexprt.h jbijtag.h
	$(CC) -g -c $<
ports.o:ports.c ports.h fastgpio.h
	$(CC) -g -c $<
fastgpio.o:fastgpio.c fastgpio.h am335x.h  gpio.h
	$(CC) -g -c $<
gpio.o:gpio.c gpio.h 
	$(CC) -g -c $<

.PHONY:clean
clean:
	rm -rf $(OBJ) $(ADDOBJ) $(EXE)
