all:
	g++ boundary.cpp SOR.cpp GS.cpp CN.cpp domain.cpp FTCS.cpp main.cpp settings.cpp sourceterm.cpp show_sample.cpp Jacobi.cpp -o solver

clean:
	rm -f solver
