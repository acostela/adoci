/* 
 * File:   acciones.cpp
 * Author: asce
 * 
 * Created on 31 de mayo de 2010, 14:21
 */

#include "acciones.h"
using namespace std;

acciones::acciones(string numJ, infoMapa* mapa, infoMechs* mechs, OpcionesJuego* opts) {
    informacion_mapa = mapa;
    informacion_mechs = mechs;
    informacion_juego = opts;
    numeroJugador = numJ;
    mov = 0;
    reaccion = 0;
    armas = 0;
    fisico = 0;
    final = 0;
}

acciones::acciones(const acciones& orig) {
}

acciones::~acciones() {

    if (mov != 0)
        delete mov;

    if (reaccion != 0)
        delete reaccion;

    if (armas != 0)
        delete armas;

    if (fisico != 0)
        delete fisico;

    if (final != 0)
        delete final;

}

void acciones::salida(string cad) {

    if (cad == "Movimiento") {
        mov = new movimiento_t(informacion_mapa,informacion_mechs);
        mov->logica_movimiento();
        mov->salida(numeroJugador);
    }
    if (cad == "Reaccion") {
        reaccion = new reaccion_t(informacion_mapa,informacion_mechs);
        reaccion->reaccion_accion();
        reaccion->salida(numeroJugador);
    }
    if (cad == "AtaqueArmas") {
        armas = new ataque_armas_t(informacion_mapa, informacion_mechs);
        armas->ataque_arma();
        armas->salida(numeroJugador);
    }
    if (cad == "AtaqueFisico") {
        fisico = new ataque_fisico_t(informacion_mapa,informacion_mechs);
        fisico->ataque_fisico();
        fisico->salida(numeroJugador);
    }
    if (cad == "FinalTurno") {
        final = new final_t;
        final->salida(numeroJugador);
    }


}

//void acciones::posiciones_adyacentes(int f, int c, int adyacentes[][2]) {
//    //Arriba
//    adyacentes[0][0] = f - 1;
//    adyacentes[0][1] = c;
//    //Abajo
//    adyacentes[3][0] = f + 1;
//    adyacentes[3][1] = c;
//
//    if (c % 2 != 0) {
//        adyacentes[1][0] = f - 1;
//        adyacentes[1][1] = c + 1;
//
//        adyacentes[2][0] = f;
//        adyacentes[2][1] = c + 1;
//
//        adyacentes[4][0] = f;
//        adyacentes[4][1] = c - 1;
//
//        adyacentes[5][0] = f - 1;
//        adyacentes[5][1] = c - 1;
//    } else {
//
//        adyacentes[1][0] = f;
//        adyacentes[1][1] = c + 1;
//
//        adyacentes[2][0] = f + 1;
//        adyacentes[2][1] = c + 1;
//
//        adyacentes[4][0] = f + 1;
//        adyacentes[4][1] = c - 1;
//
//        adyacentes[5][0] = f;
//        adyacentes[5][1] = c - 1;
//    }
//}
//
//bool acciones::dentroMapa(int fila, int columna) {
//    return ( (fila > 1 && (fila < informacion_mapa->filas)) &&
//            (columna > 1 && (columna < informacion_mapa->columnas)));
//
//}
//
//int acciones::obtenerLocalizacionMunicion(iMech mech, Componente_Mech arma) {
//    int codigoMunicion = 0;
//
//    for (int i = 0; i < mech.defMechInfo->num_componentes; i++) {
//        if (mech.defMechInfo->componentes[i].codigoArma == arma.codigo)
//            codigoMunicion = mech.defMechInfo->componentes[i].codigo;
//    }
//
//    if (codigoMunicion != 0) {
//        for (int i = 0; i < 8; i++) { // Para cada localizacion
//            for (int j = 0; j < mech.defMechInfo->localizaciones[i].slots_ocupados; j++) { // MIramos en cada slot
//                if ((mech.defMechInfo->localizaciones[i].slots[j].codigo == codigoMunicion)
//                        && (mech.defMechInfo->componentes[mech.defMechInfo->localizaciones[i].slots[j].indice_componente].cantidad > 0))
//                    return i;
//            }
//        }
//    }
//    return -1;
//}
//
//int acciones::obtenerSlotArma(iMech mech, Componente_Mech arma) {
//    for (int i = 0; i < mech.defMechInfo->localizaciones[arma.localizacion].slots_ocupados; i++) {
//        if (mech.defMechInfo->localizaciones[arma.localizacion].slots[i].codigo == arma.codigo)
//            return i;
//    }
//    return -1;
//}
////string acciones::mover(hexagono_pos destino) {
////    //AÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â±adir obstaculos mechs!
////    bool stop = false;
////    int f_ini;
////    int c_ini;
////    int i_actual, j_actual;
////    int i_tmp, j_tmp;
////    int toneladas = 100; //leer de defmech
////    int coste_mov;
////    string salida;
////
////    priority_queue<path_pos_t, vector<path_pos_t>, greater <vector<path_pos_t>::value_type> > l_abierta;
////
////    int adyacentes[6][2]; //6 hexÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡gnos adyacentes como mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ximo
////    int filas = informacion_mapa->filas;
////    int columnas = informacion_mapa->columnas;
////    path_pos_t path_map[filas][columnas];
////    path_pos_t hex_tmp;
////    for (int i = 0; i < filas; i++)
////        for (int j = 0; j < columnas; j++) {
////            path_map[i][j].fila=i;
////            path_map[i][j].columna=j;
////        }
////
////
////    f_ini = informacion_mechs->mechJugador->pos_Hexagono.fila;
////    c_ini = informacion_mechs->mechJugador->pos_Hexagono.columna;
////    l_abierta.push(path_map[f_ini][c_ini]);
////    path_map[f_ini][c_ini].en_abierta = true;
////    while (stop == false) {
////        //Cambiar elemento de cola
////        path_pos_t tmp;
////        tmp=l_abierta.top();
////        i_actual=l_abierta.top().fila;
////        j_actual=l_abierta.top().columna;
////        //salida=salida+"->"+tmp.posicion_h().stringPos();//No se puede reconstruir asÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­ el camino, elige posiciones incorrectas de la lista de abierta, adyacentes a posiciones anteriores.
////        l_abierta.pop();
////        path_map[i_actual][j_actual].en_abierta = false;
////        path_map[i_actual][j_actual].en_cerrada = true;
////        //Cambiado
////        posiciones_adyacentes(i_actual, j_actual, adyacentes);
////        for (int i = 0; i < 6; i++) {
////            i_tmp = adyacentes[i][0];
////            j_tmp = adyacentes[i][1];
////            if (dentroMapa(i_tmp, j_tmp))
////                if (!path_map[i_tmp][j_tmp].en_cerrada) {
////                    coste_mov = informacion_mapa->coste_mov_ady(path_map[i_actual][j_actual].posicion_h(), path_map[i_tmp][j_tmp].posicion_h(), toneladas);
////                    hex_tmp.fila_padre = i_actual;
////                    hex_tmp.columna_padre = j_actual;
////                    hex_tmp.fila=i_tmp;
////                    hex_tmp.columna=j_tmp;
////                    hex_tmp.g = coste_mov*9;
////                    hex_tmp.h = informacion_mapa->distancia_casillas(path_map[i_tmp][j_tmp].posicion_h(), destino)*10;
////                    hex_tmp.funcion();
////                    if(hex_tmp.posicion_h()==destino){
////                        hex_tmp.f-=10;
////                    }
////
////                    if (coste_mov == -1){
////                        path_map[i_tmp][j_tmp].valido = false;
////                    }
////                    if (path_map[i_tmp][j_tmp].valido) {
////                        if (!(path_map[i_tmp][j_tmp].en_abierta)) {
////                            hex_tmp.en_abierta=true;
////                            l_abierta.push(hex_tmp);
////                            path_map[i_tmp][j_tmp]= hex_tmp;
////                        } else {
////                            //Buscar en la lista de abierta, comparar el valor de g, si mayor , actualizar campos.
////                            cambia(l_abierta, hex_tmp);//ERROR en cambia!!
////
////                        }
////                    }
////                }
////        }
////        if (l_abierta.empty() || path_map[destino.fila][destino.columna].en_cerrada==true)
////            stop = true;
////    }
////   // if(path_map[destino.fila][destino.columna].en_cerrada==false)
////        //return "Error";
////    int fila_padre=destino.fila;
////    int columna_padre=destino.columna;
////    while(fila_padre!=-1 && columna_padre!=-1){//Error en alguna parte al reconstruir, enlaces malos.
////        salida=path_map[fila_padre][columna_padre].posicion_h().stringPos()+"->"+salida;
////        fila_padre=path_map[fila_padre][columna_padre].fila_padre;
////        columna_padre=path_map[fila_padre][columna_padre].columna_padre;
////    }
////
////    return salida;
////}
//
////path_pos_t::path_pos_t() {
////    valido = true;
////    en_cerrada = false;
////    en_abierta = false;
////    fila_padre = -1;
////    columna_padre = -1;
////    g = -1;
////    h = -1;
////    f = -1;
////}
////
////int acciones::angulo_mech(int mech_obj) {
////    int alto, ancho, fila, columna, fila_init;
////
////    alto = informacion_mapa->filas;
////    ancho = informacion_mapa->columnas;
////
////    switch (informacion_mechs->mechJugador->encaramiento_torso) {
////        case 1:
////            /*Mirar adelante*/
////            for (int i = 1; i < informacion_mechs->mechJugador->pos_Hexagono.fila; i++) {
////                if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == informacion_mechs->mechJugador->pos_Hexagono.columna)
////                        && (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == i)) {
////                    return FRONTAL;
////                }
////            }
////            /* Mirar las casillas en la diagonal superior izquierda */
////            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
////                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila - 1)*2 - 2;
////            else
////                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2 - 1;
////            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna - 1; (i > 0) && ((fila_init / 2) > 0); --i, --fila_init) {
////                for (int j = fila_init / 2; j > 0; --j) {
////                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
////                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
////                        return FRONTAL;
////                }
////            }
////            /* Mirar las casillas en la diagonal superior derecha */
////            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
////                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila - 1)*2 - 2;
////            else
////                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2 - 1;
////            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna + 1; (i < informacion_mapa->columnas) && ((fila_init / 2) > 0); ++i, --fila_init) {
////                for (int j = fila_init / 2; j > 0; --j) {
////                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
////                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
////                        return FRONTAL;
////                }
////            }
////            /* Mirar toda la lÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­nea de casillas que tiene detrÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s */
////            for (int i = informacion_mechs->mechJugador->pos_Hexagono.fila + 1; i < informacion_mapa->filas; ++i) {
////                if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == informacion_mechs->mechJugador->pos_Hexagono.columna) &&
////                        (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == i))
////                    return TRASERO;
////            }
////            /* Mirar las casillas en la diagonal inferior izquierda */
////            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
////                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila + 2)*2;
////            else
////                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila + 1)*2 + 1;
////            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna - 1; (i > 0) && ((fila_init / 2) < informacion_mapa->filas); --i, ++fila_init) {
////                for (int j = fila_init / 2; j < informacion_mapa->columnas; ++j) {
////                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
////                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
////                        return TRASERO;
////                }
////            }
////            /* Mirar las casillas en la diagonal inferior derecha */
////            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
////                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila + 2)*2;
////            else
////                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila + 1)*2 + 1;
////            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna + 1; (i < informacion_mapa->columnas) && ((fila_init / 2) < informacion_mapa->filas); ++i, ++fila_init) {
////                for (int j = fila_init / 2; j < informacion_mapa->columnas; ++j) {
////                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
////                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
////                        return TRASERO;
////                }
////            }
////            /* Mirar si estÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ en los laterales */
////            if (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna > informacion_mechs->mechJugador->pos_Hexagono.columna)
////                return DERECHO;
////            else
////                return IZQUIERDO;
////            break;
////        case 2:
////            /* Comprobar el ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ngulo frontal */
////            for (int i = 1; i < informacion_mechs->mechJugador->pos_Hexagono.fila; ++i) {
////                if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == informacion_mechs->mechJugador->pos_Hexagono.columna) &&
////                        (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == i))
////                    return FRONTAL;
////            }
////            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
////                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila + 1)*2;
////            else
////                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2 + 1;
////            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna + 1; (i < informacion_mapa->columnas) && ((fila_init / 2) < informacion_mapa->filas); ++i, ++fila_init) {
////                for (int j = fila_init / 2; j > 0; --j) {
////                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
////                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
////                        return FRONTAL;
////                }
////            }
////            /* Comprobar el ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ngulo trasero */
////            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
////                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila + 1)*2;
////            else
////                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2 + 1;
////            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna - 1; (i > 0) && ((fila_init / 2) > 0); --i, --fila_init) {
////                for (int j = fila_init / 2; j < informacion_mapa->filas; ++j) {
////                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
////                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
////                        return TRASERO;
////                }
////            }
////            /* Comprobar los ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ngulos laterales */
////            if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna > informacion_mechs->mechJugador->pos_Hexagono.columna) ||
////                    (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila > informacion_mechs->mechJugador->pos_Hexagono.fila))
////                return DERECHO;
////            else
////                return IZQUIERDO;
////            break;
////        case 3:
////            /* Comprobar el ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ngulo frontal */
////            for (int i = informacion_mechs->mechJugador->pos_Hexagono.fila + 1; i < informacion_mapa->filas; ++i) {
////                if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == informacion_mechs->mechJugador->pos_Hexagono.columna) &&
////                        (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == i))
////                    return FRONTAL;
////            }
////            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
////                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2;
////            else
////                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2 - 1;
////            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna + 1; (i < informacion_mapa->columnas) && ((fila_init / 2) > 0); ++i, --fila_init) {
////                for (int j = fila_init / 2; j < informacion_mapa->filas; ++j) {
////                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
////                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
////                        return FRONTAL;
////                }
////            }
////            /* Comprobar el ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ngulo trasero */
////            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
////                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2;
////            else
////                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2 - 1;
////            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna - 1; (i > 0) && ((fila_init / 2) < informacion_mapa->filas); --i, ++fila_init) {
////                for (int j = fila_init / 2; j > 0; --j) {
////                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
////                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
////                        return TRASERO;
////                }
////            }
////            /* Comprobar los ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ngulos laterales */
////            if (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila < informacion_mechs->mechJugador->pos_Hexagono.fila)
////                return IZQUIERDO;
////            else
////                return DERECHO;
////            break;
////        case 4:
////            /* ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¯Ãƒâ€šÃ‚Â¿Ãƒâ€šÃ‚Â½ngulo frontal */
////            for (int i = informacion_mechs->mechJugador->pos_Hexagono.fila + 1; i < informacion_mapa->filas; ++i) {
////                if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == informacion_mechs->mechJugador->pos_Hexagono.columna) &&
////                        (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == i))
////                    return FRONTAL;
////            }
////
////            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
////                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila + 1)*2;
////            else
////                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila)*2 + 1;
////            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna - 1; (i > 0) && ((fila_init / 2) < informacion_mapa->filas); --i, ++fila_init) {
////                for (int j = fila_init / 2; j < informacion_mapa->columnas; ++j) {
////                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
////                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
////                        return FRONTAL;
////                }
////            }
////
////            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
////                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila + 1)*2;
////            else
////                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila)*2 + 1;
////            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna + 1; (i < informacion_mapa->columnas) && ((fila_init / 2) < informacion_mapa->filas); ++i, ++fila_init) {
////                for (int j = fila_init / 2; j < informacion_mapa->columnas; ++j) {
////                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
////                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
////                        return FRONTAL;
////                }
////            }
////
////            /* ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¯Ãƒâ€šÃ‚Â¿Ãƒâ€šÃ‚Â½ngulo trasero */
////            for (int i = 1; i < informacion_mechs->mechJugador->pos_Hexagono.fila; ++i) {
////                if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == informacion_mechs->mechJugador->pos_Hexagono.columna) &&
////                        (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == i))
////                    return TRASERO;
////            }
////
////            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
////                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila - 1)*2;
////            else
////                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila - 2)*2 + 1;
////            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna - 1; (i > 0) && ((fila_init / 2) > 0); --i, --fila_init) {
////                for (int j = fila_init / 2; j > 0; --j) {
////                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
////                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
////                        return TRASERO;
////                }
////            }
////
////            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
////                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila - 1)*2;
////            else
////                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila - 2)*2 + 1;
////            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna + 1; (i < informacion_mapa->columnas) && ((fila_init / 2) > 0); ++i, --fila_init) {
////                for (int j = fila_init / 2; j > 0; --j) {
////                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
////                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
////                        return TRASERO;
////                }
////            }
////            /* ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¯Ãƒâ€šÃ‚Â¿Ãƒâ€šÃ‚Â½ngulos laterales */
////            if (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna > informacion_mechs->mechJugador->pos_Hexagono.columna)
////                return IZQUIERDO;
////            else
////                return DERECHO;
////            break;
////        case 5:
////            /* ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¯Ãƒâ€šÃ‚Â¿Ãƒâ€šÃ‚Â½ngulo frontal */
////            for (int i = informacion_mechs->mechJugador->pos_Hexagono.fila + 1; i < informacion_mapa->filas; ++i) {
////                if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == informacion_mechs->mechJugador->pos_Hexagono.columna) &&
////                        (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == i))
////                    return FRONTAL;
////            }
////
////            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
////                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila - 1)*2 - 2;
////            else
////                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2 - 1;
////            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna - 1; (i > 0) && ((fila_init / 2) > 0); --i, --fila_init) {
////                for (int j = fila_init / 2; j < informacion_mapa->filas; ++j) {
////                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
////                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
////                        return FRONTAL;
////                }
////            }
////            /* ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¯Ãƒâ€šÃ‚Â¿Ãƒâ€šÃ‚Â½ngulo trasero */
////            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
////                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila - 1)*2 - 2;
////            else
////                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2 - 1;
////            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna + 1; (i < informacion_mapa->columnas) && ((fila_init / 2) < informacion_mapa->filas); ++i, ++fila_init) {
////                for (int j = fila_init / 2; j > 0; --j) {
////                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
////                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
////                        return TRASERO;
////                }
////            }
////            /* ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¯Ãƒâ€šÃ‚Â¿Ãƒâ€šÃ‚Â½ngulos laterales */
////            if (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna > informacion_mechs->mechJugador->pos_Hexagono.columna)
////                return IZQUIERDO;
////            else
////                return DERECHO;
////            break;
////        case 6:
////            /* ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¯Ãƒâ€šÃ‚Â¿Ãƒâ€šÃ‚Â½ngulo frontal */
////            for (int i = 1; i < informacion_mechs->mechJugador->pos_Hexagono.fila; ++i) {
////                if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == informacion_mechs->mechJugador->pos_Hexagono.columna) &&
////                        (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == i))
////                    return FRONTAL;
////            }
////
////            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
////                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila + 1)*2;
////            else
////                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2 + 1;
////            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna - 1; (i > 0) && ((fila_init / 2) < informacion_mapa->filas); --i, ++fila_init) {
////                for (int j = fila_init / 2; j > 0; --j) {
////                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
////                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
////                        return FRONTAL;
////                }
////            }
////            /* ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¯Ãƒâ€šÃ‚Â¿Ãƒâ€šÃ‚Â½ngulo trasero */
////            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
////                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.columna + 1)*2;
////            else
////                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2 + 1;
////            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna + 1; (i < informacion_mapa->columnas) && ((fila_init / 2) > 0); ++i, --fila_init) {
////                for (int j = fila_init / 2; j < informacion_mapa->columnas; ++j) {
////                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
////                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
////                        return TRASERO;
////                }
////            }
////            /* ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¯Ãƒâ€šÃ‚Â¿Ãƒâ€šÃ‚Â½ngulos laterales */
////            if (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna > informacion_mechs->mechJugador->pos_Hexagono.columna)
////                return DERECHO;
////            else
////                return IZQUIERDO;
////            break;
////    }
////    return 0; /* No se alcanza nunca */
////
////
////}
//
//bool acciones::buscar_municion(const iMech &mech, int cod_arma) {
//    int cod_municion = 0;
//
//    for (int i = 0; i < mech.defMechInfo->num_componentes; ++i) { //Si encuentra el cÃ³digo parar
//        if (mech.defMechInfo->componentes[i].codigoArma == cod_arma)
//            cod_municion = mech.defMechInfo->componentes[i].codigo;
//    }
//    if (cod_municion != 0) {
//        for (int i = 0; i < 8; ++i) {
//            for (int j = 0; j < mech.defMechInfo->localizaciones[i].slots_ocupados; ++j) {
//                if ((mech.defMechInfo->localizaciones[i].slots[j].codigo == cod_municion) &&
//                        (mech.defMechInfo->localizaciones[i].slots[j].cantidad > 0)) {
//                    armas->armas_mech[armas->num_armas].loc_municion = i;
//                    armas->armas_mech[armas->num_armas].slot_municion = j;
//                    return true;
//                }
//            }
//        }
//    }
//    return false;
//}
//
//bool acciones::queda_municion(const iMech &mech, int codigo) {
//
//    for (int k = 0; k < mech.defMechInfo->num_componentes; ++k) {
//        if ((mech.defMechInfo->componentes[k].clase == MUNICION) &&
//                (mech.defMechInfo->componentes[k].codigoArma == codigo) &&
//                (mech.defMechInfo->componentes[k].cantidad > 0) &&
//                (mech.defMechInfo->componentes[k].operativo == true))
//            return true;
//    }
//    return false;
//}
//
//int acciones::estrategia_movimiento() {
//    informacion_mechs->mechJugador->dmj->Heridas_MW;
//    iMech* mech = informacion_mechs->mechJugador;
//    /* Si el mech esta en pie, el MechWarrior tiene pocas heridas, el
//       nivel de temperatura no es muy alto, los puntos de blindaje de la cabeza, 
//       del torso central y de las piernas no son bajos y tenemos armas no traseras
//       con las que disparar, entonces la estrategia sera de ataque */
//
//    if ((mech->enElSuelo == false) &&
//            (informacion_mechs->mechJugador->dmj->Heridas_MW < 5) && /* Para que haya como mucho una prob. de 5/6 de perder la consciencia */
//            (mech->temp_actual < 13) && /* Para evitar la desconexiÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n */
//            (mech->blindaje.CAB > 2) &&
//            (mech->blindaje.TC > 2) &&
//            (mech->blindaje.PI > 1) &&
//            (mech->blindaje.PD > 1) &&
//            mech->armas_ok())
//        return ATACAR;
//    else
//        return DEFENDER;
//
//}

