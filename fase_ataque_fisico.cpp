/* 
 * File:   fase_ataque_fisico.cpp
 * Author: asce
 * 
 * Created on 28 de marzo de 2012, 0:36
 */

#include "fase_ataque_fisico.h"
#include "infoMechs.h"

ataque_fisico_t::ataque_fisico_t(infoMapa* inf_mapa, infoMechs* inf_mechs){
    mapa = inf_mapa;
    mechs = inf_mechs;
    num_armas = 0;
}

void ataque_fisico_t::salida(string numJ) {

   string cad = "accionJ" + numJ + ".sbt";
    string accion;
    ofstream out(cad.c_str());

    /* Linea 1: Numero de armas fisicas que se van a usar */
    accion = accion + itoStr(num_armas) + "\n";

    /* Para cada arma */
    for (int i = 0; i < num_armas; ++i) {
        /* LocalizaciÃƒÆ’Ã‚Â³n del arma fÃƒÆ’Ã‚Â­sica */
        switch (armas[i].localizacion) {
            case BI_A:
                accion = accion + "BI\n";
                break;
            case BD_A:
                accion = accion + "BD\n";
                break;
            case PI_A:
                accion = accion + "PI\n";
                break;
            case PD_A:
                accion = accion + "PD\n";
                break;
            case BIBD_A://ojooooooooooooooooooo declaraciones conflictivas ...
                accion = accion + "BIBD\n";
                break;
        }

        /* Slot del arma fisica */
        accion = accion + itoStr(armas[i].slot) + "\n";

        /* Hexagono objetivo del arma */
        accion = accion + armas[i].objetivo.stringPos() + "\n";

        /* Tipo de objetivo */
        switch (armas[i].tipo_objetivo) {
            case MECH:
                accion = accion + "Mech\n";
                break;
            case HEXAGONO:
                accion = accion + "Hexagono\n";
                break;
            case NINGUNO:
                accion = accion + "Ninguno\n";
                break;
        }
    }
    /* Cerrar el archivo */
    out << accion;
    out.close();
}

void ataque_fisico_t::posiciones_adyacentes(int f, int c, int adyacentes[][2]) {
    //Arriba
    adyacentes[0][0] = f - 1;
    adyacentes[0][1] = c;
    //Abajo
    adyacentes[3][0] = f + 1;
    adyacentes[3][1] = c;

    if (c % 2 != 0) {
        adyacentes[1][0] = f - 1;
        adyacentes[1][1] = c + 1;

        adyacentes[2][0] = f;
        adyacentes[2][1] = c + 1;

        adyacentes[4][0] = f;
        adyacentes[4][1] = c - 1;

        adyacentes[5][0] = f - 1;
        adyacentes[5][1] = c - 1;
    } else {

        adyacentes[1][0] = f;
        adyacentes[1][1] = c + 1;

        adyacentes[2][0] = f + 1;
        adyacentes[2][1] = c + 1;

        adyacentes[4][0] = f + 1;
        adyacentes[4][1] = c - 1;

        adyacentes[5][0] = f;
        adyacentes[5][1] = c - 1;
    }
}

