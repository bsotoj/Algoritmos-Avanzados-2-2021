#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <float.h> 

//definicion para la estructura 
typedef struct estado estado;
struct estado{
    float beneficioActual;//beneficio -> suma acumulada
    float cotaActual;
    int nivelArbolActual;
    int capacidadReal;
};
//***********Declaracion de funciones*********************//
estado estadoInicial(int nivelActual,float cotaMax, int ponderacionMax);
estado * agregarEstado(estado *lista, int *elementos, estado estado);
estado * sacarElemento(estado *lista, int *elementos);
int estaSgteNivelFueraDeLimite(estado estadoActual, int cantidadNiveles);
estado avanzarNivel(estado actual, int considerarNumeroActual, float ** relaciones, int ** numeroYponderacion, int  cantidadNumerosArchivo);
float GreedyRelajado(int nivelActual,estado anterior,float **relaciones, int **numeroYponderacion, int largo);
float cotaMax = 0; 



//***********Implementacion de funciones****************//
//funcion que crea el estado inicial del arbol 
//entrada: nivel actual y cota maxima ambas inicializadas en 0 y ponderacion limite de la entrada del archivo
//salida: estado inicial
estado estadoInicial(int nivelActual, float cotaMax, int ponderacionMax){
    estado inicial; 
    inicial.beneficioActual = 0;
    inicial.cotaActual = cotaMax;
    inicial.nivelArbolActual = nivelActual;
    inicial.capacidadReal = ponderacionMax;
    return inicial;
}

//funcion que agrega un estado a una lista de estados
//entrada: lista de estados, cantidad de elementos de la lista y el nuevo estado 
//salida: lista de estados 
estado * agregarEstado(estado *lista, int *elementos, estado nuevoEstado){
    estado *nuevaLista = (estado *)malloc(sizeof(estado)*(*elementos + 1));
    for(int i = 0; i < *elementos; ++i){
        nuevaLista[i] = lista[i];
    }
    nuevaLista[*elementos] = nuevoEstado;
    *elementos = *elementos + 1;
    free(lista);
    return nuevaLista;
}

//funcion que saca un estado al inicio de una lista de estados 
//entrada: lista de estados y la cantidad de elementos que tiene la lista
//salida: lista de estados con un elemento menos 
estado * sacarElemento(estado *lista, int *elementos){
    estado *nuevaLista = (estado *)malloc(sizeof(estado)*(*elementos - 1));
    for(int i = 1; i < *elementos; ++i){
        nuevaLista[i-1] = lista[i];
    }
    *elementos = *elementos-1;
    free(lista);
    return nuevaLista;
}

//funcion que comprueba si el siguiente nivel excede el limite del arbol 
//entrada: estado actual y cantidad de niveles que tiene el arbol
//salida: numero entero 
int estaSgteNivelFueraDeLimite(estado estadoActual, int cantidadNiveles){
    if((estadoActual.nivelArbolActual) + 1 > cantidadNiveles ){
        return 1;
    }

    else{
        return 0;
    }

}

//funcion que comprueba el maximo entre dos numeros
//entrada: dos numeros flotante
//salida: numero entero
int maximoEntreNumeros(float caso0, float caso1){
    if(caso0 > caso1){
        return 0;
    }
    else{
        return 1;
    }
}

//funcion que calcula el beneficio maximo a alcanzar considerando la capacidad de poder fraccionar numeros 
//entrada: nivel actual del arbol, estado anterior, arreglo flotante, arreglo de enteros y largo de ambos arreglos 
//salida: maximo beneficio alcanzado
float GreedyRelajado(int nivelActual, estado anterior,float **relaciones, int **numeroYponderacion, int largo){
    


    float resultado = anterior.beneficioActual; 
    int capacidadRestante = anterior.capacidadReal;
    int iterador = nivelActual;
    for (int i = iterador; i < largo; i++){
        if(numeroYponderacion[(int)relaciones[i][1]][1] < capacidadRestante){
             resultado = resultado + (float)numeroYponderacion[(int)relaciones[i][1]][0];
             capacidadRestante = capacidadRestante - numeroYponderacion[(int)relaciones[i][1]][1];
        }
        //ej: cuando la capacidad restante de ponderacion es 3 y quiero ingresar un valor de ponderacion 9 -> hay que fraccionarlo
        //cuando realizamos esta operacion ocupamos el espacio restante 
        else if(capacidadRestante > 0){
            float valorFraccionado = relaciones[i][0] * (float)capacidadRestante;
            resultado = resultado + valorFraccionado; 
            capacidadRestante = 0; 
        }

    }

    return resultado;

}


