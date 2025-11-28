#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

//Inicializamos la barrera, la funcion recibira una struct barrera y la cantidad de hebras 
void iniciar_barrera(barrera* b , int N){
  b->N = N;
  b->count = 0;
  b->etapa = 0;
  pthread_mutex_init(&b->mutex,NULL); //Inicializamos como null nuestro mutex y la var de condicion
  pthread_cond_init(&b->cond,NULL);
}

//Funcion que hace esperar a las hebras 
void esperar(barrera* b){
  pthread_mutex_lock(&b->mutex); //Tomamos el mutex
  int actual = b->etapa;   // Obtenemos el valor de la etapa actual
  b->count++;              // Incrementamos el contador de hilos que han llegado a la barrera
  
  if(b->count < b->N){    //En caso de no ser la ultima hebra, debe esperar
    while(b->etapa == actual){  // Dejamos en espera todas las hebras que no son las ultimas hasta que la etapa cambie
      pthread_cond_wait(&b->cond, &b->mutex);
    }
  }
  
  else{
    
    /* En caso de ser la ultima hebra pasamos a la siguiente etapa,
       reiniciamos el contador de hilos, despertamos a todas las otras hebras y liberamos el mutex */
    b->etapa++;
    b->count = 0;
    pthread_cond_broadcast(&b->cond);
  }
  pthread_mutex_unlock(&b->mutex);
}


void destruir(barrera *b){   // Funcion para destruir 
  pthread_mutex_destroy(&b->mutex);
  pthread_cond_destroy(&b->cond);
}

