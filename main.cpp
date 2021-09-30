/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Jhenny Cervera Vargas
 * Codigo: 20182841
 * Created on 30 de septiembre de 2021, 11:54 AM
 */

#include "BibliotecaMemoriaDinamica.h"

int main(int argc, char** argv) {
    char **conductor, *gravedad;
    int *licencia, *infraccion;
    double *multa;
    
    cargarConductores(licencia, conductor);
    reporteConductores(licencia, conductor);
    cargarInfracciones(infraccion, gravedad, multa);
    reporteInfracciones(infraccion, gravedad, multa);
    reporteDeFaltas(licencia, conductor, infraccion, gravedad, multa);
    
    return 0;
}

