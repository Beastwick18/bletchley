decrypt: main.o crypto.o clock.o schedule.o
	gcc -g main.o crypto.o clock.o schedule.o -lpthread -lcrypto -g -o decrypt --std=c99
    
main.o: main.c
	gcc -D_POSIX_C_SOURCE -Wall -g -c main.c -o main.o
    
crypto.o: crypto.c
	gcc -D_POSIX_C_SOURCE -Wall -g -c crypto.c -o crypto.o
    
clock.o: clock.c
	gcc -D_POSIX_C_SOURCE -Wall -g -c clock.c -o clock.o
    
schedule.o: schedule.c
	gcc -D_POSIX_C_SOURCE -Wall -g -c schedule.c -o schedule.o
   
clean:
	rm *.o decrypt results/* 

check:
	diff results/ plaintext/ -x .gitignore
