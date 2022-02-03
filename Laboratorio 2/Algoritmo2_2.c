#include <stdio.h>
#include <string.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////
/*																		 //////
-> Sección donde se identifican las funciones que se ocuparan.			///////
																		///////
*/                                                                      ///////
///////////////////////////////////////////////////////////////////////////////
int buscarMenor(int * arregloResultante,int * cantidadPuntos,int * bandera);
int ** mejoresRutas(int ** arregloResultante, int * cantidadPuntos, int * puntosGenericos);
int ** lecturaArchivo(int **arregloResultante, int *cantidadPuntosArchivo, int *valorOptimoArchivo);
int * valorPuntos(int cantidadPuntos, int ** rutas, int ** puntosArchivo,int *arregloPuntos, int *mejorPunto);




/*
Entradas: Matriz de ponderaciones, la dimension de la matriz, el valor optimo.
Objetivo: Realizar una lectura del archivo txt y traspasar los datos a una matriz cuadrada, luego retornar dicha matriz.
Salida: Matriz de las ponderaciones de las rutas.
*/
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

/*
Entradas: Matriz de ponderaciones, la dimension de la matriz, lista con los puntos de la dimension de la matriz .
Objetivo: Obtener las mejores rutas del archivo entrante, empezando desde uno de los puntos de la dimension de la matriz.
Salida: Matriz las mejores rutas desde todos los puntos de la dimension de la matriz.
*/
int ** mejoresRutas(int ** arregloResultante, int * cantidadPuntos, int * puntosGenericos){
	int * bandera = (int *)malloc(sizeof(int)*(*cantidadPuntos));
	for (int i = 0; i < *cantidadPuntos; i++)
	{
		bandera[i] =  0;
	}
	int ** arregloRutas = (int **)malloc(sizeof(int *)*(*cantidadPuntos));
	int  posicion;
	int numeroMenor = 0;
	int aux = 0;
	int aux2 = 0;
	for (int i = 0; i < *cantidadPuntos; i++)
	{
		aux = i;
		arregloRutas[i] = (int *)malloc(sizeof(int)*(*cantidadPuntos + 1));
		for (int j = 0; j <*cantidadPuntos  ; j++)
		{
			if(j == 0){
				arregloRutas[i][j] = puntosGenericos[i];
				bandera[i] = 1;
			}
			else
			{
				posicion = buscarMenor(arregloResultante[aux],cantidadPuntos,bandera);
				arregloRutas[i][j] = puntosGenericos[posicion];
				aux = posicion;
			}	
		}
		arregloRutas[i][*cantidadPuntos] = arregloRutas[i][0];
		for (int k = 0; k <*cantidadPuntos ; k++)
		{
			bandera[k] = 0;
		}
	}

	for (int i = 0; i < *cantidadPuntos; i++)
	{
		for (int j = 0; j < *cantidadPuntos + 1; j++)
		{
			printf("%d ", arregloRutas[i][j]);
		}
		printf("\n");
	}
	return arregloRutas;
}

/*
Entradas: Filas de la matriz de rutas, la dimension y una bandera que marcará los puntos que ya se visitaron.
Objetivo: Encontrar la ruta mas corta de una fila, empezando desde diferentes posiciones de filas.
Salida: Posicion donde esta la cantidad menor y bandera marcada en dicha posicion.
*/

int buscarMenor(int * arregloResultante,int * cantidadPuntos,int * bandera){
  int minimo;
  int maximo;  
  int posicion;
  int key;
  int i=0;
  while ( i < *cantidadPuntos)
  {
  	if(bandera[i] == 0){
  		minimo = arregloResultante[i];
  		key = i;
  		i = *cantidadPuntos;
  	}
  	i++;
  }
  for(int cont=key;cont < *cantidadPuntos;cont++){
    if(arregloResultante[cont] <= minimo && bandera[cont] != 1 && arregloResultante[cont] != -1){
      minimo = arregloResultante[cont];
      posicion = cont; 
    }
  }
  bandera[posicion] = 1;
  return posicion;	
}

/*
Entradas: Dimension de la matriz, la matriz de las mejores rutas, matriz de las ponderaciones arreglo donde se guardaran las ponderaciones y mejor punto.
Objetivo: Obtiene el valor de las mejores rutas.
Salida: Valores de las mejores rutas y valor de mejor ruta.
*/

int * valorPuntos(int cantidadPuntos, int ** rutas, int ** puntosArchivo,int *arregloPuntos, int *mejorPunto){
    arregloPuntos = (int*)malloc(sizeof(int)*cantidadPuntos);
    int totalSuma = 0 ;
    int numeroRuta, numeroSiguiente, acumulado, numeroAnterior;
    for (int i = 0; i < cantidadPuntos; i++)
    {
        for (int j = 0; j < cantidadPuntos; j++)
        {
            if(j != cantidadPuntos){
                numeroRuta =  rutas[i][j];
                numeroSiguiente = rutas[i][j + 1];
                acumulado = puntosArchivo[numeroRuta - 1][numeroSiguiente - 1];
                totalSuma = totalSuma + acumulado;
            }
            else{
                numeroRuta =  rutas[i][j];
                numeroAnterior = rutas[i][j - 1];
                acumulado = puntosArchivo[numeroRuta - 1][numeroAnterior - 1];
                totalSuma = totalSuma + acumulado;
            }
            
        }
        arregloPuntos[i] = totalSuma;
        totalSuma = 0;
    }

    *mejorPunto = arregloPuntos[0];
    for (int i = 0; i < cantidadPuntos; i++)
    {
        if(*mejorPunto > arregloPuntos[i]){
            *mejorPunto = arregloPuntos[i];
        }
    }
    
    
    return arregloPuntos;
}


int main()
{
	
	int cantidadPuntos = 0;  
	int valorOptimo = 0;
    int mejorPunto = 0;
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

    int ** arregloRutas = mejoresRutas(puntosArchivo,&cantidadPuntos,puntosGenericos);
    int * arregloPuntos = valorPuntos(cantidadPuntos,arregloRutas,puntosArchivo,arregloPuntos,&mejorPunto);

     for (int i = 0; i < cantidadPuntos; i++)
    {
        for (int j = 0; j < cantidadPuntos + 1; j++)
        {
            printf("%d ",arregloRutas[i][j]);
        }
        
        printf(": %d\n", arregloPuntos[i]);
    }
    printf("La mejor ruta es: %d ", mejorPunto);

}