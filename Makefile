objects = src/main.o src/system.o src/auth.o

atm : $(objects)
	cc -o atm $(objects)
.o : src/header.h

clean :
	rm -f $(objects)
