#ifndef MEMORIA_VIRTUAL_H
#define MEMORIA_VIRTUAL_H

typedef struct{ // entrada de la tabla de paginas
    int nmp; // numero de marco fisico
    int bit_valido; // 1 si esta en memoria fisica, 0 si no
    int bit_referencia; //se necesita para el algoritmo de reemplazo
} entradaTablaDePaginas;

typedef struct{ // marco fisico
    int npv_cargada;

}MarcoFisico;

void inicializarTablaDePaginas(entradaTablaDePaginas* tabla);
MarcoFisico* simularRam(int tamano_ram);
int calcularBitsOffset(int tamanoMarco);

#endif