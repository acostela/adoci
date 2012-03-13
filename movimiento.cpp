/* 
 * File:   movimiento.cpp
 * Author: asce
 * 
 * Created on 29 de febrero de 2012, 14:50
 */

#include "movimiento.h"

node::node() {

}

float distanciaNodos(int forigen, int corigen, int fdestino, int cdestino) {
    float val = sqrt((forigen - fdestino)*(forigen - fdestino)+
            (corigen - cdestino)*(corigen - cdestino));
    return val;
}

void nodoEnEsaDireccion(int fil, int col, int direccion, int & filaSiguiente, int & colSiguiente) {
    if (direccion == 1 || direccion == 4) {
        if (direccion == 1)
            filaSiguiente = fil + 1;

        else if (direccion == 4)
            filaSiguiente = fil + 1;
        colSiguiente = col;

    } else if (col % 2 == 0) {//col par
        switch (direccion) {
            case 2:
                filaSiguiente = fil;
                colSiguiente = col + 1;
                break;
            case 3:
                filaSiguiente = fil + 1;
                colSiguiente = col + 1;
                break;
            case 5:
                filaSiguiente = fil + 1;
                colSiguiente = col - 1;
                break;
            case 6:
                filaSiguiente = fil;
                colSiguiente = col - 1;
                break;
            default:
                cout << "Orientación invalida!!" << endl;
                exit(0);
        }

    } else {
        switch (direccion) {
            case 2:
                filaSiguiente = fil - 1;
                colSiguiente = col + 1;
                break;
            case 3:
                filaSiguiente = fil;
                colSiguiente = col + 1;
                break;
            case 5:
                filaSiguiente = fil;
                colSiguiente = col - 1;
                break;
            case 6:
                filaSiguiente = fil - 1;
                colSiguiente = col - 1;
                break;
            default:
                cout << "Orientación invalida!!" << endl;
                exit(0);
        }
    }
}

node::node(node & padr, int fila, int columna, int orienta, float heur) {
    inicio = padr.inicio;
    destino = padr.destino;
    mapa = padr.mapa;
    peso = padr.peso;
    fil = fila;
    col = columna;
    orientacion = orienta;
    hVal = heur;
    padre=&padr;
}

node::node(node & ini, node & dest, infoMapa* map, int pesoMech) {
    inicio=&ini;
    destino=&dest;
    mapa = map;
    peso = pesoMech;
    hVal = -1;
    padre=0;
    hijos.clear();
}

node::~node() {
    for (int i = 0; i < hijos.size(); i++)
        if (hijos[i] != 0)
            delete hijos[i];
}

void node::expand() {
    hijos.resize(3);
    int anterior = orientacion - 1;
    if (anterior == 0)
        anterior = 6;
    int siguiente = orientacion + 1;
    if (siguiente == 7)
        siguiente = 1;
    int filhijo;
    int colhijo;
    float distAdest=distanciaNodos(fil, col, destino->fil, destino->col);
    float valH;
    
    nodoEnEsaDireccion(fil, col, anterior, filhijo, colhijo);
    if (filhijo > 1 && filhijo < mapa->filas && colhijo > 1 && colhijo < mapa->columnas)
        valH=distanciaNodos(filhijo, colhijo, destino->fil, destino->col);
    else valH=distAdest+1;
    hijos[0] = new node(*this, fil, col, anterior, 1 + valH);
    
    nodoEnEsaDireccion(fil, col, siguiente, filhijo, colhijo);
    if (filhijo > 1 && filhijo < mapa->filas && colhijo > 1 && colhijo < mapa->columnas)
        valH=distanciaNodos(filhijo, colhijo, destino->fil, destino->col);
    else valH=distAdest+1;
    hijos[1] = new node(*this, fil, col, siguiente, 1 + valH);
    
    nodoEnEsaDireccion(fil, col, orientacion, filhijo, colhijo);
    if (filhijo > 1 && filhijo < mapa->filas && colhijo > 1 && colhijo < mapa->columnas)
        hijos[2] = new node(*this, filhijo, colhijo, orientacion, -1);
    else hijos[2] = 0;

}

float node::g() {
    return costeDesdePadre() + padre->g();
}

float node::costeDesdePadre() {
    float valor = 0;
    if (padre == 0)
        return 0;
    if(*padre==*this)//es un movimiento de giro en un hexágono
        return 1;
    valor = mapa->coste_mov_ady(padre->fil, padre->col, this->fil, this->col, peso);
    return valor;
}

float node::h() {
    if (hVal == -1) {
        hVal = distanciaNodos(this->fil, this->col, destino->fil, destino->col);
    }
    return hVal;
}

float node::f() {
    float gV = g();
    float hV = h();
    return gV + hV;
}

bool node::operator==(const node & nodo){
    return fil==nodo.fil && col==nodo.col;
}
//inicio y destino ya están inicializados
int buscarMejor(vector<node> nodos){//busca menor f
    float menor=nodos[0].f();
    float valor;
    int ind=0;
    for(int i=0;i<nodos.size();i++){
        valor = nodos[i].f();
        if(valor < menor){
            menor=valor;
            ind=i;
        }
    }
    return ind;
}
bool contenidoEn(vector<node> nodos,const node& n){
        for(int i=0;i<nodos.size();i++){
            if(nodos[i]==n)
                return true;
        }
        return false;
}
void aStar(node & inicio, node & destino,infoMapa *mapa,int tonelaje){
    vector<node> abiertos;
    abiertos.push_back(inicio);
    vector<node> cerrados;
    bool fin=false;
    int mejor;
    while(!fin){
        mejor = buscarMejor(abiertos);
        if(abiertos[mejor]==destino)
            fin=true;
        else{
            abiertos[mejor].expand();
            for(int i=0;i<abiertos[mejor].hijos.size();i++){
                if(abiertos[mejor].hijos[i]!=0){
                    if(contenidoEn(abiertos,*abiertos[mejor].hijos[i])){
                        ;//insertarlo manteniendo info del mejor padre.
                    }else if(contenidoEn(cerrados,*abiertos[mejor].hijos[i])){
                        ;//insertarlo manteniendo info del mejor padre y actualizar info de descendientes
                    }else{
                        ;//insertarlo como un nuevo nodo en abiertos
                    }
                }
                
            }
        }
    }
    
    
}

