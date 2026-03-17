/**
 * @file      screen.cpp
 * @brief     Implementación de funciones de pantalla OLED usando U8g2 (simplificado)
 *
 * Este archivo contiene las funciones para gestionar la pantalla OLED U8g2,
 * mostrar mensajes de estado y datos del sensor.
 *
 * @author    Proyecto IoT de Bajo Consumo
 * @version   1.1
 * @date      2025
 */

#include "screen.h"
#include "LoRaBoards.h"
#include "../config/config.h"  // Configuración del proyecto

// Declaraciones forward
void turnOffDisplay();
void turnOffDisplayCompletely();

// Variables para controlar el estado del mensaje actual
static String currentMessage = "";
static ScreenMessageType currentType = MSG_INFO;
static uint32_t messageStartTime = 0;
static uint32_t messageDuration = 0;
static bool displayActive = false;

/**
 * @brief Inicializa la pantalla OLED U8g2
 *
 * @return true si la inicialización es exitosa, false en caso contrario
 */
bool initDisplay() {
    if (!ENABLE_DISPLAY) {
        Serial.println("Display disabled in configuration");
        return false;
    }

    Serial.print("DEBUG: Initializing display, u8g2 = ");
    Serial.println((u8g2 != nullptr) ? "not null" : "null");

    if (!u8g2) {
        Serial.println("Display no disponible");
        return false;
    }
    u8g2->begin();
    u8g2->clearBuffer();
    u8g2->setFont(u8g2_font_ncenB08_tr);
    u8g2->drawStr(0, 20, "MediaLab LoRaWAN");
    u8g2->drawStr(0, 40, "Bajo Consumo V.1.1");
    u8g2->sendBuffer();
    delay(2000);

    displayActive = true;
    return true;
}

/**
 * @brief Actualiza la pantalla (llamar en loop principal)
 * Maneja el tiempo de visualización de mensajes
 */
void updateDisplay() {
    if (!ENABLE_DISPLAY) {
        return;
    }

    if (!u8g2 || !displayActive) {
        return;
    }

    uint32_t currentTime = millis();

    // Si hay un mensaje con duración finita y ha expirado, limpiar pantalla y apagar
    if (messageDuration > 0 && currentTime - messageStartTime >= messageDuration) {
        clearDisplay();
        turnOffDisplay();
    }
}

/**
 * @brief Renderiza un mensaje en la pantalla según su tipo
 *
 * @param type Tipo de mensaje
 * @param text Texto del mensaje
 */
static void renderMessage(ScreenMessageType type, const String& text) {
    if (!ENABLE_DISPLAY) {
        return;
    }

    if (!u8g2) {
        return;
    }

    u8g2->clearBuffer();
    u8g2->setFont(u8g2_font_ncenB08_tr);

    // Mostrar tipo de mensaje en la parte superior
    const char* typeStr = "";
    switch (type) {
        case MSG_INFO: typeStr = "[INFO]"; break;
        case MSG_WARNING: typeStr = "[WARN]"; break;
        case MSG_ERROR: typeStr = "[ERROR]"; break;
        case MSG_SUCCESS: typeStr = "[OK]"; break;
        case MSG_SENSOR_DATA: typeStr = "[SENSOR]"; break;
        case MSG_STATUS: typeStr = "[STATUS]"; break;
    }

    u8g2->drawStr(0, 10, typeStr);

    // Mostrar el texto del mensaje
    // Dividir en líneas si es necesario
    String textCopy = text;
    int maxCharsPerLine = 16; // Aproximadamente para fuente ncenB08
    int yPos = 25;

    while (textCopy.length() > 0 && yPos < 60) {
        String line;
        if (textCopy.length() <= maxCharsPerLine) {
            line = textCopy;
            textCopy = "";
        } else {
            // Buscar un espacio para cortar la línea
            int cutPos = maxCharsPerLine;
            while (cutPos > 0 && textCopy.charAt(cutPos) != ' ') {
                cutPos--;
            }
            if (cutPos == 0) cutPos = maxCharsPerLine;

            line = textCopy.substring(0, cutPos);
            textCopy = textCopy.substring(cutPos);
            textCopy.trim(); // Remover espacio inicial
        }

        u8g2->drawStr(0, yPos, line.c_str());
        yPos += 12;
    }

    // Los indicadores de actividad se muestran en turnOffDisplay(), no aquí

    u8g2->sendBuffer();
}

/**
 * @brief Muestra un mensaje en la pantalla con duración específica
 *
 * @param type Tipo de mensaje
 * @param text Texto del mensaje
 * @param duration Duración en milisegundos (0 = mostrar hasta que llegue otro mensaje)
 */
