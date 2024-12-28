.PHONY: build run clean buildrun
.SILENT: build run clean buildrun

build:
	gcc utils.c list.c files.c main.c -o find.out

run:
	./find.out

clean:
	rm -f *.out

buildrun: build run