<<<<<<< HEAD
//void acciones::reglas_movimiento() {
//    char f_log[50];
//    iMech** mechs;
//    iMech* mechJ = informacion_mechs->mechJugador;
//
//    mechs = informacion_mechs->iMechVector;
//    int num_jugador = atoi(this->numeroJugador.c_str());
//    int PM, /* Puntos de movimiento segÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Âºn el tipo de movimiento elegido */
//            mech_objetivo,
//            direccion,
//            estrategia,
//            tipo_mov;
//    time_t tiempo;
//    /* Obtener la estrategia */
//    estrategia = estrategia_movimiento();
//    tiempo = time(&tiempo);
//
//    if (estrategia == ATACAR)
//        sprintf(f_log, "%s : Estrategia de movimiento del mech %i = Atacar\n\n", ctime(&tiempo), num_jugador);
//    else
//        sprintf(f_log, "%s : Estrategia de movimiento del mech %i = Huir\n\n", ctime(&tiempo), num_jugador);
//    flog += f_log;
//    /* Evaluar si vamos a andar, correr o saltar */
//    tipo_mov = mechJ->tipo_movimiento();
//    tiempo = time(&tiempo);
//    if (tipo_mov == CORRER)
//        sprintf(f_log, "%s : Tipo de movimiento del mech %i = Correr\n\n", ctime(&tiempo), num_jugador);
//    else
//        sprintf(f_log, "%s : Tipo de movimiento del mech %i = Andar\n\n", ctime(&tiempo), num_jugador);
//    flog += f_log;
//    switch (tipo_mov) {
//        case ANDAR:
//            PM = informacion_mechs->mechJugador->dmj->PM_andar;
//            break;
//        case CORRER:
//            PM = informacion_mechs->mechJugador->dmj->PM_correr;
//            break;
//    }
//
//    /* 1- Intentar levantar el mech si esta en el suelo y se puede levantar */
//    if ((mechJ->enElSuelo == TRUE) && (PM > 0) && mechJ->equilibrio_ok()) {
//        tiempo = time(&tiempo);
//        sprintf(f_log, "%s : El mech %i esta en el suelo e intentara levantarse\n\n", ctime(&tiempo), num_jugador);
//        flog += f_log;
//        /* Si la estrategia es de ataque, nos levantamos mirando al mech mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s cercano */
//        mech_objetivo = mechJ->buscar_mech_cercano(mechs, num_jugador, informacion_mechs->nMechs);
//        direccion = informacion_mapa->direccion_objetivo(mechJ->pos_Hexagono, mechs[mech_objetivo]->pos_Hexagono);
//        mechJ->encaramiento_mech = direccion;
//
//        /* Guardar el movimiento de levantarse. Poner en pie al mech con la direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n calculada */
//        confirmar_mov(tipo_mov, mechJ->pos_Hexagono, direccion, false, MOV_LEVANTARSE, 1);
//
//        /* Actualizar los PM que llevamos usados */
//        /* Para simplificar, suponemos que tenemos ambos brazos y no estÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡n daÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â±ados */
//        PM -= 2;
//    }
//
//    /* 2- Si quedan puntos de movimiento y las piernas estÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡n bien,
//     * realizar el resto de la fase de movimiento */
//
//    /* Si tenemos alguna pierna bien comenzamos el bucle de movimiento */
//    if (mechJ->equilibrio_ok()) {
//        if (estrategia == DEFENDER) {
//            tiempo = time(&tiempo);
//            sprintf(f_log, "%s : El mech %i estÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ en condiciones de moverse y va a huir\n\n", ctime(&tiempo), num_jugador);
//            flog += f_log;
//            mov_huir(num_jugador, this->informacion_mechs->nMechs, PM, tipo_mov);
//        } else {
//            tiempo = time(&tiempo);
//            sprintf(f_log, "%s : El mech %i estÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ en condiciones de moverse y va a atacar\n\n", ctime(&tiempo), num_jugador);
//            flog += f_log;
//            mov_atacar(num_jugador, this->informacion_mechs->nMechs, PM, tipo_mov);
//        }
//    }
//    //    salida_fase_movimiento(fase_movimiento, num_jugador);
//}
//
//void acciones::confirmar_mov(int tipo_movimiento, hexagono_pos destino, int lado, int MASC, int tipo, int veces) {
//    /* Si es el primer paso que damos tenemos que rellenar todos los campos */
//    if (mov->pasos == 0) {
//        mov->tipo_movimiento = tipo_movimiento;
//        mov->destino.columna = destino.columna;
//        mov->destino.fila = destino.fila;
//        mov->lado = lado;
//        mov->MASC = MASC;
//        mov->pasos = 1;
//        mov->tipo[0] = tipo;
//        mov->veces[0] = veces;
//    } else {
//        /* Si el paso anterior fue en la misma direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n, tan solo tenemos que actualizar el destino y las veces */
//        if (mov->tipo[mov->pasos - 1] == tipo) {
//            mov->destino.columna = destino.columna;
//            mov->destino.fila = destino.fila;
//            mov->veces[mov->pasos - 1]++;
//        } else {
//            /* Tenemos que dar un nuevo paso */
//            mov->destino.columna = destino.columna;
//            mov->destino.fila = destino.fila;
//            mov->lado = lado;
//            mov->tipo[mov->pasos] = tipo;
//            mov->veces[mov->pasos] = 1;
//            mov->pasos++;
=======
int acciones::obtenerSlotArma(iMech mech, Componente_Mech arma) {
    for (int i = 0; i < mech.defMechInfo->localizaciones[arma.localizacion].slots_ocupados; i++) {
        if (mech.defMechInfo->localizaciones[arma.localizacion].slots[i].codigo == arma.codigo)
            return i;
    }
    return -1;
}