//funcion que calcula la ramificacion al nivel siguiente
//entrada: estado anterior, bandera que indica si considerar el numero actual como solucion donde 
//0: si se considera
//-1: no se considera
//arreglo flotante, arreglo de enteros y cantidad de numeros de archivo
//salida: nuevo estado
estado avanzarNivel(estado anterior, int considerarNumeroActual, float ** relaciones, int ** numeroYponderacion, int  cantidadNumerosArchivo){
    //no consideramos al numero actual como parte de la solucion
    if(considerarNumeroActual == -1){
        
        estado nuevoEstado;
        nuevoEstado.beneficioActual = anterior.beneficioActual;
        nuevoEstado.nivelArbolActual = (anterior.nivelArbolActual) + 1; 
        nuevoEstado.capacidadReal = anterior.capacidadReal;
        nuevoEstado.cotaActual = nuevoEstado.beneficioActual + GreedyRelajado(nuevoEstado.nivelArbolActual, nuevoEstado, relaciones, numeroYponderacion, cantidadNumerosArchivo);
        return nuevoEstado; 
    

    }

    else{
        estado nuevoEstado;
        nuevoEstado.nivelArbolActual = (anterior.nivelArbolActual) + 1;
        nuevoEstado.beneficioActual = anterior.beneficioActual + (float)numeroYponderacion[(int)relaciones[(nuevoEstado.nivelArbolActual)-1][1]][0];
        nuevoEstado.capacidadReal = anterior.capacidadReal - numeroYponderacion[(int)relaciones[(nuevoEstado.nivelArbolActual)-1][1]][1];
        nuevoEstado.cotaActual = nuevoEstado.beneficioActual + GreedyRelajado(nuevoEstado.nivelArbolActual, nuevoEstado, relaciones, numeroYponderacion, cantidadNumerosArchivo);
        return nuevoEstado;
    }

}




//**************************************************

//*******************************************************//

//***************************ESTO PERTENECE A LAS FUNCIONES HECHAS EN EL LABORATORIO 2************//
//************************************************************************************************//
//funcion que emplea el metodo burbuja para ordenar un arreglo de menor a mayor
//entrada: arreglo flotante y largo del arreglo
//salida: arreglo flotante ordenado
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

//funcion que invierte una lista
//entrada: arreglo flotante, largo del arreglo
//salida: arreglo invertido
float **invertirLista(float **arreglo, int largo){
    float **nuevaLista = (float **)malloc(sizeof(float *)*largo); 
    int iteradorNuevaLista = 0;

    for(int i=0;i<largo;i++){
        nuevaLista[i] = (float *)malloc(sizeof(float)*2);
    }


    for(int i=largo-1;i>=0;i--){
        nuevaLista[iteradorNuevaLista][0] = arreglo[i][0];
        nuevaLista[iteradorNuevaLista][1] = arreglo[i][1];
        iteradorNuevaLista+=1;
    }

    for(int i=0; i<largo; i++){
        free(arreglo[i]);
    }
    free(arreglo);

    return nuevaLista;
}

//************************************************************************************************//
//funcion que calcula la relacion entre numero y ponderacion
//entrada: largo del arreglo, arreglo de enteros
//salida: arreglo flotante
float **calcularRelacion(int largoEntrada, int **numeroYPonderacion){

    float **arregloRelaciones = (float **)malloc(sizeof(float *)*largoEntrada);
    for(int i = 0; i < largoEntrada; i++){
        arregloRelaciones[i] = (float *)malloc(sizeof(float)*2);
        for(int j = 0; j < 2; j++){
            arregloRelaciones[i][0] = (float)numeroYPonderacion[i][0] / (float)numeroYPonderacion[i][1];
            arregloRelaciones[i][1] = (float)i;
        }
    }
    return arregloRelaciones;
}


