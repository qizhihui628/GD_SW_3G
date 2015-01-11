/*
 * mu609.c
 *
 *  Created on: Jan 11, 2015
 *      Author: jeqi
 */
#include "mu609.h"
#include "serial.h"
#include "main.h"
#include <unistd.h>
#include <string.h>

#define RX_BUF_SIZE  250
unsigned char rx_counter;

char serial_rx_buf[RX_BUF_SIZE];

char smstype[]="AT+CMGF=0\r";			//select 0 for PDU mode.
char smscmgs[]="AT+CMGS=31\r";			//=15+2* bytes of message.
char pdu[]="0891683110801105f011000D91685116088821f5000800166C5F592779D183026B228FCE60A8FF01\x1a";
//char end = 0x1a;

void mu609_test(void)
{
	ret_val = serial_write(Serial_fd,(u8*)smstype,sizeof(smstype));
	usleep(200000);
	ret_val = serial_read(Serial_fd,RX_BUF_SIZE,serial_rx_buf,&rx_counter);
	if(ret_val != RE_SUCCESS)
	{
		printf("Error: serial_read failed!\n");
	}
	else
	{
		if(strstr(serial_rx_buf,"OK") == NULL)
		{
			printf("%s",serial_rx_buf);
			printf("Error: strstr OK failed!\n");
		}
	}
	ret_val = serial_write(Serial_fd,(u8*)smscmgs,sizeof(smscmgs));
	usleep(200000);
	ret_val = serial_read(Serial_fd,RX_BUF_SIZE,serial_rx_buf,&rx_counter);
	if(ret_val != RE_SUCCESS)
	{
		printf("Error: serial_read failed!\n");
	}
	else
	{
		if(strstr(serial_rx_buf,">") == NULL)
		{
			printf("%s",serial_rx_buf);
			printf("Error: strstr OK failed!\n");
		}
	}
	ret_val = serial_write(Serial_fd,(u8*)pdu,sizeof(pdu));
	//ret_val = serial_write(Serial_fd,&end,sizeof(end));
	usleep(300000);
	ret_val = serial_read(Serial_fd,RX_BUF_SIZE,serial_rx_buf,&rx_counter);
	sleep(5);
	ret_val = serial_read(Serial_fd,RX_BUF_SIZE,serial_rx_buf,&rx_counter);
	if(ret_val != RE_SUCCESS)
	{
		printf("Error: serial_read failed!\n");
	}
	else
	{
		if(strstr(serial_rx_buf,"OK") == NULL)
		{
			printf("%s",serial_rx_buf);
			printf("Error: strstr OK failed!\n");
		}
	}

}

