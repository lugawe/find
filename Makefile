
build:
	gcc main.c -o find.out

run:
	./find.out

clean:
	rm -f find.out

buildrun: build run

