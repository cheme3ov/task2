CXXFLAGS = ${CFLAGS} -std=c++11

all: task2
	
task1:
	g++ task2.cpp -o task2 ${CXXFLAGS}

clean:
	rm task2

.PHONY: all clean
