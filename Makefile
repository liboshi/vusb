CC = gcc
CFLAGS = -Wall -DLINUX 
PROGS = mass-storage

all:	${PROGS}

mass-storage:	usbip.c mass-storage.c 
		${CC} ${CFLAGS} usbip.c -c 
		${CC} ${CFLAGS} usbip.o mass-storage.c -o mass-storage 

clean:
		rm -f ${PROGS} core core.* *.o temp.* *.out typescript*
