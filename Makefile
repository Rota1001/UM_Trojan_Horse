CXX = g++

CXXFLAGS = -I./include

TARGET = bin/UM.dll

SRCS = $(wildcard src/*.cpp)

OBJS = $(SRCS:src/%.cpp=build/%.o)

all: build bin $(TARGET) 

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -shared -o $(TARGET) $(OBJS) -lpsapi -lwinmm

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q build\* bin\*

bin:
	if not exist bin mkdir bin

build:
	if not exist build mkdir build