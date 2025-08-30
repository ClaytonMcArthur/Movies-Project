# Makefile to build the Movies Project test driver
CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -pedantic

SRC := \
  main.cpp \
  movie.cpp comedy.cpp drama.cpp classics.cpp \
  Customer.cpp CustomerHashTable.cpp \
  Inventory.cpp MovieFactory.cpp \
  BorrowCommand.cpp ReturnCommand.cpp \
  HistoryCommand.cpp InventoryCommand.cpp \
  CommandFactory.cpp \
  Command.cpp

OBJ := $(SRC:.cpp=.o)

BIN := movies_tester

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BIN)

.PHONY: all clean