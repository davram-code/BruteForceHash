all: client server slave

client: mainClient.cpp connection.h Config.h connection.cpp Client.h Client.cpp
	g++ -g mainClient.cpp connection.cpp Client.cpp -o mainClient -std=c++11 -lpthread  -lcrypto
server: mainServer.cpp connection.cpp Message.cpp Message.h connection.h TaskSupplier.cpp TaskSupplier.h connection.h Utils.h Server.h Server.cpp 
	g++ -g mainServer.cpp Config.h connection.cpp Message.cpp TaskSupplier.cpp Server.cpp -o mainServer -std=c++11 -lpthread -lcrypto
slave: mainSlave.cpp Config.h Slave.cpp Slave.h Message.cpp Message.h connection.cpp connection.h Utils.h
	g++ -g mainSlave.cpp connection.cpp Message.cpp Slave.cpp -o mainSlave -std=c++11 -lpthread -lcrypto

clean:
	-rm mainClient mainServer mainSlave
