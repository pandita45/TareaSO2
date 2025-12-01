#include "memoriaVirtual.h"
#include <stdlib.h>

MarcoFisico* simularRam(int tamano_ram) {
    MarcoFisico* Memoria_Simulada = malloc(
        sizeof(MarcoFisico) * tamano_ram); //-1 si esta libre el marcoFisico, si no tendra la pagina cargada
    for (int i = 0; i < tamano_ram; i++) {
        Memoria_Simulada[i].npv_cargada = -1;
    }

    return Memoria_Simulada;
}

void inicializarTablaDePaginas(entradaTablaDePaginas* tabla){
    for(int i = 0; i < 10000; i++){ // suponer un maximo de 10000 paginas virtuales
        tabla[i].nmp = -1;
        tabla[i].bit_valido = 0;
        tabla[i].bit_referencia = 0;
    }
}

int calcularBitsOffset(int tamanoMarco){
    int bitsOffset = 0;
    while (tamanoMarco > 1){
        tamanoMarco = tamanoMarco >> 1;
        bitsOffset++;
    }
    return bitsOffset;
};