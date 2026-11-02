#include<stdlib.h>
#include<stdio.h>
#include<pthreads.h>

typedef struct station{
    int passageiros_esperando;
    int assentos_disponiveis;
    int passageiros_autorizados;
    int passageiros_embarcados;
}station;

void station_load_car(station *station, int count){
    if (station == NULL){
        return;
    }else{
            if (station->passageiros_esperando == 0){
                return;
            }

            if(count != 0){
                station->assentos_disponiveis = count;
            }
        }
    }

void station_wait_for_car(station *station){
    if(station != NULL){
        if (station->assentos_disponiveis != 0 && station->assentos_disponiveis > 0){
            if(station->passageiros_esperando!=0 && station->passageiros_esperando>0){
            int temp = station->passageiros_esperando - station->assentos_disponiveis;
            station->passageiros_autorizados = station->passageiros_esperando - temp;
            station->assentos_disponiveis -= station->passageiros_autorizados;
            }
        }
    }
}

void station_on_board(station *station){
    if(station!=NULL){
        if (station->passageiros_autorizados != 0 && station->passageiros_autorizados > 0){
            station->passageiros_embarcados+=1;
            station->passageiros_autorizados-=1;
        }
    }
}
 