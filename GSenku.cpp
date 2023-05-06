#include "GSenku.hpp"
#include <iostream>
#include <assert.h>
#include<unistd.h>

#define _DEBUG_MODE_1
#define microsecond 1000000

//Funcion para poder hacer debug sin debugger
#ifdef _DEBUG_MODE_
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

int nLlenas(tpTablero &tablero) {
    int nLlenas = 0;
    for(int i = 0; i < tablero.ncols; i++) {
        for (int j = 0; j < tablero.nfils; j++) {
            if(tablero.matriz[i][j] == OCUPADA) {
                nLlenas++;
            }
        }
    }
    return nLlenas;
}

/* 
 * Pre: Tablero contiene el tablero en el estado actual, la solucionParcial contiene la lista de movimiento efectuados hasta ahora, y el caso 
 *      contiene el número de movimiento dentro del vector. 
 * Post: a lista de movimientos se le ha añadido el movimiento efectuado, y de tablero se ha eliminado la casilla necesaria.
 * 
 */
void getCoords(tpTablero &tablero, int caso, tpPosicion &posOr, tpPosicion &posDest, tpPosicion &posMed) {
    switch (caso)
    {
    case 0:
        posDest.x = posOr.x - 2;
        posDest.y = posOr.y - 2;
        posMed.x = posOr.x - 1;
        posMed.y = posOr.y - 1;
        break;
    case 1:
        posDest.x = posOr.x;
        posDest.y = posOr.y - 2;
        posMed.x = posOr.x;
        posMed.y = posOr.y - 1;
        break;
    case 2:
        posDest.x = posOr.x + 2;
        posDest.y = posOr.y - 2;
        posMed.x = posOr.x + 1;
        posMed.y = posOr.y - 1;
        break;
    case 3:
        posDest.x = posOr.x - 2;
        posDest.y = posOr.y;
        posMed.x = posOr.x - 1;
        posMed.y = posOr.y;
        break;
    case 4:
        posDest.x = posOr.x + 2;
        posDest.y = posOr.y;
        posMed.x = posOr.x + 1;
        posMed.y = posOr.y;
        break;
    case 5:

        break;
    case 6:
        posDest.x = posOr.x;
        posDest.y = posOr.y + 2;
        posMed.x = posOr.x;
        posMed.y = posOr.y + 1;
        break;
    case 7:
        posDest.x = posOr.x + 2;
        posDest.y = posOr.y + 2;
        posMed.x = posOr.x + 1;
        posMed.y = posOr.y + 1;
        break;
    default:
        break;
    }
}

void mover(tpTablero &tablero, tpListaMovimientos &solucionParcial,tpPosicion &posOr, tpPosicion &posDest, tpPosicion &posMed) {
    tablero.matriz[posOr.x][posOr.y] = VACIA;
    tablero.matriz[posMed.x][posMed.y] = VACIA;
    tablero.matriz[posDest.x][posDest.y] = OCUPADA;
    solucionParcial.movs[solucionParcial.numMovs].origen.x = posOr.x;
    solucionParcial.movs[solucionParcial.numMovs].destino.x = posDest.x;
    solucionParcial.movs[solucionParcial.numMovs].origen.y = posOr.y;
    solucionParcial.movs[solucionParcial.numMovs].destino.y = posDest.y;
    solucionParcial.numMovs++;
}

void deshacerMov(tpTablero &tablero, tpListaMovimientos &solucionParcial, tpPosicion &posOr, tpPosicion &posDest, tpPosicion &posMed) {
    tablero.matriz[posOr.x][posOr.y] = OCUPADA;
    tablero.matriz[posMed.x][posMed.y] = OCUPADA;
    tablero.matriz[posDest.x][posDest.y] = VACIA;
    solucionParcial.numMovs--;
}

char enumToToken(const tpEstadoCelda &celdaActual) {

    //assert(celdaActual == OCUPADA || celdaActual == NO_USADA || celdaActual == VACIA);
    if (celdaActual == NO_USADA) {
        return '-';
    }
    else if(celdaActual == OCUPADA) {
        return 'x';
    }
    else {
        return 'o';
    } 
}

bool estaLibre(const tpTablero &tablero,const tpPosicion &posicion) {
    if(tablero.matriz[posicion.x][posicion.y] == VACIA) {
        return true;
    }
    else {
        return false;
    }
}

bool estaLlena(const tpTablero &tablero,const tpPosicion &posicion) {
    if(tablero.matriz[posicion.x][posicion.y] == OCUPADA) {
        return true;
    }
    else {
        false;
    }
}

bool esDentro(const tpTablero &tablero,const tpPosicion &posicion) {
    if(posicion.x > 0 && posicion.y > 0 && posicion.x < tablero.ncols && posicion.y < tablero.nfils) {
        return true;
    }
    else {
        return false;
    }
}