int ataque_fisico_t::angulo_torso_enemigo(int mech_obj){
    int col_ene;
    int fil_ene;
    int fil_jug;
    int col_jug;
    int lado_hex_ene;
    int enca_jug;
    
    fil_ene = mechs->iMechVector[mech_obj]->pos_Hexagono.fila;
    col_ene = mechs->iMechVector[mech_obj]->pos_Hexagono.columna;
    fil_jug = mechs->mechJugador->pos_Hexagono.fila;
    col_jug = mechs->mechJugador->pos_Hexagono.columna;
        
    if(col_jug %2 == 0){
        if(col_ene < col_jug){ //lado 5 o 6 depende fila
            if(fil_ene > fil_jug)
                lado_hex_ene = 5;
            else
                lado_hex_ene = 6;
        }else if(col_ene > col_jug){ //lado 2 o 3 depende fila
            if(fil_ene > fil_jug)
                lado_hex_ene = 3;
            else
                lado_hex_ene = 2;
        }else if(col_ene == col_jug){ //lado 1 o 4 depende fila
            if(fil_ene < fil_jug)
                lado_hex_ene = 1;
            else
                lado_hex_ene = 4;
        }
    }else{
        if(col_ene < col_jug){ //lado 5 o 6 depende fila
            if(fil_ene < fil_jug)
                lado_hex_ene = 6;
            else
                lado_hex_ene = 5;
        }else if(col_ene > col_jug){ //lado 2 o 3 depende fila
            if(fil_ene < fil_jug)
                lado_hex_ene = 2;
            else
                lado_hex_ene = 3;
        }else if(col_ene == col_jug){ //lado 1 o 4 depende fila
            if(fil_ene < fil_jug)
                lado_hex_ene = 1;
            else
                lado_hex_ene = 4;
        }    
    }
    enca_jug = mechs->mechJugador->encaramiento_torso;
    
    if(lado_hex_ene == enca_jug){
        return FRONTAL;
    }else if(enca_jug == 1 && lado_hex_ene == 6){
        return IZQUIERDO;
    }else if(enca_jug == 1 && lado_hex_ene == 2){
        return DERECHO;
    }else if(enca_jug == 2 && lado_hex_ene == 1){
        return IZQUIERDO;
    }else if(enca_jug == 2 && lado_hex_ene == 3){
        return DERECHO;
    }else if(enca_jug == 3 && lado_hex_ene == 2){
        return IZQUIERDO;
    }else if(enca_jug == 3 && lado_hex_ene == 4){
        return DERECHO;
    }else if(enca_jug == 4 && lado_hex_ene == 3){
        return IZQUIERDO;
    }else if(enca_jug == 4 && lado_hex_ene == 5){
        return DERECHO;
    }else if(enca_jug == 5 && lado_hex_ene == 4){
        return IZQUIERDO;
    }else if(enca_jug == 5 && lado_hex_ene == 6){
        return DERECHO;
    }else if(enca_jug == 6 && lado_hex_ene == 1){
        return DERECHO;
    }else if(enca_jug == 6 && lado_hex_ene == 5){
        return IZQUIERDO;
    }
}

int ataque_fisico_t::angulo_mech_enemigo(int mech_obj){
    int col_ene;
    int fil_ene;
    int fil_jug;
    int col_jug;
    int lado_hex_ene;
    int enca_jug;
    int prueba;
    
    fil_ene = mechs->iMechVector[mech_obj]->pos_Hexagono.fila;
    col_ene = mechs->iMechVector[mech_obj]->pos_Hexagono.columna;
    fil_jug = mechs->mechJugador->pos_Hexagono.fila;
    col_jug = mechs->mechJugador->pos_Hexagono.columna;
    
    prueba = mechs->iMechVector[mech_obj]->numJ;
    
    if(col_jug %2 == 0){
        if(col_ene < col_jug){ //lado 5 o 6 depende fila
            if(fil_ene > fil_jug)
                lado_hex_ene = 5;
            else
                lado_hex_ene = 6;
        }else if(col_ene > col_jug){ //lado 2 o 3 depende fila
            if(fil_ene > fil_jug)
                lado_hex_ene = 3;
            else
                lado_hex_ene = 2;
        }else if(col_ene == col_jug){ //lado 1 o 4 depende fila
            if(fil_ene < fil_jug)
                lado_hex_ene = 1;
            else
                lado_hex_ene = 4;
        }
    }else{
        if(col_ene < col_jug){ //lado 5 o 6 depende fila
            if(fil_ene < fil_jug)
                lado_hex_ene = 6;
            else
                lado_hex_ene = 5;
        }else if(col_ene > col_jug){ //lado 2 o 3 depende fila
            if(fil_ene < fil_jug)
                lado_hex_ene = 2;
            else
                lado_hex_ene = 3;
        }else if(col_ene == col_jug){ //lado 1 o 4 depende fila
            if(fil_ene < fil_jug)
                lado_hex_ene = 1;
            else
                lado_hex_ene = 4;
        }    
    }
    enca_jug = mechs->mechJugador->encaramiento_mech;
    
    if(lado_hex_ene == enca_jug){
        return FRONTAL;
    }else if(enca_jug == 1 && lado_hex_ene == 6){
        return IZQUIERDO;
    }else if(enca_jug == 1 && lado_hex_ene == 2){
        return DERECHO;
    }else if(enca_jug == 2 && lado_hex_ene == 1){
        return IZQUIERDO;
    }else if(enca_jug == 2 && lado_hex_ene == 3){
        return DERECHO;
    }else if(enca_jug == 3 && lado_hex_ene == 2){
        return IZQUIERDO;
    }else if(enca_jug == 3 && lado_hex_ene == 4){
        return DERECHO;
    }else if(enca_jug == 4 && lado_hex_ene == 3){
        return IZQUIERDO;
    }else if(enca_jug == 4 && lado_hex_ene == 5){
        return DERECHO;
    }else if(enca_jug == 5 && lado_hex_ene == 4){
        return IZQUIERDO;
    }else if(enca_jug == 5 && lado_hex_ene == 6){
        return DERECHO;
    }else if(enca_jug == 6 && lado_hex_ene == 1){
        return DERECHO;
    }else if(enca_jug == 6 && lado_hex_ene == 5){
        return IZQUIERDO;
    }
}

