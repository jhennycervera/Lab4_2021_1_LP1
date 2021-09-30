/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



/* 
 * File:   BibliotecaMemoriaDinamica.cpp
 * Author: jhenn
 * Codigo: 20182841
 * Created on 30 de septiembre de 2021, 12:03 PM
 */

#include "BibliotecaMemoriaDinamica.h"
#include <iostream>        
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;
#define MAX 500
#define NOMB 200

void imprimirLinea(ofstream &Rep, char c, int cant) {
    Rep.fill(c);
    Rep << setw(cant) << c << endl;
    Rep.fill(' ');
}

void cargarConductores(int * &licencia, char **& conductor) {

    ifstream archCond("Conductores.csv", ios::in);
    if (!archCond) {
        cout << "No se pudo abrir el archivo Conductores.csv" << endl;
        exit(1);
    }
    int numCond = 0;
    int buffLic[MAX];
    char *buffCond[MAX];


    while (1) {
        archCond >> buffLic[numCond];
        if (archCond.eof()) break;
        archCond.get(); //coma
        buffCond[numCond] = leerCadenaCond(archCond);
        numCond++;
    }

    licencia = new int[numCond + 1];
    conductor = new char*[numCond];

    for (int i = 0; i < numCond; i++) {
        licencia[i] = buffLic[i];
        conductor[i] = buffCond[i];
    }
    licencia[numCond] = -1; //terminador

}

char* leerCadenaCond(ifstream & archCond) {

    char nombre[NOMB], *ptrNomb;

    archCond.getline(nombre, NOMB);
    ptrNomb = new char[strlen(nombre) + 1];
    strcpy(ptrNomb, nombre);

    return ptrNomb;

}

void reporteConductores(int * licencia, char ** conductor) {

    ofstream archRep("RepConductores.txt", ios::out);
    if (!archRep) {
        cout << "No se pudo abrir RepConductores.txt" << endl;
        exit(1);
    }

    archRep << left << setw(15) << "CODIGO" << "NOMBRE" << endl;

    for (int i = 0; licencia[i] != -1; i++) {
        archRep << left << setw(15) << licencia[i] << conductor[i] << endl;
    }

}

void cargarInfracciones(int * &infraccion, char * &gravedad, double * &multa) {

    ifstream archInfr("Infracciones.csv", ios::in);

    if (!archInfr) {
        cout << "No se puede abrir el archivo Infracciones.csv" << endl;
        exit(1);
    }
    int buffInfrac[MAX], numInfrac = 0;
    char buffGrav[MAX];
    double buffMult[MAX];

    while (1) {
        archInfr >> buffInfrac[numInfrac];
        if (archInfr.eof()) break;
        archInfr.get(); //coma
        leerCadenasInfra(archInfr, buffGrav[numInfrac], buffMult[numInfrac]);

        numInfrac++;
    }
    infraccion = new int[numInfrac + 1];
    gravedad = new char [numInfrac];
    multa = new double[ numInfrac];

    for (int i = 0; i < numInfrac; i++) {
        infraccion[i] = buffInfrac[i];
        gravedad[i] = buffGrav[i];
        multa[i] = buffMult[i];
    }

    infraccion[numInfrac] = -1;


}

void leerCadenasInfra(ifstream &archInfr, char &buffGrav, double &buffMult) { //por referencia porq es la dm no el valor

    char def[MAX], gravedad[10];

    archInfr.getline(def, MAX, ','); //se come la coma
    archInfr.getline(gravedad, 10, ','); //se come la coma
    archInfr>>buffMult;

    if (strcmp(gravedad, "Grave") == 0) {
        buffGrav = 'G';
    } else if (strcmp(gravedad, "Muy Grave") == 0) {
        buffGrav = 'M';
    } else {
        buffGrav = 'L';
    }

}

void reporteInfracciones(int * infraccion, char * gravedad, double * multa) {


    ofstream archRep("RepInfracciones.txt", ios::out);
    if (!archRep) {
        cout << "No se pudo abrir RepInfracciones.txt" << endl;
        exit(1);
    }

    archRep << left << setw(15) << "INFRACCION" << setw(15) << "GRAVEDAD" << "MULTA" << endl;
    for (int i = 0; infraccion[i] != -1; i++) {
        archRep << setw(15) << infraccion[i] << setw(15) << gravedad[i] << multa[i] << endl;
    }

}

void reporteDeFaltas(int * licencia, char **conductor, int *infraccion,
        char * gravedad, double *multa) {
    
    ofstream archRep("RepFaltas.txt", ios:: out);
    if(!archRep){
        cout<<"No se pudo abrir RepFaltas.txt"<<endl;
 	exit(1);
    }
    
    archRep<<"FALTAS LEVES"<<endl;
    ReporteFalta(archRep, licencia, conductor, infraccion, gravedad, multa, 'L');
    archRep<<"FALTAS GRAVES"<<endl;
    ReporteFalta(archRep, licencia, conductor, infraccion, gravedad, multa, 'G');
    archRep<<"FALTAS MUY GRAVES"<<endl;
    ReporteFalta(archRep,licencia, conductor, infraccion, gravedad, multa, 'M');


}

