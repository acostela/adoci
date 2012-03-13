/* 
 * File:   infoMechs.cpp
 * Author: asce
 * 
 * Created on 25 de mayo de 2010, 17:35
 */

#include "infoMechs.h"
#include "acciones.h"

infoMechs::infoMechs(int numJugadorActual) {//Nuestro numero de jugador
    mechJugador = new iMech;
    mechJugador->numJ = numJugadorActual;
    iMechVector = 0;
    mechJugador->dmj=new datosMechJugador;
    mechJugador->dmj->expulsada = 0;

}

infoMechs::infoMechs(const infoMechs& orig) {
}

infoMechs::~infoMechs() {
}

void infoMechs::leeDatosNarc(ifstream & in, iMech* mech) {
    string cad;
    if (mech->narc)
        delete mech->narc;
    mech->narc = new bool[nMechs];

    for (int i = 0; i < nMechs; i++) {
        in >> cad;
        mech->narc[i] = s2bool(cad);
    }

    if (mech->inarc)
        delete mech->inarc;
    mech->inarc = new bool[nMechs];

    for (int i = 0; i < nMechs; i++) {
        in >> cad;
        mech->inarc[i] = s2bool(cad);
    }
}

void infoMechs::leeDatosDefMech(int numJ,int numM,iMech* mech){
        
        ifstream defmech;
        string nombre_defmech="defmechJ"; 
        nombre_defmech+=itoStr(numJ)+"-";
        nombre_defmech+=itoStr(numM)+".sbt";

        defmech.open(nombre_defmech.c_str());
        if(!defmech){
                cerr << "\nNo es posible abrir " << nombre_defmech << "\n";
                exit(1);
        }
        leeDatosComponentes(defmech,mech);
        defmech.close();
}
void infoMechs::leeDatosComponentes(ifstream &in, iMech *mech){ //Lee los componentes de cada Mech
    string auxiliar;
    in >> auxiliar;

    /* El nombre y el modelo del mech no los necesitamos*/
    in >> auxiliar;
    in >> auxiliar;
    

    //in.ignore(1000, '\n');
    //in.ignore(1000, '\n');
    // Leemos las toneladas del mech
    in >> mech->defMechInfo->toneladas;

    // Leemos la potencia del mech
    in >> mech->defMechInfo->potencia;
    // Leemos el numero de radiadores internos
    in >> mech->defMechInfo->radiadoresInternos;
    // Leemos el numero de radiadores
    in >> mech->defMechInfo->radiadores;     
    // Leemos si tiene MASC
    in >> auxiliar;
    mech->defMechInfo->MASC = s2bool(auxiliar);//STRING TO BOOL
    // Las siguientes 3 líneas no nos hacen falta

    in >> auxiliar;
    in >> auxiliar;
    in >> auxiliar;

    // Leemos el calor maximo del mech
    in >> mech->defMechInfo->max_calor;

                // Leemos el estado de los brazos
    mech->defMechInfo->brazos = new bool[9];
    for (int i = 0; i < 9; i++){
        in >> auxiliar;
        mech->defMechInfo->brazos[i] = s2bool(auxiliar); //STRING TO BOOL
    }
       
    // Ignoramos los puntos de blindaje y de estructura interna
    for (int j = 0; j < 19; j++)
        in >> auxiliar;
    // Leemos el numero de componentes equipados
    in >> mech->defMechInfo->num_componentes;
    
    /* Leemos los componentes */
    mech->defMechInfo->componentes = new Componente_Mech[mech->defMechInfo->num_componentes];
    // Bucle para rellenar cada componente
    //string cadenaAuxiliar;
    char nombre[20];
    for (int i = 0; i < mech->defMechInfo->num_componentes; i++){           
        //Leemos el codigo
        in >> mech->defMechInfo->componentes[i].codigo;
        //Leemos el nombre
        getline(in,auxiliar);//Salto el retorno de carro del anterior
        getline(in,mech->defMechInfo->componentes[i].nombre);
        /* Leemos la clase, almacenándola de la siguiente forma
         * VACIO = 0
         * ARMA = 1
         * MUNICION = 2
         * EQUIPO = 3
         * ACTUADOR = 4
         * ARMADURA = 5
         * ARMAFISICA = 6
         */
        in >> auxiliar;
        if (auxiliar=="NADA")
            mech->defMechInfo->componentes[i].clase=VACIO;
        else if (auxiliar=="ARMA")
            mech->defMechInfo->componentes[i].clase=ARMA;
        else if (auxiliar == "MUNICION")
            mech->defMechInfo->componentes[i].clase=MUNICION;
        else if (auxiliar == "EQUIPO")
            mech->defMechInfo->componentes[i].clase=EQUIPO;
        else if (auxiliar == "ACTUADOR")
            mech->defMechInfo->componentes[i].clase=ACTUADOR;
        else if (auxiliar == "ARMADURA")
            mech->defMechInfo->componentes[i].clase=ARMADURA;
        else if (auxiliar == "ARMAFISICA")
            mech->defMechInfo->componentes[i].clase=ARMAFISICA;
        
        // Leemos si el arma esta montada en la parte trasera
        in >> auxiliar;
        mech->defMechInfo->componentes[i].trasera = s2bool(auxiliar);

        /* Leemos la localización del componente, codificada de la siguiente forma
         * BRAZO IZQ = 0
         * TORSO IZQ = 1
         * PIERNA IZQ = 2
         * PIERNA DCHA = 3
         * TORSO DCHA = 4
         * BRAZO DCHA = 5
         * TORSO CNT = 6
         * CABEZA = 7
         * ATRAS TORSO IZQ = 8
         * ATRAS TORSO DCHA = 9
         * ATRAS TORSO CNT= 10
        */
        in >> mech->defMechInfo->componentes[i].localizacion;
        // Leemos la localiación secundaria codificada igual que la anterior
        in >> mech->defMechInfo->componentes[i].localizacion2;
       
        /* Leemos el tipo de arma, codificada de la siguiente forma
         * Nada = 0
         * Energía = 1
         * Balística = 2
         * Misiles = 3
        */
        in >> auxiliar;
        if (auxiliar.compare("Nada")==0)
            mech->defMechInfo->componentes[i].tipo = 0;
        else if(auxiliar.compare(0,3,"Ene")==0)
            mech->defMechInfo->componentes[i].tipo = 1;
        else if(auxiliar.compare(0,3,"Bal")==0)
            mech->defMechInfo->componentes[i].tipo = 2;
        else if(auxiliar.compare("Misiles")==0){
            mech->defMechInfo->componentes[i].tipo = 3;
        }
        // Leemos el calor que genera el arma
        in >> mech->defMechInfo->componentes[i].calor;
        // Leemos el daño que produce el arma
        in >> mech->defMechInfo->componentes[i].danio;
        // Leemos los disparos por turno del arma
        in >> mech->defMechInfo->componentes[i].disparos_por_turno;
        // Leemos la distancia minima del arma
        in >> mech->defMechInfo->componentes[i].distanciaMinima;
        // Leemos la distancia corta del arma
        in >> mech->defMechInfo->componentes[i].distanciaCorta;
        // Leemos la distancia media
        in >> mech->defMechInfo->componentes[i].distanciaMedia;
        // Leemos la distancia larga
        in >> mech->defMechInfo->componentes[i].distanciaLarga;
        // Leemos si el componente esta operativo
        in >> auxiliar;
        mech->defMechInfo->componentes[i].operativo = s2bool(auxiliar); //STRING TO BOOL
        // Leemos el codigo del arma para el que se utiliza la municion
        in >> mech->defMechInfo->componentes[i].codigoArma;
        // Leemos la cantidad de munición
        in >> mech->defMechInfo->componentes[i].cantidad;
        // Leemos si es munición especial
        in >> auxiliar;
        if (auxiliar.compare("No")==0){
            mech->defMechInfo->componentes[i].especial = false;
        }else{
            mech->defMechInfo->componentes[i].especial = true;
        }
        // Leemos el modificador de disparo
        in >> mech->defMechInfo->componentes[i].modificador;
    }

    // Leemos el numero de armas del mech 
    in >> mech->defMechInfo->num_armas;
    // Leemos el numero de actuadores del mech
    in >> mech->defMechInfo->num_actuadores;
    
    /* Procedemos a introducir los actuadores */
    mech->defMechInfo->actuadores = new Actuador_Mech[mech->defMechInfo->num_actuadores];
    
    for (int i = 0; i < mech->defMechInfo->num_actuadores; i++){    
        // Leemos el codigo
        in >> mech->defMechInfo->actuadores[i].codigo;
        // Leemos el nombre
        
        getline(in,auxiliar);//Salto el retorno de carro del anterior
        getline(in,mech->defMechInfo->actuadores[i].nombre);
       /* Leemos la localización del actuador, codificada de la siguiente forma
        * BRAZO IZQ = 0
        * TORSO IZQ = 1
        * PIERNA IZQ = 2
        * PIERNA DCHA = 3
        * TORSO DCHA = 4
        * BRAZO DCHA = 5
        * TORSO CNT = 6
        * CABEZA = 7
        * ATRAS TORSO IZQ = 8
        * ATRAS TORSO DCHA = 9
        * ATRAS TORSO CNT= 10
       */
        in >> mech->defMechInfo->actuadores[i].localizacion;
            // Leemos si esta operativo
        in >> auxiliar;
        mech->defMechInfo->actuadores[i].operativo = s2bool(auxiliar);
       // Leemos el número de impactos
        in >> mech->defMechInfo->actuadores[i].num_impactos;
    }  // Fin de lectura de los activadores
    
    /* Procedemos a leer las localizaciones */
    mech->defMechInfo->localizaciones = new Localizacion_Mech[8];
    for (int i = 0; i < 8; i++){
        // Leemos el numero de slots ocupados
        in >> mech->defMechInfo->localizaciones[i].slots_ocupados;
        mech->defMechInfo->localizaciones[i].slots = new Slot_Mech[mech->defMechInfo->localizaciones[i].slots_ocupados];

        // Para cada slot ocupado
        for (int j = 0; j < mech->defMechInfo->localizaciones[i].slots_ocupados; j++){
            /* Leemos la clase, codificada como 
             * VACIO = 0
             * ARMA = 1
             * MUNICION = 2
             * EQUIPO = 3
             * ACTUADOR = 4
             * ARMADURA = 5
             * ARMAFISICA = 6
            */
            in >> auxiliar;
            if(auxiliar.compare("NADA")==0)
                mech->defMechInfo->localizaciones[i].slots[j].clase = 0;
            else if (auxiliar.compare("ARMA")==0)
                mech->defMechInfo->localizaciones[i].slots[j].clase = 1;
            else if (auxiliar.compare("MUNICION")==0)
                mech->defMechInfo->localizaciones[i].slots[j].clase = 2;
            else if (auxiliar.compare("EQUIPO")==0)
                mech->defMechInfo->localizaciones[i].slots[j].clase = 3;
            else if (auxiliar.compare("ACTUADOR")==0)
                mech->defMechInfo->localizaciones[i].slots[j].clase = 4;
            else if (auxiliar.compare("ARMADURA")==0)
                mech->defMechInfo->localizaciones[i].slots[j].clase = 5;
            else if (auxiliar.compare("ARMAFISICA")==0)
                mech->defMechInfo->localizaciones[i].slots[j].clase = 6;

            // Leemos la cantidad
            in >> mech->defMechInfo->localizaciones[i].slots[j].cantidad;
            // Leemos el codigo
            in >> mech->defMechInfo->localizaciones[i].slots[j].codigo;
            // Leemos el nombre
            getline(in,auxiliar);//Salto el retorno de carro del anterior
            getline(in,mech->defMechInfo->localizaciones[i].slots[j].nombre);
            // Leemos el indice del componente
            in >> mech->defMechInfo->localizaciones[i].slots[j].indice_componente;
            // Leemos el indice del actuador
            in >> mech->defMechInfo->localizaciones[i].slots[j].indice_actuador;
            // Leemos el daño de la municion
            in >> mech->defMechInfo->localizaciones[i].slots[j].danio_municion;
        }
    } // Final de la lectura de las localizaciones
    //TERMINA DE LEER DEFMECH
}

