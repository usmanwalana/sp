all: csem pc

csem: create_sem.c my_ipc.h
	gcc -o csem create_sem.c

pc: prod_cons.c my_ipc.h
	gcc -o pc prod_cons.c

clean:
	rm -f csem pc
