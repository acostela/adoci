/* 
 * File:   nodoArea.cpp
 * Author: asce
 * 
 * Created on 27 de mayo de 2012, 2:04
 */

#include "nodoArea.h"

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

void nodoArea::show()const {
    printf("Fila: %i, Columna %i, Distancia: %f\n",fila,columna,distancia);
}


void showNodosArea(const std::vector<nodoArea>& nodos){
    for(int i=0;i<nodos.size();i++)
        nodos[i].show();
    
}
