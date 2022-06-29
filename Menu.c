#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tetris.h"
#include "list.h"

void main(){

    List* ListaPuntaje=createList();
    int eleccion;
    int eleccionf;
    while(eleccion!=0){
        printf("======================================================================\n");
        printf("H                                                                    H\n");
        printf("H                          T E T R I S                               H\n");
        printf("H                           P U C V                                  H\n");
        printf("H                                                                    H\n");
        printf("H                                                                    H\n");
        printf("H                           1-.Iniciar juego                         H\n");
        printf("H                           2-Comandos                               H\n");
        printf("H                           3-.Puntajes                              H\n");
        printf("H                                                                    H\n");
        printf("H                           0-.Cerrar juego                          H\n");
        printf("======================================================================\n");
        //printf("1-.Iniciar juego\n");
        //printf("2-¿Que es el tetris?\n");
        //printf("0-.Cerrar juego\n");

        scanf("%d",&eleccion);
        system("cls");
        switch(eleccion){
            case 1:
                system("cls");
                printf("=================================\n");
                printf("H  Seleccione su dificultad:    H\n");
                printf("H           1-Normal            H\n");
                printf("H           2-Dificil           H\n");
                printf("=================================\n");
                scanf("%d",&eleccion);
                switch (eleccion)
                {
                case 1:
                    tetris(ListaPuntaje);
                    break;
                case 2:
                    tetris2(ListaPuntaje);
                    break;
                }
            break;
            case 2:
                system("cls");
                printf("=================================\n");
                printf("H   Mover : Izquierda/Derecha   H\n");
                printf("H   Rotar : Arriba              H\n");
                printf("H   Acelerar : Abajo            H\n");
                printf("H   Espacio : Bajar Tetromino   H\n");
                printf("H   S : Pausa                   H\n");
                printf("=================================\n");
                printf("\n=============================================\n");
                printf("H          PRESIONE CUALQUIER TECLA        H\n");
                printf("=============================================\n");
                scanf("%d",&eleccionf);
                system("cls");
                break;               
            case 3:
            system("cls");
            mostrarPuntajes(ListaPuntaje);
            break;
        }
    }
}
