app: main.o
	gcc sync_car-runner.o -o app

main.o: main.c
	gcc -c sync_car-runner.c

run: app
	./app

clean: 
	rm -f *.o app

.PHONY: run clean