//string acciones::mover(hexagono_pos destino) {
//    //AÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â±adir obstaculos mechs!
//    bool stop = false;
//    int f_ini;
//    int c_ini;
//    int i_actual, j_actual;
//    int i_tmp, j_tmp;
//    int toneladas = 100; //leer de defmech
//    int coste_mov;
//    string salida;
//
//    priority_queue<path_pos_t, vector<path_pos_t>, greater <vector<path_pos_t>::value_type> > l_abierta;
//
//    int adyacentes[6][2]; //6 hexÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡gnos adyacentes como mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ximo
//    int filas = informacion_mapa->filas;
//    int columnas = informacion_mapa->columnas;
//    path_pos_t path_map[filas][columnas];
//    path_pos_t hex_tmp;
//    for (int i = 0; i < filas; i++)
//        for (int j = 0; j < columnas; j++) {
//            path_map[i][j].fila=i;
//            path_map[i][j].columna=j;
>>>>>>> 6ef4bb63a69e80805e2f188877946ca3308c254f
//        }
//    }
//}
//
//void acciones::mov_huir(int num_jugador, int num_jugadores, int PM_INI, int tipo_mov) {
//    iMech ** mechs = informacion_mechs->iMechVector;
//    infoMapa* mapa = informacion_mapa;
//    iMech* mechJ = informacion_mechs->mechJugador;
//
//    int mech_objetivo, /* Guarda el nÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Âºmero del mech del que huimos */
//            fin_movimiento = false, /* TRUE->no se hacen mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s movimientos */
//            direccion = 0, /* DirecciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n hacia la que nos tenemos que mover */
//            coste, /* Variable auxiliar */
//            //candidatos[7], /* candidatos[i]==TRUE -> podemos movernos en la direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n i */
//            dir_giro,
//            coste_giro;
//    int PM = PM_INI;
//    bool candidatos[7];
//    hexagono_pos hex_obj;
//
<<<<<<< HEAD
=======
//    f_ini = informacion_mechs->mechJugador->pos_Hexagono.fila;
//    c_ini = informacion_mechs->mechJugador->pos_Hexagono.columna;
//    l_abierta.push(path_map[f_ini][c_ini]);
//    path_map[f_ini][c_ini].en_abierta = true;
//    while (stop == false) {
//        //Cambiar elemento de cola
//        path_pos_t tmp;
//        tmp=l_abierta.top();
//        i_actual=l_abierta.top().fila;
//        j_actual=l_abierta.top().columna;
//        //salida=salida+"->"+tmp.posicion_h().stringPos();//No se puede reconstruir asÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­ el camino, elige posiciones incorrectas de la lista de abierta, adyacentes a posiciones anteriores.
//        l_abierta.pop();
//        path_map[i_actual][j_actual].en_abierta = false;
//        path_map[i_actual][j_actual].en_cerrada = true;
//        //Cambiado
//        posiciones_adyacentes(i_actual, j_actual, adyacentes);
//        for (int i = 0; i < 6; i++) {
//            i_tmp = adyacentes[i][0];
//            j_tmp = adyacentes[i][1];
//            if (dentroMapa(i_tmp, j_tmp))
//                if (!path_map[i_tmp][j_tmp].en_cerrada) {
//                    coste_mov = informacion_mapa->coste_mov_ady(path_map[i_actual][j_actual].posicion_h(), path_map[i_tmp][j_tmp].posicion_h(), toneladas);
//                    hex_tmp.fila_padre = i_actual;
//                    hex_tmp.columna_padre = j_actual;
//                    hex_tmp.fila=i_tmp;
//                    hex_tmp.columna=j_tmp;
//                    hex_tmp.g = coste_mov*9;
//                    hex_tmp.h = informacion_mapa->distancia_casillas(path_map[i_tmp][j_tmp].posicion_h(), destino)*10;
//                    hex_tmp.funcion();
//                    if(hex_tmp.posicion_h()==destino){
//                        hex_tmp.f-=10;
//                    }
>>>>>>> 6ef4bb63a69e80805e2f188877946ca3308c254f
//
//    /* Obtener el nÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Âºmero del mech que tenemos mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s cerca */
//    mech_objetivo = mechJ->buscar_mech_cercano(mechs, num_jugador, informacion_mechs->nMechs);
//
//    /* Bucle de movimiento. El movimiento se realiza por pasos */
//    while ((PM > 0) && (fin_movimiento == false)) {
//
//        /* Obtener el nÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Âºmero del mech que tenemos mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s cerca */
//        mech_objetivo = mechJ->buscar_mech_cercano(mechs, num_jugador, informacion_mechs->nMechs);
//        /* Ver a quÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â© casillas nos podrÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­amos mover */
//        actualizar_mov_candidatos(PM, mechJ->pos_Hexagono, candidatos, mechJ->defMechInfo->toneladas, tipo_mov);
//        if ((mechJ->encaramiento_mech == direccion) && (candidatos[direccion] == false) && PM <= PM_INI / 5)
//            direccion = -1;
//        else
//            direccion = paso_huir(candidatos, num_jugador, mech_objetivo, PM == PM_INI);
//
//        /* Si no podemos movernos a alguna direccion buena,
//         * esperaremos al siguiente turno para probar con mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s PM iniciales */
//        if ((direccion == -1))
//            fin_movimiento = TRUE;
//            /* Si podemos movernos hacia la direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n obtenida, lo intentamos */
//        else {
//            /* Si ya estamos encarados hacia esa direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n,
//             * nos movemos hacia ella */
//            if (mechJ->encaramiento_mech == direccion) {
//                mapa->casilla_objetivo(mechJ->pos_Hexagono, direccion, hex_obj);
//                coste = mapa->coste_mov_ady(mechJ->pos_Hexagono.fila, mechJ->pos_Hexagono.columna, hex_obj.fila, hex_obj.columna, mechJ->defMechInfo->toneladas);
//                confirmar_mov(tipo_mov, hex_obj, direccion, false, MOV_ADELANTE, 1);
//                mechJ->encaramiento_mech = direccion;
//                mechJ->pos_Hexagono.columna = hex_obj.columna;
//                mechJ->pos_Hexagono.fila = hex_obj.fila;
//                PM -= coste;
//            }/* Si no estabamos encarados hacia esa direccion y
//             * es un movimiento posible, nos giramos */
//            else {
//                /* Ver para quÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â© lado nos tenemos que mover para
//                 * alcanzar antes esa direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n y hallar cuÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ntos PM
//                 * costarÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­a encararse a esa direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n */
//                dir_giro = func_direccion_giro(mechJ->encaramiento_mech, direccion);
//                coste_giro = func_coste_giro(mechJ->encaramiento_mech, direccion, dir_giro);
//                /* Si tenemos PM para girar hacia esa direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n, lo hacemos */
//                if (PM >= coste_giro) {
//                    confirmar_mov(tipo_mov, mechJ->pos_Hexagono, direccion, false, dir_giro, coste_giro);
//                    mechJ->encaramiento_mech = direccion;
//                    PM -= coste_giro;
//                }/* Si no, giramos hacia esa direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n tanto como podamos
//                 * para acercarnos */
//                else {
//                    //Podemos girar tantas veces como PM nos queden
//                    mechJ->encaramiento_mech = lado_final_giro(mechJ->encaramiento_mech, dir_giro, PM);
//                    confirmar_mov(tipo_mov, mechJ->pos_Hexagono, direccion, FALSE, dir_giro, PM);
//                    PM = 0;
//                }
//            } /* else girar */
//        } /* else realizar movimientos */
//    } /* bucle de movimiento */
//}
////Funcion que dado el mapa, los PM que quedan, y una casilla devuelve un array que contiene las casillas adyacentes a las que nos podemos mover
//
//void acciones::actualizar_mov_candidatos(int PM, hexagono_pos casilla, bool *candidatos, int toneladas, int tipo_mov) {
//    infoMapa* mapa = informacion_mapa;
//    int i;
//    hexagono_pos objetivo;
//    for (i = 1; i <= 6; i++)
//        candidatos[i] = false;
//
//    for (i = 1; i <= 6; i++) {
//        if (mapa->casilla_objetivo(casilla, i, objetivo) == false)
//            continue;
//        else {
//            if ((mapa->mapa[objetivo.fila][objetivo.columna]->terreno == AGUA) &&
//                    (mapa->mapa[objetivo.fila][objetivo.columna]->nivel < 0) &&
//                    (tipo_mov == CORRER)) {
//                candidatos[i] = false;
//            } else {
//                if ((mapa->coste_mov_ady(casilla.fila, casilla.columna, objetivo.fila, objetivo.columna, toneladas) != -1) &&
//                        (PM >= mapa->coste_mov_ady(casilla.fila, casilla.columna, objetivo.fila, objetivo.columna, toneladas))) {
//                    candidatos[i] = true;
//                }
//            }
//        }
//    }
//    //Esto es para que cuando accedamos a la posicion cero (que es 1 -1) nos refiramos a la direccion 6
//    candidatos[0] = candidatos[6];
//}
//
//int acciones::func_direccion_giro(int encaramiento, int dir_objetivo) {
//    if (abs(encaramiento - dir_objetivo) == 3)
//        return MOV_DERECHA;
//    else
//        if (((encaramiento + 1) % 6) == dir_objetivo % 6 ||
//            ((encaramiento + 2) % 6) == dir_objetivo % 6)
//        return MOV_DERECHA;
//    else
//        return MOV_IZQUIERDA;
//}
//
//int acciones::func_coste_giro(int encaramiento, int dir_objetivo, int dir_giro) {
//    int i = 0;
//    if (dir_giro == MOV_DERECHA) {
//        while (encaramiento != dir_objetivo) {
//            encaramiento = (encaramiento % 6) + 1;
//            ++i;
//        }
//    } else {
//        while (encaramiento != dir_objetivo % 6) {
//            encaramiento = (encaramiento + 5) % 6;
//            ++i;
//        }
//    }
//    return i;
//}
//
//int acciones::lado_final_giro(int enc_ini, int dir_giro, int veces) {
//    int encaramiento;
//
//    if (dir_giro == MOV_IZQUIERDA) {
//        encaramiento = enc_ini - veces;
//        if (encaramiento <= 0)
//            encaramiento = encaramiento + 6;
//    } else {
//        encaramiento = enc_ini + veces;
//        if (encaramiento > 6)
//            encaramiento = encaramiento % 6;
//    }
//    return encaramiento;
//}
//
//int acciones::paso_huir(bool* candidatos, int num_jugador, int mech_objetivo, int primer_mov) {
//    infoMapa* mapa = informacion_mapa;
//    iMech** mechs = informacion_mechs->iMechVector;
//    iMech* mechJ = informacion_mechs->mechJugador;
//
//    hexagono_pos aux;
//    int direccion,
//            dir1,
//            dir2,
//            LV1,
//            LV2,
//            LV3;
//    int centro[2],
//            derecha[2],
//            izquierda[2];
//    int valor1, valor2, valor3;
//    float dist1 = 0,
//            dist2 = 0,
//            dist = 0;
//
//
//    /* Obtener la direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n hacia la que nos queremos mover
//        y las dos casillas adyacentes a la direccion de huida en linea recta*/
//    direccion = mapa->direccion_objetivo(mechJ->pos_Hexagono, mechs[mech_objetivo]->pos_Hexagono) + 2;
//    direccion = direccion % 6 + 1;
//    dir1 = (((direccion - 1)+(5)) % 6) + 1;
//    dir2 = (((direccion - 1) + 1) % 6) + 1;
//
//    /*Ademas vamos a darle un valor entero a cada una de las tres casillas que habria
//    en la direccion contraria al objetivo. Este valor indicara los obstaculos que hay en 
//    la casilla de forma que:
//            0 -> No hay obstaculos
//            1 -> Bosque Ligero
//            2 -> Humo
//            3 -> Bosque denso
//            4-> Humo y bosque ligero
//            5 -> Humo y bosque denso
//     */
//
//
//
//
//    if (candidatos[direccion]) {
//        aux.fila = centro[1];
//        aux.columna = centro[0];
//        mapa->casilla_objetivo(mechJ->pos_Hexagono, direccion, aux);
//        valor1 = obt_valor_obstaculos(aux);
//        LV1 = linea_vision(num_jugador, aux, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);
//    } else {
//        valor1 = -1;
//        LV1 = 1;
//    }
//    if (candidatos[dir1]) {
//        aux.fila = izquierda[1];
//        aux.columna = izquierda[0];
//        mapa->casilla_objetivo(mechJ->pos_Hexagono, dir1, aux);
//        valor2 = obt_valor_obstaculos(aux);
//        LV2 = linea_vision(num_jugador, aux, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);
//    } else {
//        valor2 = -1;
//        LV2 = 1;
//    }
//    if (candidatos[dir2]) {
//        aux.fila = derecha[1];
//        aux.columna = derecha[0];
//        mapa->casilla_objetivo(mechJ->pos_Hexagono, dir2, aux);
//        valor3 = obt_valor_obstaculos(aux);
//        LV3 = linea_vision(num_jugador, aux, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);
//    } else {
//        valor3 = -1;
//        LV3 = 1;
//    }
//
//
//    /*Y tambien decidimos a quÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â© casilla nos movemos, dandole preferencia a la
//    que no tenga linea de vision entre el atacante y el defensor y tenga mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s
//    alto valor de obstaculos. En caso de que no podamos movernos a ninguna
//    comprobamos si es porque no quedan PM's o porque estamos bloqueados.
//    En el primer caso dejamos de movernos, y en el segundo probamos con las
//    dos casillas adyacentes a la de la izquierda y la derecha  */
//
//    /*Ahora elegimos el mejor movimiento de los posibles, si no hay
//    paramos paramos y al final del bucle comprobaremos si es porque
//    no quedan PM's o porque estamos atascados. En el primer caso no hacemos nada
//    y en el segundo probamos con las otras dos casillas */
//
//    if (es_mejor(LV1, valor1, LV2, valor2) && es_mejor(LV1, valor1, LV3, valor3)) {
//        /*El mejor movimiento es en linea recta porque no hay LV*/
//        if (candidatos[direccion]) {
//            return direccion;
//        } else {
//            if (es_mejor(LV2, valor2, LV3, valor3)) {
//                if (candidatos[dir1])
//                    return dir1;
//                else {
//                    if (candidatos[dir2])
//                        return dir2;
//                }
//
//            } else {
//                if (candidatos[dir2])
//                    return dir2;
//                else {
//                    if (candidatos[dir1])
//                        return dir1;
//                }
//            }
//        }
//    } else {
//        if (es_mejor(LV2, valor2, LV3, valor3)) {
//            if (candidatos[dir1])
//                return dir1;
//            else {
//                if (es_mejor(LV1, valor1, LV3, valor3)) {
//                    if (candidatos[direccion])
//                        return direccion;
//                    else
//                        if (candidatos[dir2])
//                        return dir2;
//                } else {
//                    if (candidatos[dir2])
//                        return dir2;
//                    else {
//                        if (candidatos[direccion])
//                            return direccion;
//                    }
//                }
//            }
//        } else {
//            if (candidatos[dir2])
//                return dir2;
//            else {
//                if (es_mejor(LV1, valor1, LV2, valor2)) {
//                    if (candidatos[direccion])
//                        return direccion;
//                    else {
//                        if (candidatos[dir1])
//                            return dir1;
//                    }
//                } else {
//                    if (candidatos[dir1])
//                        return dir1;
//                    else {
//                        if (candidatos[direccion])
//                            return direccion;
//                    }
//                }
//            }
//        }
//    }
//    /*En este punto hemos devuelto ya la direccion hacia la que movernos, si no
//    es asÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­, es porque no podemos ir a ninguna de las tres casillas que exploramos.
//    AsÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­ que exploramos las dos direcciones adyacentes a las casillasizquierda y
//    derecha, y solo nos movemos a una de ellas si es mejor que la actual.
//     */
//    dir1 = (((direccion - 1)+(4)) % 6) + 1;
//    dir2 = (((direccion - 1) + 2) % 6) + 1;
//
//    valor1 = obt_valor_obstaculos(mechJ->pos_Hexagono);
//    LV1 = linea_vision(num_jugador, mechJ->pos_Hexagono, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);
//
//    if (candidatos[dir1]) {
//        aux.fila = izquierda[1];
//        aux.columna = izquierda[0];
//        mapa->casilla_objetivo(mechJ->pos_Hexagono, dir1, aux);
//        valor2 = obt_valor_obstaculos(aux);
//        LV2 = linea_vision(num_jugador, aux, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);
//    } else {
//        valor2 = -1;
//        LV2 = 1;
//    }
//    if (candidatos[dir2]) {
//        aux.fila = derecha[1];
//        aux.columna = derecha[0];
//        mapa->casilla_objetivo(mechJ->pos_Hexagono, dir2, aux);
//        valor3 = obt_valor_obstaculos(aux);
//        LV3 = linea_vision(num_jugador, aux, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);
//    } else {
//        valor3 = -1;
//        LV3 = 1;
//    }
//
//
//    /*Ahora comprobamos si alguna es mejor que la actual */
//    if (es_mejor(LV2, valor2, LV1, valor1) || es_mejor(LV3, valor3, LV1, valor1)) {
//        if (es_mejor(LV2, valor2, LV3, valor3)) {
//            if (candidatos[dir1])
//                return dir1;
//            else
//                if (es_mejor(LV3, valor3, LV1, valor1) && candidatos[dir2])
//                return dir2;
//        } else
//            if (candidatos[dir2])
//            return dir2;
//        else
//            if (es_mejor(LV2, valor2, LV1, valor1) && candidatos[dir1])
//            return dir1;
//    }
//    /*Si no son mejores, comprobamos si estan mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s lejos del enemigo, y tenemos todos los PM's en cuyo caso tambien nos movemos*/
//    dist = distancia(mechJ->pos_Hexagono.columna, mechJ->pos_Hexagono.fila, mechs[mech_objetivo]->pos_Hexagono.columna, mechs[mech_objetivo]->pos_Hexagono.fila);
//    if (candidatos[dir1])
//        dist1 = distancia(izquierda[0], izquierda[1], mechs[mech_objetivo]->pos_Hexagono.columna, mechs[mech_objetivo]->pos_Hexagono.fila);
//
//    if (candidatos[dir2])
//        dist2 = distancia(derecha[0], derecha[1], mechs[mech_objetivo]->pos_Hexagono.columna, mechs[mech_objetivo]->pos_Hexagono.fila);
//
//    if (primer_mov) {
//        if (dist1 > 0 && dist2 > 0) {
//            if (dist1 >= dist2)
//                return dir1;
//            else
//                return dir2;
//        } else {
//            if (dist1 > 0)
//                return dir1;
//            else
//                if (dist2 > 0)
//                return dir2;
//        }
//    }
//    /*Comprobamos si la casilla que reduce la distancia en linea recta al objetivo
//    es mejor extrictamente que la actual y nos podemos mover a ella, en ese caso lo hacemos*/
//
//    dir1 = (((direccion - 1) + 3) % 6) + 1;
//    if (candidatos[dir1]) {
//        aux.fila = izquierda[1];
//        aux.columna = izquierda[0];
//        mapa->casilla_objetivo(mechJ->pos_Hexagono, dir1, aux);
//        valor2 = obt_valor_obstaculos(aux);
//        LV2 = linea_vision(num_jugador, aux, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);
//    } else {
//        valor1 = -1;
//        LV1 = 1;
//    }
//    if (es_mejor(LV2, valor2, LV1, valor1) && !(es_mejor(LV1, valor1, LV2, valor2)) && candidatos[dir1])
//        return dir1;
//        /* Si ninguna era mejor que la actual, o no son candidatas devolvemos
//        -1 para detener el movimiento*/
//    else
//        return -1;
//}
//
//int acciones::obt_valor_obstaculos(hexagono_pos pos) {
//    infoMapa* mapa = informacion_mapa;
//    switch (mapa->mapa[pos.fila][pos.columna]->objetoTerreno) {
//        case B_LIGERO:
//            /*Comprobamos si hay humo para devolver uno u otro valor*/
//            if (mapa->mapa[pos.fila][pos.columna]->humo == false)
//                return 1;
//            else
//                return 4;
//            break;
//        case B_DENSO:
//            if (mapa->mapa[pos.fila][pos.columna]->humo == false)
//                return 3;
//            else
//                return 5;
//            break;
//
//            /*Si no hay nada comprobamos si hay otra casilla que minimice la distancia
//            y hacemos las comprobaciones pertinentes sobre esta */
//        default:
//            if (mapa->mapa[pos.fila][pos.columna]->humo == false)
//                return 2;
//            else
//                return 0;
//            break;
//    }
//    return 0; /* No se alcanza nunca */
//}
<<<<<<< HEAD
//
//int acciones::es_mejor(int LV1, int valor1, int LV2, int valor2) {
//    if (!LV1 && LV2)
//        return 1;
//    if (!LV2 && LV1)
//        return 0;
//    if (valor1 >= valor2)
//        return 1;
//    else
//        return 0;
//}
//
/* Devuelve TRUE si hay lÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­nea de visiÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n entre el origen y el destino
=======

int acciones::angulo_mech(int mech_obj) {
    int alto, ancho, fila, columna, fila_init;

    alto = informacion_mapa->filas;
    ancho = informacion_mapa->columnas;

    switch (informacion_mechs->mechJugador->encaramiento_torso) {
        case 1:
            /*Mirar adelante*/
            for (int i = 1; i < informacion_mechs->mechJugador->pos_Hexagono.fila; i++) {
                if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == informacion_mechs->mechJugador->pos_Hexagono.columna)
                        && (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == i)) {
                    return FRONTAL;
                }
            }
            /* Mirar las casillas en la diagonal superior izquierda */
            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila - 1)*2 - 2;
            else
                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2 - 1;
            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna - 1; (i > 0) && ((fila_init / 2) > 0); --i, --fila_init) {
                for (int j = fila_init / 2; j > 0; --j) {
                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
                        return FRONTAL;
                }
            }
            /* Mirar las casillas en la diagonal superior derecha */
            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila - 1)*2 - 2;
            else
                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2 - 1;
            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna + 1; (i < informacion_mapa->columnas) && ((fila_init / 2) > 0); ++i, --fila_init) {
                for (int j = fila_init / 2; j > 0; --j) {
                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
                        return FRONTAL;
                }
            }
            /* Mirar toda la lÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­nea de casillas que tiene detrÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s */
            for (int i = informacion_mechs->mechJugador->pos_Hexagono.fila + 1; i < informacion_mapa->filas; ++i) {
                if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == informacion_mechs->mechJugador->pos_Hexagono.columna) &&
                        (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == i))
                    return TRASERO;
            }
            /* Mirar las casillas en la diagonal inferior izquierda */
            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila + 2)*2;
            else
                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila + 1)*2 + 1;
            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna - 1; (i > 0) && ((fila_init / 2) < informacion_mapa->filas); --i, ++fila_init) {
                for (int j = fila_init / 2; j < informacion_mapa->columnas; ++j) {
                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
                        return TRASERO;
                }
            }
            /* Mirar las casillas en la diagonal inferior derecha */
            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila + 2)*2;
            else
                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila + 1)*2 + 1;
            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna + 1; (i < informacion_mapa->columnas) && ((fila_init / 2) < informacion_mapa->filas); ++i, ++fila_init) {
                for (int j = fila_init / 2; j < informacion_mapa->columnas; ++j) {
                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
                        return TRASERO;
                }
            }
            /* Mirar si estÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ en los laterales */
            if (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna > informacion_mechs->mechJugador->pos_Hexagono.columna)
                return DERECHO;
            else
                return IZQUIERDO;
            break;
        case 2:
            /* Comprobar el ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ngulo frontal */
            for (int i = 1; i < informacion_mechs->mechJugador->pos_Hexagono.fila; ++i) {
                if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == informacion_mechs->mechJugador->pos_Hexagono.columna) &&
                        (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == i))
                    return FRONTAL;
            }
            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila + 1)*2;
            else
                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2 + 1;
            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna + 1; (i < informacion_mapa->columnas) && ((fila_init / 2) < informacion_mapa->filas); ++i, ++fila_init) {
                for (int j = fila_init / 2; j > 0; --j) {
                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
                        return FRONTAL;
                }
            }
            /* Comprobar el ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ngulo trasero */
            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila + 1)*2;
            else
                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2 + 1;
            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna - 1; (i > 0) && ((fila_init / 2) > 0); --i, --fila_init) {
                for (int j = fila_init / 2; j < informacion_mapa->filas; ++j) {
                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
                        return TRASERO;
                }
            }
            /* Comprobar los ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ngulos laterales */
            if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna > informacion_mechs->mechJugador->pos_Hexagono.columna) ||
                    (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila > informacion_mechs->mechJugador->pos_Hexagono.fila))
                return DERECHO;
            else
                return IZQUIERDO;
            break;
        case 3:
            /* Comprobar el ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ngulo frontal */
            for (int i = informacion_mechs->mechJugador->pos_Hexagono.fila + 1; i < informacion_mapa->filas; ++i) {
                if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == informacion_mechs->mechJugador->pos_Hexagono.columna) &&
                        (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == i))
                    return FRONTAL;
            }
            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2;
            else
                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2 - 1;
            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna + 1; (i < informacion_mapa->columnas) && ((fila_init / 2) > 0); ++i, --fila_init) {
                for (int j = fila_init / 2; j < informacion_mapa->filas; ++j) {
                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
                        return FRONTAL;
                }
            }
            /* Comprobar el ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ngulo trasero */
            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2;
            else
                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2 - 1;
            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna - 1; (i > 0) && ((fila_init / 2) < informacion_mapa->filas); --i, ++fila_init) {
                for (int j = fila_init / 2; j > 0; --j) {
                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
                        return TRASERO;
                }
            }
            /* Comprobar los ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ngulos laterales */
            if (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila < informacion_mechs->mechJugador->pos_Hexagono.fila)
                return IZQUIERDO;
            else
                return DERECHO;
            break;
        case 4:
            /* ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¯ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¿ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â½ngulo frontal */
            for (int i = informacion_mechs->mechJugador->pos_Hexagono.fila + 1; i < informacion_mapa->filas; ++i) {
                if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == informacion_mechs->mechJugador->pos_Hexagono.columna) &&
                        (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == i))
                    return FRONTAL;
            }

            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila + 1)*2;
            else
                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila)*2 + 1;
            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna - 1; (i > 0) && ((fila_init / 2) < informacion_mapa->filas); --i, ++fila_init) {
                for (int j = fila_init / 2; j < informacion_mapa->columnas; ++j) {
                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
                        return FRONTAL;
                }
            }

            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila + 1)*2;
            else
                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila)*2 + 1;
            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna + 1; (i < informacion_mapa->columnas) && ((fila_init / 2) < informacion_mapa->filas); ++i, ++fila_init) {
                for (int j = fila_init / 2; j < informacion_mapa->columnas; ++j) {
                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
                        return FRONTAL;
                }
            }

            /* ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¯ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¿ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â½ngulo trasero */
            for (int i = 1; i < informacion_mechs->mechJugador->pos_Hexagono.fila; ++i) {
                if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == informacion_mechs->mechJugador->pos_Hexagono.columna) &&
                        (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == i))
                    return TRASERO;
            }

            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila - 1)*2;
            else
                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila - 2)*2 + 1;
            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna - 1; (i > 0) && ((fila_init / 2) > 0); --i, --fila_init) {
                for (int j = fila_init / 2; j > 0; --j) {
                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
                        return TRASERO;
                }
            }

            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila - 1)*2;
            else
                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila - 2)*2 + 1;
            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna + 1; (i < informacion_mapa->columnas) && ((fila_init / 2) > 0); ++i, --fila_init) {
                for (int j = fila_init / 2; j > 0; --j) {
                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
                        return TRASERO;
                }
            }
            /* ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¯ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¿ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â½ngulos laterales */
            if (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna > informacion_mechs->mechJugador->pos_Hexagono.columna)
                return IZQUIERDO;
            else
                return DERECHO;
            break;
        case 5:
            /* ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¯ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¿ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â½ngulo frontal */
            for (int i = informacion_mechs->mechJugador->pos_Hexagono.fila + 1; i < informacion_mapa->filas; ++i) {
                if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == informacion_mechs->mechJugador->pos_Hexagono.columna) &&
                        (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == i))
                    return FRONTAL;
            }

            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila - 1)*2 - 2;
            else
                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2 - 1;
            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna - 1; (i > 0) && ((fila_init / 2) > 0); --i, --fila_init) {
                for (int j = fila_init / 2; j < informacion_mapa->filas; ++j) {
                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
                        return FRONTAL;
                }
            }
            /* ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¯ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¿ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â½ngulo trasero */
            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila - 1)*2 - 2;
            else
                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2 - 1;
            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna + 1; (i < informacion_mapa->columnas) && ((fila_init / 2) < informacion_mapa->filas); ++i, ++fila_init) {
                for (int j = fila_init / 2; j > 0; --j) {
                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
                        return TRASERO;
                }
            }
            /* ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¯ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¿ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â½ngulos laterales */
            if (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna > informacion_mechs->mechJugador->pos_Hexagono.columna)
                return IZQUIERDO;
            else
                return DERECHO;
            break;
        case 6:
            /* ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¯ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¿ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â½ngulo frontal */
            for (int i = 1; i < informacion_mechs->mechJugador->pos_Hexagono.fila; ++i) {
                if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == informacion_mechs->mechJugador->pos_Hexagono.columna) &&
                        (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == i))
                    return FRONTAL;
            }

            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.fila + 1)*2;
            else
                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2 + 1;
            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna - 1; (i > 0) && ((fila_init / 2) < informacion_mapa->filas); --i, ++fila_init) {
                for (int j = fila_init / 2; j > 0; --j) {
                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
                        return FRONTAL;
                }
            }
            /* ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¯ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¿ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â½ngulo trasero */
            if ((informacion_mechs->mechJugador->pos_Hexagono.columna % 2) == 0)
                fila_init = (informacion_mechs->mechJugador->pos_Hexagono.columna + 1)*2;
            else
                fila_init = informacion_mechs->mechJugador->pos_Hexagono.fila * 2 + 1;
            for (int i = informacion_mechs->mechJugador->pos_Hexagono.columna + 1; (i < informacion_mapa->columnas) && ((fila_init / 2) > 0); ++i, --fila_init) {
                for (int j = fila_init / 2; j < informacion_mapa->columnas; ++j) {
                    if ((informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna == i) &&
                            (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.fila == j))
                        return TRASERO;
                }
            }
            /* ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¯ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¿ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â½ngulos laterales */
            if (informacion_mechs->iMechVector[mech_obj]->pos_Hexagono.columna > informacion_mechs->mechJugador->pos_Hexagono.columna)
                return DERECHO;
            else
                return IZQUIERDO;
            break;
    }
    return 0; /* No se alcanza nunca */


}

