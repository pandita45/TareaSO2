#include "barrera.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define etapa 4   //Definimos la cantidad de etapas 
barrera b;       // Creamos una barrera global para el trabajo
 
void* exec_hebra(void *arg){      // Funcion que ejecuta una hebra 
  int pthread_n = *(int*)arg;      //Recibimos el id de la hebra y lo casteamos a entero
  for(int e = 0; e < etapa; e++){
    usleep(1000000);                // Simulamos el trabajo por cada etapa 
    printf("Hebra numero %d esperando en etapa %d\n",pthread_n, e);
    esperar(&b);     //Llamamos a la funcion esperar de nuestra barrera 
    printf("Hebra numero %d paso barrera en etapa %d\n", pthread_n, e);
  }
  return NULL;
}

  
int main(int argc, char **argv){
  int N = atoi(argv[1]);        // Guardamos en N la cantidad de hebras a utilizar 
  iniciar_barrera(&b,N);        // Inicializamos la barrera
  
  pthread_t hebras[N];          //Creamos arreglos para guardar cada hebrea y sus respectivo id
  int ids[N];
  
  for(int i = 0; i < N; i++){   //Asignamos un id a cada hebra y la creamos, pasando como paremtro un puntero a la funcion que ejecuta nuestras hebras
    ids[i] = i;
    pthread_create(&hebras[i], NULL ,&exec_hebra,&ids[i]);
  }
  for(int i = 0; i < N; i++){        
    pthread_join(hebras[i],NULL);  //Usamos join para sincronizar las hebras y no terminar el main antes de tiempo
  }
  destruir(&b);    // Destruimos la barrera
}
		 
  
  
  
