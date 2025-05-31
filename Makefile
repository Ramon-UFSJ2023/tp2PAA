# Nome do compilador e flags
CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11

# Lista de fontes e objetos
SRCS    := main.c cityFunctions.c matAdj.c progMod.c heuristica.c
OBJS    := $(SRCS:.c=.o)

# Arquivo de saída
TARGET  := programa

# Dependências de headers (por segurança, mas o make cuidará automaticamente se um .h mudar)
DEPS    := cityFunctions.h matAdj.h progMod.h heuristica.h structs.h

.PHONY: all clean

all: $(TARGET)

# Regra para gerar o executável a partir dos objetos
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regra genérica para compilar cada .c para .o
# O make vai reconstruir se o .c ou qualquer .h incluído mudar
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)