void infoMechs::leeDatosPPal(ifstream & in) {
    string cad;
    leeDatosMech(in, mechJugador);

    in >> mechJugador->dmj->PM_andar;
    in >> mechJugador->dmj->PM_correr;
    in >> mechJugador->dmj->PM_saltar;
    in >> mechJugador->dmj->Radiadores_operativos_encendidos;
    in >> mechJugador->dmj->Radiadores_operativos_apagados;
    in >> mechJugador->dmj->Heridas_MW;
    in >> cad;
    mechJugador->dmj->MW_consciente = s2bool(cad);
    for (int i = 0; i < 78; i++) {
        in >> cad;
        mechJugador->dmj->slots_impactados[i] = s2bool(cad);
    }
    for (int i = 0; i < 8; i++) {
        in >> cad;
        mechJugador->dmj->local_disparo_arma[i] = s2bool(cad);
    }
    in >> mechJugador->dmj->municiones_expulsar;
    if (mechJugador->dmj->expulsada)
        delete mechJugador->dmj->expulsada;
    mechJugador->dmj->expulsada = new municion[mechJugador->dmj->municiones_expulsar];
    int tmp;
    for (int i = 0; i < mechJugador->dmj->municiones_expulsar; i++) {

        in >> tmp;
        mechJugador->dmj->expulsada[i].localizacion = (localizacion_t) tmp;
        in >> mechJugador->dmj->expulsada[i].slot;
    }

    leeDatosNarc(in, mechJugador);
    leeDatosDefMech(mechJugador->numJ,mechJugador->numJ,mechJugador);


}

