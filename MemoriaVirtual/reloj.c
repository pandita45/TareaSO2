#include "reloj.h"
#include <stdlib.h>
#include <stdbool.h>

void inicializar_reloj(Reloj *reloj, unsigned int num_paginas, unsigned int max_paginas_cargadas, unsigned int *secuencia_paginas) {
    reloj->puntero = 0;
    reloj->num_paginas = num_paginas;
    reloj->maximo_paginas_cargadas = max_paginas_cargadas;
    reloj->bits_uso = calloc(max_paginas_cargadas * sizeof(unsigned short), 0);
    reloj->paginas_cargadas = malloc(max_paginas_cargadas * sizeof(unsigned int));
    reloj->secuencia_paginas = secuencia_paginas;
}


bool esta_Cargada(Reloj *reloj , unsigned int pagina) {
    for (int i = 0; i < reloj->num_paginas; i++){
        if(reloj->paginas_cargadas[i] == pagina){
            return true;
        }
    }
    return false;
}
unsigned int ejecutar_reloj(Reloj *reloj) {
    int indice_cargada;
    for (int i = 0; i < reloj->num_paginas; i++){
        if(esta_Cargada(reloj, reloj->secuencia_paginas[i])){
            
        }
        else{
            reloj->paginas_cargadas[indice_cargada] = reloj->secuencia_paginas[i];
            indice_cargada++;
        }
    }
    return 0;
    
}