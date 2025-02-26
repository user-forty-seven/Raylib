

CC = g++
CFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRC = code/main.cpp
OUT = main

all: $(OUT)

$(OUT): $(SRC)
	$(CC) -o $(OUT) $(SRC) $(CFLAGS)

clean:
	rm -f $(OUT)
