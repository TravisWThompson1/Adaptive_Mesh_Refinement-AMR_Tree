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
SRCS := main.cpp $(SRC_DIRS)/Point.cpp $(SRC_DIRS)/Node.cpp $(SRC_DIRS)/Static_Mesh_Tree.cpp
#OBJS = $(subst .cc,.o,$(SRCS))

# Include files.
INC_DIRS := $(SRC_DIRS)/Control.h $(SRC_DIRS)/Point.h $(SRC_DIRS)/Node.h $(SRC_DIRS)/AMR_Tree.h $(SRC_DIRS)/Static_Mesh_Tree.h

# Object files:
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/cuda_kernel.o

##########################################################

## CC COMPILER OPTIONS ##

# CC compiler options:
CC=g++
CC_FLAGS= -std=c++11 -mcmodel=medium
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
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(INC_DIR)/%.h
	$(CC) $(CC_FLAGS) -c $< -o $@

# Clean objects in object directory.
clean:
	$(RM) bin/* *.o $(EXE)









SRCS := main.cpp $(SRC_DIRS)/Point.cpp $(SRC_DIRS)/Node.cpp $(SRC_DIRS)/Static_Mesh_Tree.cpp
#OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
OBJS = $(subst .cc,.o,$(SRCS))

INC_DIRS := $(SRC_DIRS)/Control.h $(SRC_DIRS)/Point.h $(SRC_DIRS)/Node.h $(SRC_DIRS)/AMR_Tree.h $(SRC_DIRS)/Static_Mesh_Tree.h

CPPFLAGS ?=

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)


# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

MKDIR_P ?= mkdir -p




















