# Variáveis para os compiladores e flags de compilação
CC = gcc
CFLAGS = -Wall -g
# Nome do executável
EXEC = main

# Arquivos fonte e objeto
SRC = topological_sorting.c fila.c
OBJ = $(SRC:.c=.o)

# Regra padrão
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Como compilar cada arquivo .o a partir de um .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Comando para executar o programa
run:
	./$(EXEC)

# Comando para limpar arquivos compilados
clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all run clean
