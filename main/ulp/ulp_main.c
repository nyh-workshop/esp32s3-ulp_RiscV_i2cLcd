/* ULP-RISC-V example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.

   This code runs on ULP-RISC-V  coprocessor
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "ulp_aip31068.h"
#include "ulp_i2c_sw.h"
#include "ulp_riscv.h"
#include "ulp_riscv_utils.h"
#include "ulp_riscv_gpio.h"

#define LCD_ADDRESS (0x7c)

#define AIP31068_CTRL 0x80
#define AIP31068_RS 0x40

#define AIP31068_FUNCSET 0x20
#define AIP31068_LINENUM 0x08
#define AIP31068_FONTTYPE 0x04

int main (void)
{
    I2C_init();

    ulp_riscv_delay_cycles(ULP_RISCV_CYCLES_PER_MS * 500); 
    
    ULP_AIP31068_init();

    ULP_AIP31068_clearDisplay();

    ULP_AIP31068_sendCommand(AIP31068_DISP_CTRL, AIP31068_DISP);

    ULP_AIP31068_setDispAddr(ROW_1);
    ULP_AIP31068_print("hello world!");

    ULP_AIP31068_setDispAddr(ROW_2);
    ULP_AIP31068_print("1234567890");

    while(1) {
        ulp_riscv_delay_cycles(ULP_RISCV_CYCLES_PER_MS * 10);
    }
    /* ulp_riscv_halt() is called automatically when main exits */
    return 0;
}
