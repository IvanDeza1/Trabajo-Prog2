#include "GSenku.hpp"
#include <iostream>
#include <assert.h>

#define _DEBUG_MODE_1

//Funcion para poder hacer debug sin debugger
#ifdef _DEBUG_MODE_1
#define TRACE(a) std::cout << a << '\n'
#else
#define TRACE(a)
#endif

using namespace std;

/*
 * Pre: token contiene un caracter (-, o, x), celdaActual esta vacío
 * Post: celdaActual tiene guardado el estado de la celda (NO_USADA, VACIA, OCUPADA)
 */
void tokentoenum(const char token, tpEstadoCelda &celdaActual) {
    //Comprobamos que la longitud de la cadena recibida es 1
    //assert(token.length() == 1);
    if (token == '-') {
        celdaActual = NO_USADA;
            }
    else if(token == 'o') {
        celdaActual = VACIA;
    }
    else if(token == 'x') {
        celdaActual = OCUPADA;
    }
}

bool inicializarTablero(const string nombreFichero, tpTablero &tablero) {
    ifstream f;
    f.open(nombreFichero);
    if(f.is_open()) {
        //Creamos las variables necesarias para guardar los datos de el fichero
        string numCols;
        string numFils;
        //Leemos y almacenamos el número de filas y de columnas
        getline(f, numCols, ' ');
        getline(f, numFils, '\n');

        //Metemos los datos leidos en su respectivo lugar
        tablero.ncols = stoi(numCols);
        tablero.nfils = stoi(numFils);
        TRACE(tablero.ncols);
        
        //Declaramos variables necesarias para poder recorrer y leer el tablero
        char estado;
        int colAct = 0;
        int filAct = 0;
        char descarte;
        
        //Bucle para recorrer e inicializar el tablero
        while(f.get(estado)) {

            //Nos quitamos los espacios y los saltos de línea
            f.get(descarte)   ;     

            tpEstadoCelda estadoCelda;
            //Convertimos el token al valor de la enumeracion
            tokentoenum(estado, estadoCelda);
            //Guardamos el estado de la celda en la matriz
            tablero.matriz[colAct][filAct] = estadoCelda;
            
            //Necesario para poder recorrer el tablero
            colAct++;
            if(colAct = tablero.ncols - 1) {
                colAct = 0;
                filAct++;
            }
        }
        //Cerramos el fichero
        f.close();
        return true;
    }
    //Caso en el que haya algun tipo de error abriendo el fichero
    else {
        return false;
    }

}

bool inicializarMovimientosValidos (const string nombreFichero, tpMovimientosValidos &movimientos) {
    ifstream f;
    f.open(nombreFichero);


    if(f.is_open()) {
        //Declaramos las variables necesarias
        int pos = 0;
        char estado;
        char descarte;
        //Bucle que recorre el fichero de movimientos
        while(f.get(estado)) {
            //Descartamos los espacios y los saltos de linea
            f.get(descarte);
            
            // Almacenamos los movimientos en el struct
            if(estado == '-') {
                movimientos.validos[pos] = false;
            }
            else if (estado == '+') {
                movimientos.validos[pos] = true;
            }
            if(estado != 'o'){
                pos++;
            }
        }
        //Cerramos el fichero y devolvemos que todo ha ido bien
        f.close();
        return true;
    }
 
    else {
        //Si ha habido algun error abriendo el fichero devolvemos false
        return false;
    }
}

int main() {
    const string movs = "movimientos.txt";
    tpMovimientosValidos moves;
    inicializarMovimientosValidos(movs, moves);
    for(int i = 0; i < 8; i++) {
        TRACE(moves.validos[i]);
    }
    
}

