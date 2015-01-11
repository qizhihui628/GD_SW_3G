/*
 * main.c
 *
 *  Created on: Jan 11, 2015
 *      Author: jeqi
 */

#include <stdio.h>
#include "type.h"
#include "serial.h"

#define BAUDRATE 115200
char Serial_Port[] = {"/dev/ttyUSB6"};
re_error_enum ret_val = RE_SUCCESS;
int Serial_fd = -1;

void main(void)
{
	serial_init();
	ret_val = serial_creat(Serial_Port, BAUDRATE, &Serial_fd);
	if (ret_val != RE_SUCCESS || Serial_fd < 0)
	{
		printf("Error: serial_creat failed!\n");
	}


	mu609_test();
	close(Serial_fd);
	printf("Hello!!\n");
}


