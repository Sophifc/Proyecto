//Prototipo		tetris
//Aqui se definen las librerias a usar
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "list.h"
#include "tetris.h"

//Definimos Controles del Tetris
#define IZQUIERDA 75
#define DERECHA 77
#define ARRIBA 72
#define ABAJO 80

//Definimos coordenadas del tablero
#define TY 2
#define TX 3
#define TH 24
#define TW 10


//Definimos componentes del tablero
#define VACIO 0
#define PARED 1

struct Puntaje{
	char nombre[100];
	int puntosObtenidos;
};


//Declaracion de funciones a utilizar
void crearTablero();
void dibujarTetromino(int p);
void dibujarTablero();
int obtenerTecla(List* ListaPuntaje);
int verificarArea(int x,int y,int z,int r);
int descenso();
void verificarLinea();
void actualizarTablero();
void dibujarSiguienteTetromino(int p);
void puntaje(int x); 
void pausa();
void limpiarTerminal();
void tetris(List* ListaPuntaje);
void tetris2(List* ListaPuntaje);
void guardarPuntaje(List* ListaPuntaje);

//Ocultar cursor 
void ocultarCursor(){
    CONSOLE_CURSOR_INFO CurInfo;
    CurInfo.dwSize=1;
    CurInfo.bVisible=FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);
} 
 
