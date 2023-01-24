#ifndef ULP_AIP31068_H
#define ULP_AIP31068_H

#define AIP31068_ADDRESS 0x7c

#define AIP31068_CTRL 0x80
#define AIP31068_RS 0x40

#define AIP31068_CLR_DISP 0x01

#define AIP31068_RETURN_HOME 0x02

#define AIP31068_ENTRY_MODE_SET 0x04
#define AIP31068_ID 0x02
#define AIP31068_SH 0x01

#define AIP31068_DISP_CTRL 0x08
#define AIP31068_DISP 0x04
#define AIP31068_CURSOR 0x02
#define AIP31068_CURSOR_BLINK 0x01

#define AIP31068_CURDISP_SHIFT 0x10
#define AIP31068_SC 0x08
#define AIP31068_RL 0x04

#define AIP31068_FUNC_SET 0x20
#define AIP31068_LINE_NUM 0x08
#define AIP31068_FONT_TYPE 0x04

#define AIP31068_SET_CGRAM_ADDR 0x40

#define AIP31068_SET_DDRAM_ADDR 0x80

#define ROW_1 0x00
#define ROW_2 0x40

void ULP_AIP31068_init();
void ULP_AIP31068_clearDisplay();
void ULP_AIP31068_print(const char* a_str);
void ULP_AIP31068_sendCommand(uint8_t a_cmd, uint8_t a_data);
void ULP_AIP31068_setDispAddr(uint8_t a_addr);
void ULP_AIP31068_writeData(uint8_t a_dt);

#endif