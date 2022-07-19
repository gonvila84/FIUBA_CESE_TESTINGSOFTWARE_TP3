#include "leds.h"
#include "errores.h"

#define LED_TO_BIT_OFFSET   1
#define LED_MASK            1
#define LEDS_ALL_OFF        0
#define LEDS_ALL_ON         0XFFFF
#define LED_ON              1
#define LED_LOWER_LIMIT     1
#define LED_UPPER_LIMIT     16

static uint16_t * puerto;



/**
 * @brief Transforma el numero de led and el correspondiente numero de bit.
 * 
 * @param led 
 * @return uint8_t 
 */

uint8_t ledToBitPosition(uint8_t led) {
    return led - LED_TO_BIT_OFFSET;
}



/**
 * @brief Enciende el bit correspondiente al LED que se suministra como parametro.
 * 
 * @param led 
 * @return uint16_t 
 */

uint16_t LedToMask(uint8_t led) {
    return (LED_ON << (ledToBitPosition(led)));
}



/**
 * @brief Inicializa la variable que registra el estado de cada led. El valor pre-determinado es apagado.
 * 
 * @param direccion 
 */

void LedsInit(uint16_t * direccion) {
    puerto = direccion;
    LedTurnOffAllAtOnce();
}



/**
 * @brief Enciende el led que se suministra como parametro.
 * 
 * @param led 
 */

void LedTurnOn(uint8_t led) {
    if (led > LED_UPPER_LIMIT)
    {
        Alerta("Numero de led invalido");
    }
    else
    {
        *puerto |= LedToMask(led);
    } 
}



/**
 * @brief Apaga el led que se suministra como parametro.
 * 
 * @param led 
 */

void LedTurnOff(uint8_t led){
    *puerto &= ~LedToMask(led); 
}



/**
 * @brief Enciende todos los LED's.
 * 
 */

void LedTurnOnAllAtOnce(void){
    *puerto = LEDS_ALL_ON;
}



/**
 * @brief Apaga todos los LED's.
 * 
 */

void LedTurnOffAllAtOnce(void){
    *puerto = LEDS_ALL_OFF;
}



/**
 * @brief Retorna el estado de un LED (Encendido o Apagado).
 * 
 * @param led 
 * @return uint16_t 
 */

uint16_t LedGetBitStatus(uint8_t led) {
    return (*puerto >> (ledToBitPosition(led)));
}



/**
 * @brief Retorna true o false dependiendo del valor obtenido para el bit que representa al LED.
 * 
 * @param led 
 * @return bool_t 
 */

bool_t LedQueryState(uint8_t led){
    uint16_t status;
    if (led > LED_UPPER_LIMIT || led < LED_LOWER_LIMIT)
    {
        Alerta("Numero de led invalido");
        return false;
    }

    status = LedGetBitStatus(led);
    if (status & LED_ON)
    {
        return true;
    }
    return false;
}