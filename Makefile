.PHONY: build run clean buildrun
.SILENT: build run clean buildrun

build:
	gcc main.c list.c -o find.out

run:
	./find.out

clean:
	rm -f *.out

buildrun: build run

