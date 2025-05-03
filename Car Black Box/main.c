#include "main.h"

State_t state;

void init_config() {

    state = e_dashboard;

    init_clcd();
    init_matrix_keypad();
    init_adc();
    init_i2c();
    init_ds1307();
    init_uart();


    if (read_external_eeprom(0x00) == 0xFF) {
        write_external_eeprom(0x00, 0);
    }
}

void main(void) {
    init_config();
//    event_count = read_external_eeprom(100);
//    if (event_count > 10) {
//      event_count  event_count = 0;
//    }


    while (1) {
        // Detect key press and speed
        key = read_switches(STATE_CHANGE);



        switch (state) {
            case e_dashboard:
                // Display dashboard
                view_dashboard();
        
                break;

            case e_main_menu:
                // Display dashboard
                display_main_menu();
                //                if(key == 11)
                //                {
                //                    state = e_view_log;
                //                    CLEAR_DISP_SCREEN;
                //                }
                //                if()
                break;

            case e_view_log:
                // Display dashboard
                view_log();
                if (key == 12) {
                    state = e_main_menu;
                    CLEAR_DISP_SCREEN;
                } else if (state == e_main_menu) {
                    state = e_dashboard;

                }
                break;

            case e_clear_log:
                clear_log();
                break;

            case e_download_log:
                download_log();
                break;




            case e_set_time:
                set_time();
                break;





        }

    }

}


