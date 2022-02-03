#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <float.h> 

//Funcion que calcula la maxima ponderación empleado el algoritmo goloso
//Entrada: Arreglo de enteros, arreglo de flotantes, largo de entrada, limite ponderacion
//Salida: Número entero
int golosoSumaMaxima(int ** numeroYPonderacion, float **relaciones, int largoEntrada, int limitePonderacion){
    int sumaTotal = 0;
    int ponderacionActual = 0; 
   
    
    for(int i = largoEntrada-1; i >= 0; i--){
        if(ponderacionActual + numeroYPonderacion[(int)relaciones[i][1]][1] <= limitePonderacion){
            sumaTotal = sumaTotal + numeroYPonderacion[(int)relaciones[i][1]][0];
            ponderacionActual = ponderacionActual + numeroYPonderacion[(int)relaciones[i][1]][1];
        }
    }
    return sumaTotal;
 }
 



//Funcion que ordena de menor a mayor un arreglo
//Entrada: Arreglo de flotantes, largo del arreglo
//Salida: Arreglo de flotantes ordenado
float **bubbleSort(float **arreglo, int LargoArreglo){
    for(int i = 0; i < LargoArreglo - 1; i++){
        for(int j = 0; j <LargoArreglo - i - 1; j++){
            if(arreglo[j][0] > arreglo[j+1][0]){
                //swap
                float aux1 = arreglo[j][0];
                float aux2 = arreglo[j][1];

                arreglo[j][0] = arreglo[j+1][0];
                arreglo[j][1] = arreglo[j+1][1];
                
                arreglo[j+1][0] = aux1; 
                arreglo[j+1][1] = aux2;
            }
        }
    }
    return arreglo;
} 

//Funcion que calcular la relacion entre ponderacion/numero
//Entrada: Arreglo de enteros, tamaño del arreglo
//Salida: Arreglo de flotantes
float **calcularRelacion(int largoEntrada, int **numeroYPonderacion){

    float **arregloRelaciones = (float **)malloc(sizeof(float *)*largoEntrada);
    for(int i = 0; i < largoEntrada; i++){
        arregloRelaciones[i] = (float *)malloc(sizeof(float)*2);
        for(int j = 0; j < 2; j++){
            arregloRelaciones[i][0] = (float)numeroYPonderacion[i][1] / (float)numeroYPonderacion[i][0];
            arregloRelaciones[i][1] = (float)i;
        }
    }
    return arregloRelaciones;
}


//Funcion que lee un archivo entrante
//Entrada: Archivo
//Salida: Arreglo de enteros
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
    
    float **relaciones = calcularRelacion(cantidadNumerosArchivo,numeroYponderacion);
   
    relaciones = bubbleSort(relaciones,cantidadNumerosArchivo);
   
    int maximoNumero = golosoSumaMaxima(numeroYponderacion,relaciones,cantidadNumerosArchivo,ponderacionMaxima);

	//liberar memoria reservada para la lectura de archivo
	for(int i = 0; i<cantidadNumerosArchivo;i++){
		free(numeroYponderacion[i]);
        free(relaciones[i]);
	}

	free(numeroYponderacion);
    free(relaciones);


	printf("La suma mas grande sin exceder la ponderacion limite es: %d\n",maximoNumero);


	return 0; 
}		