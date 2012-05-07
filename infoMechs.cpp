/* 
 * File:   infoMechs.cpp
 * Author: asce
 * 
 * Created on 25 de mayo de 2010, 17:35
 */

#include "infoMechs.h"
#include "acciones.h"

using namespace std;
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
        getline (in,cad,'\n');
        mech->narc[i] = s2bool(cad);
    }

    if (mech->inarc)
        delete mech->inarc;
    mech->inarc = new bool[nMechs];

    for (int i = 0; i < nMechs; i++) {
        getline (in,cad,'\n');
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
    
    getline(in,auxiliar,'\n');
    /* El nombre y el modelo del mech no los necesitamos*/
   getline(in,auxiliar,'\n');
   getline(in,auxiliar,'\n');
    
    // Leemos las toneladas del mech
    getline(in,auxiliar,'\n');
    mech->defMechInfo->toneladas = atoi(auxiliar.c_str());

    // Leemos la potencia del mech
    getline(in,auxiliar,'\n');
    mech->defMechInfo->potencia = atoi(auxiliar.c_str());
    // Leemos el numero de radiadores internos
    getline(in,auxiliar,'\n');
    mech->defMechInfo->radiadoresInternos =  atoi(auxiliar.c_str());
    // Leemos el numero de radiadores
    getline(in,auxiliar,'\n');
    mech->defMechInfo->radiadores =  atoi(auxiliar.c_str());     
    // Leemos si tiene MASC
    getline(in,auxiliar,'\n');  
    mech->defMechInfo->MASC = s2bool(auxiliar);//STRING TO BOOL
    // Las siguientes 3 lÃ­neas no nos hacen falta

    getline(in,auxiliar,'\n');  
    getline(in,auxiliar,'\n');  
    getline(in,auxiliar,'\n');  

    // Leemos el calor maximo del mech
    getline(in,auxiliar,'\n');  
    mech->defMechInfo->max_calor = atoi(auxiliar.c_str());

    // Leemos el estado de los brazos
    mech->defMechInfo->brazos = new bool[9];
    for (int i = 0; i < 9; i++){
        getline(in,auxiliar,'\n');  
        mech->defMechInfo->brazos[i] = s2bool(auxiliar); //STRING TO BOOL
    }
       
    // Ignoramos los puntos de blindaje y de estructura interna
    for (int j = 0; j < 19; j++)
        getline(in,auxiliar,'\n');
    // Leemos el numero de componentes equipados
   getline(in,auxiliar,'\n');
   mech->defMechInfo->num_componentes=atoi(auxiliar.c_str());
    
    /* Leemos los componentes */
    mech->defMechInfo->componentes = new Componente_Mech[mech->defMechInfo->num_componentes];
    // Bucle para rellenar cada componente
    //string cadenaAuxiliar;
    char nombre[20];
    for (int i = 0; i < mech->defMechInfo->num_componentes; i++){           
        //Leemos el codigo
        getline(in,auxiliar,'\n');
        mech->defMechInfo->componentes[i].codigo = atoi(auxiliar.c_str());
        //Leemos el nombre
        getline(in,auxiliar,'\n');
        mech->defMechInfo->componentes[i].nombre = auxiliar;
        /* Leemos la clase, almacenÃ¡ndola de la siguiente forma
         * VACIO = 0
         * ARMA = 1
         * MUNICION = 2
         * EQUIPO = 3
         * ACTUADOR = 4
         * ARMADURA = 5
         * ARMAFISICA = 6
         */
        getline(in,auxiliar,'\n');
        if (auxiliar.compare("NADA")==0)
            mech->defMechInfo->componentes[i].clase=VACIO;
        else if (auxiliar.compare("ARMA")==0)
            mech->defMechInfo->componentes[i].clase=ARMA;
        else if (auxiliar.compare("MUNICION")==0)
            mech->defMechInfo->componentes[i].clase=MUNICION;
        else if (auxiliar.compare("EQUIPO")==0)
            mech->defMechInfo->componentes[i].clase=EQUIPO;
        else if (auxiliar.compare("ACTUADOR")==0)
            mech->defMechInfo->componentes[i].clase=ACTUADOR;
        else if (auxiliar.compare("ARMADURA")==0)
            mech->defMechInfo->componentes[i].clase=ARMADURA;
        else if (auxiliar.compare("ARMAFISICA")==0)
            mech->defMechInfo->componentes[i].clase=ARMAFISICA;
        
        // Leemos si el arma esta montada en la parte trasera
        getline(in,auxiliar,'\n');
        mech->defMechInfo->componentes[i].trasera = s2bool(auxiliar);

        /* Leemos la localizaciÃ³n del componente, codificada de la siguiente forma
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
        getline(in,auxiliar,'\n');
        mech->defMechInfo->componentes[i].localizacion=atoi(auxiliar.c_str());
        // Leemos la localiaciÃ³n secundaria codificada igual que la anterior
        getline(in,auxiliar,'\n');
        mech->defMechInfo->componentes[i].localizacion2=atoi(auxiliar.c_str());
       
        /* Leemos el tipo de arma, codificada de la siguiente forma
         * Nada = 0
         * EnergÃ­a = 1
         * BalÃ­stica = 2
         * Misiles = 3
        */
        getline(in,auxiliar,'\n');
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
        getline(in,auxiliar,'\n');
        mech->defMechInfo->componentes[i].calor = atoi(auxiliar.c_str());
        // Leemos el daÃ±o que produce el arma
        getline(in,auxiliar,'\n');
        mech->defMechInfo->componentes[i].danio = atoi(auxiliar.c_str());
        // Leemos los disparos por turno del arma
        getline(in,auxiliar,'\n');
        mech->defMechInfo->componentes[i].disparos_por_turno = atoi(auxiliar.c_str());
        // Leemos la distancia minima del arma
        getline(in,auxiliar,'\n');
        mech->defMechInfo->componentes[i].distanciaMinima = atoi(auxiliar.c_str());
        // Leemos la distancia corta del arma
        getline(in,auxiliar,'\n');
        mech->defMechInfo->componentes[i].distanciaCorta = atoi(auxiliar.c_str());
        // Leemos la distancia media
        getline(in,auxiliar,'\n');
        mech->defMechInfo->componentes[i].distanciaMedia = atoi(auxiliar.c_str());
        // Leemos la distancia larga
        getline(in,auxiliar,'\n');
        mech->defMechInfo->componentes[i].distanciaLarga = atoi(auxiliar.c_str());
        // Leemos si el componente esta operativo
        getline(in,auxiliar,'\n');
        mech->defMechInfo->componentes[i].operativo = s2bool(auxiliar); //STRING TO BOOL
        // Leemos el codigo del arma para el que se utiliza la municion
        getline(in,auxiliar,'\n');
        mech->defMechInfo->componentes[i].codigoArma = atoi(auxiliar.c_str());
        // Leemos la cantidad de municiÃ³n
        getline(in,auxiliar,'\n');
        mech->defMechInfo->componentes[i].cantidad = atoi(auxiliar.c_str());
        // Leemos si es municiÃ³n especial
        getline(in,auxiliar,'\n');
        if (auxiliar.compare("No")==0){
            mech->defMechInfo->componentes[i].especial = false;
        }else{
            mech->defMechInfo->componentes[i].especial = true;
        }
        // Leemos el modificador de disparo
        getline(in,auxiliar,'\n');
        mech->defMechInfo->componentes[i].modificador = atoi(auxiliar.c_str());
    }

    // Leemos el numero de armas del mech 
    getline(in,auxiliar,'\n');
    mech->defMechInfo->num_armas = atoi(auxiliar.c_str());
    // Leemos el numero de actuadores del mech
    getline(in,auxiliar,'\n');
    mech->defMechInfo->num_actuadores = atoi(auxiliar.c_str());
    
    /* Procedemos a introducir los actuadores */
    mech->defMechInfo->actuadores = new Actuador_Mech[mech->defMechInfo->num_actuadores];
    
    for (int i = 0; i < mech->defMechInfo->num_actuadores; i++){    
        // Leemos el codigo
        getline(in,auxiliar,'\n');
        mech->defMechInfo->actuadores[i].codigo = atoi(auxiliar.c_str());
        // Leemos el nombre
        getline(in,auxiliar,'\n');
        mech->defMechInfo->actuadores[i].nombre = auxiliar;
        //getline(in,mech->defMechInfo->actuadores[i].nombre);
       /* Leemos la localizaciÃ³n del actuador, codificada de la siguiente forma
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
        getline(in,auxiliar,'\n');
        mech->defMechInfo->actuadores[i].localizacion = atoi(auxiliar.c_str());
        // Leemos si esta operativo
        getline(in,auxiliar,'\n');
        mech->defMechInfo->actuadores[i].operativo = s2bool(auxiliar);
       // Leemos el nÃºmero de impactos
        getline(in,auxiliar,'\n');
        mech->defMechInfo->actuadores[i].num_impactos = atoi(auxiliar.c_str());
    }  // Fin de lectura de los activadores
    
    /* Procedemos a leer las localizaciones */
    mech->defMechInfo->localizaciones = new Localizacion_Mech[8];
    for (int i = 0; i < 8; i++){
        // Leemos el numero de slots ocupados
        getline(in,auxiliar,'\n');
        mech->defMechInfo->localizaciones[i].slots_ocupados = atoi(auxiliar.c_str());;
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
            getline(in, auxiliar,'\n');
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
            getline(in,auxiliar,'\n');
            mech->defMechInfo->localizaciones[i].slots[j].cantidad = atoi(auxiliar.c_str());
            // Leemos el codigo
            getline(in,auxiliar,'\n');
            mech->defMechInfo->localizaciones[i].slots[j].codigo = atoi(auxiliar.c_str());
            // Leemos el nombre
            getline(in,auxiliar,'\n');
            mech->defMechInfo->localizaciones->slots[i].nombre = auxiliar;
            // Leemos el indice del componente
            getline(in,auxiliar,'\n');
            mech->defMechInfo->localizaciones[i].slots[j].indice_componente = atoi(auxiliar.c_str());
            // Leemos el indice del actuador
            getline(in,auxiliar,'\n');
            mech->defMechInfo->localizaciones[i].slots[j].indice_actuador = atoi(auxiliar.c_str());
            // Leemos el daÃ±o de la municion
            getline(in,auxiliar,'\n');
            mech->defMechInfo->localizaciones[i].slots[j].danio_municion = atoi(auxiliar.c_str());
        }
    } // Final de la lectura de las localizaciones
    //TERMINA DE LEER DEFMECH
}

