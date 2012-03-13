/* 
 * File:   movimiento.h
 * Author: asce
 *
 * Created on 29 de febrero de 2012, 14:50
 */
#include <vector>
#include "infoMapa.h"
using namespace std;

#ifndef MOVIMIENTO_H
#define	MOVIMIENTO_H

class node {
public:
    node();
    node(node & padr, int fila, int columna, int orienta, float heur);
    node(node & ini, node & dest, infoMapa* map, int pesoMech);
    //node(const node& orig);
    vector <node *> hijos;
    void expand();
    virtual ~node();
    float f();
    float g();
    float h();
    bool operator==(const node & nodo);
private:
    node * inicio;
    node * destino;
    infoMapa* mapa;
    float hVal;

    int peso;
    int fil;
    int col;
    int orientacion;
    node * padre;
    float costeDesdePadre();


};

void nodoEnEsaDireccion(int fila, int columna, int direccion, int & filaSiguiente, int & colSiguiente);

void aStar(node & inicio, node & destino, infoMapa *mapa, int tonelaje);


#endif	/* MOVIMIENTO_H */

