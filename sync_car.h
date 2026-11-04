#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

typedef struct station{
    pthread_mutex_t tranca;
    pthread_cond_t carro_chegou;
    pthread_cond_t todos_embarcaram;
    int carro_na_estacao;
    int passageiros_esperando;
    int assentos_disponiveis;
    int passageiros_autorizados;
    int passageiros_embarcados;
}station;

void station_init(station *station){
    pthread_mutex_init(&station->tranca, NULL);
    pthread_cond_init(&station->carro_chegou, NULL);
    pthread_cond_init(&station->todos_embarcaram, NULL);
    station->passageiros_esperando = 0;
    station->assentos_disponiveis = 0;
    station->passageiros_autorizados = 0;
    station->passageiros_embarcados = 0;
    station->carro_na_estacao = 0;
}


void station_load_car(station *station, int count){
    if (station == NULL){
        return;
    }else{
            if(count < 0){
                count = 0;
            }

            pthread_mutex_lock(&station->tranca);
                
            station->carro_na_estacao = 1;
            station->assentos_disponiveis = count;
            pthread_cond_broadcast(&station->carro_chegou);
                
            while((station->assentos_disponiveis > 0 && station->passageiros_esperando > 0) || station->passageiros_autorizados > 0){
                pthread_cond_wait(&station->todos_embarcaram, &station->tranca);
            }

            station->carro_na_estacao = 0;
            station->assentos_disponiveis = 0;

            pthread_mutex_unlock(&station->tranca);
            return;
        }
    }

void station_wait_for_car(station *station){
    if(station != NULL){
        pthread_mutex_lock(&station->tranca);

        station->passageiros_esperando+=1;

            while(station->carro_na_estacao == 0||station->assentos_disponiveis == 0){
                pthread_cond_wait(&station->carro_chegou, &station->tranca);
            }

            station->passageiros_esperando -= 1;
            station->assentos_disponiveis -= 1;
            station->passageiros_autorizados += 1;

        pthread_mutex_unlock(&station->tranca);
        return;

    }else{
        return;
    }
}

void station_on_board(station *station){
    if(station!=NULL){
        pthread_mutex_lock(&station->tranca);
        
        station->passageiros_autorizados -= 1;

        pthread_cond_signal(&station->todos_embarcaram);

        pthread_mutex_unlock(&station->tranca);
    }
}