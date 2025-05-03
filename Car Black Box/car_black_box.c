
#include "main.h"
unsigned char data[10][17];
unsigned char stored[10][10];

int str_compare(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return 0;
        }
        str1++;
        str2++;
    }
    return (*str1 == '\0' && *str2 == '\0');
}

void int_to_str(int num, char *str) {
    str[0] = (num / 10) + '0';
    str[1] = (num % 10) + '0';
    str[2] = '\0';
}

unsigned  char write_add = 0;

void store_event() {
    for (int i = 0; i < 8; i++) {
        if (time[i] != ':')
            write_external_eeprom(write_add++, time[i]);

    }

    write_external_eeprom(write_add++, arr[index_val][0]);
    write_external_eeprom(write_add++, arr[index_val][1]);
    //speed
    write_external_eeprom(write_add++, (speed_str[0]));
    write_external_eeprom(write_add++, (speed_str[1]));

//    write_external_eeprom(100, event_count);
}

void event_store(void) {
    if (write_add >= 100) {
        for (int i = 0; i < 90; i++) {
            write_external_eeprom(i, read_external_eeprom(i + 10));
        }
        write_add = 90;
        event_count = 9;
    }

    store_event();
    event_count++;

}

void view_dashboard(void) {


    clcd_print("TIME      EV  SP", LINE1(0));

    get_time();
    adc_reg_val = read_adc(CHANNEL4);
    speed = (adc_reg_val) / 10.23;
    if (speed > 99) {
        speed = 99;
    }

    clcd_print(time, LINE2(0));
    //    clcd_print(arr[i], LINE2(10));
    //    clcd_putch('0' + (speed / 10), LINE2(14));
    //    clcd_putch('0' + (speed % 10), LINE2(15));

    if (key == 1) {
        if (index_val != 7) {
            index_val = 7;
            event_store();
        }
    } else if (key == 2) {
        if (index_val == 7) {
            
            index_val = 0;
        }
        if (index_val >= 0 && index_val < 6) {
            index_val++;
            event_store();
        }

    } else if (key == 3) {
        if (index_val == 7) {
            index_val = 2;
        }
        if (index_val > 1) 
        {
            index_val--;
            event_store();
        }
    }

    clcd_print(arr[index_val], LINE2(10));

    int_to_str(speed, speed_str);


    clcd_print(speed_str, LINE2(14));

    if (key == 11) {
        state = e_main_menu;
        CLEAR_DISP_SCREEN;
    }

}

void display_main_menu(void) {


    clcd_print(menu[j], LINE1(2));
    clcd_print(menu[j + 1], LINE2(2));

    if (scroll == 0) {
        clcd_print("*", LINE1(0));
        clcd_print(" ", LINE2(0));
        k = j;

    } else {
        clcd_print(" ", LINE1(0));
        clcd_print("*", LINE2(0));
        k = j + 1;
    }
    if (key == 1) {
        if (scroll == 1)
            scroll = 0;
        else if (j > 0 && j <= 2)
            j--;
    } else if (key == 2) {
        if (scroll == 0)
            scroll = 1;
        else if (j < 2 && j >= 0)
            j++;
    } else if (key == 12) {
        flag = 0;
        state = e_dashboard;
        CLEAR_DISP_SCREEN;

        j = 0;
        scroll = 0;
    }
    if (key == 11) //key is for entering menu functions
    {
        state = j + scroll + 2;
        if(state == e_view_log)
        {
            data_index = 0;
            event_number = 0;
        }
        CLEAR_DISP_SCREEN;
        //        if (str_compare(menu[i], "VIEW_LOG") == 0) {
        //
        //
        //            state = e_view_log;
        //            flag = 0;
        //        } else if (str_compare(menu[i], "SET_TIME") == 0) {
        //
        //            state = e_set_time;
        //            flag = 0;
        //        } else if (str_compare(menu[i], "DOWN_LOG") == 0) {
        //
        //            state = e_download_log;
        //            flag = 0;
        //        } else if (str_compare(menu[i], "CLEAR_LOG") == 0) {
        //
        //            state = e_clear_log;
        //            flag = 0;
        //        }
    }
}

