all:
	g++ boundary.cpp CN.cpp domain.cpp FTCS.cpp main.cpp settings.cpp sourceterm.cpp -o solver

clean:
	rm -f solver
