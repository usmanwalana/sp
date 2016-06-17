all: csem cshm rshm wshm

csem: create_sem.c my_ipc.h
	gcc -o csem create_sem.c

cshm: create_shm.c my_ipc.h
	gcc -o cshm create_shm.c

rshm: read_shm.c my_ipc.h
	gcc -o rshm read_shm.c

wshm: write_shm.c my_ipc.h
	gcc -o wshm write_shm.c

clean:
	rm csem cshm rshm wshm


