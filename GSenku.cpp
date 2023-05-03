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
/*
 * Pre: Tablero contiene el tablero en el estado actual, la solucionParcial contiene la lista de movimiento efectuados hasta ahora, y el caso 
 *      contiene el número de movimiento dentro del vector. 
 * Post: a lista de movimientos se le ha añadido el movimiento efectuado, y de tablero se ha eliminado la casilla necesaria.
 * 
 */
void moverFicha(tpTablero &tablero, tpListaMovimientoss &solucionParcial, int caso) {
    switch (case)
    {
    case 1:
        solucionParcial.movs[solucionParcial.numMovs].destino.x = solucionParcial.movs[solucionParcial.numMovs].destino.x - 2;
        solucionParcial.movs[solucionParcial.numMovs].destino.y = solucionParcial.movs[solucionParcial.numMovs].destino.y - 2;
        tablero.matriz[solucionParcial.movs[solucionParcial.numMovs].destino.x - 1][solucionParcial.movs[solucionParcial.numMovs].destino.y - 1] = VACIA;
        break;
    case 2;
        solucionParcial.movs[solucionParcial.numMovs].destino.y = solucionParcial.movs[solucionParcial.numMovs].destino.y - 2;
        tablero.matriz[solucionParcial.movs[solucionParcial.numMovs].destino.x][solucionParcial.movs[solucionParcial.numMovs].destino.y - 1] = VACIA;
        break;
    case 3:
        solucionParcial.movs[solucionParcial.numMovs].destino.x = solucionParcial.movs[solucionParcial.numMovs].destino.x + 2;
        solucionParcial.movs[solucionParcial.numMovs].destino.y = solucionParcial.movs[solucionParcial.numMovs].destino.y - 2;
        tablero.matriz[solucionParcial.movs[solucionParcial.numMovs].destino.x + 1][solucionParcial.movs[solucionParcial.numMovs].destino.y - 1] = VACIA;
        break;
    case 4:
        solucionParcial.movs[solucionParcial.numMovs].destino.x = solucionParcial.movs[solucionParcial.numMovs].destino.x - 2;
        tablero.matriz[solucionParcial.movs[solucionParcial.numMovs].destino.x - 1][solucionParcial.movs[solucionParcial.numMovs].destino.y] = VACIA;
        break;
    case 5:
        solucionParcial.movs[solucionParcial.numMovs].destino.x = solucionParcial.movs[solucionParcial.numMovs].destino.x + 2;
        tablero.matriz[solucionParcial.movs[solucionParcial.numMovs].destino.x + 1][solucionParcial.movs[solucionParcial.numMovs].destino.y] = VACIA;
        break;
    case 6:
        solucionParcial.movs[solucionParcial.numMovs].destino.x = solucionParcial.movs[solucionParcial.numMovs].destino.x - 2;
        solucionParcial.movs[solucionParcial.numMovs].destino.y = solucionParcial.movs[solucionParcial.numMovs].destino.y + 2;
        tablero.matriz[solucionParcial.movs[solucionParcial.numMovs].destino.x - 1][solucionParcial.movs[solucionParcial.numMovs].destino.y + 1] = VACIA;
        break;
    case 7:
        solucionParcial.movs[solucionParcial.numMovs].destino.y = solucionParcial.movs[solucionParcial.numMovs].destino.y + 2;
        tablero.matriz[solucionParcial.movs[solucionParcial.numMovs].destino.x][solucionParcial.movs[solucionParcial.numMovs].destino.y + 1] = VACIA;
        break;
    case 8:
        solucionParcial.movs[solucionParcial.numMovs].destino.x = solucionParcial.movs[solucionParcial.numMovs].destino.x + 2;
        solucionParcial.movs[solucionParcial.numMovs].destino.y = solucionParcial.movs[solucionParcial.numMovs].destino.y + 2;
        tablero.matriz[solucionParcial.movs[solucionParcial.numMovs].destino.x + 1][solucionParcial.movs[solucionParcial.numMovs].destino.y + 1] = VACIA;
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
            //Nos quitamos los espacios y los saltos de línea
            f.get(descarte)   ;     

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
    int posx = tablero.ncols;
    int posy = tablero.nfils;
    

    for (int posx = tablero.ncols - 1; posx >= 0; posx--) {
        for(int posy = tablero.nfils - 1; posy >= 0; posy--) {
            
            cout << enumToToken(tablero.matriz[posx][posy]) << " ";

            if(posy == 0) {
                cout << endl;
            }
        }
    }
}

void escribeListaMovimientos (string nombreFichero, const tpListaMovimientos &solucion) {
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

int buscaSolucion(tpTablero &tablero, const tpMovimientosValidos &movValidos, tpListaMovimientos &solucionParcial, const int retardo=0) {
    if (estaVacio(tablero)) {
        return 0; 
    }

    else if(!esValido) {

    }

    else {
        if(retardo > 0) {
            mostrarTablero(tablero)
        }
    }
    
}
