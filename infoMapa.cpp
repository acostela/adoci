/* 
 * File:   infoMapa.cpp
 * Author: asce
 * 
 * Created on 25 de mayo de 2010, 17:36
 */

#include "infoMapa.h"

hexagono_t::hexagono_t(int fil,int col){
    fila=fil;
    columna=col;
}

infoMapa::infoMapa() {
    filas = 0;
    columnas = 0;
    mapa = 0;
}

infoMapa::infoMapa(const infoMapa& orig) {
}

infoMapa::~infoMapa() {
    for (int i = 1; i < filas; i++)
        for (int j = 1; j < columnas; j++)
            delete mapa[i][j];
    for (int i = 1; i < filas; i++)
        delete[] mapa[i];
    delete[] mapa;
}

void infoMapa::inicializarPath(){
    for (int i = 1; i < filas; i++)
        for (int j = 1; j < columnas; j++){
            mapa[i][j]->g=0;
            mapa[i][j]->h=0;
            mapa[i][j]->padre=0;
        }
}

void infoMapa::inicializarMapa() {

    mapa = new hexagono_t**[filas];
    if (!mapa) {
        cerr << "\nError en la reserva de memoria\n";
        exit(1);
    }
    for (int i = 0; i < filas; i++) {
        if(i==0)
            mapa[i] = 0;
        else{            
            mapa[i] = new hexagono_t*[columnas];
            if (!mapa[i]) {
                cerr << "\nError en la reserva de memoria\n";
                exit(1);
            }
        }
    }
    for (int i = 1; i < filas; i++)
        for (int j = 0; j < columnas; j++){
            if(j == 0)
                mapa[i][j] = 0;
            else
                mapa[i][j] = new hexagono_t(i,j);

        }
}

void infoMapa::leeFich(string fichero) {
    string cad;
    ifstream fich(fichero.c_str()); //Creacion y apertura
    if (!fich) {
        cerr << "\nNo es posible abrir " << fichero << "\n";
        exit(1);
    }
    fich.ignore(1000, '\n'); //Ignoramos número mágico

    fich >> filas;
    filas=filas+1;
    fich >> columnas;
    columnas=columnas+1;
    //Para simplificar añadiremos una fila y una columna de más, ya que
    //en el mapa las filas y las columnas empiezan en 1 y en la matriz en 0
    if (!mapa)
        inicializarMapa();
    
    for (int i = 1; i < filas; i++)
        for (int j = 1; j < columnas; j++) {
            fich >> mapa[i][j]->nivel;
            fich >> mapa[i][j]->terreno;
            fich >> mapa[i][j]->objetoTerreno;
            fich >> mapa[i][j]->FCE;
            fich >> cad;
            mapa[i][j]->derrumbado = s2bool(cad);
            fich >> cad;
            mapa[i][j]->fuego = s2bool(cad);
            fich >> cad;
            mapa[i][j]->humo = s2bool(cad);
            fich >> mapa[i][j]->num_garrotes;
            for (int k = 0; k < 6; k++) {
                fich >> cad;
                mapa[i][j]->rioCentroCara[k] = s2bool(cad);
            }
            for (int k = 0; k < 6; k++) {
                fich >> cad;
                mapa[i][j]->carreteraCentroCara[k] = s2bool(cad);
            }
        }

}

int infoMapa::direccion_objetivo(hexagono_pos origen, hexagono_pos destino)
{
    /* Estrategia: Si la casilla objetivo está en la misma columna, la dirección será
       1 (si está arriba) o 4 (si está abajo). Si está en distinta fila y distinta
       columna, la dirección será la diagonal más apropiada
    */
    if(origen.columna == destino.columna){
        /* El mech objetivo está en la misma columna que el nuestro */
        if(origen.fila < destino.fila)
            return 4;             /* Abajo */
        else
            return 1;             /* Arriba */
    }
    else{
        if((origen.columna % 2) == 0){
            /* Columna par */
            if(origen.columna < destino.columna){
                if(origen.fila >= destino.fila)
                    return 2;     /* Diagonal arriba derecha */
                else
                    return 3;     /* Diagonal abajo derecha */
            }
            else{
                if(origen.fila >= destino.fila)
                    return 6;     /* Diagonal arriba izquierda */
                else
                    return 5;     /* Diagonal abajo izquierda */
            }
        }
        else{
            /* Columna impar */
            if(origen.columna < destino.columna){
                if(origen.fila > destino.fila)
                    return 2;     /* Diagonal arriba derecha */
                else
                    return 3;     /* Diagonal abajo derecha */
            }
            else{
                if(origen.fila > destino.fila)
                    return 6;     /* Diagonal arriba izquierda */
                else
                    return 5;     /* Diagonal abajo izquierda */
            }
        }
    }
    return 0;
}
/* Devuelve el coste del cambio de casilla. Si el movimiento es prohibido
 * devuelve -1
 */
