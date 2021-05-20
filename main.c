/*
Programa nagusia

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "definiciones.h"
#include "funciones.h"
#include "interacciones.h"
#include "probabilidad.h"

int main(int argc, char *argv[]){
	//srand(7);
	int i, alfa, beta, s;

    // irakurri sarrera-datuak
    if (argc != 5) {
        printf ("\n\nERROR: ./ fichero alfa beta semilla. \n\n");
        exit (-1);
    }

    alfa = atoi(argv[2]);
    beta = atoi(argv[3]);
    s = atoi(argv[4]);
    
    srand(s);
    
    struct poblaciones poblacion;
    struct persona_virus *personas;
    
    //poblacioneko parametroak eta aldagai globalak jaso fitxategi batetik.
    leer_parametros(&poblacion, argv[1]);

	personas = malloc(poblacion.tam*sizeof(struct persona_virus));
    //ZALANTZA parametrotan * edo & zalantza hau argitu Josekin.               personas ya helbidea da ordun hola jartzeakin listo
    inicializar(poblacion.tam, personas, poblacion.tam_escenario, alfa, beta, s);
    

    
    //Escoger el primer infectado de manera aleatoria.
    paciente0(poblacion.tam, personas);

    /*for(i=0; i<poblacion.tam; i++){
    	printf("Estado: %d   Pos_x: %d   Pos_y: %d   Morir: %f\n",personas[i].estado,personas[i].pos[0], personas[i].pos[1], personas[i].prob_morir );
    }*/
    //erakutsi(personas, &poblacion);

    //Simulazioarekin hasi
    for(i=0; i<poblacion.tiempo_simulacion; i++){

    	//Mover cada persona y determinar la nueva velocidad (para la proxima iteracion)
    	movimiento(personas, poblacion.tam, poblacion.tam_escenario);
    	//Calcular los estados y los contagios
    	propagacion(personas, &poblacion);

		if(i%5==0){
			escribir(&poblacion, personas);
		}
    }

}
