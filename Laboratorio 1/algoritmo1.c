#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

 

int calcularSumaActual(int **arregloArchivo, int n, int *arregloCombinaciones, int *ponderacion){
	int suma = 0;
	*ponderacion = 0;
	for(int i = 0; i<n; i++){
		if(arregloCombinaciones[i] == 1){
			suma = suma + arregloArchivo[i][0]; 
			*ponderacion = *ponderacion + arregloArchivo[i][1];
		}
	}
	return suma;
}


int detenerSumaBinaria(int *combinaciones,int n){
	for(int i=0; i < n; i++){
		if(combinaciones[i] == 0){
			return 1;
		}
	}
	return 0;
}		


int encontrarSumaMaxima(int **arregloArchivo, int cantidadNumeros, int ponderacionLimite){
	int *combinaciones = (int *)malloc(sizeof(int)*cantidadNumeros);
	for(int i = 0; i<cantidadNumeros;i++){
		combinaciones[i] = 0;
	}

	int mayorSumaEncontrada = 0;


	while(detenerSumaBinaria(combinaciones,cantidadNumeros) != 0){
		int seguirDesplazandose = 1;
		int largoCombinacion = cantidadNumeros - 1;

		int sumaActual = 0;
		int ponderacionActual = 0; 

		while(seguirDesplazandose == 1){
			if(combinaciones[largoCombinacion] == 0){
				combinaciones[largoCombinacion] = 1;
				seguirDesplazandose = 0;
			}

			else{
				combinaciones[largoCombinacion] = 0;
				largoCombinacion--; 
			}
		}
		
		//Mostrar combinacion actual por pantalla
		for(int i = 0; i < cantidadNumeros; i++){
			printf("%d ", combinaciones[i]);
		}
		printf("\n");
	
		sumaActual = calcularSumaActual(arregloArchivo,cantidadNumeros,combinaciones, &ponderacionActual);

		if(sumaActual > mayorSumaEncontrada){
			if(ponderacionActual <= ponderacionLimite){
				mayorSumaEncontrada = sumaActual;
			}
			}
		}
		//liberar memoria reservada para combinacion actual
	free(combinaciones);
	return mayorSumaEncontrada;	
	}

	
int **lecturaArchivo(int **arregloLecturaResultante, int *cantidadNumerosArchivo, int *ponderacionMaxima){

	char nombreArchivo[40];
	printf("Si el archivo de entrada es knapPI_1_10_269 entonces tiene que escribir knapPI_1_10_269.txt\n");
	printf("Nombre del archivo: "); 
	fflush(stdin);
	scanf("%s", &nombreArchivo); 
	char nombreArchivoAuxiliar[40];
	strcpy(nombreArchivoAuxiliar,nombreArchivo);
	
	char* piece = strtok(nombreArchivo, "_");
	char* piece2 = strtok(NULL, "_");

	*cantidadNumerosArchivo = atoi(strtok(NULL, "_"));
	*ponderacionMaxima = atoi(strtok(NULL, "_"));
	

	FILE *leer = fopen(nombreArchivoAuxiliar, "r"); 

	arregloLecturaResultante = (int **)malloc(sizeof(int *)*(*cantidadNumerosArchivo)); 

	for(int i=0; i < *cantidadNumerosArchivo; i++){
		arregloLecturaResultante[i] = (int *)malloc(sizeof(int)*2);
	}

	for(int i=0; i<*cantidadNumerosArchivo; i++){
		for(int j=0; j<2;j++){
			fscanf(leer,"%d",&arregloLecturaResultante[i][j]);


		}
	}

	fclose(leer);
	return arregloLecturaResultante;
}


int main(){

	int cantidadNumerosArchivo, ponderacionMaxima;
	int **numeroYponderacion = lecturaArchivo(numeroYponderacion, &cantidadNumerosArchivo, &ponderacionMaxima);
	int maximoNumero = encontrarSumaMaxima(numeroYponderacion,cantidadNumerosArchivo,ponderacionMaxima);
	//liberar memoria reservada para la lectura de archivo
	for(int i = 0; i<cantidadNumerosArchivo;i++){
		free(numeroYponderacion[i]);
	}

	free(numeroYponderacion);
	
	printf("La suma mas grande sin exceder la ponderacion limite es: %d\n", maximoNumero);

	return 0; 
}		