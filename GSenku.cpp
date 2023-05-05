#include "GSenku.hpp"
#include <iostream>
#include <assert.h>
#include<unistd.h>

#define _DEBUG_MODE_1
#define microsecond 1000000

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

/* TODO: Corregir movimientos.
 * Pre: Tablero contiene el tablero en el estado actual, la solucionParcial contiene la lista de movimiento efectuados hasta ahora, y el caso 
 *      contiene el número de movimiento dentro del vector. 
 * Post: a lista de movimientos se le ha añadido el movimiento efectuado, y de tablero se ha eliminado la casilla necesaria.
 * 
 */
bool validarYMover(tpTablero &tablero, tpListaMovimientos &solucionParcial, int caso,const int x,const  int y) {
    switch (caso)
    {
    case 0:
        if(tablero.matriz[x - 1][y - 1] == OCUPADA && x - 2 > 0 && y - 2 > 0) {
            solucionParcial.movs[solucionParcial.numMovs].destino.x = x - 2;
            solucionParcial.movs[solucionParcial.numMovs].destino.y = y - 2;
            tablero.matriz[x - 1][y - 1] = VACIA;
            solucionParcial.numMovs++;
            return true;
        }
        else {
            return false;
        }
        
        break;
    case 1:
        if(tablero.matriz[x][y - 1] == OCUPADA && y - 2 > 0) {
            solucionParcial.movs[solucionParcial.numMovs].destino.y = y - 2;
            tablero.matriz[x][y - 1] = VACIA;
            solucionParcial.numMovs++;
            return false;
        }
        else {
            return false;
        }
        
        break;
    case 2:
        if(tablero.matriz[x + 1][y - 1] == OCUPADA && x + 2 < tablero.ncols && y - 2 > 0) {
            solucionParcial.movs[solucionParcial.numMovs].destino.x = x + 2;
            solucionParcial.movs[solucionParcial.numMovs].destino.y = y - 2;
            tablero.matriz[x + 1][y + 1] = VACIA;
            solucionParcial.numMovs++;
            return true;
        }
        else {
            return false;
        }
        break;
    case 3:
        if(tablero.matriz[x - 1][y] == OCUPADA && x - 2 < 0) {
            solucionParcial.movs[solucionParcial.numMovs].destino.x = x - 2;
            tablero.matriz[x - 1][y] = VACIA;
            solucionParcial.numMovs++;
        return true;
        }
        else {
            return false;
        }
        break;
    case 4:
        if(tablero.matriz[x + 1][y] == OCUPADA && x + 2 < tablero.ncols) {
            solucionParcial.movs[solucionParcial.numMovs].destino.x = x + 2;
            tablero.matriz[x + 1][y] = VACIA;
            solucionParcial.numMovs++;
            return true;
        }
        else {
            return false;
        }
        break;
    case 5:
        if(tablero.matriz[x - 1][y + 1] == OCUPADA && x - 2 > 0 && y + 2 < tablero.nfils) {
            solucionParcial.movs[solucionParcial.numMovs].destino.x = x - 2;
            solucionParcial.movs[solucionParcial.numMovs].destino.y = y + 2;
            tablero.matriz[x - 1][y + 1] = VACIA;
            solucionParcial.numMovs++;
            return true;
        }
        else {
            return false;
        }
        
        break;
    case 6:
        if(tablero.matriz[x][y + 1] == OCUPADA && y + 2 < tablero.nfils) {
            solucionParcial.movs[solucionParcial.numMovs].destino.y = y + 2;
            tablero.matriz[x][y + 1] = VACIA;
            solucionParcial.numMovs++;
            return true;
        }
        else {
            return false;
        }

        break;
    case 7:
        if(tablero.matriz[x + 1][y + 1] == OCUPADA && x + 2 < tablero.ncols && y + 1 < tablero.nfils) {
            solucionParcial.movs[solucionParcial.numMovs].destino.x = x + 2;
            solucionParcial.movs[solucionParcial.numMovs].destino.y = y + 2;
            tablero.matriz[x + 1][y + 1] = VACIA;
            solucionParcial.numMovs++;
            return true;
        }
        else {
            return false;
        }
        
        break;
    default:
        return false;
        break;
    }
}

void deshacerMovimiento(tpTablero &tablero, tpListaMovimientos &solucionParcial, int caso,const int x,const  int y) {
    solucionParcial.numMovs--;
    switch (caso)
    {
    case 0:
        tablero.matriz[x - 1][y - 1] = OCUPADA;
        break;
    case 1:
            tablero.matriz[x][y - 1] = OCUPADA; 
        break;
    case 2:
        tablero.matriz[x + 1][y + 1] = OCUPADA;
        break;
    case 3:
        tablero.matriz[x - 1][y] = OCUPADA;
        break;
    case 4:
        tablero.matriz[x + 1][y] = OCUPADA;
        break;
    case 5:
        tablero.matriz[x - 1][y + 1] = OCUPADA; 
        break;
    case 6:
        tablero.matriz[x][y + 1] = OCUPADA;
        break;
    case 7:
        tablero.matriz[x + 1][y + 1] = OCUPADA;
        break;
    default:
        break;
    }
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
    if (nLlenas(tablero) == 1) {
        cout << "Se ha resuelto el tablero en " << solucionParcial.numMovs << " movimientos." << endl;
        mostrarTablero(tablero);
        return 0;
    }
    else {
        for(int x = 0; x < tablero.ncols; x++) {
            for (int y = 0; y < tablero.nfils; y++) {
                for(int i = 0; i < 8; i++) {
                    if(validarYMover(tablero, solucionParcial, i, x, y)) {
                        if(retardo > 0) {
                            mostrarTablero(tablero);
                            usleep(retardo*microsecond);
                        }
                        if (buscaSolucion(tablero, movValidos, solucionParcial, retardo) == 0){
                            return 0;
                            //Se ha encontrado la solucion
                        }
                    }
                    else if(solucionParcial.numMovs > 0){
                        deshacerMovimiento(tablero, solucionParcial, i, x, y);
                    }
                }
            }
        } 
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
