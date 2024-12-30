ramc: ramc.c
	gcc -o ramc ramc.c -lm

DESTDIR=/usr/local/bin
install:
	cp ramc $(DESTDIR)
	cp ramc.1 /usr/share/man/man1
	bzip2 -f /usr/share/man/man1/ramc.1
