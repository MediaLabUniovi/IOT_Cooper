/**
 * @file      screen.h
 * @brief     Cabeceras para el módulo de pantalla OLED usando U8g2 (simplificado)
 *
 * @author    Proyecto IoT de Bajo Consumo
 * @version   1.1
 * @date      2025
 */

#pragma once

#include <Arduino.h>

// Tipos de mensajes de pantalla
enum ScreenMessageType {
    MSG_INFO,           // Información general
    MSG_WARNING,        // Advertencia
    MSG_ERROR,          // Error
    MSG_SUCCESS,        // Éxito
    MSG_SENSOR_DATA,    // Datos del sensor
    MSG_STATUS          // Estado del sistema
};

/**
 * @brief Inicializa la pantalla OLED U8g2
 *
 * @return true si la inicialización es exitosa, false en caso contrario
 */
bool initDisplay();

/**
 * @brief Actualiza la pantalla (llamar en loop principal)
 * Maneja el tiempo de visualización de mensajes
 */
void updateDisplay();

/**
 * @brief Muestra un mensaje en la pantalla con duración específica
 *
 * @param type Tipo de mensaje
 * @param text Texto del mensaje
 * @param duration Duración en milisegundos (0 = mostrar hasta que llegue otro mensaje)
 */
void showMessage(ScreenMessageType type, const String& text, uint32_t duration = 3000);

/**
 * @brief Muestra un mensaje de información
 *
 * @param text Texto del mensaje
 * @param duration Duración en milisegundos (por defecto 3000ms)
 */
void showInfo(const String& text, uint32_t duration = 3000);

/**
 * @brief Muestra un mensaje de advertencia
 *
 * @param text Texto del mensaje
 * @param duration Duración en milisegundos (por defecto 4000ms)
 */
void showWarning(const String& text, uint32_t duration = 4000);

/**
 * @brief Muestra un mensaje de error
 *
 * @param text Texto del mensaje
 * @param duration Duración en milisegundos (por defecto 5000ms)
 */
void showError(const String& text, uint32_t duration = 5000);

/**
 * @brief Muestra un mensaje de éxito
 *
 * @param text Texto del mensaje
 * @param duration Duración en milisegundos (por defecto 2000ms)
 */
void showSuccess(const String& text, uint32_t duration = 2000);

/**
 * @brief Muestra datos del sensor en la pantalla
 *
 * @param temp Temperatura en °C
 * @param hum Humedad en %
 * @param battery Voltaje de batería en V
 * @param duration Duración en milisegundos (por defecto 5000ms)
 */
void showSensorData(float temp, float hum, float battery, uint32_t duration = 5000);

/**
 * @brief Limpia la pantalla
 */
void clearDisplay();

/**
 * @brief Apaga completamente la pantalla para deep sleep (sin indicadores)
 */
void turnOffDisplayCompletely();

/**
 * @brief Enciende la pantalla si está apagada
 */
void turnOnDisplay();