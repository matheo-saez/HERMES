#ifndef PINS_H
#define PINS_H

constexpr int STATE = 1;
constexpr int LED_R = 2;
constexpr int LED_G = 3;
constexpr int LED_B = 4;
constexpr int BUZZER = 5;
constexpr int MOSI = 6;
constexpr int MISO = 7;
constexpr int SCK = 8;
constexpr int TX_CH340C = 14;
constexpr int RX_CH340C = 15;
constexpr int TX_E220_900T22D = 16;
constexpr int RX_E220_900T22D = 17;
constexpr int TX_HM10 = 18;
constexpr int RX_HM10 = 19;
constexpr int TX_L80 = 20;
constexpr int RX_L80 = 21;
constexpr int I2C_SCL = 22;
constexpr int I2C_SDA = 23;
constexpr int PYRO_1 = 24;
constexpr int PYRO_2 = 25;
constexpr int PYRO_3 = 26;
constexpr int PYRO_4 = 27;
/*
28, 29, 33 are reserved for future use.
*/
constexpr int EN = 34;
constexpr int PPS = 35;
constexpr int SD_CS = 36;
constexpr int FLASH_CS = 37;
constexpr int AUX = 38;
constexpr int M1 = 39;
constexpr int M0 = 40;
#endif