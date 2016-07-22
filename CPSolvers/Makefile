CC=			g++ #macro CC is the C compiler to use
CFLAGS=		-std=c++14 -O3 #-lboost_regex #-O3 #-I #CFLAGS is the list of flags to pass to the compilation command
INCLUDE = #-L/usr/lib/x86_64-linux-gnu
DEPS=		BackTrack.hpp BackTrackGbj.hpp Control.hpp fileHandler.hpp ForwardChecking.hpp headers.hpp KcolorDomainDeletion.hpp KcolorGraphNode.hpp KcolorGraphProblem.hpp MinimalForwardChecking.hpp
OBJS =		KcolorGraphNode.o KcolorGraphProblem.o BackTrack.o ForwardChecking.o MinimalForwardChecking.o BackTrackGbj.o FileHandler.o Control.o main.o
TARGET =	CPSolvers

#rule to specify the dependence of cpp file from .h files.
%.o: %.cpp 
	$(CC) -c -o $@ $< $(CFLAGS)
	
$(TARGET): $(OBJS)
	$(CC) $(INCLUDE) -o $@ $^ $(CFLAGS)
	
all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
	