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
void imprime_gdr(void);
void imprime_gdv(void);


int p, pasos=10000000, actu=100000;
float temp=300;//temperatura ambiente
float m=1.67e-27;//masa de un hidrogeno

float dl=8.0/CLASES;//flotante :P
float dlv=12000.0/CLASES;//distribucion en x

long int gdx[CLASES+1]={0}, gdy[CLASES+1]={0}, gdz[CLASES+1]={0}, gdvx[CLASES+1]={0}, gdvy[CLASES+1]={0}, gdvz[CLASES+1]={0};//velocidades por componentes

FILE *dat;

//INICIO DEL PROGRAMA PRINCIPAL***************************************************************************************************************************
main(){
srand((unsigned)time(NULL));/*sembrando la semilla*/

system ("mkdir temp");

float xi, fxi, vxi, fvxi;

for(p=1; p<=pasos; p++){/*INICIO(Principal)*/
	do{
		xi=alea()*8;
		fxi=exp(-pow(xi-4,2)/2)/sqrt(2*pi);
	}while(alea()>fxi);
	gdx[int(xi/dl)+1]++;//promedio modificado do{
	
	do{
		xi=alea()*8;//en y con las mismas variables de x
		fxi=exp(-pow(xi-4,2)/2)/sqrt(2*pi); 
	}while(alea()>fxi);
	gdy[int(xi/dl)+1]++;
	
	do{
		xi=alea()*8;//en z con las mismas variables de x
		fxi=exp(-pow(xi-4,2)/2)/sqrt(2*pi);
	}while(alea()>fxi);
	gdz[int(xi/dl)+1]++;
	
	do{
		vxi=alea()*12000-6000;//distribucion en x
		fvxi=exp(-vxi*vxi*m/(2*kb*temp))*sqrt(m/(2*pi*kb*temp));//distribucion en x
	}while(alea()*1e-3>fvxi);
	gdvx[int((vxi+6000)/dlv)+1]++;//distribucion en x

	do{
		vxi=alea()*12000-6000;//distribucion en x
		fvxi=exp(-vxi*vxi*m/(2*kb*temp))*sqrt(m/(2*pi*kb*temp));//distribucion en x
	}while(alea()*1e-3>fvxi);
	gdvy[int((vxi+6000)/dlv)+1]++;//distribucion en x

	do{
		vxi=alea()*12000-6000;//distribucion en x
		fvxi=exp(-vxi*vxi*m/(2*kb*temp))*sqrt(m/(2*pi*kb*temp));//distribucion en x
	}while(alea()*1e-3>fvxi);
	gdvz[int((vxi+6000)/dlv)+1]++;//distribucion en x

	if(p%1==0)printf("\rPasos: %i", p);
	if(p%actu==0){
		imprime_gdr();
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
void imprime_gdr(void){
	int i;
	FILE *dat;
	char nombre[50];
	sprintf(nombre,"temp/gdr_%i.dat",p/actu);
		dat=fopen(nombre, "w");
		for(i=1; i<=CLASES; i++){
			fprintf(dat,"%f	%i	%f	%i	%f	%i	%f\n", (i-0.5)*dl, gdx[i], gdx[i]/(1.0*p), gdy[i], gdy[i]/(1.0*p), gdz[i], gdz[i]/(1.0*p));//distribucion en las tres componentes de r
		}
	fclose(dat);
}///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void imprime_gdv(void){
	int i;
	FILE *dat;
	char nombre[50];
	sprintf(nombre,"temp/gdv_%i.dat",p/actu);//distribucion en x
		dat=fopen(nombre, "w");
		for(i=1; i<=CLASES; i++){
			fprintf(dat,"%f	%i	%f	%i	%f	%i	%f\n", (i-0.5)*dlv-6000, gdvx[i], gdvx[i]/(1.0*p), gdvy[i], gdvy[i]/(1.0*p), gdvz[i], gdvz[i]/(1.0*p));//distribuion en las 3 componentes de v
		}
	fclose(dat);
}
/////////////////////////////////////////////////////////////////////////////THE END///////////////////////////////////////////////////////////////////////





