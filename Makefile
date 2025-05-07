CC = gcc
SRC_DIR = ./src
BIN_DIR = .

# Targets
TARGETS = vulnerable createdata3 createdata6 createdata9

all: $(TARGETS)

vulnerable: $(SRC_DIR)/hello.c
	$(CC) -o $(BIN_DIR)/vulnerable $<

createdata3: $(SRC_DIR)/createdata3.c
	$(CC) -o $(BIN_DIR)/createdata3 $<

createdata6: $(SRC_DIR)/createdata6.c
	$(CC) -o $(BIN_DIR)/createdata6 $<

createdata9: $(SRC_DIR)/createdata9.c
	$(CC) -o $(BIN_DIR)/createdata9 $<

clean:
	rm -f $(BIN_DIR)/vulnerable $(BIN_DIR)/createdata3 $(BIN_DIR)/createdata6 $(BIN_DIR)/createdata9
	rm -f $(BIN_DIR)/payload3 $(BIN_DIR)/payload6 $(BIN_DIR)/payload9