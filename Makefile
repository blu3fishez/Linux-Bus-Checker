all : program execute client server
remove :
	rm program
	rm execute
	rm client
	rm server
program : system.c set_ticker.c getch.c
	cc -o program system.c set_ticker.c getch.c
execute : execute.c
	cc -o execute execute.c
client : client.c
	cc -o client client.c
server : server.c
	cc -o server server.c
