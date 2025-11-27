#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct{
  int count;
  int N;
  int etapa;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
}barrera;

void iniciar_barrera(barrera* b , int N){
  b->N = N;
  b->count = 0;
  b->etapa = 0;
  pthread_mutex_init(&b->mutex,NULL);
  pthread_cond_init(&b->cond,NULL);
}