void infoMechs::leeDatosPPal(ifstream & in) {
    string cad;
    leeDatosMech(in, mechJugador);

    getline (in,cad,'\n');
    mechJugador->dmj->PM_andar = atoi(cad.c_str());
    getline (in,cad,'\n');
    mechJugador->dmj->PM_correr = atoi(cad.c_str());
    getline (in,cad,'\n');
    mechJugador->dmj->PM_saltar = atoi(cad.c_str());
    getline (in,cad,'\n');
    mechJugador->dmj->Radiadores_operativos_encendidos = atoi(cad.c_str());
    getline (in,cad,'\n');
    mechJugador->dmj->Radiadores_operativos_apagados = atoi(cad.c_str());
    getline (in,cad,'\n');
    mechJugador->dmj->Heridas_MW = atoi(cad.c_str());
    getline (in,cad,'\n');
    mechJugador->dmj->MW_consciente = s2bool(cad);
    
    for (int i = 0; i < 78; i++) {
        getline (in,cad,'\n');
        mechJugador->dmj->slots_impactados[i] = s2bool(cad);
    }
    for (int i = 0; i < 8; i++) {
        getline (in,cad,'\n');
        mechJugador->dmj->local_disparo_arma[i] = s2bool(cad);
    }
    getline (in,cad,'\n');
    mechJugador->dmj->municiones_expulsar = atoi(cad.c_str());
    if (mechJugador->dmj->expulsada)
        delete mechJugador->dmj->expulsada;
    mechJugador->dmj->expulsada = new municion[mechJugador->dmj->municiones_expulsar];
    int tmp;
    for (int i = 0; i < mechJugador->dmj->municiones_expulsar; i++) {
        getline (in,cad,'\n');
        tmp = atoi(cad.c_str());
        mechJugador->dmj->expulsada[i].localizacion = (localizacion_t) tmp;
        getline(in,cad,'\n');
        mechJugador->dmj->expulsada[i].slot = atoi(cad.c_str());
    }

    leeDatosNarc(in, mechJugador);
    leeDatosDefMech(mechJugador->numJ,mechJugador->numJ,mechJugador);


}

