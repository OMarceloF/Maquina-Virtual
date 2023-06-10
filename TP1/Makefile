all: main.o cpu.o gerador.o operacoes.o
	@gcc main.o cpu.o gerador.o operacoes.o -o exe
	rm -r *.o

main.o: main.c
	@gcc main.c -c -Wall

cpu.o: cpu.c
	@gcc cpu.c -c -Wall

gerador.o: gerador.c
	@gcc gerador.c -c -Wall

operacoes.o: operacoes.c operacoes.h
	@gcc operacoes.c -c -Wall

run:
	@./exe