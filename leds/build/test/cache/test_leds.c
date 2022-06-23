#include "build/test/mocks/mock_errores.h"
#include "src/leds.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


static uint16_t ledsVirtuales;



void setUp(void) {

    LedsInit(&ledsVirtuales);

}



void tearDown(void) {



}





void test_ledsOffAfterCreate(void) {

    uint16_t ledsVirtuales = 0xFFFF;

    LedsInit(&ledsVirtuales);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

   ((void *)0)

   ), (UNITY_UINT)(19), UNITY_DISPLAY_STYLE_HEX16);

}





void test_TurnOnOneLed(void) {

    LedTurnOn(5);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((1 << 4)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

   ((void *)0)

   ), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_HEX16);

}





void test_TurnOffOneLed(void) {

    LedTurnOn(5);

    LedTurnOff(5);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

   ((void *)0)

   ), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_HEX16);

}





void test_TurnOnAndOffManyLeds(void) {

    LedTurnOn(5);

    LedTurnOn(11);

    LedTurnOff(3);

    LedTurnOff(11);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((1 << 4)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

   ((void *)0)

   ), (UNITY_UINT)(41), UNITY_DISPLAY_STYLE_HEX16);

}





void test_InvalidUpperLimitTurnOnLed(void){

    RegistrarMensaje_CMockExpect(46, ALERTA, "LedTurnOn", 0, "Numero de led invalido");

    RegistrarMensaje_CMockIgnoreArg_linea(47);

    LedTurnOn(17);

}









void test_TurnOnAllLeds(void){

    ledsVirtuales = 0x0;

    LedTurnOnAllAtOnce();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xFFFF)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

   ((void *)0)

   ), (UNITY_UINT)(57), UNITY_DISPLAY_STYLE_HEX16);

}





void test_TurnOffAllLeds(void){

    ledsVirtuales = 0xFFFF;

    LedTurnOffAllAtOnce();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

   ((void *)0)

   ), (UNITY_UINT)(64), UNITY_DISPLAY_STYLE_HEX16);

}





void test_queryLedStateOff(){

    bool_t ledState = 

                     1

                         ;

    ledsVirtuales = 0 << 4;

    ledState = LedQueryState(5);

    do {if (!(ledState)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(72)));}} while(0);

}





void test_queryLedStateOn(){

    bool_t ledState = 

                     0

                          ;

    ledsVirtuales = 1 << 4;

    ledState = LedQueryState(5);

    do {if ((ledState)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(80)));}} while(0);

}





void test_queryLedStateUpperLimmit(){

    RegistrarMensaje_CMockExpect(85, ALERTA, "LedQueryState", 0, "Numero de led invalido");

    RegistrarMensaje_CMockIgnoreArg_linea(86);

    LedQueryState(17);

}



void test_queryLedStateLowerLimmit(){

    RegistrarMensaje_CMockExpect(91, ALERTA, "LedQueryState", 0, "Numero de led invalido");

    RegistrarMensaje_CMockIgnoreArg_linea(92);

    LedQueryState(0);

}
