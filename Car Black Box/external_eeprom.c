#include <xc.h>
#include "main.h"
#include "i2c.h"
#include "eeprom.h"


/* 
 * DS1307 Slave address
 * A0  -  Write Mode
 * A1  -  Read Mode
 */



void write_external_eeprom(unsigned char address, unsigned char data)   //storing data in address
{
	i2c_start();
	i2c_write(SLAVE_WRITE_E);
	i2c_write(address);
	i2c_write(data);
	i2c_stop();
    for(int k=1500;k--;);
}

unsigned char read_external_eeprom(unsigned char address)            //extracting data from address
{
	unsigned char data;

	i2c_start();
	i2c_write(SLAVE_WRITE_E);
	i2c_write(address);
	i2c_rep_start();
	i2c_write(SLAVE_READ_E);
	data = i2c_read();
	i2c_stop(); 
	return data;
}