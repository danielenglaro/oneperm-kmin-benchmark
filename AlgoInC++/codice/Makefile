# Nome dell'eseguibile
TARGET = main

# Compiler e flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# File sorgente
SOURCES = FSHashFunction.cpp FastSimilaritySketching.cpp main.cpp

# File oggetto
OBJECTS = $(SOURCES:.cpp=.o)

# Regole
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(TARGET)