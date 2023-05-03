#include "GSenku.hpp"

int main(char* argv[], int argc) {
    //Argv[1] = ficheroEntrada, argv[2] = ficheroMovs, argv[3] = retardo (por defecto rtrd = 0), *opcional argv[4] = ficheroSalida
    //Declaracion de Variables
    tpListaMovimientos solucion;
    tpTablero tablero;
    tpMovimientosValidos movs;
    tpListaMovimientos listMovs;
    //Inicializamos el tablero
    inicializarTablero(argv[1], tablero);
    //Cargamos los movimientos válidos
    inicializarMovimientosValidos(argv[2], movs);

    //Casteamos de string a int
    int retardo = stoi(argv[3]);
    buscaSolucion(tablero, movs, listMovs, retardo);

    if(argc == 4) {
        escribeListaMovimientos(argv[4], solucion);
    } 
}