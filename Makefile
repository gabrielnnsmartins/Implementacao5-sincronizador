app: sync_car-runner.o
	gcc sync_car-runner.o -o app

sync_car-runner.o: sync_car-runner.c
	gcc -Wall -Wextra -pthread -c sync_car-runner.c

run: app
	./app

clean: 
	rm -f *.o app

.PHONY: run clean
