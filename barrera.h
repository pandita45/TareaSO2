#ifndef BARRERA_H
#define BARRERA_H

#include <pthread.h>

// Definimos nuestra barrera
typedef struct {
    int count;
    int N;
    int etapa;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} barrera;

// Prototipos de funciones
void iniciar_barrera(barrera* b, int N);
void esperar(barrera* b);
void destruir(barrera* b);

#endif
