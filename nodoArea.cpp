/* 
 * File:   nodoArea.cpp
 * Author: asce
 * 
 * Created on 27 de mayo de 2012, 2:04
 */

#include "nodoArea.h"
#include "node.h"

nodoArea::nodoArea() {
}

nodoArea::nodoArea(int f, int c, float d) {
    fila = f;
    columna = c;
    distancia = d;
}

nodoArea::nodoArea(const nodoArea& orig) {
    fila = orig.fila;
    columna = orig.columna;
    distancia = orig.distancia;
}

nodoArea::~nodoArea() {
}

bool nodoArea::adyacenteNodoArea(const nodoArea & n, infoMapa* mapa)const {
    if (adyacente(fila, columna, n.fila, n.columna) == false)
        return false;

    int toneladas = mapa->info_mechs->mechJugador->defMechInfo->toneladas;
    int coste = mapa->coste_mov_ady(fila, columna, n.fila, n.columna, toneladas);
    if (coste != MOVIMIENTO_INVALIDO)
        return true;

}

void nodoArea::show()const {
    printf("Fila: %i, Columna %i, Distancia: %f\n", fila, columna, distancia);
}

bool nodoArea::operator==(const nodoArea & n)const {
    return fila == n.fila && columna == n.columna;

}

bool nodoArea::pertenece(const vector<nodoArea> & nodos)const {
    for (int i = 0; i < nodos.size(); i++) {
        if (*this == nodos[i])
            return true;
    }
    return false;
}

vector<nodoArea> nodoArea::getAdyacentes(infoMapa * mapa)const {
    vector<nodoArea> adyacentes;
    int f, c;
    for (int i = 1; i <= 6; i++) {
        nodoEnEsaDireccion(fila, columna, i, f, c);
        if (f >= 1 && f < mapa->filas && c >= 1 && c < mapa->columnas)
            adyacentes.push_back(nodoArea(f, c, -1));
    }
    return adyacentes;
}

vector<nodoArea> adyacentes(const vector<nodoArea> & anillo, infoMapa* mapa) {
    vector<nodoArea> tmp;
    vector<nodoArea> nodos_adyacentes;
    for (int i = 0; i < anillo.size(); i++) {
        tmp = anillo[i].getAdyacentes(mapa);
        for (int j = 0; j < tmp.size(); j++)
            if (tmp[j].pertenece(nodos_adyacentes) == false)
                nodos_adyacentes.push_back(tmp[j]);
    }
    return nodos_adyacentes;
}

vector<nodoArea> getAnillo(const vector<nodoArea> & anillo, const vector<nodoArea> & anillo_interior, infoMapa * mapa) {

    vector<nodoArea> anilloExterior;
    vector<nodoArea> ady = adyacentes(anillo, mapa);
    vector<nodoArea> ady_int = adyacentes(anillo_interior, mapa);

    for (int i = 0; i < ady.size(); i++) {
        if (ady[i].pertenece(ady_int) == false && ady[i].pertenece(anillo_interior) == false) {
            anilloExterior.push_back(ady[i]);
        }
    }
    return anilloExterior;
}

void showNodosArea(const std::vector<nodoArea>& nodos) {
    for (int i = 0; i < nodos.size(); i++)
        nodos[i].show();

}

vector<nodeVector> getAnillos(const nodoArea & centro, infoMapa * mapa) {

    vector<nodeVector> matrizAnillos;
    matrizAnillos.resize(7);
    vector<nodoArea> vacio;
    vacio.clear();

    //vector<nodeVector> anillo_centro;
    matrizAnillos[0].push_back(centro);
    matrizAnillos[1] = getAnillo(matrizAnillos[0], vacio, mapa);
    matrizAnillos[2] = getAnillo(matrizAnillos[1], matrizAnillos[0], mapa);
    matrizAnillos[3] = getAnillo(matrizAnillos[2], matrizAnillos[1], mapa);
    matrizAnillos[4] = getAnillo(matrizAnillos[3], matrizAnillos[2], mapa);
    matrizAnillos[5] = getAnillo(matrizAnillos[4], matrizAnillos[3], mapa);
    matrizAnillos[6] = getAnillo(matrizAnillos[5], matrizAnillos[4], mapa);

    return matrizAnillos;
}

void nodoArea::evaluaHuir(int f, int c, int enc) {
    float d = distanciaNodos(fila, columna, f, c);
    evaluacionHuir = d;
}

void cobertura(int niveles, vector<nodeVector> & anillos, int & fil_dest, int & col_dest, int f_obj, int c_obj, int enc) {
    cin.get();
    float mayor = 0;
    for (int i = 1; i < niveles; i++) {
        for (int j = 0; j < anillos[i].size(); j++){
                
                anillos[i][j].evaluaHuir(f_obj, c_obj, enc);
            
        }
    }
    for (int i = 1; i < niveles; i++) {
        for (int j = 0; j < anillos[i].size(); j++)
            if (anillos[i][j].evaluacionHuir > mayor) {
                
                mayor = anillos[i][j].evaluacionHuir;
                fil_dest = anillos[i][j].fila;
                col_dest = anillos[i][j].columna;
            }
    }

}