bool acciones::buscar_municion(const iMech &mech, int cod_arma) {
    int cod_municion = 0;

    for (int i = 0; i < mech.defMechInfo->num_componentes; ++i) { //Si encuentra el cÃƒÆ’Ã‚Â³digo parar
        if (mech.defMechInfo->componentes[i].codigoArma == cod_arma)
            cod_municion = mech.defMechInfo->componentes[i].codigo;
    }
    if (cod_municion != 0) {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < mech.defMechInfo->localizaciones[i].slots_ocupados; ++j) {
                if ((mech.defMechInfo->localizaciones[i].slots[j].codigo == cod_municion) &&
                        (mech.defMechInfo->localizaciones[i].slots[j].cantidad > 0)) {
                    armas->armas_mech[armas->num_armas].loc_municion = i;
                    armas->armas_mech[armas->num_armas].slot_municion = j;
                    return true;
                }
            }
        }
    }
    return false;
}

bool acciones::queda_municion(const iMech &mech, int codigo) {

    for (int k = 0; k < mech.defMechInfo->num_componentes; ++k) {
        if ((mech.defMechInfo->componentes[k].clase == MUNICION) &&
                (mech.defMechInfo->componentes[k].codigoArma == codigo) &&
                (mech.defMechInfo->componentes[k].cantidad > 0) &&
                (mech.defMechInfo->componentes[k].operativo == true))
            return true;
    }
    return false;
}

