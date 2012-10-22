#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "hidapi.h"


int main(int argc, char* argv[])
{
	int res;
	unsigned char buf[16];
#define MAX_STR 255
	wchar_t wstr[MAX_STR];
	hid_device *handle;
	int i;
  
	// Open the device using the VID, PID,
	// and optionally the Serial number.
	handle = hid_open(0x04D8, 0x00DF, NULL);
  
	// Read the Manufacturer String
	res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
	printf("Manufacturer String: %ls\n", wstr);
  
	// Read the Product String
	res = hid_get_product_string(handle, wstr, MAX_STR);
	printf("Product String: %ls\n", wstr);
  
	// Read the Serial Number String
	res = hid_get_serial_number_string(handle, wstr, MAX_STR);
	printf("Serial Number String: %ls", wstr);
	printf("\n");
  
  // Send an Output report to request the state (cmd 0x80)
	buf[1] = 0x81;
	hid_write(handle, buf, 16);
  
	// Read requested state
	res = hid_read(handle, buf, 16);
  printf("read 80 result: %d\n", res);
	if (res < 0)
		printf("Unable to read()\n");
  
	// Print out the returned buffer.
	for (i = 0; i < res; i++)
		printf("buf[%d]: %d\n", i, buf[i]);  
  
	// Set the hid_read() function to be non-blocking.
//	hid_set_nonblocking(handle, 1);
  
  buf[0] = 0;

  buf[1] = 0x10; //configure
  buf[5] = 0x00; //IO bitmap
  buf[6] = 0x00; //alt config pin settings
  buf[7] = 0x00; //default value butmap
  buf[8] = 0x00; //alternative function options
  buf[9] = 0xC0; //baud hi
  buf[10] = 0x2D; // baud low
  printf("Sending configure \n");
  hid_write(handle, buf, 16);

  for(i = 0; i < 10; i++) {
    printf("Sending GPIO manipulation \n");
    buf[1] = 0x08; //set clear outputs
    buf[12] = 0xff;
    buf[13] = 0x00;

    hid_write(handle, buf, 16);
    
    usleep(50000);

    buf[1] = 0x08; //set clear outputs
    buf[12] = 0x00;
    buf[13] = 0xff;

    hid_write(handle, buf, 16);
    usleep(50000);
  }
  
	return 0;
}