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
DEMO_TARGET := demo

MAIN_SRC := $(filter-out demo.cpp, $(SRC))
DEMO_SRC := $(filter-out main.cpp, $(SRC))

MAIN_OBJ := $(MAIN_SRC:.cpp=.o)
DEMO_OBJ := $(DEMO_SRC:.cpp=.o)

all: $(TARGET) $(DEMO_TARGET)

$(TARGET): $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(DEMO_TARGET): $(DEMO_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(DEP) $(TARGET) $(DEMO_TARGET)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

valgrind-demo:
	valgrind --leak-check=full --show-leak-kinds=all ./$(DEMO_TARGET)

.PHONY: all clean valgrind valgrind-demo