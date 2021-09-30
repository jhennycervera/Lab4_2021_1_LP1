/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BibliotecaMemoriaDinamica.h
 * Author: jhenn
 *
 * Created on 30 de septiembre de 2021, 12:03 PM
 */

#ifndef BIBLIOTECAMEMORIADINAMICA_H
#define BIBLIOTECAMEMORIADINAMICA_H

#include <iostream>        
#include <fstream>
using namespace std;

void imprimirLinea(ofstream &Rep, char c, int cant);

void cargarConductores(int * &licencia,  char **& conductor);
char* leerCadenaCond(ifstream & archCond);
void reporteConductores(int * licencia, char ** conductor);

void cargarInfracciones(int * &infraccion, char * &gravedad, double * &multa) ;
void leerCadenasInfra(ifstream &archInfr, char &buffGrav, double &buffMult);
void reporteInfracciones(int * infraccion, char * gravedad, double * multa);

void reporteDeFaltas(int * licencia, char **conductor, int *infraccion,
        char * gravedad, double *multa) ;
void ReporteFalta(ofstream &archRep, int * licencia, char **conductor, int *infraccion,
        char * gravedad, double *multa, char letra);
char * leerPlaca(ifstream &archFalta) ;

int leerCodInfra(ifstream &archFalta);
int infraccionEsLGM(int codInfr, int * infraccion, char * gravedad, double *multa, double &auxmulta, char letra) ;
int  buscarPlacaEnBuffAux( char *placa, char *buffplaca[], int numPlaca);
void  imprimirRep(ofstream &archRep, int *licencia, int *cantidad, double *monto, char **placa);
void liberarMemoria(int * &licencia, int * &cantidad, double *monto, char **placa);

#endif /* BIBLIOTECAMEMORIADINAMICA_H */
