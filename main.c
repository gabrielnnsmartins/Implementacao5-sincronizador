#include<stdlib.h>
#include<stdio.h>
#include<pthreads>

typedef sctruct station{
    int passageiros_esperando;
    int assentos_disponiveis;
    int passageiros_embarcados;
}station;

station_load_car(station *station, int cont){
    if (station != NULL){
        if (station->assentos_disponiveis == 0){
            return;
        }else{
            cont = passageiros_esperando - assentos_disponiveis;
            station->passageiros_embarcados += station->assentos_disponiveis;
            
        }
    }
}
 