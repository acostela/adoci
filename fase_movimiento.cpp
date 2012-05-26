/* 
 * File:   fase_movimiento.cpp
 * Author: asce
 * 
 * Created on 28 de marzo de 2012, 0:34
 */

#include "fase_movimiento.h"

movimiento_t::movimiento_t(infoMapa* inf_mapa, infoMechs * inf_mechs) {
    mapa = inf_mapa;
    mechs = inf_mechs;
    tipo_movimiento = 0;
    destino.fila = 0;
    destino.columna = 0;
    lado = 0;
    MASC = false;
    pasos = 0;
    for (int i = 0; i < 20; ++i) {
        tipo[i] = -1;
        veces[i] = 0;
    }
}

void movimiento_t::salida(string numJ) {
    /* Crear el archivo de salida */
    string cad = "accionJ" + numJ + ".sbt";
    string accion;
    ofstream out(cad.c_str());
    //out.open(cad.c_str());
    /* Linea 1: tipo de movimiento */
    switch (tipo_movimiento) {
        case INMOVIL:
            accion = accion + "Inmovil\n";
            break;
        case ANDAR:
            accion = accion + "Andar\n";
            break;
        case CORRER:
            accion = accion + "Correr\n";
            break;
        case SALTAR:
            accion = accion + "Saltar\n";
            break;
    }

    /* Si el movimiento es INMOVIL, terminar aquÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­ */
    if (tipo_movimiento == INMOVIL) {
        out << accion;
        cout << accion;
        out.close();
        return;
    }

    /* Linea 2: HexÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡gono de destino */
    accion = accion + destino.stringPos() + "\n";

    /* Linea 3: Lado de destino */
    accion = accion + itoStr(lado) + "\n";
    /* Si el movimiento es SALTAR, terminar aquÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­ */
    if (tipo_movimiento == SALTAR) {
        out << accion;
        out.close();
        return;
    }

    /* Linea 4: Usar MASC */
    switch (MASC) {
        case true:
            accion = accion + "True\n";
            break;
        case false:
            accion = accion + "False\n";
            break;
    }

    /* Linea 5: nÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Âºmero de pasos */
    accion = accion + itoStr(pasos) + "\n";

    /* Para cada paso */
    for (int i = 0; i < pasos; ++i) {
        /* Tipo de paso */
        switch (tipo[i]) {
            case MOV_ADELANTE:
                accion = accion + "Adelante\n";
                break;
            case MOV_ATRAS:
                accion = accion + "Atras\n";
                break;
            case MOV_IZQUIERDA:
                accion = accion + "Izquierda\n";
                break;
            case MOV_DERECHA:
                accion = accion + "Derecha\n";
                break;
            case MOV_LEVANTARSE:
                accion = accion + "Levantarse\n";
                break;
            case MOV_TIERRA:
                accion = accion + "Cuerpo a Tierra\n";
                break;
        }
        /* Numero de veces o lado */
        accion = accion + itoStr(veces[i]) + "\n";
    }
    cout << accion << endl;

    /* Cerrar el archivo */
    out << accion;

    out.close();
}

void movimiento_t::getDestino(int & fil_dest, int & col_dest, int & lado_dest, int estrategia) {
    int f, c, lado;
    int ind_objetivo = mechs->mechJugador->buscar_mech_cercano(mechs->iMechVector, mechs->mechJugador->numJ, mechs->nMechs);
    int f_obj = mechs->iMechVector[ind_objetivo]->pos_Hexagono.fila;
    int c_obj = mechs->iMechVector[ind_objetivo]->pos_Hexagono.columna;
    int enc_obj = mechs->iMechVector[ind_objetivo]->encaramiento_mech;
    nodoEnEsaDireccion(f_obj, c_obj, enc_obj, f, c);
    switch (enc_obj) {
        case 1:
            lado = 4;
            break;
        case 2:
            lado = 5;
            break;
        case 3:
            lado = 6;
            break;
        case 4:
            lado = 1;
            break;
        case 5:
            lado = 2;
            break;
        case 6:
            lado = 3;
            break;
    }
    switch (estrategia) {
        case ATACAR:
            fil_dest = f;
            col_dest = c;
            lado_dest = lado;
            //Pos mas cercana al mas cercano
            break;
        case HUIR:
            fil_dest = 1;
            col_dest = 1;
            lado_dest = 3;
            //Huimos del mas fuerte
            break;
    }
    //    fil_dest = 4;
    //    col_dest = 8;
    //    lado_dest = 1;

}

int movimiento_t::estrategia_movimiento() {
    mechs->mechJugador->dmj->Heridas_MW;
    iMech* mech = mechs->mechJugador;
    /* Si el mech esta en pie, el MechWarrior tiene pocas heridas, el
       nivel de temperatura no es muy alto, los puntos de blindaje de la cabeza, 
       del torso central y de las piernas no son bajos y tenemos armas no traseras
       con las que disparar, entonces la estrategia sera de ataque */

    if ((mech->enElSuelo == FALSE) &&
            (mechs->mechJugador->dmj->Heridas_MW < 5) && /* Para que haya como mucho una prob. de 5/6 de perder la consciencia */
            (mech->temp_actual < 13) && /* Para evitar la desconexiÃƒÂ³n */
            (mech->blindaje.CAB > 2) &&
            (mech->blindaje.TC > 2) &&
            (mech->blindaje.PI > 1) &&
            (mech->blindaje.PD > 1) &&
            mech->armas_ok())
        return ATACAR;
    else
        return HUIR;
}

