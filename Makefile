app: sync_car-runner.o sync_car.o
	gcc sync_car-runner.o sync_car.o -o app

sync_car-runner.o: sync_car-runner.c sync_car.h
	gcc -Wall -Wextra -pthread -c sync_car-runner.c

sync_car.o: sync_car.c sync_car.h
	gcc -Wall -Wextra -pthread -c sync_car.c

run: app
	./app

clean: 
	rm -f *.o app

.PHONY: run clean
