/**************************************************************************************************
 ** (c) Copyright 2019: Esteban VOLENTINI <evolentini@gmail.com>
 ** ALL RIGHTS RESERVED, DON'T USE OR PUBLISH THIS FILE WITHOUT AUTORIZATION
 *************************************************************************************************/

#ifndef ERRORES_H   /*! @cond    */
#define ERRORES_H   /*! @endcond */

/** @file errores.h
 ** @brief Declaraciones de la libreria para el registro de errores
 **
 ** Libreria para el registro del los errores del sistema.
 **
 **| REV | YYYY.MM.DD | Autor           | Descripción de los cambios                              |
 **|-----|------------|-----------------|---------------------------------------------------------|
 **|   1 | 2019.06.10 | evolentini      | Version inicial del archivo para manejo de errores      |
 **
 ** @addtogroup plataforma
 ** @{ */

/* === Inclusiones de archivos externos ======================================================== */

/* === Cabecera C++ ============================================================================ */
#ifdef __cplusplus
extern "C" {
#endif

/* === Definicion y Macros ===================================================================== */

/**
 * @brief Macro para registrar un mensaje en la bitacora de errores del sistema
 * 
 * @param   gravedad    Gravedad del error que se registra
 * @param   mensaje     Cadena con el mensaje de error
 * @param   ...         Referencias a las variables para completar el mensaje que se registra
 */
#define Registrar(gravedad, mensaje, ...)    \
    RegistrarMensaje(gravedad, __FUNCTION__, __LINE__, mensaje, ##__VA_ARGS__)

/**
 * @brief Macro para registrar un error en la bitacora de errores del sistema
 * 
 * @param   mensaje     Cadena con el mensaje de error
 * @param   ...         Referencias a las variables para completar el mensaje del error
 */
#define Error(mensaje, ...)    \
    RegistrarMensaje(ERROR, __FUNCTION__, __LINE__, mensaje, ##__VA_ARGS__)

/**
 * @brief Macro para registrar una alerta en la bitacora de errores del sistema
 * 
 * @param   mensaje     Cadena con el mensaje de la alerta
 * @param   ...         Referencias a las variables para completar el mensaje de la alerta
 */
#define Alerta(mensaje, ...)    \
    RegistrarMensaje(ALERTA, __FUNCTION__, __LINE__, mensaje, ##__VA_ARGS__)

/* === Declaraciones de tipos de datos ========================================================= */

//! Tipo de datos enumerado para definir la gravedad de un registro en la bitacora de errores
typedef enum gravedad_e {
    ERROR,              //!< Mensaje de error
    ALERTA,             //!< Mensaje de alerta
    INFORMACION,        //!< Mensaje de informacion
    DEPURACION,         //!< Mensaje de depuracino
} gravedad_t;

/* === Declaraciones de variables externas ===================================================== */

/* === Declaraciones de funciones externas ===================================================== */
/**
 * @brief Funcion para registrar un mensaje en la bitacora de errores del sistema
 * 
 * @param   gravedad    Nivel de gravedad del mensaje registrado
 * @param   funcion     Funcion que realiza el registro del mensaje
 * @param   linea       Linea del codigo fuente en la que se llama al registro del mensaje
 * @param   mensaje     Cadena de caracteres con el mensaje que se desea registrar
 * @param   ...         Referencias a las variables para completar el mensaje que se registra
 */
void RegistrarMensaje(gravedad_t gravedad, const char * funcion, int linea, const char * mensaje, ...);

/* === Ciere de documentacion ================================================================== */
#ifdef __cplusplus
}
#endif

/** @} Final de la definición del modulo para doxygen */

#endif   /* ERRORES_H */
