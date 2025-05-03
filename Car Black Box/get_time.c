#include <xc.h>
#include "main.h"

unsigned char clock_reg[3];    //array variable is used to extracting data from address
unsigned char time[9];      //array variable to store time characters


//function to get real time
void get_time(void)
{
	clock_reg[0] = read_ds1307(HOUR_ADDR);    //extracting hour data from specific address
	clock_reg[1] = read_ds1307(MIN_ADDR);     //extracting minute data from specific address
	clock_reg[2] = read_ds1307(SEC_ADDR);     //extracting second data from specific address     

	 if (clock_reg[0] & 0x40)                 //converting BCD value to decimal after converting into character
	 {
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);         
		time[1] = '0' + (clock_reg[0] & 0x0F);
	 }
	 else
	 {
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	 }
        time[2] = ':';
        time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
        time[4] = '0' + (clock_reg[1] & 0x0F);
        time[5] = ':';
        time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
        time[7] = '0' + (clock_reg[2] & 0x0F);
        time[8] = '\0';
}

