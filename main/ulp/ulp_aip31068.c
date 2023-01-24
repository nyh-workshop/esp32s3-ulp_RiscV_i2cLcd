#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "ulp_i2c_sw.h"
#include "ulp_aip31068.h"

void ULP_AIP31068_init()
{
    uint8_t data[2] = {0 | AIP31068_CTRL, 0 | AIP31068_FUNC_SET | AIP31068_LINE_NUM | AIP31068_FONT_TYPE};

    I2C_transmit(AIP31068_ADDRESS, data, sizeof(data));
}

void ULP_AIP31068_clearDisplay()
{
    uint8_t data[2] = {0 | AIP31068_CTRL, 0 | AIP31068_CLR_DISP};

    I2C_transmit(AIP31068_ADDRESS, data, sizeof(data));

    ulp_riscv_delay_cycles(ULP_RISCV_CYCLES_PER_US * 50);
}

void ULP_AIP31068_sendCommand(uint8_t a_cmd, uint8_t a_dt)
{
    uint8_t data[2] = {AIP31068_CTRL, 0 | a_cmd | a_dt};

    I2C_transmit(AIP31068_ADDRESS, data, sizeof(data));

    ulp_riscv_delay_cycles(ULP_RISCV_CYCLES_PER_US * 50);
}

void ULP_AIP31068_writeData(uint8_t a_dt)
{
    uint8_t data[2] = {AIP31068_RS, a_dt};

    I2C_transmit(AIP31068_ADDRESS, data, sizeof(data));

    ulp_riscv_delay_cycles(ULP_RISCV_CYCLES_PER_US * 50);
}

void ULP_AIP31068_setDispAddr(uint8_t a_addr)
{
    uint8_t data[2] = {AIP31068_CTRL, a_addr | AIP31068_SET_DDRAM_ADDR};

    I2C_transmit(AIP31068_ADDRESS, data, sizeof(data));

    ulp_riscv_delay_cycles(ULP_RISCV_CYCLES_PER_US * 50);
}

void ULP_AIP31068_print(const char* a_str)
{
    while(*a_str)
    {
        ULP_AIP31068_writeData(*a_str++);
    }
}
