#llama a object para generar los .o antes unir los objetos en el ejecutable 

all: 

	g++ -c -std=c++14 KcolorGraphNode.cpp KcolorGraphProblem.cpp BackTrack.cpp main.cpp ForwardChecking.cpp MinimalForwardChecking.cpp FileHandler.cpp BackTrackGbj.cpp Control.cpp 
	g++ -o CPSolvers  KcolorGraphNode.o KcolorGraphProblem.o BackTrack.o ForwardChecking.o MinimalForwardChecking.o BackTrackGbj.o FileHandler.o Control.o main.o

#define clean
clean:
#-r: recursive -f force *.o todos los .o *~ borrar todos los temporales, tambien borra el ejecutable
	rm -rf *.o *~ CPSolvers 