//*************************************************************************************************//
//funcion que lee el contenido de un archivo
//entrada: arreglo de enteros, puntero a entero que indica la cantidad de elementos del archivo y puntero a entero que indica la ponderacion limite
//asociada al archivo
//salida: arreglo de enteros
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
//*************************************************************************************************//
int main(){
    //*********Lectura del archivo**********//
	int cantidadNumerosArchivo, ponderacionMaxima;
	int **numeroYponderacion = lecturaArchivo(numeroYponderacion, &cantidadNumerosArchivo, &ponderacionMaxima);

    //********Establecer relacion numero/ponderacion*********//
    float **relaciones = calcularRelacion(cantidadNumerosArchivo,numeroYponderacion);
    relaciones = bubbleSort(relaciones,cantidadNumerosArchivo);
    relaciones= invertirLista(relaciones,cantidadNumerosArchivo);
    
    
     
    int canAbiertos = 0;
    int canCerrados = 0; 
    
   // caso 0 -> no consideramos al siguiente numero en la solucion
   // caso 1 -> consideramos el siguiente numero en la solucion 
    
    estado actual, siguienteCaso0, siguienteCaso1;
    estado *abiertos = (estado *)malloc(sizeof(estado)*canAbiertos);
    estado *cerrados= (estado *)malloc(sizeof(estado)*canCerrados);
    estado inicial = estadoInicial(0,0,ponderacionMaxima);

    abiertos = agregarEstado(abiertos, &canAbiertos, inicial);
    while(canAbiertos > 0){
        //trabajar con este para calcular los siguientes niveles
        actual = abiertos[0];
        abiertos = sacarElemento(abiertos, &canAbiertos);
        cerrados = agregarEstado(cerrados, &canCerrados, actual);
        //si es 0 quiere decir que aun podemos seguir descendiendo en el arbol
        if(estaSgteNivelFueraDeLimite(actual, cantidadNumerosArchivo) == 0){
            siguienteCaso0 = avanzarNivel(actual,-1,relaciones,numeroYponderacion,cantidadNumerosArchivo);
            siguienteCaso1 = avanzarNivel(actual,0,relaciones,numeroYponderacion,cantidadNumerosArchivo);
    
            //buscar si existe una cota mayor que la actual    
            int maximo = maximoEntreNumeros(siguienteCaso0.cotaActual,siguienteCaso1.cotaActual); 
            if(maximo == 0){
                if(siguienteCaso0.cotaActual > cotaMax){
                    if(siguienteCaso0.capacidadReal > 0){
                        cotaMax = siguienteCaso0.cotaActual;
                    }
                }
            }
            else if(maximo == 1){
                if(siguienteCaso1.cotaActual > cotaMax){
                    if(siguienteCaso1.cotaActual > 0){
                        cotaMax = siguienteCaso1.cotaActual;
                    }
                }

            }
            //si el estado actual que no incluye al numero actual es mayor o igual a la cota se puede seguir ramificando
            if(siguienteCaso0.cotaActual >= cotaMax){
                abiertos = agregarEstado(abiertos,&canAbiertos,siguienteCaso0);
            }
            else{
                cerrados = agregarEstado(cerrados,&canCerrados,siguienteCaso0);
            }
            //si el estado actual que si incluye al numero actual es mayor o igual a la cota se puede seguir ramificando
            if(siguienteCaso1.cotaActual >= cotaMax){
                abiertos = agregarEstado(abiertos,&canAbiertos,siguienteCaso1);
            }

            else{
                cerrados = agregarEstado(cerrados,&canCerrados,siguienteCaso1);
            }

        }



    }
    //de todos los estados generados, consideramos aquel que sea mayor y que sea factible 
    //es decir que no haya excedido la capacidad limite dada
    float mayorBeneficio = 0; 
    for(int i=0;i<canCerrados;i++){
        if(cerrados[i].beneficioActual > mayorBeneficio && cerrados[i].capacidadReal >= 0){
            mayorBeneficio = cerrados[i].beneficioActual;
        }
    }
    printf("la mayor suma encontrada utilizando ramificacion y acotamiento es:%d\n",(int)mayorBeneficio);
  

	//********Seccion liberacion memoria********//
	for(int i = 0; i<cantidadNumerosArchivo;i++){
		free(numeroYponderacion[i]);
       free(relaciones[i]);
	}

	free(numeroYponderacion);
    free(relaciones);


    free(abiertos);
    free(cerrados);
    //*****************************************//


	return 0; 
}		