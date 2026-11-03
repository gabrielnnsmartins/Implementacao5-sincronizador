#include<stdlib.h>
#include<stdio.h>
#include<pthreads.h>

typedef struct station{
    pthread_mutex_t tranca;
    pthread_cond_t carro_chegou;
    pthread_cond_t todos_embarcaram;
    int passageiros_esperando;
    int assentos_disponiveis;
    int passageiros_autorizados;
    int passageiros_embarcados;
}station;

void station_init(station *station){
    pthread_mutex_init(&station->tranca, NULL);
    pthread_mutex_init(&station->carro_chegou, NULL);
    pthread_mutex_init(&station->todos_embarcaram, NULL);
    station->passageiros_esperando = 0;
    station->assentos_disponiveis = 0;
    station->passageiros_autorizados = 0;
    station->passageiros_embarcados = 0;
}


void station_load_car(station *station, int count){
    if (station == NULL){
        return;
    }else{
            if(count != 0 && count > 0){
                pthread_mutex_lock(&station->tranca);
                int n_assentos;
                if(count > station->passageiros_esperando){
                    n_assentos = station->passageiros_esperando;
                }else{
                    n_assentos = count;
                }

                station->assentos_disponiveis = n_assentos;
                pthread_cond_broadcast(&station->carro_chegou);
                
                while(station->assentos_disponiveis > 0 && station->passageiros_esperando > 0){
                    pthread_cond_wait(&station->todos_embarcaram, &station->tranca);
                }

                pthread_mutex_unlock(&station->tranca);
                return;
            }
        }
    }

void station_wait_for_car(station *station){
    if(station != NULL){

        if(station->passageiros_esperando>0){
        if (station->assentos_disponiveis != 0 && station->assentos_disponiveis > 0){
            if(station->passageiros_esperando!=0 && station->passageiros_esperando>0){
            int temp = station->passageiros_esperando - station->assentos_disponiveis;
            station->passageiros_autorizados = station->passageiros_esperando - temp;
            station->passageiros_esperando -= station->passageiros_autorizados;
            station->assentos_disponiveis -= station->passageiros_autorizados;
            }
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
 