###########################################################

## Make variables ##

# Target executable name:
EXE = TEST_AMR

##########################################################

## Project file structure ##

# Source file directory:
SRC_DIR = src

# Object file directory:
OBJ_DIR = bin

# Include header file diretory:
INC_DIR = include

##########################################################

## File list ##

# Source files.
SRCS = main.cpp $(SRC_DIR)/Point.cpp

# Include files.
INC_DIRS = $(INC_DIR)/Control.h $(INC_DIR)/Point.h $(INC_DIR)/Node.h $(INC_DIR)/AMR_Tree.h $(INC_DIR)/Static_Mesh_Tree.h

# Object files:
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/Point.o

##########################################################

## CC COMPILER OPTIONS ##

# CC compiler options:
CC=g++
CC_FLAGS= -std=c++11
#CC_FLAGS=-std=c++11 -mcmodel=medium
CC_LIBS=

##########################################################


## Compile ##

# Link c++ compiled object files to target executable:
$(EXE) : $(OBJS)
	$(CC) $(CC_FLAGS) $(OBJS) -o $@

# Compile main .cpp file to object files:
$(OBJ_DIR)/%.o : %.cpp
	$(CC) $(CC_FLAGS) -c $< -o $@

# Compile C++ source files to object files:
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(CC_FLAGS) -c $< -o $@


.PHONY: clean
# Clean objects in object directory.
clean:
	rm -f $(OBJ_DIR)/* *.o $(EXE) $(EXE).*

