int ataque_fisico_t::objetivoFisico() {
    int auxColumna;
    int auxFila;
    int columnaJugador;
    int filaJugador;
    int mech_mas_debil;
    int score_objetivo[mechs->nMechs - 1]; //Aqui se guardara en cada dimension el Score de cada objetivo para elegir el mejor al que disparar
    int armaduraux = 0;
    int armaduraminima = 100000;
    int objetivo;
    int scoreaux;

    columnaJugador = mechs->mechJugador->pos_Hexagono.columna;
    filaJugador = mechs->mechJugador->pos_Hexagono.fila;

    for (int i = 0; i < mechs->nMechs - 1; i++) {
        score_objetivo[i] = 0;
    }

    for (int i = 0; i < mechs->nMechs - 1; i++) {
        auxColumna = mechs->iMechVector[i]->pos_Hexagono.columna;
        auxFila = mechs->iMechVector[i]->pos_Hexagono.fila;
        if (mechs->iMechVector[i]->operativo == true) 
            score_objetivo[i] = distancia_hexagonal(filaJugador, columnaJugador, auxFila, auxColumna);//Se pone como Score la distancia del Mech con respecto al nuestro

        
//        armaduraux += mechs->iMechVector[i]->blindaje.BD;
//        armaduraux += mechs->iMechVector[i]->blindaje.BI;
//        armaduraux += mechs->iMechVector[i]->blindaje.CAB;
//        armaduraux += mechs->iMechVector[i]->blindaje.PATC;
//        armaduraux += mechs->iMechVector[i]->blindaje.PATD;
//        armaduraux += mechs->iMechVector[i]->blindaje.PATI;
//        armaduraux += mechs->iMechVector[i]->blindaje.PD;
//        armaduraux += mechs->iMechVector[i]->blindaje.PI;
//        armaduraux += mechs->iMechVector[i]->blindaje.TC;
//        armaduraux += mechs->iMechVector[i]->blindaje.TD;
//        armaduraux += mechs->iMechVector[i]->blindaje.TI;
    }

    for (int i = 0; i < mechs->nMechs; i++) {
        if (score_objetivo[i] == 1) {
            objetivo = i;
        }
    }
   // objetivo = mechs->iMechVector[objetivo]->numJ;
    return objetivo;
}