bool movimiento_t::check_mov_correr(const vector<node>& nodos) {

    int PM = mechs->mechJugador->dmj->PM_correr;
    for (int i = 0; i < nodos.size(); i++) {
        cout << mapa->mapa[nodos[i].fil][nodos[i].col]->rioCentroCara[nodos[i].orientacion] << endl;
        if (mapa->mapa[nodos[i].fil][nodos[i].col]->nivel <= 1 &&
                mapa->mapa[nodos[i].fil][nodos[i].col]->terreno == AGUA &&
                nodos[i].coste < PM) return false;
    }

    return true;

}

int movimiento_t::tipo_movim(const vector<node>& nodos) {
    int tipo_mov;
    if (mechs->mechJugador->dmj->PM_correr > mechs->mechJugador->dmj->PM_andar)
        tipo_mov = CORRER;
    else
        tipo_mov = ANDAR;

    if (tipo_mov == CORRER) {
        if (check_mov_correr(nodos))
            return CORRER;
        else return ANDAR;
    }
}

void movimiento_t::logica_movimiento() {
    vector<node> nodos;
    int PM;
    int estrategia = estrategia_movimiento(); //ATACAR o HUIR

    int tons = mechs->mechJugador->defMechInfo->toneladas;
    int col_mech = 9; //mechs->mechJugador->pos_Hexagono.columna;
    int fil_mech = 15; //mechs->mechJugador->pos_Hexagono.fila;
    int lado_mech = 5; //mechs->mechJugador->encaramiento_mech;
    int col_dest = 8, fil_dest = 14, lado_dest = 6;


    //Si esta  en el suelo intentar levantarse

    //ATACAR O HUIR
    //--getDestino(fil_dest, col_dest, lado_dest, estrategia);


    node *destino = new node(fil_dest, col_dest, lado_dest, mapa, tons);
    node *inicio = new node(fil_mech, col_mech, lado_mech, destino, mapa, tons);

    if (distanciaNodos(fil_mech, col_mech, fil_dest, col_dest) < 5 && estrategia == ATACAR)
        tipo_movimiento = INMOVIL; //Ya estamos cerca así que no desperdiciamos puntos
    else {

        aStar(inicio, destino, nodos, mapa, tons);



        int tipo_mov = tipo_movim(nodos);
        tipo_movimiento = tipo_mov;
        switch (tipo_mov) {
            case ANDAR:
                PM = mechs->mechJugador->dmj->PM_andar;
                break;
            case CORRER:
                PM = mechs->mechJugador->dmj->PM_correr;
                break;
        }//Añadir saltar




        //        for(int i=0;i<nodos.size();i++)
        //            nodos[i].show();
        //if(mechj->equilibrio_ok())

        getSecuenciaPasos(nodos, PM);

        //        for(int i=0;i<pasos;i++)
        //                cout<<"TIPO: "<<tipo[i]<<endl;
        //        for(int i=0;i<pasos;i++)
        //                cout<<"VECES: "<<veces[i]<<endl;
        //        cout<<"Pasos: "<<pasos<<endl;
    }
}

int movimiento_t::getTipoMov(const node & n1, const node & n2) {

    int o1, o2;
    int f, c;
    if (n1.mismo_hexagono(n2)) {
        o1 = n1.orientacion;
        o2 = n2.orientacion;
        if (o2 == o1 + 1 || (o1 == 6 && o2 == 1))
            return MOV_DERECHA;
        else if (o2 == o1 - 1 || (o1 == 1 && o2 == 6))
            return MOV_IZQUIERDA;
        else {
            cout << "Problema en getTipoMov, pulse uan tecla para continuar ...\n";
            cin.get();
            return 0;
        }
        //IZQ O DER
    } else {
        nodoEnEsaDireccion(n1.fil, n1.col, n1.orientacion, f, c);
        if (n2.fil == f && n2.col == c)
            return MOV_ADELANTE;
        else return MOV_ATRAS;
        //ADELANTE O ATRÁS
    }


}

void movimiento_t::getSecuenciaPasos(const vector<node> & nodosPath, int PM) {

    vector<node> nodos = nodosPath;
    //Por ahora para correr
    //    tipo_movimiento = CORRER;
    //    int PM = mechs->mechJugador->dmj->PM_correr;

    while (nodos.back().coste > PM) {
        nodos.pop_back();
    }
    //Si no tenemos PM para movernos nos quedamos inmoviles
    if (nodos.size() == 1) {
        tipo_movimiento = INMOVIL;
        return;
    }
    /////

    destino.fila = nodos.back().fil;
    destino.columna = nodos.back().col;
    lado = nodos.back().orientacion;

    //    int veces[20];
    //    for(int i=0;i<20;i++)
    //        veces[i]=0;

    pasos = 0; //Pasos en los que se divide el movimiento

    int dir_actual = getTipoMov(nodos[0], nodos[1]);
    int dir;
    node ultimo_nodo(nodos[1]);
    nodos.erase(nodos.begin());
    nodos.erase(nodos.begin());
    tipo[pasos] = dir_actual; //ADELANTE,ATRÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¯Ãƒâ€šÃ‚Â¿Ãƒâ€šÃ‚Â½S,IZQ,DERE,LEVANTARSE, CUERPO A TIERRA
    veces[pasos] = 1;
    while (!nodos.empty()) {
        dir = getTipoMov(ultimo_nodo, nodos.front());
        ultimo_nodo = nodos.front();
        nodos.erase(nodos.begin());
        if (dir == dir_actual)
            veces[pasos]++; //incrementamos las veces del paso actual
        else {
            pasos++; //Incrementamos el paso actual
            dir_actual = dir;
            tipo[pasos] = dir_actual;
            veces[pasos] = 1;
        }
    }
    pasos++; //El num de pasos sera el paso actual +1 (empiezan en )

}
