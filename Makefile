CXX = g++
CXXFLAGS = -I/home/gfaerny/gf/pro/tng/include -Wall -std=c++17
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = tng

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
