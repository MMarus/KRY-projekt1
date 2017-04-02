CC=g++ -std=c++11
CFLAGS= -c -Wall
LDFLAGS= -lgmpxx -lgmp -lssl -lcrypto -fexceptions
SOURCES= main.cpp Communicator.cpp IO.cpp DiffieHellman.cpp AES.cpp Hash.cpp FFS.cpp Client.cpp Server.cpp
OBJECTS= $(SOURCES:.cpp=.o)
EXECUTABLE= KRY_projekt1

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o $(EXECUTABLE) fromClient fromServer
