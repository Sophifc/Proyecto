//Declaracion de funciones a utilizar

#include "list.h"
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