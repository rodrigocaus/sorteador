SRC := sorteador.cpp
BIN := sort
FLAGS := -O2 -std=c++11 -Wall -Wextra -Wpedantic

AVALIADORES :=avaliadores.psger
CANDIDATOS :=candidatos_ra.psger
ACR := 3

all: $(BIN)

$(BIN): $(SRC)
	g++ $^ -o $@ $(FLAGS)

test: $(BIN)
	./$(BIN) -e $(AVALIADORES) -c $(CANDIDATOS) -r $(ACR)

clear:
	rm $(BIN)
