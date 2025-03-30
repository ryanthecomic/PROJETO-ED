# Compilador
CC = gcc
# Opções de compilação
CFLAGS = -Wall -Wextra -Iinclude
# Diretórios
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
# Arquivos fonte
SRCS = $(SRC_DIR)/materia_ppc.c $(SRC_DIR)/grade_oferta.c $(SRC_DIR)/main.c
# Arquivos objeto
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)
# Nome do executável
TARGET = $(BIN_DIR)/programa

# Regra padrão
all: $(BIN_DIR) $(TARGET)

# Cria o diretório bin se não existir
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Liga os objetos para criar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Compila cada arquivo fonte para objeto
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa os arquivos gerados
clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean