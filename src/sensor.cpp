/**
 * @file      sensor.cpp
 * @brief     Implementación del sensor BME280
 *
 * Este archivo implementa el sistema de lectura y empaquetado del sensor BME280.
 *
 * @author    Proyecto IoT de Bajo Consumo
 * @version   1.0
 * @date      2025
 */

#include "../config/config.h"  // Configuración unificada del proyecto
#include "sensor_interface.h"  // Interfaz genérica de sensores
#include "LoRaBoards.h"  // Para readBatteryVoltage y batteryPercentFromVoltage

// Declaración externa para funciones de carga solar
extern bool isSolarChargingBattery();

// ============================================================================
// FUNCIONES PARA GESTIONAR EL SENSOR BME280
// ============================================================================

/**
 * @brief Inicializa el sensor
 * @return true si el sensor se inicializó correctamente
 */
bool sensors_init_all(void) {
#ifdef ENABLE_SENSOR_PROXIMITY
    return sensor_proximity_init();
#else
    return false;
#endif
}

/**
 * @brief Verifica si el sensor está disponible
 * @return true si el sensor está operativo
 */
bool sensors_is_any_available(void) {
#ifdef ENABLE_SENSOR_PROXIMITY
    return sensor_proximity_is_available();
#else
    return false;
#endif
}

/**
 * @brief Intenta reinicializar el sensor
 * @return true si el sensor se reinicializó correctamente
 */
bool sensors_retry_init_all(void) {
#ifdef ENABLE_SENSOR_PROXIMITY
    return sensor_proximity_retry_init();
#else
    return false;
#endif
}

/**
 * @brief Lee datos del sensor
 * @param data Puntero a estructura donde almacenar los datos
 * @return true si se pudieron leer datos del sensor
 */
bool sensors_read_all(sensor_data_t* data) {
    if (!data) return false;

    // Inicializar con valores de error
    data->distance = SENSOR_ERROR_DISTANCE;
    data->battery = readBatteryVoltage();
    data->valid = false;

    bool any_data = false;

    // Leer del sensor JSN-SR04T
#ifdef ENABLE_SENSOR_PROXIMITY
    {
        if (sensor_proximity_read_all(data)) {
            if (data->distance != SENSOR_ERROR_DISTANCE) {
                any_data = true;
            }
        }
    }
#endif

    data->valid = any_data;
    return any_data;
}

/**
 * @brief Construye el payload con datos del sensor
 * @param config Configuración del payload
 * @return Número de bytes escritos
 */
uint8_t sensors_get_payload(payload_config_t* config) {
    if (!config || config->max_size < PAYLOAD_SIZE_BYTES) return 0;

    sensor_data_t data;
    bool sensor_ok = sensors_read_all(&data);

    if (!sensor_ok) {
        // Si no hay datos válidos, intentar reinicializar
        sensors_retry_init_all();
        // Usar datos de error
        data.distance = SENSOR_ERROR_DISTANCE;
    }

    uint8_t offset = 0;

    // Distancia (si está disponible en el sistema)
    if (SYSTEM_HAS_DISTANCE) {
        // Formato cooperjosee: Little Endian (lowByte, highByte)
        config->buffer[offset++] = (data.distance) & 0xFF;         // lowByte
        config->buffer[offset++] = ((data.distance) >> 8) & 0xFF;  // highByte
    }

    // Batería (siempre incluida)
#ifdef BATTERY_AS_PERCENTAGE
    // Enviar como porcentaje (1 byte)
    uint8_t batt_percent = batteryPercentFromVoltage(data.battery);
    Serial.printf("DEBUG: Battery voltage %.2f V = %u%%\n", data.battery, batt_percent);
    config->buffer[offset++] = batt_percent;
#else
    // Enviar como voltaje (2 bytes)
    uint16_t batt_int = (uint16_t)(data.battery * 100);
    Serial.printf("DEBUG: Packing battery voltage %.2f V as %u (0x%04X)\n", data.battery, batt_int, batt_int);
    config->buffer[offset++] = batt_int >> 8;
    config->buffer[offset++] = batt_int & 0xFF;
#endif

    config->written = offset;
    return offset;
}

/**
 * @brief Obtiene el nombre del sensor activo
 * @return Cadena con el nombre del sensor
 */
const char* sensors_get_name(void) {
#ifdef ENABLE_SENSOR_PROXIMITY
    return "JSN-SR04T";
#else
    return "NINGUNO";
#endif
}

/**
 * @brief Fuerza el estado del sensor para testing
 * @param available true para simular disponible, false para simular fallo
 */
void sensors_set_available_for_testing(bool available) {
#ifdef ENABLE_SENSOR_PROXIMITY
    sensor_proximity_set_available_for_testing(available);
#endif
}

// ============================================================================
// FUNCIONES DE COMPATIBILIDAD HACIA ATRÁS
// ============================================================================

/**
 * Funciones legacy para mantener compatibilidad con el código existente
 * Estas funciones llaman a la nueva interfaz multisensor
 */

bool initSensor() {
    return sensors_init_all();
}

bool isSensorAvailable() {
    return sensors_is_any_available();
}

bool retrySensorInit() {
    return sensors_retry_init_all();
}

void setSensorAvailableForTesting(bool available) {
    sensors_set_available_for_testing(available);
}

uint8_t getSensorPayload(uint8_t* payload, uint8_t maxSize) {
    payload_config_t config = {payload, maxSize, 0};
    return sensors_get_payload(&config);
}

bool getSensorDataForDisplay(float& distance, float& battery) {
    sensor_data_t data;
    bool ok = sensors_read_all(&data);

    distance = data.distance; 
    battery = data.battery;

    return ok && data.valid;
}