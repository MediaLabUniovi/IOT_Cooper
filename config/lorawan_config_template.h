/**
 * @file      lorawan_config_template.h
 * @brief     Plantilla de configuración de claves LoRaWAN para múltiples
 * sensores BME280
 *
 * Este archivo es una PLANTILLA para configurar las claves LoRaWAN de múltiples
 * sensores. El proyecto está optimizado para MÚLTIPLES NODOS, cada uno con un
 * sensor BME280 (Temperatura, Humedad y Presión atmosférica).
 *
 * ESTRUCTURA MULTISENSOR:
 * =======================
 * Este proyecto soporta hasta 5 sensores/placas diferentes (SENSOR_ID 1-5).
 * Cada sensor tiene su propia placa LilyGo T3 v1.6.1 con BME280 integrado.
 * Cada sensor tiene sus propias credenciales LoRaWAN registradas en TTN.
 *
 * VENTAJAS DEL DISEÑO MULTISENSOR:
 * - No necesitas cambiar código al cargar en diferentes placas
 * - Solo cambia el define SENSOR_ID según la placa que uses
 * - Cada placa puede estar en una ubicación diferente
 * - Todas reportan a la misma aplicación en TTN
 *
 * INSTRUCCIONES DE SETUP:
 * =======================
 * 1. Copia este archivo como lorawan_config.h en el directorio config/
 * 2. Para cada placa, crea una aplicación/dispositivo en TTN Console
 * 3. Obtén las claves APPEUI, DEVEUI y APPKEY para cada sensor
 * 4. Reemplaza los valores en las secciones correspondientes (SENSOR_ID 1-5)
 * 5. En config/config.h, establece el SENSOR_ID activo
 * 6. El archivo lorawan_config.h será ignorado por git (está en .gitignore)
 *
 * NOTA SOBRE LOS FORMATOS:
 * ========================
 * - APPEUI y DEVEUI: Usa formato LSB (Little-Endian) desde TTN Console
 * - APPKEY: Usa formato MSB (Big-Endian) desde TTN Console
 *   Si ves valores como "12 34 56 78" en TTN Console:
 *   - Para LSB: {0x78, 0x56, 0x34, 0x12, ...}  (invierte el orden)
 *   - Para MSB: {0x12, 0x34, 0x56, 0x78, ...}  (mantén el orden)
 *
 * SENSOR BME280:
 * ==============
 * Cada nodo monta un sensor BME280 que proporciona:
 * - Temperatura: -40 a +85°C con precisión de 0.01°C
 * - Humedad: 0 a 100%
 * - Presión: 300 a 1100 hPa
 *
 * Conexión I2C:
 * - SDA: GPIO 17
 * - SCL: GPIO 18
 * - Dirección I2C: 0x76 o 0x77 (configurable en el sensor)
 *
 * @author    Proyecto IoT de Bajo Consumo
 * @version   2.0
 * @date      2026
 */

#ifndef LORAWAN_CONFIG_H
#define LORAWAN_CONFIG_H

#include <Arduino.h>
#include <lmic.h>

// ==================== SELECCIÓN DE SENSOR ====================
// Descomenta UNA de las siguientes líneas según el sensor/placa que uses:
// #define SENSOR_ID 1  // Nodo 1
// #define SENSOR_ID 2  // Nodo 2
// #define SENSOR_ID 3  // Nodo 3
// #define SENSOR_ID 4  // Nodo 4
#define SENSOR_ID 5 // Nodo 5 (por defecto)

// ==================== CLAVES LoRaWAN OTAA ====================
// Las claves se seleccionan automáticamente según SENSOR_ID

#if SENSOR_ID == 1
// ========== SENSOR 1 ==========
// TODO: Reemplaza estos valores con las claves reales de TTN para el Sensor 1

// Application EUI (AppEUI) - 8 bytes en formato LSB
static const u1_t PROGMEM APPEUI[8] = {
    0x00, 0x00, 0x00, 0x00, // TODO: Reemplaza con valores reales
    0x00, 0x00, 0x00, 0x00};

// Device EUI (DevEUI) - 8 bytes en formato LSB
static const u1_t PROGMEM DEVEUI[8] = {
    0xCC, 0xFC, 0x06, 0xD0, // TODO: Reemplaza con valores reales
    0x7E, 0xD5, 0xB3, 0x70};

// Application Key (AppKey) - 16 bytes en formato MSB
static const u1_t PROGMEM APPKEY[16] = {
    0x48, 0x42, 0xBB, 0x8A,
    0x89, 0xBE, 0xF2, 0x12, // TODO: Reemplaza con valores reales
    0xDD, 0x76, 0x80, 0x51,
    0x26, 0x34, 0xC8, 0x8E};

