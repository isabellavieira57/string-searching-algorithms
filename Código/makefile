CC     = gcc
CFLAGS = -g -Wall
OBJS = funcoes_auxiliares.o cadeia_caracteres.o tp3.o 
TARGET = tp3

all: $(TARGET)

tp3: $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o tp3
	
tp3.o: tp3.c funcoes_auxiliares.c funcoes_auxiliares.h cadeia_caracteres.c cadeia_caracteres.h
		$(CC) $(CFLAGS) -c tp3.c
	
funcoes_auxiliares.o: funcoes_auxiliares.c funcoes_auxiliares.h
	$(CC) $(CFLAGS) -c funcoes_auxiliares.c
	
cadeia_caracteres.o: cadeia_caracteres.c cadeia_caracteres.h funcoes_auxiliares.c funcoes_auxiliares.h
	$(CC) $(CFLAGS) -c cadeia_caracteres.c
	
tad.o: tad.c tad.h  
	$(CC) $(CFLAGS) -c tad.c
	
clean: 
	rm -rf *.o ./$(TARGET)

