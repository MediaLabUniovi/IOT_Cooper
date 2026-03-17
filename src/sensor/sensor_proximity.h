#ifndef SENSOR_PROXIMITY_H
#define SENSOR_PROXIMITY_H

#include <Arduino.h>
#include "../../config/config.h"

#ifdef ENABLE_SENSOR_PROXIMITY

/**
 * @brief Inicializa el sensor de proximidad ultrasónico (JSN-SR04T)
 * @return true si la inicialización fue exitosa
 */
bool sensor_proximity_init(void);

/**
 * @brief Verifica si el sensor está disponible y comunicándose
 * @return true si el sensor responde correctamente
 */
bool sensor_proximity_is_available(void);

/**
 * @brief Intenta reinicializar el sensor en caso de fallo
 * @return true si se recuperó la comunicación
 */
bool sensor_proximity_retry_init(void);

/**
 * @brief Lee todos los datos del sensor
 * @param data Puntero a la estructura donde se guardarán los datos
 * @return true si la lectura fue exitosa
 */
bool sensor_proximity_read_all(sensor_data_t* data);

/**
 * @brief Fuerza el estado del sensor para propósitos de testing
 * @param available Estado a forzar (true = disponible, false = fallo)
 */
void sensor_proximity_set_available_for_testing(bool available);

#endif // ENABLE_SENSOR_PROXIMITY
#endif // SENSOR_PROXIMITY_H