int acciones::estrategia_movimiento() {
    informacion_mechs->mechJugador->dmj->Heridas_MW;
    iMech* mech = informacion_mechs->mechJugador;
    /* Si el mech esta en pie, el MechWarrior tiene pocas heridas, el
       nivel de temperatura no es muy alto, los puntos de blindaje de la cabeza, 
       del torso central y de las piernas no son bajos y tenemos armas no traseras
       con las que disparar, entonces la estrategia sera de ataque */

    if ((mech->enElSuelo == false) &&
            (informacion_mechs->mechJugador->dmj->Heridas_MW < 5) && /* Para que haya como mucho una prob. de 5/6 de perder la consciencia */
            (mech->temp_actual < 13) && /* Para evitar la desconexiÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n */
            (mech->blindaje.CAB > 2) &&
            (mech->blindaje.TC > 2) &&
            (mech->blindaje.PI > 1) &&
            (mech->blindaje.PD > 1) &&
            mech->armas_ok())
        return ATACAR;
    else
        return DEFENDER;

}

void acciones::reglas_movimiento() {
    char f_log[50];
    iMech** mechs;
    iMech* mechJ = informacion_mechs->mechJugador;

    mechs = informacion_mechs->iMechVector;
    int num_jugador = atoi(this->numeroJugador.c_str());
    int PM, /* Puntos de movimiento segÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Âºn el tipo de movimiento elegido */
            mech_objetivo,
            direccion,
            estrategia,
            tipo_mov;
    time_t tiempo;
    /* Obtener la estrategia */
    estrategia = estrategia_movimiento();
    tiempo = time(&tiempo);

    if (estrategia == ATACAR)
        sprintf(f_log, "%s : Estrategia de movimiento del mech %i = Atacar\n\n", ctime(&tiempo), num_jugador);
    else
        sprintf(f_log, "%s : Estrategia de movimiento del mech %i = Huir\n\n", ctime(&tiempo), num_jugador);
    flog += f_log;
    /* Evaluar si vamos a andar, correr o saltar */
    tipo_mov = mechJ->tipo_movimiento();
    tiempo = time(&tiempo);
    if (tipo_mov == CORRER)
        sprintf(f_log, "%s : Tipo de movimiento del mech %i = Correr\n\n", ctime(&tiempo), num_jugador);
    else
        sprintf(f_log, "%s : Tipo de movimiento del mech %i = Andar\n\n", ctime(&tiempo), num_jugador);
    flog += f_log;
    switch (tipo_mov) {
        case ANDAR:
            PM = informacion_mechs->mechJugador->dmj->PM_andar;
            break;
        case CORRER:
            PM = informacion_mechs->mechJugador->dmj->PM_correr;
            break;
    }

    /* 1- Intentar levantar el mech si esta en el suelo y se puede levantar */
    if ((mechJ->enElSuelo == TRUE) && (PM > 0) && mechJ->equilibrio_ok()) {
        tiempo = time(&tiempo);
        sprintf(f_log, "%s : El mech %i esta en el suelo e intentara levantarse\n\n", ctime(&tiempo), num_jugador);
        flog += f_log;
        /* Si la estrategia es de ataque, nos levantamos mirando al mech mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s cercano */
        mech_objetivo = mechJ->buscar_mech_cercano(mechs, num_jugador, informacion_mechs->nMechs);
        direccion = informacion_mapa->direccion_objetivo(mechJ->pos_Hexagono, mechs[mech_objetivo]->pos_Hexagono);
        mechJ->encaramiento_mech = direccion;

        /* Guardar el movimiento de levantarse. Poner en pie al mech con la direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n calculada */
        confirmar_mov(tipo_mov, mechJ->pos_Hexagono, direccion, false, MOV_LEVANTARSE, 1);

        /* Actualizar los PM que llevamos usados */
        /* Para simplificar, suponemos que tenemos ambos brazos y no estÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡n daÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â±ados */
        PM -= 2;
    }

    /* 2- Si quedan puntos de movimiento y las piernas estÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡n bien,
     * realizar el resto de la fase de movimiento */

    /* Si tenemos alguna pierna bien comenzamos el bucle de movimiento */
    if (mechJ->equilibrio_ok()) {
        if (estrategia == DEFENDER) {
            tiempo = time(&tiempo);
            sprintf(f_log, "%s : El mech %i estÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ en condiciones de moverse y va a huir\n\n", ctime(&tiempo), num_jugador);
            flog += f_log;
            mov_huir(num_jugador, this->informacion_mechs->nMechs, PM, tipo_mov);
        } else {
            tiempo = time(&tiempo);
            sprintf(f_log, "%s : El mech %i estÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ en condiciones de moverse y va a atacar\n\n", ctime(&tiempo), num_jugador);
            flog += f_log;
            mov_atacar(num_jugador, this->informacion_mechs->nMechs, PM, tipo_mov);
        }
    }
    //    salida_fase_movimiento(fase_movimiento, num_jugador);
}

void acciones::confirmar_mov(int tipo_movimiento, hexagono_pos destino, int lado, int MASC, int tipo, int veces) {
    /* Si es el primer paso que damos tenemos que rellenar todos los campos */
    if (mov->pasos == 0) {
        mov->tipo_movimiento = tipo_movimiento;
        mov->destino.columna = destino.columna;
        mov->destino.fila = destino.fila;
        mov->lado = lado;
        mov->MASC = MASC;
        mov->pasos = 1;
        mov->tipo[0] = tipo;
        mov->veces[0] = veces;
    } else {
        /* Si el paso anterior fue en la misma direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n, tan solo tenemos que actualizar el destino y las veces */
        if (mov->tipo[mov->pasos - 1] == tipo) {
            mov->destino.columna = destino.columna;
            mov->destino.fila = destino.fila;
            mov->veces[mov->pasos - 1]++;
        } else {
            /* Tenemos que dar un nuevo paso */
            mov->destino.columna = destino.columna;
            mov->destino.fila = destino.fila;
            mov->lado = lado;
            mov->tipo[mov->pasos] = tipo;
            mov->veces[mov->pasos] = 1;
            mov->pasos++;
        }
    }
}

