

#include <xc.h>
#include "adc.h"
#include "car_black_box.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "eeprom.h"
#include "i2c.h"
#include "ds1370.h"
#include "uart.h"


#define _XTAL_FREQ 20000000  

//Dashboard
    unsigned char key,count;
    unsigned short adc_reg_val;
    int index_val ,speed;
    char speed_str[3]; 
    char *arr[8] = {"ON", "GR", "GN", "G1", "G2", "G3", "G4", "C_"};
    extern unsigned char time[9];
    int i;
 
 // main menu
char menu[4][17] = {"VIEW_LOG","CLEAR_LOG","DOWN_LOG","SET_TIME"};
    int k,j;
    int scroll;
    int flag;
    
    //view log
    static int data_index = 0, once = 1;
    int event_number=0;
    char array[17];
    int x;
    int event_count = 0;
    
    char hour,min,sec;
    int blink,field,delay,a,b;
    