void ataque_fisico_t::ataque_fisico(){
    bool brazo_izq = true;
    bool brazo_der = true;
    bool ene_adyacente = false;
    int contador_armas=0;
    int desnivel;
    int objetivo;
    int angulo;
    int angulo_patadas;
 
    if(mechs->mechJugador->enElSuelo){ //Si esta en el suelo no puede pegar;
        num_armas=0;
        return;
    }
    int fil_jugador, col_jugador, filaux, colaux;
    int adyacentes [6][2];
    int filene=0;
    int colene=0;

    fil_jugador = mechs->mechJugador->pos_Hexagono.fila;
    col_jugador = mechs->mechJugador->pos_Hexagono.columna;
    
    posiciones_adyacentes(fil_jugador, col_jugador, adyacentes);

    //Consideramos enemigo adyacente si esta en una casilla al lado y el desnivel no es mayor que 1 (Le podemos pegar cuerpo a cuerpo).
    for (int i = 0; i < mechs->nMechs - 1; i++) {
        filaux = mechs->iMechVector[i]->pos_Hexagono.fila;
        colaux = mechs->iMechVector[i]->pos_Hexagono.columna;
        for (int j = 0; j < 6; j++) {
            if (adyacentes[j][0] == filaux && adyacentes[j][1] == colaux){
                if (abs(mapa->mapa[fil_jugador][col_jugador]->nivel - mapa->mapa[filaux][colaux]->nivel) <= 1){ //Si hay enemigo adyacente y estÃƒÂ¡ a buena altura
                    ene_adyacente = true; 
                }
            }
        }
    }
    
    if(ene_adyacente){
        objetivo = objetivoFisico();
        filene = mechs->iMechVector[objetivo]->pos_Hexagono.fila;
        colene = mechs->iMechVector[objetivo]->pos_Hexagono.columna;
        angulo = angulo_torso_enemigo(objetivo);
        if(angulo != TRASERO){
            if(!mechs->mechJugador->defMechInfo->brazos[0]){ //Si no tiene brazos no puede pegar puÃ±etazos
                brazo_izq = false;
                brazo_der = false;
            }else{
                for(int i=1; i<5; i++){
                    if(!mechs->mechJugador->defMechInfo->brazos[i])
                        brazo_izq = false;
                }
                for(int i=5; i<9; i++){
                    if(!mechs->mechJugador->defMechInfo->brazos[i])
                        brazo_der = false;
                }
            }
            if(angulo == FRONTAL){ //Puede pegar con los dos brazos.
                desnivel = mapa->mapa[fil_jugador][col_jugador]->nivel - mapa->mapa[filene][colene]->nivel;
                if((desnivel ==0 || desnivel == -1) && !mechs->iMechVector[objetivo]->enElSuelo){ //Tiene que estar a la altura correcta y no en el suelo
                    if(brazo_der){
                        armas[contador_armas].localizacion = BD;
                        armas[contador_armas].slot = 1000;
                        contador_armas++;    
                    }
                    if(brazo_izq){
                        armas[contador_armas].localizacion = BI;
                        armas[contador_armas].slot = 1000;
                        contador_armas++;    
                    } 
                }
                if(desnivel == 0 || desnivel == 1){
                    angulo_patadas = angulo_mech_enemigo(objetivo);
                    if(angulo_patadas = FRONTAL){
                        if(mechs->iMechVector[objetivo]->enElSuelo){
                            if(desnivel == 0){
                                armas[contador_armas].localizacion = PD;
                                armas[contador_armas].slot = 2000;
                                contador_armas++;
                            }
                        }else{
                            armas[contador_armas].localizacion = PD;
                            armas[contador_armas].slot = 2000;
                            contador_armas++;    
                        }
                        
                    }else if(angulo_patadas == DERECHO){
                        if(mechs->iMechVector[objetivo]->enElSuelo){
                            if(desnivel == 0){
                                armas[contador_armas].localizacion = PD;
                                armas[contador_armas].slot = 2000;
                                contador_armas++;
                            }
                        }else{
                            armas[contador_armas].localizacion = PD;
                            armas[contador_armas].slot = 2000;
                            contador_armas++;    
                        }
                    }else if(angulo_patadas == IZQUIERDO){
                        if(mechs->iMechVector[objetivo]->enElSuelo){
                            if(desnivel == 0){
                                armas[contador_armas].localizacion = PI;
                                armas[contador_armas].slot = 2000;
                                contador_armas++;
                            }
                        }else{
                            armas[contador_armas].localizacion = PI;
                            armas[contador_armas].slot = 2000;
                            contador_armas++;    
                        }
                    }
                }
            }else if(angulo == DERECHO){
                if((desnivel ==0 || desnivel == -1) && !mechs->iMechVector[objetivo]->enElSuelo){
                    if(brazo_der){
                        armas[contador_armas].localizacion = BD;
                        armas[contador_armas].slot = 1000;
                        contador_armas++;
                    }                  
                }
                if(desnivel == 0 || desnivel == 1){
                    angulo_patadas = angulo_mech_enemigo(objetivo);
                    if(angulo_patadas = FRONTAL){
                       if(mechs->iMechVector[objetivo]->enElSuelo){
                            if(desnivel == 0){
                                armas[contador_armas].localizacion = PD;
                                armas[contador_armas].slot = 2000;
                                contador_armas++;
                            }
                        }else{
                            armas[contador_armas].localizacion = PD;
                            armas[contador_armas].slot = 2000;
                            contador_armas++;    
                        }
                    }else if(angulo_patadas == DERECHO){
                        if(mechs->iMechVector[objetivo]->enElSuelo){
                            if(desnivel == 0){
                                armas[contador_armas].localizacion = PD;
                                armas[contador_armas].slot = 2000;
                                contador_armas++;
                            }
                        }else{
                            armas[contador_armas].localizacion = PD;
                            armas[contador_armas].slot = 2000;
                            contador_armas++;    
                        }
                    }else if(angulo_patadas == IZQUIERDO){
                        if(mechs->iMechVector[objetivo]->enElSuelo){
                            if(desnivel == 0){
                                armas[contador_armas].localizacion = PI;
                                armas[contador_armas].slot = 2000;
                                contador_armas++;
                            }
                        }else{
                            armas[contador_armas].localizacion = PI;
                            armas[contador_armas].slot = 2000;
                            contador_armas++;    
                        }
                    }
                }
            }else if(angulo == IZQUIERDO){
                if((desnivel ==0 || desnivel == -1) && !mechs->iMechVector[objetivo]->enElSuelo){
                    if(brazo_izq){
                        armas[contador_armas].localizacion = BI;
                        armas[contador_armas].slot = 1000;
                        contador_armas++;   
                    }
                }                
                if(desnivel == 0 || desnivel == 1){
                    angulo_patadas = angulo_mech_enemigo(objetivo);
                    if(angulo_patadas = FRONTAL){
                       if(mechs->iMechVector[objetivo]->enElSuelo){
                            if(desnivel == 0){
                                armas[contador_armas].localizacion = PI;
                                armas[contador_armas].slot = 2000;
                                contador_armas++;
                            }
                        }else{
                            armas[contador_armas].localizacion = PI;
                            armas[contador_armas].slot = 2000;
                            contador_armas++;    
                        }
                    }else if(angulo_patadas == DERECHO){
                        if(mechs->iMechVector[objetivo]->enElSuelo){
                            if(desnivel == 0){
                                armas[contador_armas].localizacion = PD;
                                armas[contador_armas].slot = 2000;
                                contador_armas++;
                            }
                        }else{
                            armas[contador_armas].localizacion = PD;
                            armas[contador_armas].slot = 2000;
                            contador_armas++;    
                        }
                    }else if(angulo_patadas == IZQUIERDO){
                        if(mechs->iMechVector[objetivo]->enElSuelo){
                            if(desnivel == 0){
                                armas[contador_armas].localizacion = PI;
                                armas[contador_armas].slot = 2000;
                                contador_armas++;
                            }
                        }else{
                            armas[contador_armas].localizacion = PI;
                            armas[contador_armas].slot = 2000;
                            contador_armas++;    
                        }
                    }
                }
            }
            num_armas = contador_armas;
            for (int i=0; i<num_armas; i++){
                armas[i].tipo_objetivo = MECH;
                armas[i].objetivo.fila = filene;
                armas[i].objetivo.columna = colene;
            }
        }
        else{
            num_armas=0;
            return;
        }
    }else{
        num_armas=0;
        return;
    }
    cout << "Fin de logica de cuerpo a cuerpo" << endl;
    cin.get();



//    // Creamos un vector del numero de ataques que podemos hacer a un objetivo
//    int[] num_ataques = new int[3];
//    // Creamos una matriz de los miembros con los que podemos atacar a cada uno
//    // segun este orden: brazo izquierdo, brazo derecho, pierna izquierda y pierna derecha
//    bool [][] miembros = new bool [adyacentes.Count][];
//    // Creamos una lista de hexagonos que nos hara falta a la hora de escribir el fichero
//    List<string> hexagonos = new List<string>();
//    int objetivo = 0, nivel_objetivo=0;
//
//
//    for(int i=0; i<adyacentes.Count; i++){
//        miembros[i] = new bool [4]{false,false,false,false};
//
//        // Si hay un enemigo
//        if (adyacentes[i] != -1)
//        {
//
//            // Encontramos a que Mech objetivo vamos a intentar atacar
//            for (int j = 0; j < datos.num_mechs; j++)
//            {
//
//                string hexagono = "";
//
//                if (datos.tablero.casillas[adyacentes[i]].col < 10)
//                    hexagono += "0" + datos.tablero.casillas[adyacentes[i]].col;
//                else
//                    hexagono += datos.tablero.casillas[adyacentes[i]].col;
//
//
//                if (datos.tablero.casillas[adyacentes[i]].fil < 10)
//                    hexagono += "0" + datos.tablero.casillas[adyacentes[i]].fil;
//                else
//                    hexagono += datos.tablero.casillas[adyacentes[i]].fil;
//
//                // AÃƒÂ±adimos el hexagono a la lista de hexagonos
//                hexagonos.Add(hexagono);
//
//                if (datos.robots[j].pos_hexagono == hexagono)
//                    objetivo = j;
//            }
//
//            // Comprobamos el nivel en el que se encuentra el objetivo respecto a nosotros
//
//            if (datos.tablero.getCasilla(col, fil).nivel == datos.tablero.casillas[adyacentes[i]].nivel - 1)
//                nivel_objetivo = 1;
//            if (datos.tablero.getCasilla(col, fil).nivel == datos.tablero.casillas[adyacentes[i]].nivel + 1)
//                nivel_objetivo = -1;
//
//
//            // Comprobaremos el numero de ataques que podemos realizar a cada uno:
//            // Si el Mech objetivo no se encuentra por debajo de nosotros o no esta tumbado
//            if (!(nivel_objetivo == -1) || !datos.robots[objetivo].tumbado)
//            {
//
//
//                // Si el Mech esta a nuestra izquierda
//                if (i == 0)
//                {
//
//                    if (!datos.disp_brazo_izq)
//                    {
//                        if (!datos.robots[objetivo].tumbado)
//                        {
//                            // Si el objetivo esta a nuestra altura o mas alto
//                            if (nivel_objetivo == 0 || nivel_objetivo == 1)
//                            {
//                                num_ataques[i]++;
//                                miembros[i][0] = true;
//                            }
//                        }
//                        else
//                        {
//                            if (nivel_objetivo == 1)
//                            {
//                                num_ataques[i]++;
//                                miembros[i][0] = true;
//                            }
//                        }
//                    }
//
//                    if (!datos.disp_pierna_izq)
//                    {
//                        // Si el objetivo esta a nuestra altura o mas bajo
//                        if (nivel_objetivo == 0 || nivel_objetivo == -1)
//                        {
//                            num_ataques[i]++;
//                            miembros[i][2] = true;
//                        }
//
//                    }
//                }
//
//                // Si el Mech esta a nuestra derecha
//                if (i == 2)
//                {
//
//                    if (!datos.disp_brazo_der)
//                    {
//                        if (!datos.robots[objetivo].tumbado)
//                        {
//                            // Si el objetivo esta a nuestra altura o mas alto
//                            if (nivel_objetivo == 0 || nivel_objetivo == 1)
//                            {
//                                num_ataques[i]++;
//                                miembros[i][0] = true;
//                            }
//                        }
//                        else
//                        {
//                            if (nivel_objetivo == 1)
//                            {
//                                num_ataques[i]++;
//                                miembros[i][1] = true;
//                            }
//                        }
//                    }
//
//                    if (!datos.disp_pierna_der)
//                    {
//                        // Si el objetivo esta a nuestra altura o mas bajo
//                        if (nivel_objetivo == 0 || nivel_objetivo == -1)
//                        {
//                            num_ataques[i]++;
//                            miembros[i][3] = true;
//                        }
//
//                    }
//                }
//
//                // Si el Mech se encuentra enfrente nuestra
//                if (i == 1)
//                {
//
//                    if (nivel_objetivo == 0 || nivel_objetivo == 1)
//                    {
//                        if (!datos.disp_brazo_izq)
//                        {
//                            if (!datos.robots[objetivo].tumbado)
//                            {
//                                // Si el objetivo esta a nuestra altura o mas alto
//                                if (nivel_objetivo == 0 || nivel_objetivo == 1)
//                                {
//                                    num_ataques[i]++;
//                                    miembros[i][0] = true;
//                                }
//                            }
//                            else
//                            {
//                                if (nivel_objetivo == 1)
//                                {
//                                    num_ataques[i]++;
//                                    miembros[i][0] = true;
//                                }
//                            }
//                        }
//
//                        if (!datos.disp_brazo_der)
//                        {
//                            if (!datos.robots[objetivo].tumbado)
//                            {
//                                // Si el objetivo esta a nuestra altura o mas alto
//                                if (nivel_objetivo == 0 || nivel_objetivo == 1)
//                                {
//                                    num_ataques[i]++;
//                                    miembros[i][1] = true;
//                                }
//                            }
//                            else
//                            {
//                                if (nivel_objetivo == 1)
//                                {
//                                    num_ataques[i]++;
//                                    miembros[i][1] = true;
//                                }
//                            }
//                        }
//
//                    }
//
//                    if (nivel_objetivo == 0 || nivel_objetivo == -1)
//                        if (!datos.disp_pierna_izq || !datos.disp_pierna_der)
//                        {
//                            num_ataques[i]++;
//                            miembros[i][2] = true;
//                            miembros[i][3] = true;
//                        }
//
//                }
//
//            }
//
//        }
//
//        else
//        {
//            hexagonos.Add(null);
//        }
//
//    }
//
//
//    int objetivo_fijado=0, aux=0;
//    // Averiguamos cual es el mejor Mech a atacar
//    for(int i=0; i<num_ataques.Length; i++){
//
//        if(num_ataques[i] > aux){
//            objetivo_fijado = i;
//            aux = num_ataques[i];
//        }
//    }
//
//    // Si no tuvieramos ningun ataque que hacer a nadie, finalizamos
//    if (num_ataques[objetivo_fijado] == 0)
//    {
//        finAtaqueFisico();
//        return;
//    }
//
//
//    // --- Escribimos en el Fichero --- //
//    bool atacado_PI = false;
//
//    writer_log.WriteLine("FASE DE ATAQUES FISICOS\n\n");
//
//    // Escribimos el numero de armas fisicas
//    writer.WriteLine(num_ataques[objetivo_fijado]);
//    writer_log.WriteLine("Vamos a atacar con " + num_ataques[objetivo_fijado] + " armas.\n\n");
//
//    // Por cada arma
//    for(int i=0; i<4; i++){
//
//        // Si podemos atacar con ese miembro
//        if(miembros[objetivo_fijado][i] == true){
//
//            if(i == 0){
//                writer_log.WriteLine("Damos un punetazo con el Brazo Izquierdo al Mech objetivo en la posicion: "+hexagonos[objetivo_fijado]+".\n");
//                writer.WriteLine("BI");
//                writer.WriteLine("1000");
//                writer.WriteLine(hexagonos[objetivo_fijado]);
//                writer.WriteLine("Mech");
//            }
//            if(i == 1){
//                writer_log.WriteLine("Damos un punetazo con el Brazo Derecho al Mech objetivo en la posicion: " + hexagonos[objetivo_fijado] + ".\n");
//                writer.WriteLine("BD");
//                writer.WriteLine("1000");
//                writer.WriteLine(hexagonos[objetivo_fijado]);
//                writer.WriteLine("Mech");
//            }
//            if(i == 2){
//                writer_log.WriteLine("Damos una patada con la Pierna Izquierda al Mech objetivo en la posicion: " + hexagonos[objetivo_fijado] + ".\n");
//                writer.WriteLine("PI");
//                writer.WriteLine("2000");
//                writer.WriteLine(hexagonos[objetivo_fijado]);
//                writer.WriteLine("Mech");
//                atacado_PI = true;
//            }
//            if(i == 3 && !atacado_PI){
//                writer_log.WriteLine("Damos una patada con la Pierna Derecha al Mech objetivo en la posicion: " + hexagonos[objetivo_fijado] + ".\n");
//                writer.WriteLine("PD");
//                writer.WriteLine("2000");
//                writer.WriteLine(hexagonos[objetivo_fijado]);
//                writer.WriteLine("Mech");
//            }
//
//        }
//
//    }
//
//    // Cerramos el fichero de acciones
//    writer.Close();
    
}