void acciones::mov_huir(int num_jugador, int num_jugadores, int PM_INI, int tipo_mov) {
    iMech ** mechs = informacion_mechs->iMechVector;
    infoMapa* mapa = informacion_mapa;
    iMech* mechJ = informacion_mechs->mechJugador;

    int mech_objetivo, /* Guarda el nÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Âºmero del mech del que huimos */
            fin_movimiento = false, /* TRUE->no se hacen mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s movimientos */
            direccion = 0, /* DirecciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n hacia la que nos tenemos que mover */
            coste, /* Variable auxiliar */
            //candidatos[7], /* candidatos[i]==TRUE -> podemos movernos en la direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n i */
            dir_giro,
            coste_giro;
    int PM = PM_INI;
    bool candidatos[7];
    hexagono_pos hex_obj;


    /* Obtener el nÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Âºmero del mech que tenemos mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s cerca */
    mech_objetivo = mechJ->buscar_mech_cercano(mechs, num_jugador, informacion_mechs->nMechs);

    /* Bucle de movimiento. El movimiento se realiza por pasos */
    while ((PM > 0) && (fin_movimiento == false)) {

        /* Obtener el nÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Âºmero del mech que tenemos mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s cerca */
        mech_objetivo = mechJ->buscar_mech_cercano(mechs, num_jugador, informacion_mechs->nMechs);
        /* Ver a quÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â© casillas nos podrÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­amos mover */
        actualizar_mov_candidatos(PM, mechJ->pos_Hexagono, candidatos, mechJ->defMechInfo->toneladas, tipo_mov);
        if ((mechJ->encaramiento_mech == direccion) && (candidatos[direccion] == false) && PM <= PM_INI / 5)
            direccion = -1;
        else
            direccion = paso_huir(candidatos, num_jugador, mech_objetivo, PM == PM_INI);

        /* Si no podemos movernos a alguna direccion buena,
         * esperaremos al siguiente turno para probar con mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s PM iniciales */
        if ((direccion == -1))
            fin_movimiento = TRUE;
            /* Si podemos movernos hacia la direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n obtenida, lo intentamos */
        else {
            /* Si ya estamos encarados hacia esa direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n,
             * nos movemos hacia ella */
            if (mechJ->encaramiento_mech == direccion) {
                mapa->casilla_objetivo(mechJ->pos_Hexagono, direccion, hex_obj);
                coste = mapa->coste_mov_ady(mechJ->pos_Hexagono.fila, mechJ->pos_Hexagono.columna, hex_obj.fila, hex_obj.columna, mechJ->defMechInfo->toneladas);
                confirmar_mov(tipo_mov, hex_obj, direccion, false, MOV_ADELANTE, 1);
                mechJ->encaramiento_mech = direccion;
                mechJ->pos_Hexagono.columna = hex_obj.columna;
                mechJ->pos_Hexagono.fila = hex_obj.fila;
                PM -= coste;
            }/* Si no estabamos encarados hacia esa direccion y
             * es un movimiento posible, nos giramos */
            else {
                /* Ver para quÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â© lado nos tenemos que mover para
                 * alcanzar antes esa direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n y hallar cuÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ntos PM
                 * costarÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­a encararse a esa direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n */
                dir_giro = func_direccion_giro(mechJ->encaramiento_mech, direccion);
                coste_giro = func_coste_giro(mechJ->encaramiento_mech, direccion, dir_giro);
                /* Si tenemos PM para girar hacia esa direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n, lo hacemos */
                if (PM >= coste_giro) {
                    confirmar_mov(tipo_mov, mechJ->pos_Hexagono, direccion, false, dir_giro, coste_giro);
                    mechJ->encaramiento_mech = direccion;
                    PM -= coste_giro;
                }/* Si no, giramos hacia esa direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n tanto como podamos
                 * para acercarnos */
                else {
                    //Podemos girar tantas veces como PM nos queden
                    mechJ->encaramiento_mech = lado_final_giro(mechJ->encaramiento_mech, dir_giro, PM);
                    confirmar_mov(tipo_mov, mechJ->pos_Hexagono, direccion, FALSE, dir_giro, PM);
                    PM = 0;
                }
            } /* else girar */
        } /* else realizar movimientos */
    } /* bucle de movimiento */
}
//Funcion que dado el mapa, los PM que quedan, y una casilla devuelve un array que contiene las casillas adyacentes a las que nos podemos mover

void acciones::actualizar_mov_candidatos(int PM, hexagono_pos casilla, bool *candidatos, int toneladas, int tipo_mov) {
    infoMapa* mapa = informacion_mapa;
    int i;
    hexagono_pos objetivo;
    for (i = 1; i <= 6; i++)
        candidatos[i] = false;

    for (i = 1; i <= 6; i++) {
        if (mapa->casilla_objetivo(casilla, i, objetivo) == false)
            continue;
        else {
            if ((mapa->mapa[objetivo.fila][objetivo.columna]->terreno == AGUA) &&
                    (mapa->mapa[objetivo.fila][objetivo.columna]->nivel < 0) &&
                    (tipo_mov == CORRER)) {
                candidatos[i] = false;
            } else {
                if ((mapa->coste_mov_ady(casilla.fila, casilla.columna, objetivo.fila, objetivo.columna, toneladas) != -1) &&
                        (PM >= mapa->coste_mov_ady(casilla.fila, casilla.columna, objetivo.fila, objetivo.columna, toneladas))) {
                    candidatos[i] = true;
                }
            }
        }
    }
    //Esto es para que cuando accedamos a la posicion cero (que es 1 -1) nos refiramos a la direccion 6
    candidatos[0] = candidatos[6];
}

int acciones::func_direccion_giro(int encaramiento, int dir_objetivo) {
    if (abs(encaramiento - dir_objetivo) == 3)
        return MOV_DERECHA;
    else
        if (((encaramiento + 1) % 6) == dir_objetivo % 6 ||
            ((encaramiento + 2) % 6) == dir_objetivo % 6)
        return MOV_DERECHA;
    else
        return MOV_IZQUIERDA;
}

int acciones::func_coste_giro(int encaramiento, int dir_objetivo, int dir_giro) {
    int i = 0;
    if (dir_giro == MOV_DERECHA) {
        while (encaramiento != dir_objetivo) {
            encaramiento = (encaramiento % 6) + 1;
            ++i;
        }
    } else {
        while (encaramiento != dir_objetivo % 6) {
            encaramiento = (encaramiento + 5) % 6;
            ++i;
        }
    }
    return i;
}

int acciones::lado_final_giro(int enc_ini, int dir_giro, int veces) {
    int encaramiento;

    if (dir_giro == MOV_IZQUIERDA) {
        encaramiento = enc_ini - veces;
        if (encaramiento <= 0)
            encaramiento = encaramiento + 6;
    } else {
        encaramiento = enc_ini + veces;
        if (encaramiento > 6)
            encaramiento = encaramiento % 6;
    }
    return encaramiento;
}

int acciones::paso_huir(bool* candidatos, int num_jugador, int mech_objetivo, int primer_mov) {
    infoMapa* mapa = informacion_mapa;
    iMech** mechs = informacion_mechs->iMechVector;
    iMech* mechJ = informacion_mechs->mechJugador;

    hexagono_pos aux;
    int direccion,
            dir1,
            dir2,
            LV1,
            LV2,
            LV3;
    int centro[2],
            derecha[2],
            izquierda[2];
    int valor1, valor2, valor3;
    float dist1 = 0,
            dist2 = 0,
            dist = 0;


    /* Obtener la direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n hacia la que nos queremos mover
        y las dos casillas adyacentes a la direccion de huida en linea recta*/
    direccion = mapa->direccion_objetivo(mechJ->pos_Hexagono, mechs[mech_objetivo]->pos_Hexagono) + 2;
    direccion = direccion % 6 + 1;
    dir1 = (((direccion - 1)+(5)) % 6) + 1;
    dir2 = (((direccion - 1) + 1) % 6) + 1;

    /*Ademas vamos a darle un valor entero a cada una de las tres casillas que habria
    en la direccion contraria al objetivo. Este valor indicara los obstaculos que hay en 
    la casilla de forma que:
            0 -> No hay obstaculos
            1 -> Bosque Ligero
            2 -> Humo
            3 -> Bosque denso
            4-> Humo y bosque ligero
            5 -> Humo y bosque denso
     */




    if (candidatos[direccion]) {
        aux.fila = centro[1];
        aux.columna = centro[0];
        mapa->casilla_objetivo(mechJ->pos_Hexagono, direccion, aux);
        valor1 = obt_valor_obstaculos(aux);
        LV1 = linea_vision(num_jugador, aux, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);
    } else {
        valor1 = -1;
        LV1 = 1;
    }
    if (candidatos[dir1]) {
        aux.fila = izquierda[1];
        aux.columna = izquierda[0];
        mapa->casilla_objetivo(mechJ->pos_Hexagono, dir1, aux);
        valor2 = obt_valor_obstaculos(aux);
        LV2 = linea_vision(num_jugador, aux, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);
    } else {
        valor2 = -1;
        LV2 = 1;
    }
    if (candidatos[dir2]) {
        aux.fila = derecha[1];
        aux.columna = derecha[0];
        mapa->casilla_objetivo(mechJ->pos_Hexagono, dir2, aux);
        valor3 = obt_valor_obstaculos(aux);
        LV3 = linea_vision(num_jugador, aux, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);
    } else {
        valor3 = -1;
        LV3 = 1;
    }


    /*Y tambien decidimos a quÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â© casilla nos movemos, dandole preferencia a la
    que no tenga linea de vision entre el atacante y el defensor y tenga mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s
    alto valor de obstaculos. En caso de que no podamos movernos a ninguna
    comprobamos si es porque no quedan PM's o porque estamos bloqueados.
    En el primer caso dejamos de movernos, y en el segundo probamos con las
    dos casillas adyacentes a la de la izquierda y la derecha  */

    /*Ahora elegimos el mejor movimiento de los posibles, si no hay
    paramos paramos y al final del bucle comprobaremos si es porque
    no quedan PM's o porque estamos atascados. En el primer caso no hacemos nada
    y en el segundo probamos con las otras dos casillas */

    if (es_mejor(LV1, valor1, LV2, valor2) && es_mejor(LV1, valor1, LV3, valor3)) {
        /*El mejor movimiento es en linea recta porque no hay LV*/
        if (candidatos[direccion]) {
            return direccion;
        } else {
            if (es_mejor(LV2, valor2, LV3, valor3)) {
                if (candidatos[dir1])
                    return dir1;
                else {
                    if (candidatos[dir2])
                        return dir2;
                }

            } else {
                if (candidatos[dir2])
                    return dir2;
                else {
                    if (candidatos[dir1])
                        return dir1;
                }
            }
        }
    } else {
        if (es_mejor(LV2, valor2, LV3, valor3)) {
            if (candidatos[dir1])
                return dir1;
            else {
                if (es_mejor(LV1, valor1, LV3, valor3)) {
                    if (candidatos[direccion])
                        return direccion;
                    else
                        if (candidatos[dir2])
                        return dir2;
                } else {
                    if (candidatos[dir2])
                        return dir2;
                    else {
                        if (candidatos[direccion])
                            return direccion;
                    }
                }
            }
        } else {
            if (candidatos[dir2])
                return dir2;
            else {
                if (es_mejor(LV1, valor1, LV2, valor2)) {
                    if (candidatos[direccion])
                        return direccion;
                    else {
                        if (candidatos[dir1])
                            return dir1;
                    }
                } else {
                    if (candidatos[dir1])
                        return dir1;
                    else {
                        if (candidatos[direccion])
                            return direccion;
                    }
                }
            }
        }
    }
    /*En este punto hemos devuelto ya la direccion hacia la que movernos, si no
    es asÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­, es porque no podemos ir a ninguna de las tres casillas que exploramos.
    AsÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­ que exploramos las dos direcciones adyacentes a las casillasizquierda y
    derecha, y solo nos movemos a una de ellas si es mejor que la actual.
     */
    dir1 = (((direccion - 1)+(4)) % 6) + 1;
    dir2 = (((direccion - 1) + 2) % 6) + 1;

    valor1 = obt_valor_obstaculos(mechJ->pos_Hexagono);
    LV1 = linea_vision(num_jugador, mechJ->pos_Hexagono, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);

    if (candidatos[dir1]) {
        aux.fila = izquierda[1];
        aux.columna = izquierda[0];
        mapa->casilla_objetivo(mechJ->pos_Hexagono, dir1, aux);
        valor2 = obt_valor_obstaculos(aux);
        LV2 = linea_vision(num_jugador, aux, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);
    } else {
        valor2 = -1;
        LV2 = 1;
    }
    if (candidatos[dir2]) {
        aux.fila = derecha[1];
        aux.columna = derecha[0];
        mapa->casilla_objetivo(mechJ->pos_Hexagono, dir2, aux);
        valor3 = obt_valor_obstaculos(aux);
        LV3 = linea_vision(num_jugador, aux, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);
    } else {
        valor3 = -1;
        LV3 = 1;
    }


    /*Ahora comprobamos si alguna es mejor que la actual */
    if (es_mejor(LV2, valor2, LV1, valor1) || es_mejor(LV3, valor3, LV1, valor1)) {
        if (es_mejor(LV2, valor2, LV3, valor3)) {
            if (candidatos[dir1])
                return dir1;
            else
                if (es_mejor(LV3, valor3, LV1, valor1) && candidatos[dir2])
                return dir2;
        } else
            if (candidatos[dir2])
            return dir2;
        else
            if (es_mejor(LV2, valor2, LV1, valor1) && candidatos[dir1])
            return dir1;
    }
    /*Si no son mejores, comprobamos si estan mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s lejos del enemigo, y tenemos todos los PM's en cuyo caso tambien nos movemos*/
    dist = distancia(mechJ->pos_Hexagono.columna, mechJ->pos_Hexagono.fila, mechs[mech_objetivo]->pos_Hexagono.columna, mechs[mech_objetivo]->pos_Hexagono.fila);
    if (candidatos[dir1])
        dist1 = distancia(izquierda[0], izquierda[1], mechs[mech_objetivo]->pos_Hexagono.columna, mechs[mech_objetivo]->pos_Hexagono.fila);

    if (candidatos[dir2])
        dist2 = distancia(derecha[0], derecha[1], mechs[mech_objetivo]->pos_Hexagono.columna, mechs[mech_objetivo]->pos_Hexagono.fila);

    if (primer_mov) {
        if (dist1 > 0 && dist2 > 0) {
            if (dist1 >= dist2)
                return dir1;
            else
                return dir2;
        } else {
            if (dist1 > 0)
                return dir1;
            else
                if (dist2 > 0)
                return dir2;
        }
    }
    /*Comprobamos si la casilla que reduce la distancia en linea recta al objetivo
    es mejor extrictamente que la actual y nos podemos mover a ella, en ese caso lo hacemos*/

    dir1 = (((direccion - 1) + 3) % 6) + 1;
    if (candidatos[dir1]) {
        aux.fila = izquierda[1];
        aux.columna = izquierda[0];
        mapa->casilla_objetivo(mechJ->pos_Hexagono, dir1, aux);
        valor2 = obt_valor_obstaculos(aux);
        LV2 = linea_vision(num_jugador, aux, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);
    } else {
        valor1 = -1;
        LV1 = 1;
    }
    if (es_mejor(LV2, valor2, LV1, valor1) && !(es_mejor(LV1, valor1, LV2, valor2)) && candidatos[dir1])
        return dir1;
        /* Si ninguna era mejor que la actual, o no son candidatas devolvemos
        -1 para detener el movimiento*/
    else
        return -1;
}