//Funcion para mover el cursor por la ventana
void gotoxy(int x,int y){
    COORD pos={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//Array donde almacenamos los tetrominos, su construccion y orientaciones
int tetromino[7][4][8] =
	{
        {
            {0,-1,1,-1,-1,0,0,0},
            {-1,-1,-1,0,0,0,0,1},
            {0,-1,1,-1,-1,0,0,0},
            {-1,-1,-1,0,0,0,0,1}
        },
        {
            {0,0,1,0,0,-1,-1,-1},
            {-1,1,-1,0,0,0,0,-1},
            {0,0,1,0,0,-1,-1,-1},
            {-1,1,-1,0,0,0,0,-1}},
        {
            {-2,1,-1,1,0,1,1,1},
            {-1,2,-1,1,-1,0,-1,-1},
            {-2,1,-1,1,0,1,1,1},
            {-1,2,-1,1,-1,0,-1,-1}
        },
        {
            {-1,1,0,1,1,1,-1,0},
            {-1,1,0,1,0,0,0,-1},
            {0,1,0,0,-1,0,-2,0},
            {-1,2,-1,1,-1,0,0,0}
        },
        {
            {-1,1,0,1,-1,0,0,0},
            {-1,1,0,1,-1,0,0,0},
            {-1,1,0,1,-1,0,0,0},
            {-1,1,0,1,-1,0,0,0}},
        {
            {-2,1,-1,1,0,1,0,0},
            {0,2,0,1,0,0,-1,0},
            {-1,1,-1,0,0,0,1,0},
            {-1,1,0,1,-1,0,-1,-1}
        },
        {
            {0,1,-1,0,0,0,1,0},
            {0,1,0,0,1,0,0,-1},
            {-1,0,0,0,1,0,0,-1},
            {0,1,0,0,-1,0,0,-1}
        }
    };

//Variables a usar en la interfaz grafica
int tablero[TW+2][TH+2];
int figura,orientacion,siguiente_figura,siguiente_orientacion;
int nx,ny; 
int aux1 = 10;
int aux2;
int puntos = 0;
int lineas = 0;

void tetris (List* ListaPuntaje){
	int i,j;
	limpiarTerminal();
	ocultarCursor();
    srand(time(NULL));
	crearTablero();
	dibujarTablero();
	Sleep(3000);

	//Obtenemos los valores al azar para generar los tetrominos
	figura = rand()%7;
	orientacion = rand()%4;

	while(TRUE){
		//Obtenemos los valores al azar para genera el siguiente tetromino
		siguiente_figura = rand()%7;
	    siguiente_orientacion = rand()%4;

		//Coordenadas de donde nacen los tetrominos
		nx = TW/2;
		ny = 1;

		//Dibujamos los tetrominos
		dibujarSiguienteTetromino(TRUE);
		dibujarTetromino(TRUE);

		//Si no puede generar mas tetrominos, el juego acaba
		if(verificarArea(nx,ny,figura,orientacion)!=0)break;

		//Tiempo de descenso del tetromino
		aux2 = aux1;
		while(TRUE){
			aux2 -= 1;
			if(aux2==0){
				aux2 = aux1;
				if(descenso())break;
			}
			if(obtenerTecla(ListaPuntaje))break;
			Sleep(1000/20);
		}

		//Aqui pasamos al siguiente tetromino
		dibujarSiguienteTetromino(FALSE);
		figura = siguiente_figura;
		orientacion = siguiente_orientacion;
	}

	
	//Final del juego
	char fin;
 	gotoxy(TX+TW+3,TY+7);
 	printf("======================================");
 	gotoxy(TX+TW+3,TY+8);
 	printf("|                                    |");
 	gotoxy(TX+TW+3,TY+9);
 	printf("|                                    |");
 	gotoxy(TX+TW+3,TY+10);
 	printf("|    J U E G O  T E R M I N A D O    |");
 	gotoxy(TX+TW+3,TY+11);
 	printf("|  PRESIONE G PARA GUARDAR PUNTAJE   |");
 	gotoxy(TX+TW+3,TY+12);
 	printf("|                                    |");
 	gotoxy(TX+TW+3,TY+13);
 	printf("======================================");
	while(TRUE){
		if(obtenerTecla(ListaPuntaje))break;
	}
	fin = getch();
	gotoxy(1,28);
	system("cls");
	
}

void tetris2(List* ListaPuntaje){
	int i,j;
	limpiarTerminal();
	ocultarCursor();
    srand(time(NULL));
	crearTablero();
	dibujarTablero();
	Sleep(3000);

	//Obtenemos los valores al azar para generar los tetrominos
	figura = rand()%7;
	orientacion = rand()%4;

	while(TRUE){
		//Obtenemos los valores al azar para genera el siguiente tetromino
		siguiente_figura = rand()%7;
	    siguiente_orientacion = rand()%4;

		//Coordenadas de donde nacen los tetrominos
		nx = TW/2;
		ny = 1;

		//Dibujamos los tetrominos
		dibujarSiguienteTetromino(TRUE);
		dibujarTetromino(TRUE);

		//Si no puede generar mas tetrominos, el juego acaba
		if(verificarArea(nx,ny,figura,orientacion)!=0)break;

		//Tiempo de descenso del tetromino
		aux2 = aux1;
		while(TRUE){
			aux2 -= 1;
			if(aux2==0){
				aux2 = aux1;
				if(descenso())break;
			}
			if(obtenerTecla(ListaPuntaje))break;
			Sleep(100/20);
		}

		//Aqui pasamos al siguiente tetromino
		dibujarSiguienteTetromino(FALSE);
		figura = siguiente_figura;
		orientacion = siguiente_orientacion;
	}

	//Final del juego
	char fin;
 	gotoxy(TX+TW+3,TY+7);
 	printf("======================================");
 	gotoxy(TX+TW+3,TY+8);
 	printf("|                                    |");
 	gotoxy(TX+TW+3,TY+9);
 	printf("|                                    |");
 	gotoxy(TX+TW+3,TY+10);
 	printf("|    J U E G O  T E R M I N A D O    |");
 	gotoxy(TX+TW+3,TY+11);
 	printf("|  PRESIONE G PARA GUARDAR PUNTAJE   |");
 	gotoxy(TX+TW+3,TY+12);
 	printf("|                                    |");
 	gotoxy(TX+TW+3,TY+13);
 	printf("======================================");

	while(TRUE){
		if(obtenerTecla(ListaPuntaje))break;
	}
	fin = getch();
	gotoxy(1,28);
	system("cls");
}

//Funcion donde creamos la ubicacion de los componentes del tabero
void crearTablero(){
	int i,j;
	for(i=0;i<TW+2;i++){
		for(j=0;j<TH+2;j++){
			if(i==0 || i==TW+1 || j==TH+1){
				tablero[i][j]=PARED;
			}
			else{
				tablero[i][j]=VACIO;
			}
		}
	}
}

//Funcion para dibujar el tetromino
void dibujarTetromino(int p){
	int i;
		for(i=0;i<8;i+=2){
		gotoxy(TX+(tetromino[figura][orientacion][i]+nx)*2,TY+tetromino[figura][orientacion][i+1]+ny);
		if(p == TRUE){
			printf("#");
		}
		else{
			printf(" ");
		}
	}
}

//Funcion para dibujar el tablero
void dibujarTablero(){
	int i,j;
	for(i=0;i<TW+2;i++){
		for(j=0;j<TH+2;j++){
		    gotoxy(TX+i*2,TY+j);
			if(tablero[i][j] == PARED){
				printf("H");
			}
			else{
				printf(" ");
			}
		}
	}

	gotoxy(34,2);
	printf("======= Siguiente ========\n");
	gotoxy(34,3);
	printf("|                        |\n");
	gotoxy(34,4);
	printf("|                        |\n");
	gotoxy(34,5);
	printf("|                        |\n");
	gotoxy(34,6);
	printf("|                        |\n");
	gotoxy(34,7);
	printf("|                        |\n");
	gotoxy(34,8);
	printf("|                        |\n");
	gotoxy(34,9);
	printf("==========================\n");
	gotoxy(34,13);
	printf("Mover : Izquierda/Derecha");
	gotoxy(34,14);
	printf("Rotar : Arriba");
	gotoxy(34,15);
	printf("Acelerar : Abajo"); 
	gotoxy(34,16);
    printf("Espacio : Bajar Tetromino");
    gotoxy(34,17);
    printf("S : Pausa");
    puntaje(0);
}

//Funcion donde declaramos los controles del Tetris
int obtenerTecla(List* ListaPuntaje){
	char tecla;
	if(kbhit()){
		tecla = getch();
	switch(tecla){
		case 's':
		case 'S':
			pausa();
			break;
		case IZQUIERDA:
		    if(verificarArea(nx-1,ny,figura,orientacion)==(VACIO)){
			 dibujarTetromino(FALSE);
			    nx--;
			 dibujarTetromino(TRUE);
		    }
			break;
		case DERECHA:
			if(verificarArea(nx+1,ny,figura,orientacion)==VACIO){
			 dibujarTetromino(FALSE);
				nx++;
			 dibujarTetromino(TRUE);
			}
			break;
		case ARRIBA:
			if(verificarArea(nx,ny,figura,(orientacion+1)%4)==VACIO){
			 dibujarTetromino(FALSE);
				orientacion=(orientacion+1)%4;
			 dibujarTetromino(TRUE);
			}
			break;
		case ABAJO:
			if(descenso()){
				return TRUE;
			}
			break;
		case ' ':
			while(descenso()==FALSE);
			return TRUE;
		case 'g':
		case 'G':
		guardarPuntaje(ListaPuntaje);
		break;
	}}
    return FALSE;	
}

//Verifica si el tetromino choca contra algo, 1 = Colision, 0 = Vacio
int verificarArea(int x,int y,int z,int r){
 	int i,k=VACIO;
 	for(i=0;i<8;i+=2){
 		k=max(k,tablero[x+tetromino[z][r][i]][y+tetromino[z][r][i+1]]);
 	}
 	return k;
 }

//Funcion donde el tetromino baja mientras no tope con algo
int descenso(){
	if(verificarArea(nx,ny+1,figura,orientacion) != VACIO){
		  verificarLinea();
          return TRUE;
		  }
 dibujarTetromino(FALSE);
	ny++;
 dibujarTetromino(TRUE);
	return FALSE;
}

//Funcion que verifica si la linea esta completa
void verificarLinea(){
	int i,j,x,y,n=0;
	for(i=0;i<8;i+=2){
		tablero[nx+tetromino[figura][orientacion][i]][ny+tetromino[figura][orientacion][i+1]]=PARED;
		gotoxy(TX+(tetromino[figura][orientacion][i]+nx)*2,TY+tetromino[figura][orientacion][i+1]+ny);
		printf("#");
	}
    for(i=1;i<TH+1;i++){
	    for(j=1;j<TW+1;j++){ 
		    if(tablero[j][i]!=PARED)break;
			}
	    if(j==TW+1){
            n++;
		    for(x=i;x>1;x--){
		        for(y=1;y<TW+1;y++){
		        	tablero[y][x]=tablero[y][x-1];
		        }
		    }
		    Sleep(400);
			lineas++;
			puntaje(x*100);
		    actualizarTablero();
	    }
	}
}

//Funcion que actualiza el tablero luego de eliminada una linea
void actualizarTablero(){
	int i,j;
	for(i=1;i<TW+1;i++){
		for(j=1;j<TH+1;j++){
			gotoxy(TX+i*2,TY+j);
			if(tablero[i][j] == PARED){
				printf("#");
			}
			else{
				printf(" ");
			}
		}
	}
}

//Funcion que dibuja el siguiente tetromino a aparecer
void dibujarSiguienteTetromino(int p){
	int i;
	for(i=0;i<8;i+=2){
		gotoxy(48+tetromino[siguiente_figura][siguiente_orientacion][i]*2,5+tetromino[siguiente_figura][siguiente_orientacion][i+1]);
		if(p == TRUE){
			printf("#");
		}
		else{
			printf(" ");
		}
	}
}

//Funcion que calcula y muestra el puntaje
void puntaje(int x){
	puntos+=x;
	gotoxy(36,21);
	printf("Puntos : %d",puntos);
	gotoxy(36,22);
	printf("Lineas : %d",lineas);
}

//Funcion para pausar el juego
void pausa(){
	char pause;
 	gotoxy(TX+TW+3,TY+7);
 	printf("=================================");
 	gotoxy(TX+TW+3,TY+8);
 	printf("|                               |");
	gotoxy(TX+TW+3,TY+9);
 	printf("|                               |");
 	gotoxy(TX+TW+3,TY+10);
 	printf("|         P  A  U  S  A         |");
 	gotoxy(TX+TW+3,TY+11);
 	printf("|                               |");
 	gotoxy(TX+TW+3,TY+12);
 	printf("|                               |");
 	gotoxy(TX+TW+3,TY+13);
 	printf("=================================");
 	pause = getch();
 	system("cls");
 	dibujarTablero();
 	actualizarTablero();
 	dibujarSiguienteTetromino(TRUE);
 	dibujarTetromino(TRUE);
}

//Funcion que guarda los puntajes obtenidos
void guardarPuntaje(List* ListaPuntaje){

	int auxPuntaje=puntos;
	system("cls");

	char aux;
	Puntaje* puntajeNuevo=(Puntaje*) malloc (sizeof(Puntaje));
	char nombreUsuario[100];
	printf("=================================\n");
	printf("|                               |\n");
	printf("|INGRESE SU NOMBRE O APODO      |\n");
	printf("|                               |\n");
	printf("=================================\n");
	scanf("%s^[/n]", &nombreUsuario);
	strcpy(puntajeNuevo->nombre,nombreUsuario);
	system("cls");
	puntajeNuevo->puntosObtenidos=auxPuntaje;
	printf("=================================\n");
	if(puntajeNuevo->puntosObtenidos<1000){
	printf("|        puntaje: %i           |\n", puntajeNuevo->puntosObtenidos);
	}
	if(puntajeNuevo->puntosObtenidos>999 && puntajeNuevo->puntosObtenidos<10000){
	printf("|        puntaje: %i           |\n", puntajeNuevo->puntosObtenidos);
	}
	if(puntajeNuevo->puntosObtenidos>9999 && puntajeNuevo->puntosObtenidos<100000){
	printf("|        puntaje: %i          |\n", puntajeNuevo->puntosObtenidos);
	}
	pushBack(ListaPuntaje,puntajeNuevo);
	printf("|                               |\n");
	printf("|      agregado a la lista      |\n");
	printf("=================================\n");
	aux = getch();
}

void mostrarPuntajes(List* ListaPuntaje){

	Puntaje* auxPuntaje=firstList(ListaPuntaje);
	if(auxPuntaje==NULL){
		printf("No hay puntos\n");
	}
	while(auxPuntaje!=NULL){
		printf("%s -> %i\n",auxPuntaje->nombre, auxPuntaje->puntosObtenidos);
		auxPuntaje=nextList(ListaPuntaje);
	}
}

//Funcion para limpiar la Terminal
void limpiarTerminal(){
 	system("cls");
 }