int infoMapa::coste_mov_ady(int f_origen,int c_origen,int f_objetivo,int c_objetivo, int toneladas)
{
    int coste=0,
        col_ini = c_origen,
        fil_ini = f_origen,
        col_obj = c_objetivo,
        fil_obj = f_objetivo,
        dif_nivel;

    /* Coste del tipo de terreno */


    switch(mapa[fil_obj][col_obj]->terreno){
        case 0://ABIERTO:
            coste++;
            break;
        case 1://PAVIMENTADO:
            coste++;
            break;
        case 2://AGUA:
            switch (mapa[fil_obj][col_obj]->nivel){
                case 0:
                    coste++;
                    break;
                case -1:
                    coste+=2;
                    break;
                default:
                    coste+=4;
            }
            break;
        case 3://PANTANO:
            coste+=2;
            break;
    }
    /* Coste de objetos en el terreno */
    switch(mapa[fil_obj][col_obj]->objetoTerreno){
         //0-escombros, 1-bosque ligero, 2-bosque denso,
    //3-edificio ligero,4-edificio medio, 5-edificio pesado,
    //6-edificio reforzado, 7-búnker, 255-nada
        case 0://ESCOMBROS:
            coste+=2;
            break;
        case 1://B_LIGERO:
            coste+=2;
            break;
        case 2://B_DENSO:
            coste+=3;
            break;
        case 3://E_LIGERO:
        case 4://E_MEDIO:
        case 5://E_PESADO:
        case 6://E_REFORZADO:
        case 7://BUNKER:
            if(mapa[fil_obj][col_obj]->FCE < toneladas)
                return -1;
            break;
    }
    /* Coste del cambio de elevación */
    dif_nivel=abs(mapa[fil_ini][col_ini]->nivel - mapa[fil_obj][col_obj]->nivel);
    switch(dif_nivel){
        case 0:
            break;
        case 1:
            coste++;
            break;
        case 2:
            coste+=2;
            break;
        default:
            return -1;
    }
    return coste;
}

/* IMPORTANTE: Que esta función devuelva FALSE si la casilla objetivo se sale del tablero
 * y TRUE si no se sale */
/* Esta función modifica el array objetivo */
bool infoMapa::casilla_objetivo(hexagono_pos casilla, int direccion,hexagono_pos & objetivo)
{
    switch (direccion){
        case 1:
            objetivo.columna = casilla.columna;
            objetivo.fila = casilla.fila - 1;
            break;
        case 2:
            if(casilla.columna % 2 == 0){
                objetivo.columna=casilla.columna+1;
                objetivo.fila=casilla.fila;
            }
            else {
                objetivo.columna=casilla.columna+1;
                objetivo.fila=casilla.fila-1;
            }
            break;
        case 3:
            if(casilla.columna % 2 == 0){
                objetivo.columna=casilla.columna+1;
                objetivo.fila=casilla.fila+1;
            }
            else {
                objetivo.columna=casilla.columna+1;
                objetivo.fila=casilla.fila;
            }
            break;
        case 4:
            objetivo.columna=casilla.columna;
            objetivo.fila=casilla.fila+1;
            break;
        case 5:
            if(casilla.columna % 2 == 0){
                objetivo.columna=casilla.columna-1;
                objetivo.fila=casilla.fila+1;
            }
            else {
                objetivo.columna=casilla.columna-1;
                objetivo.fila=casilla.fila;
            }
            break;
        case 6:
            if(casilla.columna % 2 == 0){
                objetivo.columna=casilla.columna-1;
                objetivo.fila=casilla.fila;
            }
            else {
                objetivo.columna=casilla.columna-1;
                objetivo.fila=casilla.fila-1;
            }
            break;
    }
    if( (objetivo.columna < 1)           ||
        (objetivo.fila < 1)           ||
        (objetivo.columna >= columnas) ||
        (objetivo.fila >= filas)   )
        return false;
    else
        return true;
}

int infoMapa::distancia_casillas(hexagono_pos casilla_ini, hexagono_pos casilla_obj)
{
    hexagono_pos casilla_aux;

	if(casilla_ini.columna == casilla_obj.columna && casilla_ini.fila == casilla_obj.fila)
		return 0;
	else {
		if(	casilla_objetivo(casilla_ini, direccion_objetivo(casilla_ini, casilla_obj), casilla_aux))
			return 1 + distancia_casillas(casilla_aux, casilla_obj);
		else
			return -1;
	}
}
/* Devuelve la distancia en línea recta entre dos casillas */
float infoMapa::distancia(int col_ini, int fil_ini, int col_obj, int fil_obj)
{
    return sqrtf( (float)(col_ini - col_obj)*(col_ini - col_obj) +
                  (float)(fil_ini - fil_obj)*(fil_ini - fil_obj) );
}

