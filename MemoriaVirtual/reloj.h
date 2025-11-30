#ifndef RELOJ_H
#define RELOJ_H
#include <stdbool.h>
typedef struct
{
    unsigned int maximo_paginas_cargadas;
    unsigned int puntero;
    unsigned int num_paginas;
    unsigned char *bits_uso;
    unsigned int *paginas_cargadas;
    unsigned int *secuencia_paginas;
} Reloj;

// funcion para inicializar el reloj
void inicializar_reloj(Reloj *reloj, unsigned int num_paginas, unsigned int max_paginas_cargadas,
                       unsigned int *secuencia_paginas);
unsigned int ejecutar_reloj(Reloj *reloj);

bool esta_Cargada(Reloj *reloj , unsigned int pagina);
#endif