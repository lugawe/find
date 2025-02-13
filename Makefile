.PHONY: build run clean buildrun
.SILENT: build run clean buildrun

all:
	gcc utils.c list.c files.c main.c -o find.out

run:
	./find.out

clean:
	rm -f *.out

buildrun: all run

test_no_args:
	@echo "Running test: No Arguments"
	@./find.out > output.txt
	@if [ -s output.txt ]; then echo "✅ Passed"; else echo "❌ Failed"; fi
	@rm output.txt

test_name:
	@echo "Running test: Name Filter (-n)"
	@./find.out -n "Makefile" > output.txt
	@if grep -q "Makefile" output.txt; then echo "✅ Passed"; else echo "❌ Failed"; fi
	@rm output.txt

test_type:
	@echo "Running test: Type Filter (-t)"
	@./find.out -t "directory" > output.txt
	@if grep -q "/" output.txt; then echo "✅ Passed"; else echo "❌ Failed"; fi
	@rm output.txt

test_m:
	@echo "Running test: Modified Filter (-m 1)"
	@./find.out -m +1 > output.txt
	@if [ -s output.txt ]; then echo "✅ Passed"; else echo "❌ Failed"; fi
	@rm output.txt

test_e:
	@echo "Running test: Execute Command (-e cat)"
	@./find.out -t f -e cat > output.txt 
	@if grep -q "build:" output.txt; then echo "✅ Passed"; else echo "❌ Failed"; fi
	@rm output.txt

test_s:
	@echo "Running test: File Size (-s 10)"
	@./find.out -s 10 > output.txt
	@if [ -s output.txt ]; then echo "✅ Passed"; else echo "❌ Failed"; fi
	@rm output.txt

test_d:
	@echo "Running test: Depth (-d 1)"
	@./find.out -d 1 > output.txt
	@if grep -q "/" output.txt; then echo "✅ Passed"; else echo "❌ Failed"; fi
	@rm output.txt

test_n_t_e:
	@echo "Running test: Name, Type, Exec (-n "*.c" -t "f" -e cat > output.txt)"
	@./find.out -n "*.c" -t "f" -e cat > output.txt
	@if grep -q "/" output.txt; then echo "✅ Passed"; else echo "❌ Failed"; fi
	@rm output.txt

test_all: test_no_args test_name test_type test_m test_e test_s test_d test_n_t_e