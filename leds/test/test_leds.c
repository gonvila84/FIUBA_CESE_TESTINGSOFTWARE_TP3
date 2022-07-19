#include "unity.h"
#include "leds.h"
#include "mock_errores.h"

static uint16_t ledsVirtuales;

void setUp(void) {
    LedsInit(&ledsVirtuales);
}

void tearDown(void) {

}

//Despues de la inicializacion todos los LED's deben quedar apagados.
void test_ledsOffAfterCreate(void) {
    uint16_t ledsVirtuales = 0xFFFF;
    LedsInit(&ledsVirtuales);
    TEST_ASSERT_EQUAL_HEX16(0x0000, ledsVirtuales);
}

//Se puede prender un LED individual.
void test_TurnOnOneLed(void) {
    LedTurnOn(5);
    TEST_ASSERT_EQUAL_HEX16(1 << 4, ledsVirtuales);   
}

//Se puede apagar un LED individual.
void test_TurnOffOneLed(void) {
    LedTurnOn(5);
    LedTurnOff(5);
    TEST_ASSERT_EQUAL_HEX16(0x0000, ledsVirtuales);   
}

//Se pueden prender y apagar multiples LED's.
void test_TurnOnAndOffManyLeds(void) {
    LedTurnOn(5);
    LedTurnOn(11);
    LedTurnOff(3);
    LedTurnOff(11);
    TEST_ASSERT_EQUAL_HEX16(1 << 4, ledsVirtuales);   
}

//
void test_InvalidUpperLimitTurnOnLed(void){
    RegistrarMensaje_Expect(ALERTA, "LedTurnOn", 0, "Numero de led invalido");
    RegistrarMensaje_IgnoreArg_linea();
    LedTurnOn(17);
}

//Hechos por mi

//Se pueden prender todos los LEDs de una vez.
void test_TurnOnAllLeds(void){
    ledsVirtuales = 0x0;
    LedTurnOnAllAtOnce();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, ledsVirtuales);
}

//Se pueden apagar todos los LEDs de una vez.
void test_TurnOffAllLeds(void){
    ledsVirtuales = 0xFFFF;
    LedTurnOffAllAtOnce();
    TEST_ASSERT_EQUAL_HEX16(0x0, ledsVirtuales);
}

//Se puede consultar el estado de un led.
void test_queryLedStateOff(){
    bool_t ledState = true;
    ledsVirtuales = 0 << 4;
    ledState = LedQueryState(5);
    TEST_ASSERT_FALSE(ledState);
}

//Se puede consultar el estado de un led.
void test_queryLedStateOn(){
    bool_t ledState = false;
    ledsVirtuales = 1 << 4;
    ledState = LedQueryState(5);
    TEST_ASSERT_TRUE(ledState);
}

//Se prueban la funcion de consulta del estado del led on los limites led < 1 y led > 16
void test_queryLedStateUpperLimmit(){
    RegistrarMensaje_Expect(ALERTA, "LedQueryState", 0, "Numero de led invalido");
    RegistrarMensaje_IgnoreArg_linea();
    LedQueryState(17);
}

//Se prueban la funcion de consulta del estado del led on los limites led < 1 y led > 16
void test_queryLedStateLowerLimmit(){
    RegistrarMensaje_Expect(ALERTA, "LedQueryState", 0, "Numero de led invalido");
    RegistrarMensaje_IgnoreArg_linea();
    LedQueryState(0);
}