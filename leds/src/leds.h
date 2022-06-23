#ifndef _LEDS_H
#define _LEDS_H

#include <stdint.h>
#include <stdbool.h>

typedef bool bool_t;

/**
 * @brief Configura la biblioteca y apaga todos los leds
 * 
 * @param direccion Direccion del puerto GPIO que controla los leds.
 */
void LedsInit(uint16_t * direccion);

/**
 * @brief Prende un led
 * 
 * @param led Numero de led a prender (1 al 16)
 */
void LedTurnOn(uint8_t led);

/**
 * @brief Apaga un led
 * 
 * @param led Numero de led a apagar (1 al 16)
 */
void LedTurnOff(uint8_t led);

/**
 * @brief Enciende todos los leds con una unica invocacion
 * 
 */
void LedTurnOnAllAtOnce(void);

/**
 * @brief Apaga todos los leds con una unica invocacion
 * 
 */
void LedTurnOffAllAtOnce(void);

bool_t LedQueryState(uint8_t led);

#endif