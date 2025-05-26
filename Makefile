# Nome do executável
EXEC = programa

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -O2

# Arquivos-fonte
SRCS = main.c matAdj.c cityFunctions.c progMod.c

# Arquivos-objeto (substitui .c por .o)
OBJS = $(SRCS:.c=.o)

# Regra principal
all: $(EXEC)

# Como compilar o executável
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

# Regra para limpar arquivos compilados
clean:
	rm -f $(OBJS) $(EXEC)

# Regra para rodar o programa
run: $(EXEC)
	./$(EXEC) 
