/**
 * @file      hardware_config.h
 * @brief     Configuración de hardware para placas LilyGo LoRa
 *
 * Este archivo contiene todas las definiciones de pines y configuraciones
 * específicas para cada placa LilyGo LoRa soportada.
 *
 * @author    Proyecto IoT de Bajo Consumo
 * @version   1.0
 * @date      2025
 */

#ifndef HARDWARE_CONFIG_H
#define HARDWARE_CONFIG_H

#include <Arduino.h>

// =============================================================================
// CONFIGURACIÓN DE PLACAS LILYGO LORA
// =============================================================================

// Las definiciones de placa se hacen en utilities.h
// Este archivo solo contiene las configuraciones específicas de hardware

#ifdef T3_V1_3_SX1276

#define USING_SX1276

// I2C para pantalla y sensores
#define I2C_SDA 21
#define I2C_SCL 22
#define OLED_RST UNUSED_PIN

// Radio LoRa
#define RADIO_SCLK_PIN 5
#define RADIO_MISO_PIN 19
#define RADIO_MOSI_PIN 27
#define RADIO_CS_PIN 18
#define RADIO_DIO0_PIN 26
#define RADIO_RST_PIN 14
#define RADIO_DIO1_PIN 33
#define RADIO_DIO2_PIN 32

// Energía y batería
#define ADC_PIN 35
#define HAS_PMU
#define PMU_IRQ 35
#define PMU_WIRE_PORT Wire

// Pantalla
#define HAS_DISPLAY
#define DISPLAY_MODEL_SSD_LIB SSD1306Wire
#define DISPLAY_MODEL U8G2_SSD1306_128X64_NONAME_F_HW_I2C

// LED
#define BOARD_LED 25
#define LED_ON LOW

// Información de placa
#ifndef BOARD_VARIANT_NAME // Solo definir si no está ya definido
#define BOARD_VARIANT_NAME "T3 V1.3 SX1276"
#endif

// Constantes de batería
#define BAT_ADC_PULLUP_RES (100000.0)
#define BAT_ADC_PULLDOWN_RES (100000.0)
#define BAT_MAX_VOLTAGE (4.2)
#define BAT_VOL_COMPENSATION (0.0)

// T3 V1.3 con SX1278
#elif defined(T3_V1_3_SX1278)

#define USING_SX1278

#define I2C_SDA 21
#define I2C_SCL 22
#define OLED_RST UNUSED_PIN

#define RADIO_SCLK_PIN 5
#define RADIO_MISO_PIN 19
#define RADIO_MOSI_PIN 27
#define RADIO_CS_PIN 18
#define RADIO_DIO0_PIN 26
#define RADIO_RST_PIN 14
#define RADIO_DIO1_PIN 33
#define RADIO_DIO2_PIN 32

#define ADC_PIN 35
#define HAS_PMU
#define PMU_IRQ 35
#define PMU_WIRE_PORT Wire

#define HAS_DISPLAY
#define DISPLAY_MODEL_SSD_LIB SSD1306Wire
#define DISPLAY_MODEL U8G2_SSD1306_128X64_NONAME_F_HW_I2C

#define BOARD_LED 25
#define LED_ON LOW

#define BOARD_VARIANT_NAME "T3 V1.3 SX1278"

#define BAT_ADC_PULLUP_RES (100000.0)
#define BAT_ADC_PULLDOWN_RES (100000.0)
#define BAT_MAX_VOLTAGE (4.2)
#define BAT_VOL_COMPENSATION (0.0)

// T3 V1.6 con SX1276
#elif defined(T3_V1_6_SX1276)

#define USING_SX1276

#define I2C_SDA 21
#define I2C_SCL 22
#define OLED_RST UNUSED_PIN

#define RADIO_SCLK_PIN 5
#define RADIO_MISO_PIN 19
#define RADIO_MOSI_PIN 27
#define RADIO_CS_PIN 18
#define RADIO_DIO0_PIN 26
#define RADIO_RST_PIN 23
#define RADIO_DIO1_PIN 33
#define RADIO_DIO2_PIN 32

