/* ***********************************************************************************************************************************************************
TTGO LoRa32 V2.1 for The Things Network

Copyright (C) 2019 by Roel van Wanrooy (www.connectix.nl)

This code requires LMIC library by Matthijs Kooijman: https://github.com/matthijskooijman/arduino-lmic

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.
*********************************************************************************************************************************************************** */
#pragma once

#include <Arduino.h>
#include <lmic.h>
void ttn_register(void (*callback)(uint8_t message));

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Configuration
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// If using a single-channel gateway, uncomment this next option and set to your gateway's channel
//#define SINGLE_CHANNEL_GATEWAY  0

// If you are having difficulty sending messages to TTN after the first successful send, uncomment the next option and experiment with values (~ 1 - 5)
#define CLOCK_ERROR             1

#define DEBUG_PORT              Serial      // Serial debug port
#define SERIAL_BAUD             115200      // Serial debug baud rate
#define ENABLE_DEBUG            0           // Serial debug on/off
#define SLEEP_BETWEEN_MESSAGES  1           // Do sleep between messages
#define SEND_INTERVAL_RELAXED   60000     // Sleep for these many millis
#define SEND_INTERVAL_INTENSIVE 30000
#define LORAWAN_PORT            1           // Port the messages will be sent to
#define LORAWAN_CONFIRMED_EVERY 0           // Send confirmed message every these many messages (0 means never)
#define LORAWAN_SF              DR_SF7      // Spreading factor
#define LORAWAN_ADR             1           // Enable ADR
#define TARGET_ARRAY_LENGTH     5           // Tamaño del Buffer Circular

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// DEBUG
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef DEBUG_PORT
#define DEBUG_MSG(...) DEBUG_PORT.printf( __VA_ARGS__ )
#else
#define DEBUG_MSG(...)
#endif

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Custom messages
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
#define EV_QUEUED       100
#define EV_PENDING      101
#define EV_ACK          102
#define EV_RESPONSE     103

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Sensores
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
#define trigPin         13                  // Defino pin para 'Trig' - AJ-SR04M
#define echoPin         12                  // Defino pin para 'Echo' - AJ-SR04M
#define MAX_DISTANCE    400                 // En 'MAX_DISTANCE' guardaré de forma inmutable la máxima distancia a la que funciona el sensor, unos 400 a 500 cm
#define MIN_DISTANCE    23                  // En 'MIN_DISTANCE' guardaré de forma inmutable la mínima distancia a la que funciona el sensor, por debajo de 24 cm, siempre seran 24 cm
#define VBATPIN         35
                  // Defino pin 'vbatPin' - Voltaje
#define VOUT_PIN        0                   // Defino un pin que configuraré a siempre 'HIGH' para alimentar el sensor y que lo desconecte tras el deep sleep

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// LoRa SPI
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
#define SCK_GPIO        5
#define MISO_GPIO       19
#define MOSI_GPIO       27
#define NSS_GPIO        18
#define RESET_GPIO      23
#define DIO0_GPIO       26
#define DIO1_GPIO       33
#define DIO2_GPIO       32

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// AXP192 (Rev1-specific options)
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
#define LORA_POWER_CTRL_CH    2
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Calcular nivel de batería
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
#define V_REF 3.3