void ReporteFalta(ofstream &archRep, int * licencia, char **conductor, int *infraccion,
        char * gravedad, double *multa, char letra) {

    ifstream archFalta("RegistroDeFaltas.csv", ios::in);
    if (!archFalta) {
        cout << "No se puede abrir el archivo RegistroDeFaltas.csv" << endl;
        exit(1);
    }
    //estructuras
    int *licencia1, *cantidad;
    double *monto;
    char** placa;

    //buffers y auxiliares
    int numPlaca = 0, buffLic[MAX], buffcantidad[MAX] = {}; //inicializar con 0
    double buffmonto[MAX] = {};
    char * buffplaca[MAX];

    int codLic, codInfr;
    char *auxplaca;
    double auxmulta;

    while (1) { //solo agrego al buffer si lo que he leido es una falta leve
        archFalta>>codLic;
        if (archFalta.eof()) break;
        auxplaca = leerPlaca(archFalta);
        codInfr = leerCodInfra(archFalta);
        //otro forma era buscar la pos de la infraccion y comparar la grav[pos]=car
        if (infraccionEsLGM(codInfr, infraccion, gravedad, multa, auxmulta, letra)) { //lleno en los auxiliares
            
            int pos = buscarPlacaEnBuffAux(auxplaca, buffplaca, numPlaca);
            if (pos != numPlaca) { //la placa se repite  , no sobreescribo la licencia ni la placa
                buffcantidad[pos]++;
                buffmonto[pos] += auxmulta;
            } else { //nueva placa                 buffLic[numPlaca]=codLic;
                buffLic[numPlaca] = codLic;
                buffcantidad[numPlaca]++;
                buffmonto[numPlaca] = auxmulta;
                buffplaca[numPlaca] = auxplaca;
                numPlaca++;
            }
        }
    }
    licencia1 = new int[numPlaca];
    cantidad = new int[numPlaca];
    monto = new double[numPlaca];
    placa = new char*[numPlaca + 1];

    for (int i = 0; i < numPlaca; i++) {
        licencia1[i] = buffLic[i];
        cantidad[i] = buffcantidad[i];
        monto[i] = buffmonto[i];
        placa[i] = buffplaca[i];
    }
    placa[numPlaca] = nullptr;

    imprimirRep(archRep,licencia1, cantidad, monto, placa);
    liberarMemoria(licencia1, cantidad, monto, placa);

}

char * leerPlaca(ifstream &archFalta) {
    char placa[8], *ptrPlaca, fecha[15];

    archFalta.get(); //coma
    archFalta.getline(placa, 8, ','); //se come la coma
    archFalta.getline(fecha, 15, ','); //se come la coma

    ptrPlaca = new char[strlen(placa) + 1];
    strcpy(ptrPlaca, placa);

    return ptrPlaca;

}

int leerCodInfra(ifstream &archFalta) {
    int d;
    archFalta>>d;
    return d;
}

int infraccionEsLGM(int codInfr, int * infraccion, char * gravedad, double *multa, double &auxmulta, char letra) {

    for (int i = 0; infraccion[i] != -1; i++) {
        if (infraccion[i] == codInfr) {
            if (gravedad[i] == letra) {
                auxmulta = multa[i];
                return 1;
            }
            else return 0; //la infraccion no es Leve, grave, o muy grave
        }
    }
    return 0; //no enocntro la infraccion

}

int  buscarPlacaEnBuffAux( char *placa, char *buffplaca[], int numPlaca){
    
    for(int i=0; i<numPlaca; i++){
        if( strcmp(buffplaca[i] , placa)  == 0){
            return i;
        }
    }
    return numPlaca;
}

void  imprimirRep(ofstream &archRep, int *licencia, int *cantidad, double *monto, char **placa){
    
    imprimirLinea(archRep, '=', NOMB);
    
    for(int i=0; placa[i]!=nullptr ; i++ ){
        archRep<<left<<setw(5)<<i+1<<setw(15)<<licencia[i]<<setw(15)<<placa[i]<<setw(15)<<cantidad[i]<<monto[i]<<endl;
        
    }
    imprimirLinea(archRep, '*', NOMB);
}

void liberarMemoria(int * &licencia, int * &cantidad, double *monto, char **placa){
    
    for(int i=0; placa[i]!= nullptr ; i++){
        delete placa[i];
    }
    
    delete placa;
    delete licencia;
    delete cantidad;
    delete monto;
}