void infoMechs::leeDatosMech(ifstream & in, iMech* mech) {
    string cad;    
    in >> cad;
    mech->operativo = s2bool(cad);

    in >> cad;
    mech->desconectado = s2bool(cad);

    in >> cad;
    mech->atascadoEnPantano = s2bool(cad);

    in >> cad;
    if(strcmp(cad.c_str(),"True")==0)
        mech->enElSuelo = TRUE;
    else
        mech->enElSuelo = FALSE;

    in >> cad;

    mech->pos_Hexagono.ini(cad);

    in >> mech->encaramiento_mech;

    in >> mech->encaramiento_torso;

    in >> mech->temp_actual;

    in >> cad;
    mech->ardiendo = s2bool(cad);

    in >> cad;
    mech->con_garrote = s2bool(cad);

    in >> mech->tipo_garrote;

    in >> mech->blindaje.BI;
    in >> mech->blindaje.TI;
    in >> mech->blindaje.PI;
    in >> mech->blindaje.PD;
    in >> mech->blindaje.TD;
    in >> mech->blindaje.BD;
    in >> mech->blindaje.TC;
    in >> mech->blindaje.CAB;
    in >> mech->blindaje.PATI;
    in >> mech->blindaje.PATD;
    in >> mech->blindaje.PATC;

    in >> mech->puntosEstructuraInterna.BI;
    in >> mech->puntosEstructuraInterna.TI;
    in >> mech->puntosEstructuraInterna.PI;
    in >> mech->puntosEstructuraInterna.PD;
    in >> mech->puntosEstructuraInterna.TD;
    in >> mech->puntosEstructuraInterna.BD;
    in >> mech->puntosEstructuraInterna.TC;
    in >> mech->puntosEstructuraInterna.CAB;
}

