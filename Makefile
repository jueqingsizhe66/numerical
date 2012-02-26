all:
	g++ boundary.cpp CN.cpp domain.cpp FTCS.cpp main.cpp settings.cpp sourceterm.cpp show_sample.cpp mat_ops.cpp Jacobi.cpp -o solver

clean:
	rm -f solver
