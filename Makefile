CC=g++
CFLAGS= -std=c++11
EXECUTABLE=econf
default:
	$(CC) econf.cpp $(CFLAGS) -o $(EXECUTABLE)
run:
	$(CC) econf.cpp $(CFLAGS) -o $(EXECUTABLE) && ./$(EXECUTABLE)