void infoMechs::leeDatosMechVector(ifstream & in, int indice, int numJMech) {
    iMechVector[indice]->numJ = numJMech;
    leeDatosMech(in, iMechVector[indice]);
    leeDatosNarc(in, iMechVector[indice]);
    leeDatosDefMech(mechJugador->numJ,numJMech,iMechVector[indice]);
}

void infoMechs::leeFich(string fichero) {
    int numJ_leido;
    ifstream fich(fichero.c_str()); //Creacion y apertura
    if (!fich) {
        cerr << "\nNo es posible abrir " << fichero << "\n";
        exit(1);
    }

    fich.ignore(1000, '\n'); //Ignoramos número mágico
    fich >> nMechs;
    if (iMechVector == 0)
        iMechVector = new iMech*[nMechs - 1];
    for (int i = 0; i < nMechs - 1; i++)//Inicializamos el vector de iMechs
        iMechVector[i] = new iMech;

    fich >> numJ_leido;

    int indice = 0;
    bool leido_ppal = false; //leido mech principal
    bool fin = false;
    while (!fin) {
        if (numJ_leido == mechJugador->numJ) {
            leeDatosPPal(fich);
            leido_ppal = true;
        } else {
            leeDatosMechVector(fich, indice, numJ_leido);
            indice++;
        }
        if (indice == nMechs - 1 && leido_ppal == true)
            fin = true;
        else
            fich >> numJ_leido;

    }
}


