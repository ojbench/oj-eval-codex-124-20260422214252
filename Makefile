CXX := g++
CXXFLAGS := -O2 -pipe -std=gnu++17 -static-libgcc -static-libstdc++
LDFLAGS :=

all: code

code: main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f code
