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
};

void station_init(struct station *station);


void station_load_car(struct station *station, int count);

void station_wait_for_car(struct station *station);

void station_on_board(struct station *station);