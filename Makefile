CC = g++
CFLAGS = -std=c++11 -g -Wall
LIBS = -lboost_serialization -lboost_signals -lboost_thread -lboost_system
OBJS = netaddr.o icommand.o shellcommand.o commandhandler.o commandrecver.o commandsender.o mxsocket.o
all : client server
client : $(OBJS) client.o
	$(CC) $(CFLAGS) -o client $(OBJS) client.o $(LIBS)
server : $(OBJS) server.o
	$(CC) $(CFLAGS) -o server $(OBJS) server.o $(LIBS)
client.o : client.cpp
	$(CC) $(CFLAGS) -c client.cpp
server.o : server.cpp
	$(CC) $(CFLAGS) -c server.cpp
$(OBJS) : %.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
.PHONY : clean
clean :
	rm $(OBJS) client.o server.o client server
