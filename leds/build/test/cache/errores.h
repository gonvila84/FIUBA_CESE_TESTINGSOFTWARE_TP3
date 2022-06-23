typedef enum gravedad_e {

    ERROR,

    ALERTA,

    INFORMACION,

    DEPURACION,

} gravedad_t;

void RegistrarMensaje(gravedad_t gravedad, const char * funcion, int linea, const char * mensaje, ...);