void showMessage(ScreenMessageType type, const String& text, uint32_t duration) {
    if (!ENABLE_DISPLAY) {
        return;
    }

    Serial.print("DEBUG: Showing message: '");
    Serial.print(text);
    Serial.print("' for ");
    Serial.print(duration);
    Serial.println("ms");

    currentMessage = text;
    currentType = type;
    messageStartTime = millis();
    messageDuration = duration;

    turnOnDisplay();
    renderMessage(type, text);
}

/**
 * @brief Muestra un mensaje de información
 *
 * @param text Texto del mensaje
 * @param duration Duración en milisegundos (por defecto MESSAGE_DURATION_SUCCESS)
 */
void showInfo(const String& text, uint32_t duration) {
    if (duration == 0) duration = MESSAGE_DURATION_SUCCESS;
    showMessage(MSG_INFO, text, duration);
}

/**
 * @brief Muestra un mensaje de advertencia
 *
 * @param text Texto del mensaje
 * @param duration Duración en milisegundos (por defecto MESSAGE_DURATION_ERROR)
 */
void showWarning(const String& text, uint32_t duration) {
    if (duration == 0) duration = MESSAGE_DURATION_ERROR;
    showMessage(MSG_WARNING, text, duration);
}

/**
 * @brief Muestra un mensaje de error
 *
 * @param text Texto del mensaje
 * @param duration Duración en milisegundos (por defecto MESSAGE_DURATION_ERROR)
 */
void showError(const String& text, uint32_t duration) {
    if (duration == 0) duration = MESSAGE_DURATION_ERROR;
    showMessage(MSG_ERROR, text, duration);
}

/**
 * @brief Muestra un mensaje de éxito
 *
 * @param text Texto del mensaje
 * @param duration Duración en milisegundos (por defecto MESSAGE_DURATION_SUCCESS)
 */
void showSuccess(const String& text, uint32_t duration) {
    if (duration == 0) duration = MESSAGE_DURATION_SUCCESS;
    showMessage(MSG_SUCCESS, text, duration);
}

/**
 * @brief Muestra datos del sensor en la pantalla
 *
 * @param temp Temperatura en °C
 * @param hum Humedad en %
 * @param battery Voltaje de batería en V
 * @param duration Duración en milisegundos (por defecto 5000ms)
 */
void showSensorData(float temp, float hum, float battery, uint32_t duration) {
    char buffer[64];
    if (temp == -999.0f && hum == -1.0f) {
        // Datos de error del sensor
        showMessage(MSG_ERROR, "Sensor ERROR!", duration);
    } else {
        // Datos válidos del sensor
        sprintf(buffer, "T:%.1fC H:%.1f%% B:%.2fV", temp, hum, battery);
        showMessage(MSG_SENSOR_DATA, buffer, duration);
    }
}

/**
 * @brief Limpia la pantalla
 */
void clearDisplay() {
    if (!ENABLE_DISPLAY) {
        return;
    }

    if (u8g2) {
        u8g2->clearBuffer();
        u8g2->sendBuffer();
    }
    currentMessage = "";
    messageDuration = 0;
}

/**
 * @brief Apaga la pantalla para ahorrar energía, pero mantiene indicadores visuales
 *        Muestra 4 píxeles indicadores para confirmar que el dispositivo está activo
 */
void turnOffDisplay() {
    if (!ENABLE_DISPLAY) {
        return;
    }

    if (u8g2) {
        u8g2->clearBuffer();

        if (SHOW_ACTIVITY_INDICATORS) {
            // Indicadores de actividad: 4 píxeles en patrón de "cuadrado"
            // Esquina superior derecha
            u8g2->drawPixel(125, 1);
            u8g2->drawPixel(126, 1);
            u8g2->drawPixel(125, 2);
            u8g2->drawPixel(126, 2);

            u8g2->sendBuffer();

            // NO apagamos completamente la pantalla para mantener los indicadores visibles
            // u8g2->setPowerSave(1);  // Comentado para mantener indicadores
        } else {
            u8g2->sendBuffer();
            u8g2->setPowerSave(1);  // Apagar completamente si no hay indicadores
        }
    }
    displayActive = false;
}

/**
 * @brief Apaga completamente la pantalla para deep sleep (sin indicadores)
 */
void turnOffDisplayCompletely() {
    if (!ENABLE_DISPLAY) {
        return;
    }

    if (u8g2) {
        u8g2->clearBuffer();
        u8g2->sendBuffer();
        u8g2->setPowerSave(1);  // Apagar completamente la pantalla
    }
    displayActive = false;
}

/**
 * @brief Enciende la pantalla si está apagada
 */
void turnOnDisplay() {
    if (!ENABLE_DISPLAY) {
        return;
    }

    if (u8g2) {
        // La pantalla nunca se apaga completamente, solo se limpia y se muestran indicadores
        // u8g2->setPowerSave(0);  // No necesario ya que nunca se apaga
        // Pequeño delay para estabilidad
        delay(10);
        // El buffer ya se limpia en renderMessage()
    }
    displayActive = true;
} 
