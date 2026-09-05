# Amira Ajanaku (25111699)
# Senzo Lukhele (24691497)
# Jay Macaskill (25198387)

# COS 214 (Software Modelling) Practical 4
# Last Modified: 5 September 2026

# Makefile

CXX := g++
CXXFLAGS := -std=c++11 -Wall -g

SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)
DEP := $(OBJ:.o=.d)
TARGET := taskforge

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) $(DEP)

valgrind:
	valgrind ./$(TARGET)

gdb:
	gdb ./$(TARGET)

.PHONY: all clean valgrind