#elif SENSOR_ID == 2
// ========== SENSOR 2 ==========
// TODO: Reemplaza estos valores con las claves reales de TTN para el Sensor 2

// Application EUI (AppEUI) - 8 bytes en formato LSB
static const u1_t PROGMEM APPEUI[8] = {0xAD, 0x93, 0x27, 0xF7,
                                       0x27, 0x96, 0x2A, 0xFF};

// Device EUI (DevEUI) - 8 bytes en formato LSB
static const u1_t PROGMEM DEVEUI[8] = {0xC1, 0x02, 0x99, 0x64,
                                       0x9F, 0xA5, 0x2F, 0x1C};

// Application Key (AppKey) - 16 bytes en formato MSB
static const u1_t PROGMEM APPKEY[16] = {0xE8, 0x34, 0xA5, 0x7E, 0x71, 0x0B,
                                        0x47, 0x00, 0xF5, 0xF1, 0xB4, 0x56,
                                        0x85, 0x33, 0x34, 0x80};

#elif SENSOR_ID == 3
// ========== SENSOR 3 ==========
// TODO: Reemplaza estos valores con las claves reales de TTN para el Sensor 3

// Application EUI (AppEUI) - 8 bytes en formato LSB
static const u1_t PROGMEM APPEUI[8] = {
    0x00, 0x00, 0x00, 0x00, // TODO: Reemplaza con valores reales
    0x00, 0x00, 0x00, 0x00};

// Device EUI (DevEUI) - 8 bytes en formato LSB
static const u1_t PROGMEM DEVEUI[8] = {
    0xCA, 0xFC, 0x06, 0xD0, // TODO: Reemplaza con valores reales
    0x7E, 0xD5, 0xB3, 0x70};

// Application Key (AppKey) - 16 bytes en formato MSB
static const u1_t PROGMEM APPKEY[16] = {
    0x72, 0x7F, 0x18, 0xAB,
    0x5C, 0x29, 0xC4, 0xB6, // TODO: Reemplaza con valores reales
    0x14, 0xD8, 0x1E, 0xC7,
    0xC1, 0xE1, 0xF1, 0x89};

#elif SENSOR_ID == 4
// ========== SENSOR 4 ==========
// TODO: Reemplaza estos valores con las claves reales de TTN para el Sensor 4

// Application EUI (AppEUI) - 8 bytes en formato LSB
static const u1_t PROGMEM APPEUI[8] = {
    0x00, 0x00, 0x00, 0x00, // TODO: Reemplaza con valores reales
    0x00, 0x00, 0x00, 0x00};

// Device EUI (DevEUI) - 8 bytes en formato LSB
static const u1_t PROGMEM DEVEUI[8] = {
    0xCB, 0xFC, 0x06, 0xD0, // TODO: Reemplaza con valores reales
    0x7E, 0xD5, 0xB3, 0x70};

// Application Key (AppKey) - 16 bytes en formato MSB
static const u1_t PROGMEM APPKEY[16] = {
    0x20, 0x74, 0x13, 0x08,
    0x90, 0xA2, 0x14, 0x27, // TODO: Reemplaza con valores reales
    0xDD, 0x0A, 0x6B, 0x04,
    0x3F, 0x87, 0x7B, 0xD2};

#elif SENSOR_ID == 5
// ========== SENSOR 5 (DEFAULT) ==========
// TODO: Reemplaza estos valores con las claves reales de TTN para el Sensor 5

// Application EUI (AppEUI) - 8 bytes en formato LSB
static const u1_t PROGMEM APPEUI[8] = {
    0x00, 0x00, 0x00, 0x00, // TODO: Reemplaza con valores reales
    0x00, 0x00, 0x00, 0x00};

// Device EUI (DevEUI) - 8 bytes en formato LSB
static const u1_t PROGMEM DEVEUI[8] = {
    0xD3, 0x46, 0x07, 0xD0, // TODO: Reemplaza con valores reales
    0x7E, 0xD5, 0xB3, 0x70};

// Application Key (AppKey) - 16 bytes en formato MSB
static const u1_t PROGMEM APPKEY[16] = {
    0x84, 0xF9, 0x6D, 0x76,
    0x0E, 0x90, 0x8F, 0xC8, // TODO: Reemplaza con valores reales
    0x9F, 0x81, 0x28, 0x24,
    0xBE, 0x50, 0x46, 0x9E};

#else
#error "SENSOR_ID debe estar definido como 1, 2, 3, 4 o 5"
#endif

#endif // LORAWAN_CONFIG_H