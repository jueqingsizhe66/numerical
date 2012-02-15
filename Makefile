all:
	g++ boundary.cpp CN.cpp domain.cpp FTCS.cpp main.cpp settings.cpp sourceterm.cpp show_sample.cpp -o solver

clean:
	rm -f solver
