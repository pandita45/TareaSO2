# TareaSO2
## Requisitos
- Sistema operativo linux x86_64
- Se necesitan las dependencias de C

# Implementacion de Barrera (Parte 1)
## Compilacion
Se necesita estar en el directorio "PrimitivasDeSincronizacion"
``` bash
gcc -o Barrera hebras.c barrera.c -pthread
./Barrera N    # Ejecuta el programa simulando el trabajo de N hebras
```

# Simulacion de memoria virtual (Parte 2)
Se necesita estar en el directorio "MemoriaVirtual"
##Compilaciòn
``` bash
gcc -o Sim sim.c
./Sim <Numero_Marcos> <Tamaño_Marco> <trace1.txt/trace2.txt>
```
