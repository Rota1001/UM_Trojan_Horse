CXX = g++

CXXFLAGS = -I./include

TARGET = bin\UM.dll

SRCS = $(wildcard src/*.cpp)

OBJS = $(SRCS:src/%.cpp=build/%.o)

all: build bin $(TARGET) output

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -shared -o $(TARGET) $(OBJS) -lpsapi -lwinmm

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f build/*.o
	rm -f bin/*.dll
	rm -f output/*

bin:
	if [ ! -d bin ]; then mkdir bin; fi

build:
	if [ ! -d build ]; then mkdir build; fi

output:
	if [ ! -d output ]; then mkdir output; fi 
	cp bin/UM.dll output
