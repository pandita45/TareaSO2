#include <stdio.h>
#include "memoriaVirtual.c"
#include <stdlib.h>

int main(int argc, char **argv){
    if (argc != 4){
        printf("Uso: %s <numero_de_marcos> <tamano_de_pagina> <nombre_de_traza>\n", argv[0]);
        return -1;
    }
    int Nmarcos = atoi(argv[1]);
    int PAGE_SIZE = atoi(argv[2]);
    char *nombreTraza = argv[3];

    int b = calcularBitsOffset(PAGE_SIZE);
                
    int MASK = (1UL << b) - 1;

    MarcoFisico *RAM = simularRam(Nmarcos);

    FILE *archivoTraza = fopen(nombreTraza, "r");
    if (archivoTraza == NULL){
        return -1;
    }
    entradaTablaDePaginas *tablaDePaginas = malloc(sizeof(entradaTablaDePaginas) * 20000); // suponer un maximo de 20000 paginas virtuales
    inicializarTablaDePaginas(tablaDePaginas);

    unsigned long dv;
    unsigned long direccionFisica;

    int TotalReferencias = 0;
    int fallosDePagina = 0;
    int bitDeUso = 0;

    while (fscanf(archivoTraza, "%lx\n", &dv) != EOF){ 
        TotalReferencias++;
        int offset = dv & MASK;
        int npv = dv >> b;

        if (tablaDePaginas[npv].bit_valido == 1){// HIT(esta cargado)
            tablaDePaginas[npv].bit_referencia = 1; // actualizar el bit de referencia
            direccionFisica = (tablaDePaginas[npv].nmp << b) | offset;
            printf("La pagina virtual %d se cargo en el marco fisico %d y la direccion fisica es %lx\n", npv, tablaDePaginas[npv].nmp, direccionFisica);
        }
        else{ // MISS (no esta cargado)
            fallosDePagina++;
            int fueCargada = 0;

            printf("Fallo de pagina en la pagina virtual: %d\n", npv);
            // buscar un marco libre en la RAM

            for (int i = 0; i < Nmarcos; i++){
                if (RAM[i].npv_cargada == -1){ // marco sin nada cargado
                    RAM[i].npv_cargada = npv;
                    tablaDePaginas[npv].nmp = i;
                    tablaDePaginas[npv].bit_valido = 1;
                    tablaDePaginas[npv].bit_referencia = 1;
                    direccionFisica = (i << b) | offset;
                    fueCargada = 1;
                    printf("La pagina virtual %d se cargo en el marco fisico %d y la direccion fisica es %lx\n", npv, i, direccionFisica);
                    break;
                }
            }
            // si no hay marcos libres, usar el algoritmo de reemplazo de reloj
            while(fueCargada == 0){
                if(tablaDePaginas[RAM[bitDeUso].npv_cargada].bit_referencia == 0){

                    tablaDePaginas[RAM[bitDeUso].npv_cargada].bit_valido = 0; //marcar como no valido (lo saca de la memoria fisica)
                    int npv_sacado = RAM[bitDeUso].npv_cargada;
                    RAM[bitDeUso].npv_cargada = npv;
                    tablaDePaginas[npv].nmp = bitDeUso;
                    tablaDePaginas[npv].bit_valido = 1;
                    tablaDePaginas[npv].bit_referencia = 1;
                    direccionFisica = (bitDeUso << b) | offset;
                    fueCargada = 1;

                    printf("La pagina virtual %d se retiro del marco fisico %d\n", npv_sacado, bitDeUso);
                    printf("La pagina virtual %d se cargo en el marco fisico %d y la direccion fisica es %lx\n", npv, bitDeUso, direccionFisica);
                    break;
                }
                else{
                    tablaDePaginas[RAM[bitDeUso].npv_cargada].bit_referencia = 0; // darle una segunda oportunidad
                }
                bitDeUso = (bitDeUso + 1) % Nmarcos;
            }
        }
    }
    printf("Total de referencias: %d\n", TotalReferencias);
    printf("Tasa de errores de pagina: %.2f%%\n", (fallosDePagina / (float)TotalReferencias) * 100);
    printf("Numero de fallos de pagina: %d\n", fallosDePagina);
    free(RAM);
    free(tablaDePaginas);
    fclose(archivoTraza);
    return 0; 
}