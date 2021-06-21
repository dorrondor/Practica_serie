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

    //Denbora neurketak egiteko aldagaiak hasieratu
    struct timeval begin, end;
	remove("Resultato.metricas");
	remove("Resultato.por");    
    gettimeofday(&begin, 0);


	int i, alfa, beta, s;

    // irakurri sarrera-datuak
    if (argc != 5) {
        printf ("\n\nERROR: ./ fichero alfa beta semilla. \n\n");
        exit (-1);
    }

    //sarrera-datuak char->int
    alfa = atoi(argv[2]);
    beta = atoi(argv[3]);
    s = atoi(argv[4]);
    
    //Hausazko aldagaietarako
    srand(s);
    
    //poblacion -> datu orokorrak
    //*personas -> esperimetuko pertsona guztiez osatutako array bat. (punteroa)
    struct poblaciones poblacion;
    struct persona_virus *personas;
    struct metricas metrica;
    metrica.anterior=1;
    
    //poblacioneko parametroak jaso fitxategi batetik.
    leer_parametros(&poblacion, argv[1]);

    //personas array-arentzat espazioa reserbatu
	personas = malloc(poblacion.tam*sizeof(struct persona_virus));

    //personas arrayeko pertsona bakoitzari baloreak eman (adina, posizioa... )
    inicializar(poblacion.tam, personas, poblacion.tam_escenario, alfa, beta, s);
        
    //Escoger el primer infectado de manera aleatoria.
    paciente0(poblacion.tam, personas);

    
    

    //Simulazioarekin hasi
    for(i=0; i<poblacion.tiempo_simulacion; i++){

    	//Mover cada persona y determinar la nueva velocidad (para la proxima iteracion)
    	movimiento(personas, poblacion.tam, poblacion.tam_escenario);

    	//Calcular los estados y los contagios
    	propagacion(personas, &poblacion);

        coger_metricas(&poblacion, personas, &metrica);

		if(i%5==0){
            //escribir los datos y las metricas cada 5 iteraciones en resultado.pos y resultado.metricas
			if(poblacion.metrica == 1)
                escribir_metrica(&poblacion, personas, &metrica);
            if(poblacion.posicion == 1)
                escribir_posicion(&poblacion, personas);
		}

        //erakutsi(personas, poblacion);

    }

    gettimeofday(&end, 0);

    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;

    printf("Time measured: %.3f seconds.\n", elapsed);
        
}
