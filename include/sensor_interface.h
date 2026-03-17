/**
 * @file      sensor_interface.h
 * @brief     Interfaz genérica para sensores
 *
 * Esta interfaz define las funciones que debe implementar cada sensor,
 * permitiendo cambiar de sensor sin modificar el código principal.
 *
 * Las estructuras de datos están definidas en config.h para facilitar
 * la personalización por parte del usuario.
 *
 * @author    Proyecto IoT de Bajo Consumo
 * @version   1.0
 * @date      2025
 */

#ifndef SENSOR_INTERFACE_H
#define SENSOR_INTERFACE_H

#include <stdint.h>
#include <stdbool.h>

// Las estructuras de datos están definidas en config.h
// #include "../config/config.h"  // Ya incluido en los archivos que usan esta interfaz

// ============================================================================
// FUNCIONES DE LA INTERFAZ DEL SENSOR
// ============================================================================

/**
 * @brief Inicializa el sensor DHT22
 */
bool sensor_dht22_init(void);

/**
 * @brief Verifica si el sensor DHT22 está disponible
 */
bool sensor_dht22_is_available(void);

/**
 * @brief Intenta reinicializar el sensor DHT22
 */
bool sensor_dht22_retry_init(void);

/**
 * @brief Lee todos los datos del sensor DHT22
 */
bool sensor_dht22_read_all(sensor_data_t* data);

/**
 * @brief Obtiene el payload del sensor DHT22
 */
uint8_t sensor_dht22_get_payload(payload_config_t* config);

/**
 * @brief Obtiene el nombre del sensor DHT22
 */
const char* sensor_dht22_get_name(void);

/**
 * @brief Fuerza el estado del sensor DHT22 para testing
 */
void sensor_dht22_set_available_for_testing(bool available);

/**
 * @brief Inicializa el sensor DHT11
 */
bool sensor_dht11_init(void);

/**
 * @brief Verifica si el sensor DHT11 está disponible
 */
bool sensor_dht11_is_available(void);

/**
 * @brief Intenta reinicializar el sensor DHT11
 */
bool sensor_dht11_retry_init(void);

/**
 * @brief Lee todos los datos del sensor DHT11
 */
bool sensor_dht11_read_all(sensor_data_t* data);

/**
 * @brief Obtiene el payload del sensor DHT11
 */
uint8_t sensor_dht11_get_payload(payload_config_t* config);

/**
 * @brief Obtiene el nombre del sensor DHT11
 */
const char* sensor_dht11_get_name(void);

/**
 * @brief Fuerza el estado del sensor DHT11 para testing
 */
void sensor_dht11_set_available_for_testing(bool available);

/**
 * @brief Inicializa el sensor DS18B20
 */
bool sensor_ds18b20_init(void);

/**
 * @brief Verifica si el sensor DS18B20 está disponible
 */
bool sensor_ds18b20_is_available(void);

/**
 * @brief Intenta reinicializar el sensor DS18B20
 */
bool sensor_ds18b20_retry_init(void);

/**
 * @brief Lee todos los datos del sensor DS18B20
 */
bool sensor_ds18b20_read_all(sensor_data_t* data);

/**
 * @brief Obtiene el payload del sensor DS18B20
 */
uint8_t sensor_ds18b20_get_payload(payload_config_t* config);

/**
 * @brief Obtiene el nombre del sensor DS18B20
 */
const char* sensor_ds18b20_get_name(void);

/**
 * @brief Fuerza el estado del sensor DS18B20 para testing
 */
void sensor_ds18b20_set_available_for_testing(bool available);

/**
 * @brief Inicializa el sensor BME280
 */
bool sensor_bme280_init(void);

/**
 * @brief Verifica si el sensor BME280 está disponible
 */
bool sensor_bme280_is_available(void);

/**
 * @brief Intenta reinicializar el sensor BME280
 */
bool sensor_bme280_retry_init(void);

/**
 * @brief Lee todos los datos del sensor BME280
 */
bool sensor_bme280_read_all(sensor_data_t* data);

/**
 * @brief Obtiene el payload del sensor BME280
 */
uint8_t sensor_bme280_get_payload(payload_config_t* config);

/**
 * @brief Obtiene el nombre del sensor BME280
 */
const char* sensor_bme280_get_name(void);

/**
 * @brief Fuerza el estado del sensor BME280 para testing
 */
void sensor_bme280_set_available_for_testing(bool available);

/**
 * @brief Inicializa el sensor HC-SR04
 */
bool sensor_hcsr04_init(void);

/**
 * @brief Verifica si el sensor HC-SR04 está disponible
 */
bool sensor_hcsr04_is_available(void);

/**
 * @brief Intenta reinicializar el sensor HC-SR04
 */
bool sensor_hcsr04_retry_init(void);

/**
 * @brief Lee todos los datos del sensor HC-SR04
 */
bool sensor_hcsr04_read_all(sensor_data_t* data);

/**
 * @brief Obtiene el payload del sensor HC-SR04
 */
uint8_t sensor_hcsr04_get_payload(payload_config_t* config);

/**
 * @brief Obtiene el nombre del sensor HC-SR04
 */
const char* sensor_hcsr04_get_name(void);

/**
 * @brief Fuerza el estado del sensor HC-SR04 para testing
 */
void sensor_hcsr04_set_available_for_testing(bool available);

/**
 * @brief Inicializa el sensor NONE
 */
bool sensor_none_init(void);

/**
 * @brief Verifica si el sensor NONE está disponible
 */
bool sensor_none_is_available(void);

/**
 * @brief Intenta reinicializar el sensor NONE
 */
bool sensor_none_retry_init(void);

/**
 * @brief Lee todos los datos del sensor NONE
 */
bool sensor_none_read_all(sensor_data_t* data);

/**
 * @brief Obtiene el payload del sensor NONE
 */
uint8_t sensor_none_get_payload(payload_config_t* config);

/**
 * @brief Obtiene el nombre del sensor NONE
 */
const char* sensor_none_get_name(void);

/**
 * @brief Fuerza el estado del sensor NONE para testing
 */
void sensor_none_set_available_for_testing(bool available);

/**
 * @brief Inicializa todos los sensores habilitados
 */
bool sensors_init_all(void);

/**
 * @brief Verifica si al menos un sensor está disponible
 */
bool sensors_is_any_available(void);

/**
 * @brief Intenta reinicializar todos los sensores
 */
bool sensors_retry_init_all(void);

/**
 * @brief Lee datos de todos los sensores habilitados y los combina
 */
bool sensors_read_all(sensor_data_t* data);

/**
 * @brief Construye el payload con datos de todos los sensores
 */
uint8_t sensors_get_payload(payload_config_t* config);

/**
 * @brief Obtiene el nombre de los sensores activos
 */
const char* sensors_get_name(void);

/**
 * @brief Fuerza el estado de todos los sensores para testing
 */
void sensors_set_available_for_testing(bool available);

#endif // SENSOR_INTERFACE_H