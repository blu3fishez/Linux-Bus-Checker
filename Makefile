all : server client program showtime reserve
program : system.c
	cc -o program system.c
showtime : showtime.c
	cc -o showtime showtime.c
reserve : reserve.c
	cc -o reserve reserve.c
client : client.c
	cc -o client client.c
server : server.c
	cc -o server server.c