void infoMechs::leeDatosMech(ifstream & in, iMech* mech) {
    string cad;    
    getline (in,cad,'\n');
    mech->operativo = s2bool(cad);

    getline (in,cad,'\n');
    mech->desconectado = s2bool(cad);

    getline (in,cad,'\n');
    mech->atascadoEnPantano = s2bool(cad);

    getline (in,cad,'\n');
    if(strcmp(cad.c_str(),"True")==0)
        mech->enElSuelo = true;
    else
        mech->enElSuelo = false;

    getline (in,cad,'\n');
    mech->pos_Hexagono.ini(cad);

    getline (in,cad,'\n');
    mech->encaramiento_mech = atoi(cad.c_str());

    getline(in,cad,'\n');
    mech->encaramiento_torso = atoi(cad.c_str());
    
    getline (in,cad,'\n');
    mech->temp_actual = atoi(cad.c_str());

    getline (in,cad,'\n');
    mech->ardiendo = s2bool(cad);

    getline (in,cad,'\n');
    mech->con_garrote = s2bool(cad);

    getline (in,cad,'\n');
    mech->tipo_garrote = atoi(cad.c_str());

    getline (in,cad,'\n');
    mech->blindaje.BI = atoi(cad.c_str());
    getline (in,cad,'\n');
    mech->blindaje.TI = atoi(cad.c_str());
    getline (in,cad,'\n');
    mech->blindaje.PI = atoi(cad.c_str());
    getline (in,cad,'\n');
    mech->blindaje.PD = atoi(cad.c_str());
    getline (in,cad,'\n');
    mech->blindaje.TD = atoi(cad.c_str());
    getline (in,cad,'\n');
    mech->blindaje.BD = atoi(cad.c_str());
    getline (in,cad,'\n');
    mech->blindaje.TC = atoi(cad.c_str());
    getline (in,cad,'\n');
    mech->blindaje.CAB = atoi(cad.c_str());
    getline (in,cad,'\n');
    mech->blindaje.PATI = atoi(cad.c_str());
    getline (in,cad,'\n');
    mech->blindaje.PATD = atoi(cad.c_str());
    getline (in,cad,'\n');
    mech->blindaje.PATC = atoi(cad.c_str());
    
    getline (in,cad,'\n');
    mech->puntosEstructuraInterna.BI = atoi(cad.c_str());
    getline (in,cad,'\n');
    mech->puntosEstructuraInterna.TI = atoi(cad.c_str());
    getline (in,cad,'\n');
    mech->puntosEstructuraInterna.PI = atoi(cad.c_str());
    getline (in,cad,'\n');
    mech->puntosEstructuraInterna.PD = atoi(cad.c_str());
    getline (in,cad,'\n');
    mech->puntosEstructuraInterna.TD = atoi(cad.c_str());
    getline (in,cad,'\n');
    mech->puntosEstructuraInterna.BD = atoi(cad.c_str());
    getline (in,cad,'\n');
    mech->puntosEstructuraInterna.TC = atoi(cad.c_str());
    getline (in,cad,'\n');
    mech->puntosEstructuraInterna.CAB = atoi(cad.c_str());
}

