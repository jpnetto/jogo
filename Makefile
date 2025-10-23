CC = gcc 
CFLAGS = -Wall -std=c99     #Usando isso só para confirmar que os warnings vao aparecer e garantir que o codigo vai rodar na versão mais recente, que é o c99
TARGET = jogo     #nome do nosso executável 
OBJS = main.o snake.o janela.o     #aqui é a lista de arquivos que vão ser ligados para formar o executável
RAYLIB = -lm -lraylib

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(RAYLIB)

main.o: main.c snake.h
	$(CC) $(CFLAGS) -c main.c

snake.o: snake.c snake.h
	$(CC) $(CFLAGS) -c snake.c

janela.o: janela.c janela.h
	$(CC) $(CFLAGS) -c janela.c

run: $(TARGET)
	./jogo

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all run clean #Isso aqui é só para indicar que all run e clean não sao arquivos