void event_read() {
    unsigned char read_addr = 0x00;

    for (int i = 0; i < event_count; i++) {
        for (int j = 0; j < 16; j++) {
            if (j == 13 || j == 10 || j == 1) {
                data[i][j] = ' ';
            } else if (j == 0) {
                data[i][j] = i + '0';
            } else if (j == 4 || j == 7) {
                data[i][j] = ':';
            } else {
                data[i][j] = read_external_eeprom(read_addr++);
            }
        }

        data[i][16] = '\0';
    }
}

//static int data_index = 0, once = 1;

void view_log(void) {


//    clcd_putch(event_count+48,LINE1(0));
//    while(1);
    if(event_count < 1){
        for(int delay = 1000 ; delay--;)
        {
            clcd_print("NO EVENT FOUND !", LINE1(0));
        }
        state = e_main_menu;
        return;
    }
    clcd_print("#  TIME    EV SP", LINE1(0));
//    if (once) {
//        once = 0;
//        event_read();
//    }

    clcd_putch(event_number+'0', LINE2(0));
    clcd_putch(read_external_eeprom(data_index), LINE2(2));
    clcd_putch(read_external_eeprom(data_index+1), LINE2(3));
    clcd_putch(':', LINE2(4));
    clcd_putch(read_external_eeprom(data_index+2), LINE2(5));
    clcd_putch(read_external_eeprom(data_index+3), LINE2(6));
    clcd_putch(':', LINE2(7));
    clcd_putch(read_external_eeprom(data_index+4), LINE2(8));
    clcd_putch(read_external_eeprom(data_index+5), LINE2(9));
    clcd_putch(' ', LINE2(10));
    clcd_putch(read_external_eeprom(data_index+6), LINE2(11));
    clcd_putch(read_external_eeprom(data_index+7), LINE2(12));
    clcd_putch(' ',LINE2(13));
    clcd_putch(read_external_eeprom(data_index+8), LINE2(14));
    clcd_putch(read_external_eeprom(data_index+9), LINE2(15));


    //    if (data_index < 0) {
    //        data_index = 0;
    //    } else if (data_index >= event_count) {
    //        data_index = event_count - 1;
    //    }


    if (key == 1 && data_index > 0) {
        data_index -= 10;
        event_number--;
    } else if (key == 2 && data_index < write_add-10) {
        data_index+=10;
        event_number++;
    } else if (key == 12) {
        state = e_main_menu;
        CLEAR_DISP_SCREEN;
    }
}

void clear_log(void) 
{
   event_count = 0;
    write_add = 0x00;    event_number = 0;
    for (int j = 0; j < 100; j++) {
        write_external_eeprom(write_add++, ' ');
    }

    clcd_print("    CLEAN       ", LINE1(0));
    clcd_print("   SUCCESSFULLY ", LINE2(0));

    __delay_ms(2000);


    i = 10;
    x = 0;
    write_add = 0x00;
    event_store();
    flag = 0;
    state = e_main_menu;
    CLEAR_DISP_SCREEN;
    
}

void download_log(void) 
{
    i = 10;
    event_store();

    write_add = 0x00;
    puts("# TIME    EV  SP");
    puts("\n\r");

    if (event_count == 0)
    {
        CLEAR_DISP_SCREEN;
        puts("no events\n\r");
        state = e_main_menu;
        return;
    }
    putch(event_count+48);
    event_read();
    puts("\n\r");
    for (int x = 0; x < event_count-1; x++) {
        puts(data[x]);
        
//        write_add = x * 10;[]
//        for (k = 0; k < 16; k++) {
//            if (k == 0) {
//                array[k] = '0' + x;
//            } else if (k == 4 || k == 7) {
//                array[k] = ':';
//            } else if (k == 1 || k == 10 || k == 13) {
//                array[k] = ' ';
//            } else {
//                array[k] = read_external_eeprom(write_add++);
//            }
//        }
//        array[k] = '\0';
//        puts(array);
        puts("\n\r");
    }
    puts("DOWNLOADED SUCCESSFULLY...\n\r");


    clcd_print("   DOWNLOADED   ", LINE1(0));
    clcd_print("  SUCCESSFULLY  ", LINE2(0));
    __delay_ms(2000);

    flag = 0;
    state = e_main_menu;
    CLEAR_DISP_SCREEN;
    
}

