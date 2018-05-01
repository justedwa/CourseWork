note.o: note.c fnct.h auth.c readIn.c flags.c timestamp.c
	gcc note.c fnct.h auth.c flags.c readIn.c timestamp.c -o note -lcurses
run:
	./note
clean:
	@rm -f note
	@rm -f *.txt
	@rm -f *.nte
	@rm -f *.cfg
