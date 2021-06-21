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
	fscanf(f1, "%d", &a1);
    poblacion->metrica = a1;
    fscanf(f1, "%d", &a1);
    poblacion->posicion = a1;

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
void coger_metricas(struct poblaciones *poblacion, struct persona_virus *personas, struct metricas *metrica){

	int i;

	for(i=0; i<poblacion->tam; i++){
        switch (personas[i].estado){
            case 0:
                metrica->sano++;
                break;
            case 1:
            	metrica->incubando++;
            case 2:
                metrica->contagiado++;
                break;
            case 3:
                metrica->recuperado++;
                break;
            case 5:
                metrica->muerto++;
                break;
        }
    }
    metrica->r0+=(float) metrica->contagiado/metrica->anterior;
	printf("%f %d %d\n", metrica->r0, metrica->anterior, metrica->contagiado);
	//Este if evita que cuando toda la poblacion se haya contagiado y curado se realicen divisiones 0/0 al calcular R0
    if(metrica->contagiado!=0)
	metrica->anterior=metrica->contagiado;
	else
	metrica->anterior=1;
}

//Guardar las metricas en resultados.metricas
void escribir_metrica(struct poblaciones *poblacion, struct persona_virus *personas, struct metricas *metrica){
	FILE  *f2;
    int i, ps=0, pc=0, pr=0, pf=0;
	float r0=0.0;
	f2=fopen("Resultato.metricas","a");
//	fseek(f2,0,SEEK_END);
	
	if (f2==NULL){
		printf("ERROR! No se pudo abrir el documento");
		exit(-1);
	}

        ps=(metrica->sano)/5;
        pc=(metrica->contagiado)/5;
        pr=(metrica->recuperado)/5;
        pf=(metrica->muerto)/5;
	r0=(metrica->r0)/5.0;

    fprintf(f2,"Datos de la poblacion:\n Sanos: %d Contagiosos: %d Recuperados  %d Fallecidos %d R0 %f\n", ps, pc, pr, pf,r0);
    
//printf("Datos de la poblacion:\n Sanos: %d Contagiosos: %d Recuperados  %d Fallecidos %d  R0 %f\n", ps, pc, pr, pf, r0);

    fclose(f2);
    metrica->sano=0;
    metrica->contagiado=0;
    metrica->recuperado=0;
    metrica->muerto=0;
	metrica->r0=0.0;
//	metrica->anterior=1;
}

//Guardar las posiciones en resultados.pos
void escribir_posicion(struct poblaciones *poblacion, struct persona_virus *personas){
    FILE *f1;
    int i;
    f1=fopen("Resultato.pos","a");
//    fseek(f1,0,SEEK_END);    


    if (f1==NULL){
        printf("ERROR! No se pudo abrir el documento");
        exit(-1);
    }
    
    for(i=0; i<poblacion->tam; i++){
        fprintf(f1,"Persona: %d Posicion: %d / %d Estado: %d \n", i, personas[i].pos[0], personas[i].pos[1], personas[i].estado);
    }
    
    fclose(f1);
}


void erakutsi(struct persona_virus *personas, struct poblaciones poblacion){
    int j;
	for(j=0; j<poblacion.tam; j++){
        printf("Estado: %d    Persona: %d\n",personas[j].estado, j );
        }

}
