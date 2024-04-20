project = main.c

atm : $(project)
	gcc -o atm $(project)
.o : header.h

clean :
	rm -f $(project)
