/* 
 * File:   movimiento.cpp
 * Author: asce
 * 
 * Created on 29 de febrero de 2012, 14:50
 */

#include "movimiento.h"

node::node(int fila, int columna, int orient, infoMapa* map, int pesoMech) {
    fil = fila;
    col = columna;
    mapa = map;
    padre = 0;
    inicio = 0;
    destino = 0;
    peso = pesoMech;
    hVal = -1;
    orientacion = orient;
    hijos.clear();
}

node::node(int fila, int columna, int orient, node * destino, infoMapa* map, int pesoMech) {
    fil = fila;
    col = columna;
    mapa = map;
    padre = 0;
    inicio = 0;
    peso = pesoMech;
    hVal = -1;
    hijos.clear();
    orientacion = orient;
    this->destino = destino;
}

node::node(node * padr, int fila, int columna, int orienta, float heur) {
    inicio = padr->inicio;
    destino = padr->destino;
    mapa = padr->mapa;
    peso = padr->peso;
    fil = fila;
    col = columna;
    orientacion = orienta;
    hVal = heur;
    padre = padr;
}

node::node(node * ini, node * dest, infoMapa* map, int pesoMech) {
    inicio = ini;
    destino = dest;
    mapa = map;
    peso = pesoMech;
    hVal = -1;
    padre = 0;
    hijos.clear();
}
void node::showPath(){
    node* nodePointer;
    nodePointer=this;
    printf("\n\nCamino->\n");
    while(nodePointer->padre!=0){
        nodePointer->showInfo();
        nodePointer=nodePointer->padre;
    }
    printf("Fin de camino--------------------\n\n");
    
}

float distanciaNodos(int forigen, int corigen, int fdestino, int cdestino) {
    float val = sqrt((forigen - fdestino)*(forigen - fdestino)+
            (corigen - cdestino)*(corigen - cdestino));
    return val;
}

void nodoEnEsaDireccion(int fil, int col, int direccion, int & filaSiguiente, int & colSiguiente) {
    if (direccion == 1 || direccion == 4) {
        if (direccion == 1)
            filaSiguiente = fil - 1;

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
                cout << "OrientaciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n invalida!!" << endl;
                cout << "OrientaciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n: " << direccion << endl;
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
                cout << "OrientaciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n invalida!!" << endl;
                exit(0);
        }
    }
}

node::~node() {
    for (int i = 0; i < hijos.size(); i++)
        if (hijos[i] != 0)
            delete hijos[i];
}

void node::showInfo() {
    printf("Fila: %i\nColumna: %i\nOrientacion: %i\nNum. Hijos: %i\n", fil, col, orientacion, hijos.size());
    printf("f: %f, g: %f, h: %f\n", f(), g(), h());

//    if (padre != 0) {
//        printf("----------------------------\nInfo. Padre:\n");
//        padre->showInfo();
//        printf("----------------------------\n\n");
//    }

}

void node::showInfoHijos() {
    cout << "INFO HIJOS:------------" << endl;
    for (int i = 0; i < hijos.size(); i++)
        hijos[i]->showInfo();
}
//void node::expand() {
//    hijos.resize(3);
//    int anterior = orientacion - 1;
//    if (anterior == 0)
//        anterior = 6;
//    int siguiente = orientacion + 1;
//    if (siguiente == 7)
//        siguiente = 1;
//    int filhijo;
//    int colhijo;
//    //printf("Vamos a crear los hijos...\n");
//
//    float distAdest = distanciaNodos(fil, col, destino->fil, destino->col);
//    float valH;
//    //printf("Vamos a crear los hijos...\n");
//    nodoEnEsaDireccion(fil, col, anterior, filhijo, colhijo);
//    if (filhijo > 0 && filhijo < mapa->filas && colhijo > 0 && colhijo < mapa->columnas)
//        valH = distanciaNodos(filhijo, colhijo, destino->fil, destino->col);
//    else valH = distAdest + 1;
//    hijos[0] = new node(this, fil, col, anterior, 1 + valH);
//    //printf("Creado hijo 0\n");
//
//    nodoEnEsaDireccion(fil, col, siguiente, filhijo, colhijo);
//    if (filhijo > 0 && filhijo < mapa->filas && colhijo > 0 && colhijo < mapa->columnas)
//        valH = distanciaNodos(filhijo, colhijo, destino->fil, destino->col);
//    else valH = distAdest + 1;
//    hijos[1] = new node(this, fil, col, siguiente, 1 + valH);
//    //printf("Creado hijo 1\n");
//
//
//    nodoEnEsaDireccion(fil, col, orientacion, filhijo, colhijo);
//    if (filhijo > 0 && filhijo < mapa->filas && colhijo > 0 && colhijo < mapa->columnas)
//        hijos[2] = new node(this, filhijo, colhijo, orientacion, -1);
//    else {
//        hijos[2] = 0;
//        hijos.resize(2);
//    }
//    //printf("Creado hijo 2\n");
//
//    //showInfoHijos();
//
//}
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
    //printf("Vamos a crear los hijos...\n");

    //printf("Vamos a crear los hijos...\n");
    nodoEnEsaDireccion(fil, col, anterior, filhijo, colhijo);
    hijos[0] = new node(this, fil, col, anterior,-1);
    //printf("Creado hijo 0\n");
    
    nodoEnEsaDireccion(fil, col, siguiente, filhijo, colhijo);
    hijos[1] = new node(this, fil, col, siguiente,-1);
    //printf("Creado hijo 1\n");


    nodoEnEsaDireccion(fil, col, orientacion, filhijo, colhijo);
    if (filhijo > 0 && filhijo < mapa->filas && colhijo > 0 && colhijo < mapa->columnas)
        hijos[2] = new node(this, filhijo, colhijo, orientacion, -1);
    else {
        hijos[2] = 0;
        hijos.resize(2);
    }
    //printf("Creado hijo 2\n");

    //showInfoHijos();

}

