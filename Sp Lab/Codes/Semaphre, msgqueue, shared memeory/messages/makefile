all: mc mp

mc: mcons.c msg_header.h
	gcc -o mc mcons.c

mp: mprod.c msg_header.h
	gcc -o mp mprod.c

clean:
	rm mc mp
