#include "unity.h"
#include "leds.h"
#include "mock_errores.h"

static uint16_t ledsVirtuales;

/**
 * @brief Se realiza la configuracion inicial de los LED's para todos los tests. Los LED's se inicializan apagados.
 * 
 */

void setUp(void) {
    LedsInit(&ledsVirtuales);
}



/**
 * @brief Se realiza el cleanup de cada test tras la ejecucion del test. En este caso no se utiliza.
 * 
 */

void tearDown(void) {

}



/**
 * @brief Se verifica que tras la inicializacion todos los LED's esten apagados.
 * 
 */

void test_ledsOffAfterCreate(void) {
    uint16_t ledsVirtuales = 0xFFFF;
    LedsInit(&ledsVirtuales);
    TEST_ASSERT_EQUAL_HEX16(0x0000, ledsVirtuales);
}



/**
 * @brief Se verifica que se pueda encender un LED de forma individual.
 * 
 */

void test_TurnOnOneLed(void) {
    LedTurnOn(5);
    TEST_ASSERT_EQUAL_HEX16(1 << 4, ledsVirtuales);   
}



/**
 * @brief Se verifica que se pueda apagar un LED de forma individual.
 * 
 */

void test_TurnOffOneLed(void) {
    LedTurnOn(5);
    LedTurnOff(5);
    TEST_ASSERT_EQUAL_HEX16(0x0000, ledsVirtuales);   
}



/**
 * @brief Se verifica que se pueda encender y apagar multiples LED's.
 * 
 */

void test_TurnOnAndOffManyLeds(void) {
    LedTurnOn(5);
    LedTurnOn(11);
    LedTurnOff(3);
    LedTurnOff(11);
    TEST_ASSERT_EQUAL_HEX16(1 << 4, ledsVirtuales);   
}



/**
 * @brief Se verifica que la funcion retorne un mensaje de error ante un parametro que se encuentra sobre el numero maximo de LED's.
 * 
 */

void test_InvalidUpperLimitTurnOnLed(void){
    RegistrarMensaje_Expect(ALERTA, "LedTurnOn", 0, "Numero de led invalido");
    RegistrarMensaje_IgnoreArg_linea();
    LedTurnOn(17);
}



/**
 * @brief Se verifica que todos los LED's pueden encenderse de una vez.
 * 
 */

void test_TurnOnAllLeds(void){
    LedTurnOnAllAtOnce();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, ledsVirtuales);
}



/**
 * @brief Se verifica que todos los LED's pueden apagarse de una vez.
 * 
 */

void test_TurnOffAllLeds(void){
    LedTurnOnAllAtOnce();
    LedTurnOffAllAtOnce();
    TEST_ASSERT_EQUAL_HEX16(0x0, ledsVirtuales);
}



/**
 * @brief Se verifica que se pueda consultar el estado de un LED apagado.
 * 
 */

void test_queryLedStateOff(){
    bool_t ledState = true;
    ledsVirtuales = 0 << 4;
    ledState = LedQueryState(5);
    TEST_ASSERT_FALSE(ledState);
}



/**
 * @brief Se verifica que se pueda consultar el estado de un LED encendido.
 * 
 */

void test_queryLedStateOn(){
    bool_t ledState = false;
    ledsVirtuales = 1 << 4;
    ledState = LedQueryState(5);
    TEST_ASSERT_TRUE(ledState);
}



/**
 * @brief Se verifica la funcion de consulta del estado del LED on en el limite LED > 16.
 * 
 */

void test_queryLedStateUpperLimmit(){
    RegistrarMensaje_Expect(ALERTA, "LedQueryState", 0, "Numero de led invalido");
    RegistrarMensaje_IgnoreArg_linea();
    LedQueryState(17);
}



/**
 * @brief Se verifica la funcion de consulta del estado del LED on en el limite LED < 1.
 * 
 */

void test_queryLedStateLowerLimmit(){
    RegistrarMensaje_Expect(ALERTA, "LedQueryState", 0, "Numero de led invalido");
    RegistrarMensaje_IgnoreArg_linea();
    LedQueryState(0);
}