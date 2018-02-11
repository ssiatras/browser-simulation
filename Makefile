CC=gcc
CFLAGS=
OBJECTS= browser_simulation.o session.o tab.o site.o

browser_simulation: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o browser_simulation

browser_simulation.o: browser_simulation.c
	$(CC) $(CFLAGS) -c browser_simulation.c

site.o: site.c
	$(CC) $(CFLAGS) -c site.c

tab.o: tab.c
	$(CC) $(CFLAGS) -c tab.c

session.o: session.c
	$(CC) $(CFLAGS) -c session.c


.PHONY: clean

clean:
	rm -f browser_simulation $(OBJECTS)