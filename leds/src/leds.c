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

// Private functions declaration section ---------------------------------------------------------------------------------------

/**
 * @brief Funcion de ayuda para determinar si el numero de led se encuentra entre los limites validos 
 * 
 * @param led 
 * @return bool_t 
 */

bool_t    isLedNumberValid(uint8_t led);



/**
 * @brief Funcion de ayuda para traducir el numero de led a un numero de bit dentro del vector de leds
 * 
 * @param led 
 * @return uint8_t 
 */

uint8_t   ledToBitPosition(uint8_t led);



/**
 * @brief Funcion de ayuda que genera un bit de encendido para la posicion de bit correspondiente al numero de led
 * 
 * @param led 
 * @return uint16_t 
 */

uint16_t  LedToMask(uint8_t led);



/**
 * @brief Funcion de ayuda que permite recuperar el estado del bit correspondiente a un led determinado
 * 
 * @param led 
 * @return uint16_t 
 */

uint16_t  LedGetBitStatus(uint8_t led);

// -----------------------------------------------------------------------------------------------------------------------------



// Functions declaration section -----------------------------------------------------------------------------------------------

uint8_t ledToBitPosition(uint8_t led) {
    return led - LED_TO_BIT_OFFSET;
}



uint16_t LedToMask(uint8_t led) {
    return (LED_ON << (ledToBitPosition(led)));
}



void LedsInit(uint16_t * direccion) {
    puerto = direccion;
    LedTurnOffAllAtOnce();
}



void LedTurnOn(uint8_t led) {
    if (!isLedNumberValid(led))
    {
        Alerta("Numero de led invalido");
    }
    else
    {
        *puerto |= LedToMask(led);
    } 
}



void LedTurnOff(uint8_t led){
    *puerto &= ~LedToMask(led); 
}



void LedTurnOnAllAtOnce(void){
    *puerto = LEDS_ALL_ON;
}



void LedTurnOffAllAtOnce(void){
    *puerto = LEDS_ALL_OFF;
}



uint16_t LedGetBitStatus(uint8_t led) {
    return (*puerto >> (ledToBitPosition(led)));
}



bool_t LedQueryState(uint8_t led){
    uint16_t status;
    if (!isLedNumberValid(led))
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



bool_t isLedNumberValid(uint8_t led)
{
    if (led > LED_UPPER_LIMIT || led < LED_LOWER_LIMIT)
    {
        return false;
    }
    return true;
}

// -----------------------------------------------------------------------------------------------------------------------------