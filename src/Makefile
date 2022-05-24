PROJ_NAME=origem-ps

C_SOURCE=$(wildcard *.cpp)
H_SOURCE=$(wildcard *.hpp)

OBJ=$(C_SOURCE:.cpp=.o)

CC=g++
CC_FLAGS=-c

all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^

%.o: %.cpp %.hpp
	$(CC) -o $@ $< $(CC_FLAGS)

main.o: main.cpp $(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)

clean:
	rm -rf *.o $(PROJ_NAME) *~