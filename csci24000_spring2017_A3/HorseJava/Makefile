

JAVAC=javac
sources = $(wildcard *.java)
classes = $(sources:.java=.class)

all: $(classes)

run:
	java Game
clean :
	rm -f *.class

%.class : %.java
	$(JAVAC) $<