void infoMechs::leeDatosMechVector(ifstream & in, int indice, int numJMech) {
    iMechVector[indice]->numJ = numJMech;
    leeDatosMech(in, iMechVector[indice]);
    leeDatosNarc(in, iMechVector[indice]);
    leeDatosDefMech(mechJugador->numJ,numJMech,iMechVector[indice]);
}

void infoMechs::leeFich(string fichero) {
    int numJ_leido;
    string cad;
    ifstream fich(fichero.c_str()); //Creacion y apertura
    if (!fich) {
        cerr << "\nNo es posible abrir " << fichero << "\n";
        exit(1);
    }

    getline(fich,cad,'\n');
    //fich.ignore(1000, '\n'); //Ignoramos nÃºmero mÃ¡gico
    getline(fich, cad, '\n');
    nMechs = atoi(cad.c_str());
   // fich >> nMechs;
    if (iMechVector == 0)
        iMechVector = new iMech*[nMechs - 1];
    for (int i = 0; i < nMechs - 1; i++)//Inicializamos el vector de iMechs
        iMechVector[i] = new iMech;

    getline(fich,cad,'\n');
    numJ_leido = atoi(cad.c_str());

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
        else{
            getline(fich,cad,'\n');
            numJ_leido = atoi(cad.c_str());
        }

    }
}


