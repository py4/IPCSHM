OBJS = account.o applier.o bank.o core.o main.o shared_mem.o utils.o validator.o
CC = g++ -lcrypto -pthread
CFLAGS = -c

a.out : $(OBJS)
	$(CC) $(OBJS)

main.o : main.cpp core.h
	$(CC) $(CFLAGS) main.cpp

account.o : account.cpp
	$(CC) $(CFLAGS) account.cpp

applier.o : applier.cpp bank.h shared_mem.h utils.h
	$(CC) $(CFLAGS) applier.cpp

bank.o : bank.cpp account.h
	$(CC) $(CFLAGS) bank.cpp

core.o : core.cpp shared_mem.h transaction.h validator.h applier.h
	$(CC) $(CFLAGS) core.cpp

shared_mem.o : shared_mem.cpp transaction.h
	$(CC) $(CFLAGS) shared_mem.cpp

utils.o : utils.cpp
	$(CC) $(CFLAGS) utils.cpp


clean:
	\rm *.o *~ a.out
