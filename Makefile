CC=gcc
CFLAGS=-I
DEPS=bola.h jogador.h

compilar:
	@gcc main.c bola.c jogador.c -lGL -lglut -lSOIL -o pong.o
	@echo "Compilado!"
run: compilar
	@echo "Executando Pong."
	@./pong.o
	@echo "Fim."
clean:
	@rm -f *.o
	@echo "Limpo!"
