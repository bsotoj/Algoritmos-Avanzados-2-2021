#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int ** lecturaArchivo(int **arregloResultante, int *cantidadPuntosArchivo, int *valorOptimoArchivo){
    char nombreArchivo[40];
	printf("Si el archivo es RT_4_30 entonces tiene que escribir RT_4_30.txt\n");
	printf("Nombre del archivo: ");
	fflush(stdin);
	scanf("%s", &nombreArchivo);
	char nombreArchivoAuxiliar[40];
	strcpy(nombreArchivoAuxiliar,nombreArchivo);

	char* piece = strtok(nombreArchivo, "_");

	*cantidadPuntosArchivo = atoi(strtok(NULL,"_"));
	*valorOptimoArchivo = atoi(strtok(NULL,"-"));
    

	FILE *leer = fopen(nombreArchivoAuxiliar,"r");

	arregloResultante = (int **)malloc(sizeof(int *)*(*cantidadPuntosArchivo));
	for(int filas = 0; filas < *cantidadPuntosArchivo; filas++){
		arregloResultante[filas] = (int *)malloc(sizeof(int)*(*cantidadPuntosArchivo));
		for(int columnas = 0; columnas < *cantidadPuntosArchivo; columnas++){
			fscanf(leer,"%d",&arregloResultante[filas][columnas]);
			printf("%d ", arregloResultante[filas][columnas]);
		}
		printf("\n");
	}

	fclose(leer);
	return arregloResultante;
}
int costeRutaOptima = 0;
int costeRutaActual(int * arr, int arrSize, int ** biArr){
    int suma = 0;
    int posicionFinal = arrSize - 1;
    for(int i = 0; i < arrSize - 1; i++){
        suma = suma + biArr[arr[i] - 1][arr[i + 1] - 1];
    }
    suma = suma + biArr[arr[posicionFinal] - 1][arr[0] - 1];
    return suma;
}
void mostrarPermutacionActual(int * arr, int size)
{
    int i,j;
    for(i=0; i<size; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("%d",arr[0]);
}
//intercambiar dos posiciones en un arreglo
void swap(int *posicionA, int *posicionB)
{
    int aux;
    aux = *posicionA;
    *posicionA = *posicionB;
    *posicionB = aux;
}

//generar todas las solucionnes
void generarPermutaciones(int *arr, int start, int end, int ** biArr)
{
	//caso base
    if(start==end)
    {
        mostrarPermutacionActual(arr, end+1);
        //calcular coste de la ruta actual generada
        int valorRutaActual = costeRutaActual(arr,end+1,biArr);
        printf(" = %d\n", valorRutaActual);

        //evaluar si el coste de la ruta actual es mejor que la anterior
        if(costeRutaOptima > valorRutaActual || costeRutaOptima == 0){
            costeRutaOptima = valorRutaActual;          
        } 
        return;
    }
    int i;
    for(i=start;i<=end;i++)
    {
        //intercambiar posiciones
        swap((arr+i), (arr+start));
        generarPermutaciones(arr, start+1, end,biArr);
        //intercambiar nuevamente las posiciones cambiadas para volver al valor original
        swap((arr+i), (arr+start));
    }
}

int main()
{
    int cantidadPuntos = 0;  
	int valorOptimo = 0;
    
    int **puntosArchivo = lecturaArchivo(puntosArchivo, &cantidadPuntos, &valorOptimo);
    int * puntosGenericos = (int*)malloc(sizeof(int)*cantidadPuntos);
    for (int i = 0; i < cantidadPuntos ; i++)
    {
       if(i == 0){
           puntosGenericos[i] = 1;
       }
       else{
           puntosGenericos[i] = puntosGenericos[i-1] + 1;
       }
    }
    ; 
  
    generarPermutaciones(puntosGenericos, 0, cantidadPuntos-1,puntosArchivo);
    printf("El coste de la ruta mas corta es: %d\n ", costeRutaOptima);

    //liberar memoria 
    for(int i = 0; i < cantidadPuntos; i++){
    	free(puntosArchivo[i]);
    }
    free(puntosArchivo);
    free(puntosGenericos);
    return 0;
}