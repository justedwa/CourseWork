server:
	gcc -o server server.c game.h game.c
client:
	gcc -o client client.c -lcurses
clean:
	rm -f server 
	rm -f client
host:
	./server
RunGame:
	./server & ./client
Snake:
	gcc -o server server.c game.h game.c
	gcc -o client client.c -lcurses
connect:
	./client