bool sePuedeMover(const tpTablero &tablero, const tpPosicion &posicionLlegada, const tpPosicion &posicionMedio) {

    if(estaLibre(tablero, posicionLlegada) && estaLlena(tablero, posicionMedio) && esDentro(tablero, posicionLlegada)) {
        return true;
    }
    else {
        return false;
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
        
        //Declaramos variables necesarias para poder recorrer y leer el tablero
        char estado;
        int colAct = 0;
        int filAct = 0;
        char descarte;
        
        //Bucle para recorrer e inicializar el tablero
        while(f.get(estado)) {

            f.get(descarte);
            
            tpEstadoCelda estadoCelda;
            //Convertimos el token al valor de la enumeracion
            tokentoenum(estado, estadoCelda);
            //Guardamos el estado de la celda en la matriz
            tablero.matriz[colAct][filAct] = estadoCelda;
            // TRACE cout << tablero.matriz[colAct][filAct] << " " << colAct << " " << filAct << endl;
            
            //Necesario para poder recorrer el tablero
            colAct++;
            if(colAct == tablero.ncols) {
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
        cerr << "Ha habido algun problema abriendo el fichero: " << nombreFichero << endl;
    }

}

bool inicializarMovimientosValidos (const string nombreFichero, tpMovimientosValidos &movimientos) {
    TRACE("SE HAN INICIALIZADO LOS MOVS");
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
        cerr << "Ha habido algun problema abriendo el fichero: " << nombreFichero << endl;
    }
}

void mostrarTablero(const tpTablero &tablero) {

    for (int posy = 0; posy < tablero.nfils; posy++) {
        cout << endl;
        for(int posx = 0; posx < tablero.ncols; posx++) {
            
            cout << enumToToken(tablero.matriz[posx][posy]) << " ";
        }
    }
}

int buscaSolucion(tpTablero &tablero, const tpMovimientosValidos &movValidos, tpListaMovimientos &solucionParcial, const int retardo) {
    
    tpPosicion posOr;
    tpPosicion posDest;
    tpPosicion posMed;
    tpListaMovimientos listaMovs;
    
    //Caso base para se ha encontrado la solucion
    if (nLlenas(tablero) == 1) {
        cout << "Se ha resuelto el tablero en " << solucionParcial.numMovs << " movimientos." << endl;
        mostrarTablero(tablero);
        return 0;
    }
    //Mientras no se haya encontrado la solucion:
    else {
        //Bucle que recorre todas las casillas y todos los movimientos posibles
        for(int x = 0; x < tablero.ncols; x++) {
            for (int y = 0; y < tablero.nfils; y++) {
                for(int i = 0; i < 8; i++) {
                    //Inicializamos x e y con las coordinadas actuales
                    posOr.x = x;
                    posOr.y = y;
                    //Obtenemos las coordenadas destino y la media
                    getCoords(tablero, i, posOr, posDest, posMed);
                    
                    if(sePuedeMover(tablero, posDest, posMed)) {
                        //Si la ficha se puede mover la movemos
                        mover(tablero, listaMovs, posOr, posDest, posMed);
                        //Si el retardo es mayor de 0 mostramos
                        if(retardo > 0) {
                            mostrarTablero(tablero);
                            usleep(retardo*microsecond);
                        }
                        if (buscaSolucion(tablero, movValidos, solucionParcial, retardo) == 0){
                            return 0;
                            //Se ha encontrado la solucion
                        }
                        deshacerMov(tablero, solucionParcial, posOr, posDest, posMed);
                    }
                }
            }
        } 
        //No encontrado
        return -1;   
    }
}

void escribeListaMovimientos (string nombreFichero, const tpListaMovimientos &solucion) {
    TRACE("SE HA PASADO POR ELDM");
    //Creamos y abrimos el flujo
    ofstream f;
    f.open(nombreFichero);
    //Comprobamos si se ha abierto o creado con éxito
    if(f.is_open()) {
        //Comprobamos si no esta vacia la lista de solucion
        if(solucion.numMovs == 0) {
            f << "-1" << endl;
        }
        //En caso de que no este vacía:
        else {
            for(int i = 0; i < solucion.numMovs; i++) {
                //Guardamos, para cada movimiento, los movimientos realizados en el fichero
                f << solucion.movs[i].origen.x << ", " << solucion.movs[i].origen.y << ":" << solucion.movs[i].destino.x << ", " << solucion.movs[i].destino.y << endl;
            }
        }
    }
    else {
        //En caso de que no se haya podido abrir, imprimimos un error.
        cerr << "No se ha podido crear o abrir el fichero " << nombreFichero << "." << endl;
    }
}
