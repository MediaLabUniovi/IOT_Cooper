/**
 * @file      solar.h
 * @brief     Funciones para gestión de carga solar
 *
 * Este archivo contiene las funciones para detectar y monitorear
 * el estado de carga de paneles solares conectados al sistema.
 *
 * @author    Proyecto IoT de Bajo Consumo
 * @version   1.0
 * @date      2025
 */

#ifndef SOLAR_H
#define SOLAR_H

#include <stdbool.h>

// ============================================================================
// FUNCIONES PÚBLICAS
// ============================================================================

/**
 * @brief Verifica si la placa solar está cargando la batería
 * @return true si hay entrada VBUS y la batería está cargándose
 */
// bool isSolarChargingBattery();

/**
 * @brief Obtiene el estado de carga de la placa solar
 * @return true si está cargando, false en caso contrario
 */
// bool getSolarChargeStatus();

/**
 * @brief Función de monitoreo para depuración y logging
 * Imprime el estado de carga solar en Serial
 */
void checkSolarStatus();

#endif // SOLAR_H