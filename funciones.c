/*
funciones.c

funciones auxiliares

*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "definiciones.h"
#include "interacciones.h"
#include "probabilidad.h"
#include "funciones.h"


//poblacioneko parametroak irakurri.
void leer_parametros(struct poblaciones *poblacion, char *f){
    FILE *f1;
    f1=fopen(f,"r");
    int i, a1;
    float a2;
    
    if(f1==NULL){
        printf("ERROR! No se pudo abrir el documento");
        exit(-1);
    }
    
    //Poblacionen datuak jaso
    fscanf(f1, "%d", &a1);
    poblacion->tam=a1;
    fscanf(f1, "%d", &a1);
    poblacion->radio_cont=a1;
    fscanf(f1, "%d", &a1);
    poblacion->periodo_incu=a1;
    fscanf(f1, "%d", &a1);
    poblacion->periodo_rec=a1;
    fscanf(f1, "%f", &a2);
    poblacion->prob_cont=a2;
    fscanf(f1, "%f", &a2);
    poblacion->prob_camb_vel=a2;
	fscanf(f1, "%d", &a1);
	poblacion->tam_escenario = a1;
	fscanf(f1, "%d", &a1);
	poblacion->tiempo_simulacion = a1;

	fclose(f1);

}

//Inicializar el array persona_virus
// ZALANTZA parametroetan * jarri behar ahal da?            Balorea ez da pasa behar aldagai hoi baizik, beraz bere helbidea pasa behar da
// ZALANTZA poblaciones.tamaño EDO poblaciones->tamaño      helbidea baldin bada -> erabili bestela .
void inicializar(int tam_poblacion, struct persona_virus *personas, int tam_escenario, int alfa, int beta, int s){

    int i;

    calc_edad(tam_poblacion, personas, alfa, beta, s);
    
    for(i=0; i<tam_poblacion; i++){
        personas[i].t_estado = 0; //Tiempo en el estado 0
        personas[i].estado = 0; //Todos sanos
        personas[i].pos[0] = calc_pos(tam_escenario); 		//Beti zenbaki berdina ez emateko semilla bezela i pasa
        personas[i].pos[1] = calc_pos(tam_escenario);
        personas[i].vel[0] = calc_vel();
        personas[i].vel[1] = calc_vel();
        personas[i].prob_morir = calc_morir(personas[i].edad);
        } 
}

//Elegir el primer paciente infectado
void paciente0(int tam_poblacion, struct persona_virus *personas){
    int i = rand()%tam_poblacion;
    personas[i].estado = 2;
}

int porciento(int tam, int c){
    return c/tam;
}



//Guardar los datos en los ficheros
void escribir(struct poblaciones *poblacion, struct persona_virus *personas){
	FILE *f1, *f2;
    int i, ps=0, pc=0, pr=0, pf=0, r0=0;
	f1=fopen("Resultato.pos","w+");
	f2=fopen("Resultato.metricas","w+");
	
	if (f1==NULL || f2==NULL){
		printf("ERROR! No se pudo abrir el documento");
		exit(-1);
	}
	
	for(i=0; i<poblacion->tam; i++){
        fprintf(f1,"Persona: %d Posicion: %d / %d Estado: %d \n", i, personas[i].pos[0], personas[i].pos[1], personas[i].estado);
    }
    
    for(i=0; i<poblacion->tam; i++){
        switch (personas[i].estado){
            case 0:
                ps++;
                break;
            case 1:
            case 2:
                pc++;
                break;
            case 3:
                pr++;
                break;
            case 5:
                pf++;
                break;
        }
    }
    
    fprintf(f2,"Datos de la poblacion:\n Sanos: %d Contagiosos: %d Recuperados  %d Fallecidos %d %d\n", ps, pc, pr, pf);
    
    fclose(f1);
    fclose(f2);
}

void erakutsi(struct persona_virus *personas, struct poblaciones poblacion){
    int j;
	for(j=0; j<poblacion.tam; j++){
        printf("Estado: %d    Persona: %d\n",personas[j].estado, j );
        }

}
