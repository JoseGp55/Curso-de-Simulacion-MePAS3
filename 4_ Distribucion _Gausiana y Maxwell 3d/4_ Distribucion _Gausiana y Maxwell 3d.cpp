//distribución gaussiana de pariculas y de velocidades de Maxwell-Boltzmann
//José Guadalupe Ibarra Armenta
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define CLASES 500
#define pi 3.14159265358979323846
#define kb 1.38062e-23

double alea(void);
void imprime_gdrx(void);
void imprime_gdv(void);

int p, pasos=10000000, actu=100000;
float temp=300;//temperatura ambiente
float m=1.67e-27;//masa de un hidrogeno

float dlx=8.0/CLASES;//flotante :P
float dlv=8000.0/CLASES;

long int gdrx[CLASES+1]={0}, gdvx[CLASES+1]={0};
FILE *dat;
//INICIO DEL PROGRAMA PRINCIPAL***************************************************************************************************************************
main(){
srand((unsigned)time(NULL));/*sembrando la semilla*/

system ("mkdir temp");

float xi, fxi, vi, fvi;

for(p=1; p<=pasos; p++){/*INICIO(Principal)*/
	do{
		xi=alea()*8-4;
		fxi=exp(-pow(xi,2)/2)/sqrt(2*pi);
	}while(alea()>fxi);
	gdrx[int((xi+4)/dlx)+1]++;
	do{
		vi=alea()*8000;
		fvi=4*pi*vi*vi*exp(-vi*vi*m/(2*kb*temp))*pow(m/(2*pi*kb*temp), 3.0/2.0);
	}while(alea()*1e-3>fvi);
		gdv[int(vi/dlv)+1]++;
	if(p%1==0)printf("\rPasos: %i", p);
	if(p%actu==0){
		imprime_gdrx();
		imprime_gdv();
	}
}/*FINAL(Principal)*/
return(0);
}
//FINAL DEL PROGRAMA PRINCIPAL*****************************************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double alea(void){//genera numeros aleatorios entre 0 y 1
return((double)rand()/RAND_MAX); //32767 dependiente de la libreria
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void imprime_gdrx(void){
	int i;
	FILE *dat;
	char nombre[50];
	sprintf(nombre,"temp/gdrx_%i.dat",p/actu);
		dat=fopen(nombre, "w");
		for(i=1; i<=CLASES; i++){
			fprintf(dat,"%f	%i	%f\n", (i-0.5)*dlx-4, gdrx[i], gdrx[i]/(1.0*p));
		}
	fclose(dat);
}///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void imprime_gdv(void){
	int i;
	FILE *dat;
	char nombre[50];
	sprintf(nombre,"temp/gdv_%i.dat",p/actu);
		dat=fopen(nombre, "w");
		for(i=1; i<=CLASES; i++){
			fprintf(dat,"%f	%i	%f\n", (i-0.5)*dlv, gdv[i], gdv[i]/(1.0*p));
		}
	fclose(dat);
}
/////////////////////////////////////////////////////////////////////////////THE END///////////////////////////////////////////////////////////////////////





