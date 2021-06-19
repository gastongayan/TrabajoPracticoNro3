/*
 * input.c
 *
 *  Created on: 8 may. 2021
 *      Author: gasto
 */



//Funcion que recibe el valor como parametro devolviendolo incrmentado en 1
#include <string.h>
#include <stdio.h>

int incrementarId(int* id){
	*(id)++;
	return id;
}


float CargarUnFloat(char* mensaje){
	float numero;
	do{
		printf("%s: ",mensaje);
		scanf("%f",&numero);
	}while(numero<0);

	return numero;
}
int CargarUnEntero(char* mensaje, int menor, int mayor){

	int numero;
	printf("%s: ",mensaje);
	scanf("%d",&numero);
	numero= ValidarRango(numero, menor, mayor);
	return numero;
}

int ValidarRango(int numero, int menor, int mayor){
	int contador;
	contador=0;
	while(numero<menor || numero>mayor){
		printf("Error, ingrese datos entre %d y %d\n",menor, mayor);
		scanf("%d",&numero);
		contador++;
		if(contador==3){
			printf("Demasiados intentos realizados\nEl dato no fue cargado\n");
			return 0;
			break;
		}
	}
	return numero;
}


int CargarUnaCadena(char* mensaje, char datoIngresado[]){

	int rtn = 0;
	char auxString[500];
	int attemps = 0;
	do{
		attemps++;
		printf("%s:", mensaje);
		fflush(stdin);
		scanf("%s",auxString);
	}while((strlen(auxString)>50 || strlen(auxString)==0) && attemps != 4);
	if(attemps!=4){

		strcpy(datoIngresado, auxString);

		rtn = 1;
	}

	return rtn;
}

