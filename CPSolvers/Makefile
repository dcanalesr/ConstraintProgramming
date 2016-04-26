#llama a object para generar los .o antes unir los objetos en el ejecutable 

all: 

	g++ -c -std=c++11 KcolorGraphNode.cpp KcolorGraphProblem.cpp BackTrack.cpp main.cpp ForwardChecking.cpp
	g++ -o CPSolvers  KcolorGraphNode.o KcolorGraphProblem.o BackTrack.o ForwardChecking.o main.o

#define clean
clean:
#-r: recursive -f force *.o todos los .o *~ borrar todos los temporales, tambien borra el ejecutable
	rm -rf *.o *~ CPSolvers 