int acciones::obt_valor_obstaculos(hexagono_pos pos) {
    infoMapa* mapa = informacion_mapa;
    switch (mapa->mapa[pos.fila][pos.columna]->objetoTerreno) {
        case B_LIGERO:
            /*Comprobamos si hay humo para devolver uno u otro valor*/
            if (mapa->mapa[pos.fila][pos.columna]->humo == false)
                return 1;
            else
                return 4;
            break;
        case B_DENSO:
            if (mapa->mapa[pos.fila][pos.columna]->humo == false)
                return 3;
            else
                return 5;
            break;

            /*Si no hay nada comprobamos si hay otra casilla que minimice la distancia
            y hacemos las comprobaciones pertinentes sobre esta */
        default:
            if (mapa->mapa[pos.fila][pos.columna]->humo == false)
                return 2;
            else
                return 0;
            break;
    }
    return 0; /* No se alcanza nunca */
}

int acciones::es_mejor(int LV1, int valor1, int LV2, int valor2) {
    if (!LV1 && LV2)
        return 1;
    if (!LV2 && LV1)
        return 0;
    if (valor1 >= valor2)
        return 1;
    else
        return 0;
}

/* Devuelve TRUE si hay lÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­nea de visiÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n entre el origen y el destino
>>>>>>> 6ef4bb63a69e80805e2f188877946ca3308c254f
 * y FALSE si no la hay */

<<<<<<< HEAD
//bool acciones::linea_vision(int num_jugador, hexagono_pos origen, int nivel_origen, hexagono_pos destino, int nivel_destino) {
//    char orden[100];
//    string linea;
//    ifstream fichero_LDV;
//
//    snprintf(orden, 99, "LDVyC.exe mapaJ%i.sbt %02i%02i %i %02i%02i %i", num_jugador, origen.columna,
//            origen.fila, nivel_origen, destino.columna, destino.fila, nivel_destino);
//
//    system(orden);
//
//    do {
//        fichero_LDV.open("LDV.sbt");
//        //fichero_LDV = fopen("LDV.sbt", "r");
//    } while (fichero_LDV == NULL);
//
//   leeLinea(fichero_LDV, linea, '\n');
//    leeLinea(fichero_LDV, linea, '\n');
//
//    fichero_LDV.close();
//
//    if (linea.compare("True") == 0)
//        return true;
//    else
//        return false;
//}
=======
    if (linea.compare("True") == 0)
        return true;
    else
        return false;
}

void acciones::mov_atacar(int num_jugador, int num_jugadores, int PM, int tipo_mov) {
    iMech** mechs = informacion_mechs->iMechVector;
    iMech* mechJ = informacion_mechs->mechJugador;
    infoMapa* mapa = informacion_mapa;
    hexagono_pos hex_obj;
    int mech_objetivo, /* Guarda el nÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Âºmero del mech al que nos queremos acercar */
            fin_movimiento = FALSE, /* TRUE->no se hacen mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s movimientos */
            direccion = 0, /* DirecciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n hacia la que nos tenemos que mover */
            coste, /* Variable auxiliar */
            //candidatos[7], /* candidatos[i]==TRUE -> podemos movernos en la direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n i */
            dir_giro,
            coste_giro;
    int PM_INI = PM;
    bool candidatos[7];

    /* Obtener el nÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Âºmero del mech que tenemos mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s cerca */
    mech_objetivo = mechJ->buscar_mech_cercano(mechs, num_jugador, informacion_mechs->nMechs);

    /* Bucle de movimiento. El movimiento se realiza por pasos */
    while ((PM > 0) && (fin_movimiento == FALSE)) {
        /* Ver a quÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â© casillas nos podrÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­amos mover */
        actualizar_mov_candidatos(PM, mechJ->pos_Hexagono, candidatos, mechJ->defMechInfo->toneladas, tipo_mov);

        /* Si estamos encarados hacia la direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n que nos interesa pero
         * no nos podemos mover a ella, no hacemos ningÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Âºn movimiento mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s.
         * En caso contrario, buscamos de entre las direcciones candidatas
         * la mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s adecuada para movernos */
        if ((mechJ->encaramiento_mech == direccion) &&
                (candidatos[direccion] == FALSE) && (PM <= PM_INI / 5))
            direccion = -1;
        else
            direccion = mov_acercarse(num_jugador, mech_objetivo, candidatos, PM);

        /* Si no podemos movernos a alguna direccion buena,
         * esperaremos al siguiente turno para probar con mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s PM iniciales */
        if (direccion == -1)
            fin_movimiento = TRUE;
            /* Si podemos movernos hacia la direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n obtenida, lo intentamos */
        else {
            /* Si ya estamos encarados hacia esa direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n,
             * nos movemos hacia ella */
            if (mechJ->encaramiento_mech == direccion) {
                mapa->casilla_objetivo(mechJ->pos_Hexagono, direccion, hex_obj);
                if (casilla_ocupada(num_jugadores, hex_obj) == TRUE) {
                    fin_movimiento = TRUE;
                    printf("dist_disparo = %i, dist_casillas=%i\n", mechJ->dist_disparo(), mapa->distancia_casillas(hex_obj, mechs[mech_objetivo]->pos_Hexagono));
                } else if (mechJ->dist_disparo() > mapa->distancia_casillas(hex_obj, mechs[mech_objetivo]->pos_Hexagono)) {
                    if (linea_vision(num_jugador, hex_obj, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2))

                        fin_movimiento = TRUE;
                } else {
                    coste = mapa->coste_mov_ady(mechJ->pos_Hexagono.fila, mechJ->pos_Hexagono.columna, hex_obj.fila, hex_obj.columna, mechJ->defMechInfo->toneladas);
                    confirmar_mov(tipo_mov, hex_obj, direccion, FALSE, MOV_ADELANTE, 1);
                    mechJ->encaramiento_mech = direccion;
                    mechJ->pos_Hexagono.columna = hex_obj.columna;
                    mechJ->pos_Hexagono.fila = hex_obj.fila;
                    PM -= coste;
                }
            }/* Si no estabamos encarados hacia esa direccion y
             * es un movimiento posible, nos giramos */
            else {
                /* Ver para quÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â© lado nos tenemos que mover para
                 * alcanzar antes esa direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n y hallar cuÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ntos PM
                 * costarÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­a encararse a esa direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n */
                dir_giro = func_direccion_giro(mechJ->encaramiento_mech, direccion);
                coste_giro = func_coste_giro(mechJ->encaramiento_mech, direccion, dir_giro);
                /* Si tenemos PM para girar hacia esa direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n, lo hacemos */



                if (PM >= coste_giro) {
                    confirmar_mov(tipo_mov, mechJ->pos_Hexagono, direccion, FALSE, dir_giro, coste_giro);
                    mechJ->encaramiento_mech = direccion;
                    PM -= coste_giro;
                }/* Si no, giramos hacia esa direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n tanto como podamos
                 * para acercarnos */
                else {
                    //Podemos girar tantas veces como PM nos queden
                    mechJ->encaramiento_mech = lado_final_giro(mechJ->encaramiento_mech, dir_giro, PM);
                    confirmar_mov(tipo_mov, mechJ->pos_Hexagono, direccion, FALSE, dir_giro, PM);
                    PM = 0;
                }
            } /* else girar */
        } /* else realizar movimientos */
    } /* bucle de movimiento */
}

int acciones::casilla_ocupada(int num_jugadores, hexagono_pos casilla) {
    iMech** mechs = informacion_mechs->iMechVector;
    for (int i = 0; i < num_jugadores - 1; ++i) {
        if ((mechs[i]->pos_Hexagono.columna == casilla.columna) &&
                (mechs[i]->pos_Hexagono.fila == casilla.fila))
            return TRUE;
    }
    return FALSE;
}

/* Funcion que evalua los posibles movimientos desde la casilla origen para acercarnos al objetivo,
 * teniendo en cuenta los PM's restantes, de la casilla que venimos, y a quien nos queremos acercar */
int acciones::mov_acercarse(int num_jugador, int mech_objetivo, bool *candidatos, int PM) {
    infoMapa* mapa = informacion_mapa;
    iMech* mechJ = informacion_mechs->mechJugador;
    iMech** mechs = informacion_mechs->iMechVector;
    int direccion,
            i,
            dir1,
            dir2,
            ultimo_mov;
    hexagono_pos hex_obj,
            hex_obj2;
    int LV1, LV2, LV3;

    /* Obtener la direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n hacia la que nos queremos mover */
    direccion = informacion_mapa->direccion_objetivo(mechJ->pos_Hexagono, mechs[mech_objetivo]->pos_Hexagono);
    mapa->casilla_objetivo(mechJ->pos_Hexagono, direccion, hex_obj);

    LV1 = linea_vision(num_jugador, hex_obj, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);

    /* Si tenemos PM suficientes para hacer el movimiento en linea recta
     * (sin tener en cuenta si no tendremos que girar o no), entonces lo hacemos */
    if (candidatos[direccion] && LV1)
        return direccion;

        /* Si no hay PM suficientes para hacer el movimiento en lÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­nea recta,
         * tenemos que buscar una ruta alternativa */
    else {
        /* Si no es el primer paso del movimiento, 
         * tenemos en cuenta la casilla de la que venimos para no volver a ella */
        ultimo_mov = obt_paso_anterior(mechJ->encaramiento_mech);
        /* Borramos la direccion de vuelta de los candidatos */
        if (ultimo_mov != -1)
            candidatos[ultimo_mov] = false;

        for (i = 1; i <= 2; i++) {
            // Lo primero sera obtener las direcciones de las casillas adyacentes al camino en linea recta
            dir1 = (((direccion - 1)+(6 - i)) % 6) + 1;
            dir2 = (((direccion - 1) + i) % 6) + 1;

            /* Si las dos direcciones llevan a casillas candidatas, 
             * nos movemos a la que nos deje mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s cerca del objetivo */
            if ((candidatos[dir1] == true) && (candidatos[dir2] == true)) {
                mapa->casilla_objetivo(mechJ->pos_Hexagono, dir1, hex_obj);
                mapa->casilla_objetivo(mechJ->pos_Hexagono, dir2, hex_obj2);

                LV2 = linea_vision(num_jugador, hex_obj, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);
                LV3 = linea_vision(num_jugador, hex_obj2, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);

                if (LV2 && LV3) {
                    if (distancia(hex_obj.columna, hex_obj.fila, mechs[mech_objetivo]->pos_Hexagono.columna, mechs[mech_objetivo]->pos_Hexagono.fila) <=
                            distancia(hex_obj2.columna, hex_obj2.fila, mechs[mech_objetivo]->pos_Hexagono.columna, mechs[mech_objetivo]->pos_Hexagono.fila))
                        return dir1;
                    else
                        return dir2;
                } else {
                    if (LV2)
                        return dir1;
                    if (LV3)
                        return dir2;
                }
            } else {
                if (candidatos[dir1] == TRUE) {
                    mapa->casilla_objetivo(mechJ->pos_Hexagono, dir1, hex_obj);
                    LV2 = linea_vision(num_jugador, hex_obj, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);
                    if (LV2)
                        return dir1;
                }
                if (candidatos[dir2] == TRUE) {
                    mapa->casilla_objetivo(mechJ->pos_Hexagono, dir2, hex_obj);
                    LV3 = linea_vision(num_jugador, hex_obj2, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);
                    if (LV3)
                        return dir2;
                }
            }
        }
        /*Si llegamos aqui es que no hemos podido movernos a una casilla donde tengamos LV
        asi que acemos el movimiento tan solo para acercarnos, en espera de que pasemos los 
        obstaculos que impiden el tiro limpio */
        if (candidatos[direccion])
            return direccion;

            /* Si no hay PM suficientes para hacer el movimiento en lÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­nea recta,
             * tenemos que buscar una ruta alternativa */
        else {
            /* Si no es el primer paso del movimiento, 
             * tenemos en cuenta la casilla de la que venimos para no volver a ella */
            ultimo_mov = obt_paso_anterior(mechJ->encaramiento_mech);
            /* Borramos la direccion de vuelta de los candidatos */
            if (ultimo_mov != -1)
                candidatos[ultimo_mov] = FALSE;

            for (i = 1; i <= 2; i++) {
                // Lo primero sera obtener las direcciones de las casillas adyacentes al camino en linea recta
                dir1 = (((direccion - 1)+(6 - i)) % 6) + 1;
                dir2 = (((direccion - 1) + i) % 6) + 1;

                /* Si las dos direcciones llevan a casillas candidatas, 
                 * nos movemos a la que nos deje mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s cerca del objetivo */
                if ((candidatos[dir1] == TRUE) && (candidatos[dir2] == TRUE)) {
                    mapa->casilla_objetivo(mechJ->pos_Hexagono, dir1, hex_obj);
                    mapa->casilla_objetivo(mechJ->pos_Hexagono, dir2, hex_obj2);
                    if (distancia(hex_obj.columna, hex_obj.fila, mechs[mech_objetivo]->pos_Hexagono.columna, mechs[mech_objetivo]->pos_Hexagono.fila) <=
                            distancia(hex_obj2.columna, hex_obj2.fila, mechs[mech_objetivo]->pos_Hexagono.columna, mechs[mech_objetivo]->pos_Hexagono.fila))
                        return dir1;
                    else
                        return dir2;
                } else {
                    if (candidatos[dir1] == TRUE)
                        return dir1;
                    if (candidatos[dir2] == TRUE)
                        return dir2;
                }
            }
        }

    }
    return -1;
}

