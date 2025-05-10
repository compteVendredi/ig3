SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = ./include/
LIB_DIR = ./lib/

CXX = g++
CXXFLAGS = -Wall -std=c++17 -I$(INCLUDE_DIR) -L$(LIB_DIR)
LIBS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

SRC = $(wildcard $(SRC_DIR)/*)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXEC = $(BIN_DIR)/projet

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(EXEC)
