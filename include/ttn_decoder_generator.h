/**
 * @file      ttn_decoder_generator.h
 * @brief     Header para el generador dinámico de decoders TTN
 *
 * @author    Proyecto IoT de Bajo Consumo
 * @version   1.0
 * @date      2025
 */

#ifndef TTN_DECODER_GENERATOR_H
#define TTN_DECODER_GENERATOR_H

// =============================================================================
// FUNCIONES PÚBLICAS DEL GENERADOR DE DECODERS TTN
// =============================================================================

/**
 * @brief Genera e imprime el decoder TTN completo por Serial
 *
 * Esta función analiza la configuración actual de sensores y genera
 * automáticamente el código JavaScript necesario para decodificar
 * el payload en The Things Network Console.
 *
 * El decoder se imprime por Serial solo si SHOW_TTN_DECODER está habilitado
 * en config.h. El usuario puede copiar el código generado y pegarlo
 * directamente en TTN Console -> Applications -> Payload formatters.
 */
void generate_and_print_ttn_decoder();

/**
 * @brief Genera el decoder TTN y lo devuelve como string
 *
 * @param buffer Buffer donde almacenar el código generado
 * @param max_size Tamaño máximo del buffer
 * @return Número de caracteres escritos (0 si error)
 */
uint16_t generate_ttn_decoder_string(char* buffer, uint16_t max_size);

#endif // TTN_DECODER_GENERATOR_H