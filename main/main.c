/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include "esp_sleep.h"
#include "ulp_riscv.h"
#include "ulp_main.h"

#include "driver/gpio.h"
#include "driver/rtc_io.h"

#include "soc/soc.h"
#include "soc/gpio_periph.h"
#include "hal/gpio_hal.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern const uint8_t ulp_main_bin_start[] asm("_binary_ulp_main_bin_start");
extern const uint8_t ulp_main_bin_end[]   asm("_binary_ulp_main_bin_end");

static void init_ulp_program(void);

void app_main(void)
{
    init_ulp_program();

    printf("Hello World!\n");

    // Note:
    // For Cytron Maker Feather AIOT S3 users, please enable GPIO11 to use the diagnostic LEDs!
    // 
    esp_rom_gpio_pad_select_gpio(GPIO_NUM_11);
    gpio_set_direction(GPIO_NUM_11, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_11, 1);

    // GPIO No. 4 and 7 are used for Software I2C.
    // For Cytron Maker Feather AIOT S3 users, you can connect the Grove I2C LCD to the Maker Port (A4 and A5):
    esp_rom_gpio_pad_select_gpio(GPIO_NUM_4);
    esp_rom_gpio_pad_select_gpio(GPIO_NUM_7);
    
    esp_rom_gpio_pad_select_gpio(GPIO_NUM_21);
    esp_rom_gpio_pad_select_gpio(GPIO_NUM_39);    

    gpio_set_direction(GPIO_NUM_39, GPIO_MODE_OUTPUT);    
    
    gpio_set_level(GPIO_NUM_39, 0);
  
    while (1)
    {
        gpio_set_level(GPIO_NUM_39, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_NUM_39, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

static void init_ulp_program(void)
{
    esp_err_t err = ulp_riscv_load_binary(ulp_main_bin_start, (ulp_main_bin_end - ulp_main_bin_start));
    ESP_ERROR_CHECK(err);

    rtc_gpio_init(GPIO_NUM_4);
    rtc_gpio_set_direction(GPIO_NUM_4, RTC_GPIO_MODE_INPUT_OUTPUT_OD);
    rtc_gpio_pulldown_dis(GPIO_NUM_4);
    rtc_gpio_pullup_en(GPIO_NUM_4);

    rtc_gpio_init(GPIO_NUM_7);
    rtc_gpio_set_direction(GPIO_NUM_7, RTC_GPIO_MODE_INPUT_OUTPUT_OD);
    rtc_gpio_pulldown_dis(GPIO_NUM_7);
    rtc_gpio_pullup_en(GPIO_NUM_7);
    
    /* Start the program */
    err = ulp_riscv_run();
    ESP_ERROR_CHECK(err);
}