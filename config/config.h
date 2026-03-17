#ifndef CONFIG_H
#define CONFIG_H

// =============================================================================
// CONFIGURACIÓN DE HARDWARE (PLACA)
// =============================================================================

// Selección de placa LilyGo LoRa
// Descomenta solo UNA de las siguientes líneas según tu placa

// #define T3_V1_3_SX1276    // T3 V1.3 con SX1276
// #define T3_V1_3_SX1278    // T3 V1.3 con SX1278
#define T3_V1_6_SX1276    // T3 V1.6 con SX1276
// #define T3_V1_6_SX1278    // T3 V1.6 con SX1278
// #define T_BEAM_SX1276     // T-Beam con SX1276
// Otras placas disponibles en hardware_config.h

#include <Arduino.h>
#include "hardware_config.h"  // Configuración específica del hardware

// Incluir configuración LoRaWAN (con las claves)
#include <lmic.h>
#include "lorawan_config.h"

// =============================================================================
// CONFIGURACIÓN DE SENSORES - PROXIMIDAD (JSN-SR04T)
// =============================================================================

// Sensor de proximidad ultrasónico
#define ENABLE_SENSOR_PROXIMITY

// =============================================================================
// ESTRUCTURAS DE DATOS PARA SENSORES (MODIFICABLES POR EL USUARIO)
// =============================================================================
// Estas estructuras pueden ser modificadas al añadir nuevos sensores

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Estructura que contiene todas las lecturas del sensor
 * @note MODIFICA esta estructura al añadir nuevos tipos de datos de sensores
 */
typedef struct {
    int distance;         /**< Distancia al agua en cm */
    float battery;        /**< Voltaje de batería en V */
    bool valid;           /**< true si todas las lecturas son válidas */
} sensor_data_t;

/**
 * @brief Estructura para configuración del payload LoRaWAN
 * @note MODIFICA esta estructura si necesitas cambiar el formato del payload
 */
typedef struct {
    uint8_t* buffer;      /**< Buffer donde escribir el payload */
    uint8_t max_size;     /**< Tamaño máximo del buffer */
    uint8_t written;      /**< Bytes realmente escritos */
    // Añade aquí campos adicionales para configuración de payload
    // bool include_timestamp;
    // uint8_t compression_level;
} payload_config_t;

// =============================================================================
// INCLUSIÓN AUTOMÁTICA DEL SENSOR DE PROXIMIDAD
// =============================================================================

#ifdef ENABLE_SENSOR_PROXIMITY
#include "sensor.h"
#include "sensor/sensor_proximity.h"
#endif

// =============================================================================
// CONFIGURACIÓN DE PANTALLA OLED
// =============================================================================

#define ENABLE_DISPLAY false         // true: pantalla activa, false: apagada para máximo ahorro
#define SHOW_ACTIVITY_INDICATORS false // true: mostrar indicadores permanentes, false: solo mensajes

// Duraciones de mensajes (ms)
#define MESSAGE_DURATION_SUCCESS 5000
#define MESSAGE_DURATION_ERROR 3000
#define MESSAGE_DURATION_WARNING 4000
#define MESSAGE_DURATION_INFO 3000
#define MESSAGE_DURATION_SLEEP 3000

// =============================================================================
// CONFIGURACIÓN LoRaWAN
// =============================================================================

// Región LoRaWAN
#define LORAWAN_REGION LMIC_region_t::LMIC_REGION_eu868

// Parámetros de transmisión
#define TX_POWER_DBM 17              // Potencia de transmisión (máx 17 para evitar interferencias)
#define BACKOFF_INITIAL_SECONDS 300  // Backoff inicial exponencial

// =============================================================================
// CLAVES LoRaWAN OTAA (¡MODIFICA EN lorawan_config.h!)
// =============================================================================
// Las claves LoRaWAN se definen en lorawan_config.h para mantenerlas separadas
// de la configuración general (por seguridad y organización)

// =============================================================================
// CONFIGURACIÓN DE TIMING Y ENERGÍA
// =============================================================================

#define SEND_INTERVAL_SECONDS 300    // Intervalo entre envíos (mínimo 60s para evitar sobrecarga)
#define WATCHDOG_TIMEOUT_MINUTES 5   // Timeout del watchdog en minutos

// Energía y batería
#define ENABLE_SOLAR_CHARGING true   // Habilitar carga solar
#define BATTERY_LOW_THRESHOLD 20     // Umbral de batería baja (%)
#define BATTERY_AS_PERCENTAGE        // Descomentar para enviar batería como porcentaje (1 byte)
                                     // Comentar para enviar como voltaje (2 bytes)

// =============================================================================
// CONFIGURACIÓN DE DEPURACIÓN Y LOGGING
// =============================================================================

#define ENABLE_SERIAL_LOGS true      // Habilitar logs por Serial
#define LOG_LEVEL 1                  // 0: ninguno, 1: básico, 2: detallado
#define SHOW_TTN_DECODER true  // true: mostrar decoder TTN por Serial al iniciar

// =============================================================================
// CONFIGURACIÓN DE PAYLOAD Y DATOS
// =============================================================================

#define SENSOR_HAS_DISTANCE 1

// Determinación automática de capacidades del sistema
#if defined(ENABLE_SENSOR_PROXIMITY) && SENSOR_HAS_DISTANCE
#define SYSTEM_HAS_DISTANCE 1
#else
#define SYSTEM_HAS_DISTANCE 0
#endif

// Cálculo del tamaño del payload usando directivas del preprocesador
#if defined(ENABLE_SENSOR_PROXIMITY)
#define PAYLOAD_SIZE_DISTANCE 2
#else
#define PAYLOAD_SIZE_DISTANCE 0
#endif

// Tamaño de batería según configuración
#ifdef BATTERY_AS_PERCENTAGE
#define PAYLOAD_SIZE_BATTERY 1  // 1 byte para porcentaje (0-100)
#else
#define PAYLOAD_SIZE_BATTERY 2  // 2 bytes para voltaje (* 100)
#endif

#define PAYLOAD_SIZE_BYTES ( \
    PAYLOAD_SIZE_DISTANCE + \
    PAYLOAD_SIZE_BATTERY \
)

// Valores de error para lecturas fallidas
#define SENSOR_ERROR_DISTANCE -1
#define SENSOR_ERROR_BATTERY -1.0f



#endif // CONFIG_H