/*Esta funcion devuelve un entero con la direccion por la que hemos llegado a la 
  casilla actual en caso de que no sea el primer movimiento. Para ello va recorriendo la estructura
  de movimientos y teniendo en cuenta en el encaramiento del mech, va ajustÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ndolo segÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Âºn los pasos
  que se hayan hecho, hasta que se encuentre un movimiento adelante o hacia atrÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s, en cuyo
  caso devuelve la direccion contraria a la del movimiento*/
int acciones::obt_paso_anterior(int direccion) {

    int dir = direccion,
            i;
>>>>>>> 6ef4bb63a69e80805e2f188877946ca3308c254f

//void acciones::mov_atacar(int num_jugador, int num_jugadores, int PM, int tipo_mov) {
//    iMech** mechs = informacion_mechs->iMechVector;
//    iMech* mechJ = informacion_mechs->mechJugador;
//    infoMapa* mapa = informacion_mapa;
//    hexagono_pos hex_obj;
//    int mech_objetivo, /* Guarda el nÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Âºmero del mech al que nos queremos acercar */
//            fin_movimiento = FALSE, /* TRUE->no se hacen mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s movimientos */
//            direccion = 0, /* DirecciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n hacia la que nos tenemos que mover */
//            coste, /* Variable auxiliar */
//            //candidatos[7], /* candidatos[i]==TRUE -> podemos movernos en la direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n i */
//            dir_giro,
//            coste_giro;
//    int PM_INI = PM;
//    bool candidatos[7];
//
//    /* Obtener el nÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Âºmero del mech que tenemos mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s cerca */
//    mech_objetivo = mechJ->buscar_mech_cercano(mechs, num_jugador, informacion_mechs->nMechs);
//
//    /* Bucle de movimiento. El movimiento se realiza por pasos */
//    while ((PM > 0) && (fin_movimiento == FALSE)) {
//        /* Ver a quÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â© casillas nos podrÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­amos mover */
//        actualizar_mov_candidatos(PM, mechJ->pos_Hexagono, candidatos, mechJ->defMechInfo->toneladas, tipo_mov);
//
//        /* Si estamos encarados hacia la direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n que nos interesa pero
//         * no nos podemos mover a ella, no hacemos ningÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Âºn movimiento mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s.
//         * En caso contrario, buscamos de entre las direcciones candidatas
//         * la mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s adecuada para movernos */
//        if ((mechJ->encaramiento_mech == direccion) &&
//                (candidatos[direccion] == FALSE) && (PM <= PM_INI / 5))
//            direccion = -1;
//        else
//            direccion = mov_acercarse(num_jugador, mech_objetivo, candidatos, PM);
//
//        /* Si no podemos movernos a alguna direccion buena,
//         * esperaremos al siguiente turno para probar con mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s PM iniciales */
//        if (direccion == -1)
//            fin_movimiento = TRUE;
//            /* Si podemos movernos hacia la direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n obtenida, lo intentamos */
//        else {
//            /* Si ya estamos encarados hacia esa direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n,
//             * nos movemos hacia ella */
//            if (mechJ->encaramiento_mech == direccion) {
//                mapa->casilla_objetivo(mechJ->pos_Hexagono, direccion, hex_obj);
//                if (casilla_ocupada(num_jugadores, hex_obj) == TRUE) {
//                    fin_movimiento = TRUE;
//                    printf("dist_disparo = %i, dist_casillas=%i\n", mechJ->dist_disparo(), mapa->distancia_casillas(hex_obj, mechs[mech_objetivo]->pos_Hexagono));
//                } else if (mechJ->dist_disparo() > mapa->distancia_casillas(hex_obj, mechs[mech_objetivo]->pos_Hexagono)) {
//                    if (linea_vision(num_jugador, hex_obj, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2))
//
//                        fin_movimiento = TRUE;
//                } else {
//                    coste = mapa->coste_mov_ady(mechJ->pos_Hexagono.fila, mechJ->pos_Hexagono.columna, hex_obj.fila, hex_obj.columna, mechJ->defMechInfo->toneladas);
//                    confirmar_mov(tipo_mov, hex_obj, direccion, FALSE, MOV_ADELANTE, 1);
//                    mechJ->encaramiento_mech = direccion;
//                    mechJ->pos_Hexagono.columna = hex_obj.columna;
//                    mechJ->pos_Hexagono.fila = hex_obj.fila;
//                    PM -= coste;
//                }
//            }/* Si no estabamos encarados hacia esa direccion y
//             * es un movimiento posible, nos giramos */
//            else {
//                /* Ver para quÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â© lado nos tenemos que mover para
//                 * alcanzar antes esa direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n y hallar cuÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ntos PM
//                 * costarÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­a encararse a esa direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n */
//                dir_giro = func_direccion_giro(mechJ->encaramiento_mech, direccion);
//                coste_giro = func_coste_giro(mechJ->encaramiento_mech, direccion, dir_giro);
//                /* Si tenemos PM para girar hacia esa direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n, lo hacemos */
//
//
//
//                if (PM >= coste_giro) {
//                    confirmar_mov(tipo_mov, mechJ->pos_Hexagono, direccion, FALSE, dir_giro, coste_giro);
//                    mechJ->encaramiento_mech = direccion;
//                    PM -= coste_giro;
//                }/* Si no, giramos hacia esa direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n tanto como podamos
//                 * para acercarnos */
//                else {
//                    //Podemos girar tantas veces como PM nos queden
//                    mechJ->encaramiento_mech = lado_final_giro(mechJ->encaramiento_mech, dir_giro, PM);
//                    confirmar_mov(tipo_mov, mechJ->pos_Hexagono, direccion, FALSE, dir_giro, PM);
//                    PM = 0;
//                }
//            } /* else girar */
//        } /* else realizar movimientos */
//    } /* bucle de movimiento */
//}
//
//int acciones::casilla_ocupada(int num_jugadores, hexagono_pos casilla) {
//    iMech** mechs = informacion_mechs->iMechVector;
//    for (int i = 0; i < num_jugadores - 1; ++i) {
//        if ((mechs[i]->pos_Hexagono.columna == casilla.columna) &&
//                (mechs[i]->pos_Hexagono.fila == casilla.fila))
//            return TRUE;
//    }
//    return FALSE;
//}
//
///* Funcion que evalua los posibles movimientos desde la casilla origen para acercarnos al objetivo,
// * teniendo en cuenta los PM's restantes, de la casilla que venimos, y a quien nos queremos acercar */
//int acciones::mov_acercarse(int num_jugador, int mech_objetivo, bool *candidatos, int PM) {
//    infoMapa* mapa = informacion_mapa;
//    iMech* mechJ = informacion_mechs->mechJugador;
//    iMech** mechs = informacion_mechs->iMechVector;
//    int direccion,
//            i,
//            dir1,
//            dir2,
//            ultimo_mov;
//    hexagono_pos hex_obj,
//            hex_obj2;
//    int LV1, LV2, LV3;
//
//    /* Obtener la direcciÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³n hacia la que nos queremos mover */
//    direccion = informacion_mapa->direccion_objetivo(mechJ->pos_Hexagono, mechs[mech_objetivo]->pos_Hexagono);
//    mapa->casilla_objetivo(mechJ->pos_Hexagono, direccion, hex_obj);
//
//    LV1 = linea_vision(num_jugador, hex_obj, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);
//
//    /* Si tenemos PM suficientes para hacer el movimiento en linea recta
//     * (sin tener en cuenta si no tendremos que girar o no), entonces lo hacemos */
//    if (candidatos[direccion] && LV1)
//        return direccion;
//
//        /* Si no hay PM suficientes para hacer el movimiento en lÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­nea recta,
//         * tenemos que buscar una ruta alternativa */
//    else {
//        /* Si no es el primer paso del movimiento, 
//         * tenemos en cuenta la casilla de la que venimos para no volver a ella */
//        ultimo_mov = obt_paso_anterior(mechJ->encaramiento_mech);
//        /* Borramos la direccion de vuelta de los candidatos */
//        if (ultimo_mov != -1)
//            candidatos[ultimo_mov] = false;
//
//        for (i = 1; i <= 2; i++) {
//            // Lo primero sera obtener las direcciones de las casillas adyacentes al camino en linea recta
//            dir1 = (((direccion - 1)+(6 - i)) % 6) + 1;
//            dir2 = (((direccion - 1) + i) % 6) + 1;
//
//            /* Si las dos direcciones llevan a casillas candidatas, 
//             * nos movemos a la que nos deje mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s cerca del objetivo */
//            if ((candidatos[dir1] == true) && (candidatos[dir2] == true)) {
//                mapa->casilla_objetivo(mechJ->pos_Hexagono, dir1, hex_obj);
//                mapa->casilla_objetivo(mechJ->pos_Hexagono, dir2, hex_obj2);
//
//                LV2 = linea_vision(num_jugador, hex_obj, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);
//                LV3 = linea_vision(num_jugador, hex_obj2, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);
//
//                if (LV2 && LV3) {
//                    if (distancia(hex_obj.columna, hex_obj.fila, mechs[mech_objetivo]->pos_Hexagono.columna, mechs[mech_objetivo]->pos_Hexagono.fila) <=
//                            distancia(hex_obj2.columna, hex_obj2.fila, mechs[mech_objetivo]->pos_Hexagono.columna, mechs[mech_objetivo]->pos_Hexagono.fila))
//                        return dir1;
//                    else
//                        return dir2;
//                } else {
//                    if (LV2)
//                        return dir1;
//                    if (LV3)
//                        return dir2;
//                }
//            } else {
//                if (candidatos[dir1] == TRUE) {
//                    mapa->casilla_objetivo(mechJ->pos_Hexagono, dir1, hex_obj);
//                    LV2 = linea_vision(num_jugador, hex_obj, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);
//                    if (LV2)
//                        return dir1;
//                }
//                if (candidatos[dir2] == TRUE) {
//                    mapa->casilla_objetivo(mechJ->pos_Hexagono, dir2, hex_obj);
//                    LV3 = linea_vision(num_jugador, hex_obj2, (mechJ->enElSuelo + 1) % 2, mechs[mech_objetivo]->pos_Hexagono, (mechs[mech_objetivo]->enElSuelo + 1) % 2);
//                    if (LV3)
//                        return dir2;
//                }
//            }
//        }
//        /*Si llegamos aqui es que no hemos podido movernos a una casilla donde tengamos LV
//        asi que acemos el movimiento tan solo para acercarnos, en espera de que pasemos los 
//        obstaculos que impiden el tiro limpio */
//        if (candidatos[direccion])
//            return direccion;
//
//            /* Si no hay PM suficientes para hacer el movimiento en lÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­nea recta,
//             * tenemos que buscar una ruta alternativa */
//        else {
//            /* Si no es el primer paso del movimiento, 
//             * tenemos en cuenta la casilla de la que venimos para no volver a ella */
//            ultimo_mov = obt_paso_anterior(mechJ->encaramiento_mech);
//            /* Borramos la direccion de vuelta de los candidatos */
//            if (ultimo_mov != -1)
//                candidatos[ultimo_mov] = FALSE;
//
//            for (i = 1; i <= 2; i++) {
//                // Lo primero sera obtener las direcciones de las casillas adyacentes al camino en linea recta
//                dir1 = (((direccion - 1)+(6 - i)) % 6) + 1;
//                dir2 = (((direccion - 1) + i) % 6) + 1;
//
//                /* Si las dos direcciones llevan a casillas candidatas, 
//                 * nos movemos a la que nos deje mÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s cerca del objetivo */
//                if ((candidatos[dir1] == TRUE) && (candidatos[dir2] == TRUE)) {
//                    mapa->casilla_objetivo(mechJ->pos_Hexagono, dir1, hex_obj);
//                    mapa->casilla_objetivo(mechJ->pos_Hexagono, dir2, hex_obj2);
//                    if (distancia(hex_obj.columna, hex_obj.fila, mechs[mech_objetivo]->pos_Hexagono.columna, mechs[mech_objetivo]->pos_Hexagono.fila) <=
//                            distancia(hex_obj2.columna, hex_obj2.fila, mechs[mech_objetivo]->pos_Hexagono.columna, mechs[mech_objetivo]->pos_Hexagono.fila))
//                        return dir1;
//                    else
//                        return dir2;
//                } else {
//                    if (candidatos[dir1] == TRUE)
//                        return dir1;
//                    if (candidatos[dir2] == TRUE)
//                        return dir2;
//                }
//            }
//        }
//
//    }
//    return -1;
//}
//
///*Esta funcion devuelve un entero con la direccion por la que hemos llegado a la 
//  casilla actual en caso de que no sea el primer movimiento. Para ello va recorriendo la estructura
//  de movimientos y teniendo en cuenta en el encaramiento del mech, va ajustÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ndolo segÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Âºn los pasos
//  que se hayan hecho, hasta que se encuentre un movimiento adelante o hacia atrÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡s, en cuyo
//  caso devuelve la direccion contraria a la del movimiento*/
//int acciones::obt_paso_anterior(int direccion) {
//
//    int dir = direccion,
//            i;
//
//    for (i = mov->pasos; i > 0; --i) {
//        switch (mov->tipo[i]) {
//            case MOV_ADELANTE:
//                return ((dir + 2) % 6) + 1;
//            case MOV_DERECHA:
//                dir = ((dir - 1 + mov->veces[i]) % 6) + 1;
//                break;
//            case MOV_IZQUIERDA:
//                dir = ((dir + 5 - mov->veces[i]) % 6) + 1;
//                break;
//            case MOV_ATRAS:
//                return dir;
//        }
//    }
//    return -1;
//}
