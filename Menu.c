#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tetris.h"
#include "list.h"

void main(){

    List* ListaPuntaje=createList();
    int eleccion;
    while(eleccion!=0){
        printf("======================================================================\n");
        printf("H                                                                    H\n");
        printf("H                            TETRIS                                  H\n");
        printf("H                             PUCV                                   H\n");
        printf("H                                                                    H\n");
        printf("H                                                                    H\n");
        printf("H                            1-.Iniciar juego                        H\n");
        printf("H                            2-%cQue es el tetris?                    H\n",168);
        printf("H                                                                    H\n");
        printf("H                            0-.Cerrar juego                         H\n");
        printf("======================================================================\n");
        //printf("1-.Iniciar juego\n");
        //printf("2-¿Que es el tetris?\n");
        //printf("0-.Cerrar juego\n");

        scanf("%d",&eleccion);

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

        }
    }
}
