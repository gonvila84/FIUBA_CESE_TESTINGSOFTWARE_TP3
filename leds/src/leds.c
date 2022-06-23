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

uint8_t ledToBitPosition(uint8_t led) {
    return led - 1;
}

uint16_t LedToMask(uint8_t led) {
    return (1 << (ledToBitPosition(led)));
}

void LedsInit(uint16_t * direccion) {
    puerto = direccion;
    *puerto = 0;
}

void LedTurnOn(uint8_t led) {
    if (led > 16)
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