float node::g() {
    if(padre==0)
        return 0;
    else
        return costeDesdePadre() + padre->g();
}

float node::costeDesdePadre() {
    float valor = 0;
    if (padre == 0)
        return 0;
    if (*padre == *this)//es un movimiento de giro en un hexÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡gono
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
    float fV = gV + hV;
    return fV;
}
node& node::operator=(const node & nodo){
    this->col=nodo.col;
    this->fil=nodo.fil;
    this->destino=nodo.destino;
    this->hVal=nodo.hVal;
    this->hijos=nodo.hijos;
    this->inicio=nodo.inicio;
    this->mapa=nodo.mapa;
    this->orientacion=nodo.orientacion;
    this->padre=nodo.padre;
    this->peso=nodo.peso;
}

bool node::operator==(const node & nodo) {
    return fil == nodo.fil && col == nodo.col && orientacion == nodo.orientacion;
}

int buscarMejor(vector<node*> nodos) {//busca menor f
    float menor = nodos[0]->f();
    float valor;
    int ind = 0;
    for (int i = 0; i < nodos.size(); i++) {
        valor = nodos[i]->f();
        if (valor < menor) {
            menor = valor;
            ind = i;
        }
    }
//    printf("\nContenido del buffer de nodos:\n");
//    for (int i = 0; i < nodos.size(); i++) {
//        nodos[i]->showInfo();
//        printf("f: %i\n",nodos[i]->f());
//        printf("g: %i\n",nodos[i]->g());
//        printf("h: %i\n",nodos[i]->h());
//    }
//printf("\nFin de contenido del buffer\n");
    return ind;
    
}

int contenidoEn(vector<node*> nodos, const node& n) {
    for (int i = 0; i < nodos.size(); i++) {
        if (*nodos[i] == n)
            return i;
    }
    return 0;
}

void aStar(node * inicio, node * destino, infoMapa *mapa, int tonelaje) {
    vector<node*> abiertos;
    //inicio->h();
    abiertos.push_back(inicio);
    vector<node*> cerrados;
    bool fin = false;
    int mejor;
    int nInd;
    while (!fin) {
        mejor = buscarMejor(abiertos);
//        cout<<"Elegido Nodo ..."<<endl;
//        abiertos[mejor]->showInfo();
//        cout<<"----------"<<endl;
//        cout<<"de entre los siguientes: -->"<<endl;
//        for(int i=0;i<abiertos.size();i++){
//            abiertos[i]->showInfo();
//        }
//                cout<<"-----------------------------\n"<<endl;


        
        //cin.get();
        if (*abiertos[mejor] == *destino){
            fin = true;
            printf("Alcanzado destino:\n-->\n");
            abiertos[mejor]->showPath();
        }
        else {
            abiertos[mejor]->expand();
            cerrados.push_back(abiertos[mejor]);
            for (int i = 0; i < abiertos[mejor]->hijos.size(); i++) {
                if (abiertos[mejor]->hijos[i] != 0) {
                    if ((nInd = contenidoEn(abiertos, *abiertos[mejor]->hijos[i])) != 0) {
                        //insertarlo manteniendo info del mejor padre.
                        if (abiertos[nInd]->f() > abiertos[mejor]->hijos[i]->f()){
                            //abiertos[nInd]->showInfo();
                            //abiertos[mejor]->hijos[i]->showInfo();
                            abiertos[nInd] = abiertos[mejor]->hijos[i];
                            
                        }
                    } else if ((nInd = contenidoEn(cerrados, *abiertos[mejor]->hijos[i])) != 0) {
                        //insertarlo manteniendo info del mejor padre y actualizar info de descendientes
                        if (cerrados[nInd]->f() > abiertos[mejor]->hijos[i]->f()) {
                            //cerrados[nInd]->padre=abiertos[mejor]->hijos[i]->padre;
                            abiertos[mejor]->hijos[i]->hijos = cerrados[nInd]->hijos; //enlazo descendientes
                            cerrados[nInd] = abiertos[mejor]->hijos[i]; //sustituyo
                        }
                    } else {
                        abiertos.push_back(abiertos[mejor]->hijos[i]); //insertarlo como un nuevo nodo en abiertos
                    }
                }
            }
            abiertos.erase(abiertos.begin()+mejor);
            
        }
        if(abiertos.empty()){
            fin=true;
            printf("No se ha alcanzado destino...\nNo se converge a la soluciÃƒÂ³n.\n");
        }
    }


}