void set_time(void) {
    /* sw1 = increace
    sw2 = change feild
    sw11 = save and exit 
     sw12 = unsave and exit
     */

    clcd_print("HH:MM:SS", LINE1(3));

    if (a == 0) {

        hour = (time[0] - '0') * 10 + (time[1] - '0');
        min = (time[3] - '0') * 10 + (time[4] - '0');
        sec = (time[6] - '0') * 10 + (time[7] - '0');
        a = 1;
    }

    if (field == 0) {
        clcd_putch(min % 10 + '0', LINE2(7));
        clcd_putch(min / 10 + '0', LINE2(6));
        clcd_putch(':', LINE2(8));
        clcd_putch(sec % 10 + '0', LINE2(10));
        clcd_putch(sec / 10 + '0', LINE2(9));
        clcd_putch(':', LINE2(5));

        if (blink) {
            clcd_putch(hour % 10 + '0', LINE2(4));
            clcd_putch(hour / 10 + '0', LINE2(3));
        } else {
            clcd_print("  ", LINE2(3));
        }
    } else if (field == 1) {
        clcd_putch(hour % 10 + '0', LINE2(4));
        clcd_putch(hour / 10 + '0', LINE2(3));
        clcd_putch(':', LINE2(5));
        clcd_putch(sec % 10 + '0', LINE2(10));
        clcd_putch(sec / 10 + '0', LINE2(9));
        clcd_putch(':', LINE2(8));

        if (blink) {
            clcd_putch(min % 10 + '0', LINE2(7));
            clcd_putch(min / 10 + '0', LINE2(6));
        } else {
            clcd_print("  ", LINE2(6));
        }
    } else if (field == 2) {
        clcd_putch(hour % 10 + '0', LINE2(4));
        clcd_putch(hour / 10 + '0', LINE2(3));
        clcd_putch(':', LINE2(5));
        clcd_putch(min % 10 + '0', LINE2(7));
        clcd_putch(min / 10 + '0', LINE2(6));
        clcd_putch(':', LINE2(8));

        if (blink) {
            clcd_putch(sec % 10 + '0', LINE2(10));
            clcd_putch(sec / 10 + '0', LINE2(9));
        } else {
            clcd_print("  ", LINE2(9));
        }
    }


    if (key == 2) {
        field = (field + 1) % 3;
    } else if (key == 1) {
        if (field == 0)
            hour = (hour + 1) % 24;
        else if (field == 1)
            min = (min + 1) % 60;
        else if (field == 2)
            sec = (sec + 1) % 60;
    } else if (key == 11) {

        write_ds1307(0x00, ((sec / 10) << 4) | (sec % 10));
        write_ds1307(0x01, ((min / 10) << 4) | (min % 10));
        write_ds1307(0x02, ((hour / 10) << 4) | (hour % 10));

        
        clcd_print("TIME SAVED", LINE1(3));
        clcd_print("SUCCESSFULLY", LINE2(2));

        __delay_ms(2000);
         CLEAR_DISP_SCREEN;

        i = 9;
        event_store();
        flag = 0;
        state = e_main_menu;
    } else if (key == 12) {
        CLEAR_DISP_SCREEN;
        clcd_print("TIME NOT SAVED", LINE1(1));
        clcd_print("SUCCESSFULLY", LINE2(2));

        __delay_ms(2000);

        i = 9;
        event_store();
        flag = 0;
        state = e_main_menu;
        CLEAR_DISP_SCREEN;
        
    }


    if (delay++ == 150) {
        delay = 0;
        blink = ~blink;
    }



}










