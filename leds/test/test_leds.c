#include "unity.h"
#include "leds.h"
#include "mock_errores.h"

#define TST_ALL_LEDS_ON                 0xFFFF
#define TST_ALL_LEDS_OFF                0x0000
#define TST_LED_ON                      1
#define TST_LED_OFF                     0
#define TST_LED5                        5
#define TST_MESSAGE_LINE                0
#define TST_LED_INVALID_LOWER_LIMIT     0
#define TST_LED_INVALID_UPPER_LIMIT     17
#define TST_LED_TO_BIT(x) (x-1)

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
    uint16_t ledsVirtuales = TST_ALL_LEDS_ON;
    LedsInit(&ledsVirtuales);
    TEST_ASSERT_EQUAL_HEX16(TST_ALL_LEDS_OFF, ledsVirtuales);
}



/**
 * @brief Se verifica que se pueda encender un LED de forma individual.
 * 
 */

void test_TurnOnOneLed(void) {
    LedTurnOn(TST_LED5);
    TEST_ASSERT_EQUAL_HEX16(TST_LED_ON << TST_LED_TO_BIT(TST_LED5), ledsVirtuales);   
}



/**
 * @brief Se verifica que se pueda apagar un LED de forma individual.
 * 
 */

void test_TurnOffOneLed(void) {
    LedTurnOn(TST_LED5);
    LedTurnOff(TST_LED5);
    TEST_ASSERT_EQUAL_HEX16(TST_LED_OFF, ledsVirtuales);   
}



/**
 * @brief Se verifica que se pueda encender y apagar multiples LED's.
 * 
 */

void test_TurnOnAndOffManyLeds(void) {
    LedTurnOn(TST_LED5);
    LedTurnOn(11);
    LedTurnOff(3);
    LedTurnOff(11);
    TEST_ASSERT_EQUAL_HEX16(TST_LED_ON << TST_LED_TO_BIT(TST_LED5), ledsVirtuales);   
}



/**
 * @brief Se verifica que la funcion retorne un mensaje de error ante un parametro que se encuentra sobre el numero maximo de LED's.
 * 
 */

void test_InvalidUpperLimitTurnOnLed(void){
    RegistrarMensaje_Expect(ALERTA, "LedTurnOn", TST_MESSAGE_LINE, "Numero de led invalido");
    RegistrarMensaje_IgnoreArg_linea();
    LedTurnOn(TST_LED_INVALID_UPPER_LIMIT);
}



/**
 * @brief Se verifica que todos los LED's pueden encenderse de una vez.
 * 
 */

void test_TurnOnAllLeds(void){
    LedTurnOnAllAtOnce();
    TEST_ASSERT_EQUAL_HEX16(TST_ALL_LEDS_ON, ledsVirtuales);
}



/**
 * @brief Se verifica que todos los LED's pueden apagarse de una vez.
 * 
 */

void test_TurnOffAllLeds(void){
    LedTurnOnAllAtOnce();
    LedTurnOffAllAtOnce();
    TEST_ASSERT_EQUAL_HEX16(TST_ALL_LEDS_OFF, ledsVirtuales);
}



/**
 * @brief Se verifica que se pueda consultar el estado de un LED apagado.
 * 
 */

void test_queryLedStateOff(){
    bool_t ledState = true;
    ledsVirtuales = TST_LED_OFF << TST_LED_TO_BIT(TST_LED5);
    ledState = LedQueryState(TST_LED5);
    TEST_ASSERT_FALSE(ledState);
}



/**
 * @brief Se verifica que se pueda consultar el estado de un LED encendido.
 * 
 */

void test_queryLedStateOn(){
    bool_t ledState = false;
    ledsVirtuales = TST_LED_ON << TST_LED_TO_BIT(TST_LED5);
    ledState = LedQueryState(TST_LED5);
    TEST_ASSERT_TRUE(ledState);
}



/**
 * @brief Se verifica la funcion de consulta del estado del LED on en el limite LED > 16.
 * 
 */

void test_queryLedStateUpperLimmit(){
    RegistrarMensaje_Expect(ALERTA, "LedQueryState", TST_MESSAGE_LINE, "Numero de led invalido");
    RegistrarMensaje_IgnoreArg_linea();
    LedQueryState(TST_LED_INVALID_UPPER_LIMIT);
}



/**
 * @brief Se verifica la funcion de consulta del estado del LED on en el limite LED < 1.
 * 
 */

void test_queryLedStateLowerLimmit(){
    RegistrarMensaje_Expect(ALERTA, "LedQueryState", TST_MESSAGE_LINE, "Numero de led invalido");
    RegistrarMensaje_IgnoreArg_linea();
    LedQueryState(TST_LED_INVALID_LOWER_LIMIT);
}