/**
 * @file      loramac.h
 * @brief     Cabeceras para el módulo LoRaWAN y sensor de bajo consumo
 *
 * Este archivo declara las funciones principales para la gestión de LoRaWAN,
 * integración del sensor BME280 y control de bajo consumo.
 *
 * Funcionalidades:
 * - Inicialización de LMIC y sensor
 * - Lectura y envío de datos del sensor
 * - Gestión de eventos LoRaWAN
 * - Control de sueño profundo
 *
 * @note      Diseñado para ser modular y reutilizable en otros proyectos IoT
 * @author    Proyecto de Sensor LoRaWAN
 * @version   1.0
 * @date      2025
 */

#pragma once

/**
 * @brief     Inicializa LMIC, sensor BME280 y configura OTAA
 *
 * Configura pines LoRa, claves LoRaWAN, callbacks de eventos y sensor.
 * Debe llamarse una vez en setup().
 */
void setupLMIC(void);

/**
 * @brief     Bucle principal para procesar eventos LoRaWAN
 *
 * Maneja el estado de LMIC, eventos de join/envío y transiciones a sueño profundo.
 * Se llama continuamente en loop() de Arduino.
 */
void loopLMIC(void);


