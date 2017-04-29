CC = avr-gcc
MCU = atmega328
F_CPU = 1000000
CCOPTS=  -Wall -O1 -DF_CPU=$(F_CPU) -mmcu=$(MCU) 


default: main

main:main.c qtr_driver.o motor.o
	 $(CC) $(CCOPTS) main.c qtr_driver.o motor.o -o main

qtr_driver.o: qtr_driver.c qtr_driver.h
	 $(CC) $(CCOPTS) -c qtr_driver.h qtr_driver.c


motor.o: motor.c motor.h
	 $(CC) $(CCOPTS) -c motor.h motor.c


program: main
	avr-objcopy -R .eeprom -O ihex main main.hex
	avrdude -c usbtiny -p atmega328 -U flash:w:main.hex


clean:
	rm main main.hex motor.o qtr_driver.o motor.h.gch qtr_driver.h.gch

