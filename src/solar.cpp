#include <XPowersLib.h>
#include <Arduino.h>

// Declaración externa para funciones de carga solar
extern XPowersLibInterface *PMU;

/**
 * @brief Verifica si la placa solar está cargando la batería
 * @return true si hay entrada VBUS y la batería está cargándose
 */
bool isSolarChargingBattery() {
    if (!PMU) return false;  // Verificar que PMU esté inicializado
    
    // Verifica si hay entrada VBUS (placa solar conectada y generando voltaje)
    if (!PMU->isVbusIn()) {
        return false;  // No hay entrada solar
    }
    
    // Verifica si la batería está cargándose
    return PMU->isCharging();
}

/**
 * @brief Obtiene el estado de carga de la placa solar
 * @return true si está cargando, false en caso contrario
 */
bool getSolarChargeStatus() {
    return isSolarChargingBattery();
}

/**
 * @brief Función de monitoreo para depuración y logging
 * Imprime el estado de carga solar en Serial
 */
void checkSolarStatus() {
    bool isCharging = getSolarChargeStatus();
    if (isCharging) {
        Serial.println("Placa solar cargando batería");
    } else {
        Serial.println("Batería no cargándose (posiblemente sin sol o batería llena)");
    }
}