#define SDCARD_MOSI 15
#define SDCARD_MISO 2
#define SDCARD_SCLK 14
#define SDCARD_CS 13

#define BOARD_LED 25
#define LED_ON HIGH

#define ADC_PIN 34

#define HAS_SDCARD
#define HAS_DISPLAY
#define HAS_PMU
#define PMU_IRQ 35
#define PMU_WIRE_PORT Wire
#define BOARD_VARIANT_NAME "T3 V1.6 SX1276"

#define DISPLAY_MODEL_SSD_LIB SSD1306Wire
#define DISPLAY_MODEL U8G2_SSD1306_128X64_NONAME_F_HW_I2C

#define BAT_ADC_PULLUP_RES (100000.0)
#define BAT_ADC_PULLDOWN_RES (100000.0)
#define BAT_MAX_VOLTAGE (4.1)
#define BAT_VOL_COMPENSATION (0.2)

// T-Beam con SX1276
#elif defined(T_BEAM_SX1276)

#define USING_SX1276

#define GPS_RX_PIN 34
#define GPS_TX_PIN 12
#define BUTTON_PIN 38
#define BUTTON_PIN_MASK GPIO_SEL_38

#define I2C_SDA 21
#define I2C_SCL 22
#define PMU_IRQ 35

#define RADIO_SCLK_PIN 5
#define RADIO_MISO_PIN 19
#define RADIO_MOSI_PIN 27
#define RADIO_CS_PIN 18
#define RADIO_DIO0_PIN 26
#define RADIO_RST_PIN 23
#define RADIO_DIO1_PIN 33
#define RADIO_DIO2_PIN 32

#define BOARD_LED 4
#define LED_ON LOW

#define GPS_BAUD_RATE 9600
#define HAS_GPS
#define HAS_DISPLAY
#define HAS_PMU

#define PMU_WIRE_PORT Wire
#define BOARD_VARIANT_NAME "T-Beam SX1276"
#define DISPLAY_MODEL_SSD_LIB SSD1306Wire
#define DISPLAY_MODEL U8G2_SSD1306_128X64_NONAME_F_HW_I2C

// Otras placas pueden añadirse aquí siguiendo el mismo patrón...

#else
#error                                                                         \
    "Debes definir una placa LilyGo LoRa en config.h (ej: #define T3_V1_3_SX1276)"
#endif

// =============================================================================
// DEFINICIONES COMUNES A TODAS LAS PLACAS
// =============================================================================

#define UNUSED_PIN (0)

// =============================================================================
// PINES DEL SENSOR DE PROXIMIDAD JSN-SR04T
// =============================================================================
// Basado en el proyecto cooperjosee.
// ¡ATENCIÓN! En la placa T3 V1.6, los pines 15 y 13 coinciden con SPI para SD.
// Si se utliza SD, estos pines deberán ser cambiados.
#define SENSOR_TRIG_PIN 13 // Pin para 'Trig' - JSN-SR04T
#define SENSOR_ECHO_PIN 12 // Pin para 'Echo' - JSN-SR04T
#define SENSOR_VSLEEP_PIN                                                      \
  14 // Pin para controlar el transistor de alimentación (NPN)
#define SENSOR_VOUT_PIN                                                        \
  0 // Pin extra que se mantiene en HIGH (usado en cooperjosee)

// Tipos de radio soportados
#if defined(USING_SX1262)
#define RADIO_TYPE_STR "SX1262"
#elif defined(USING_SX1276)
#define RADIO_TYPE_STR "SX1276"
#elif defined(USING_SX1278)
#define RADIO_TYPE_STR "SX1278"
#elif defined(USING_LR1121)
#define RADIO_TYPE_STR "LR1121"
#elif defined(USING_SX1280)
#define RADIO_TYPE_STR "SX1280"
#endif

#endif // HARDWARE_CONFIG_H