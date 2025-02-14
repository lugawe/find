# find
A (partial) find rewrite in C

## Build Process

This project includes a `Makefile` to compile and execute the program efficiently. The following targets are available:

### Building the Program
To compile the source files and generate the executable `find.out`, run:

```bash
make all # or just make
```
This compiles `utils.c`, `list.c`, `files.c`, `filecomp.c`, and `main.c` into `find.out`.

### Running the Programm
Once built, you can execute the program with:
```bash
make run
```

or manually:
```bash
./find.out [directory] [options]
```

### Cleaning Up
To remove the compiled binary and any output files:
```bash
make clean
```
This deletes `find.out` and ensures a clean working directory.

### Building & Running in One Step
To compile and immediately execute the program in one command:
```bash
make buildrun
```
This runs `make all` followed by `make run`.

## Use cases
### 1 - Call without arguments  
Should print all files and directories in working directory recursively.

### 2 - Call with parameter -n
Should print all files where the given parameter name matches (regex) the file name. This option applies only to regular files (f) and directories (d), ignoring other file types like symbolic links or sockets.

### 3 - Call with parameter -t
Should only print files with the same type as the given parameter.

### 4 - Call with parameter -m n
Prints out all files of which has last been modified more than, less than or exact n days ago. With n being a positive integer.

Passing value n requires one of the following formats: +n, -n, or n.

### 5 - Call with parameter -e command
Executes the specified command for all found files. For example calling with "-e cat" prints the content of all found files. 

### 6 - Call with parameter -s n
Should only print files with file size of n bytes.

### 7 - Call with parameter -d n
Should only print files which are n subdirectories deep.

### 8 - Call with parameter -p
Should only print files that match the given path pattern. The parameter expects a valid file path pattern and filters the results accordingly.

### 9 - Call with parameter -o value
Sorts files using a linked list according to parameter value.

### 10 - Call with parameter -c
Prints the number of found files and directories instead of them themself.

### 11 - Call with parameter -u username
Prints only Files owned by user username.

### 12 - Call with parameter -h
Print a summary of the command-line usage of the command and exit.


Passing parameter requires one of the following values: 'name' or 'type'.

## Running Tests

The `Makefile` includes test cases to validate the program's functionality. 

To run all tests:

```bash
make test_all
```
To run individual tests:
```bash
make test_no_args      # Test: No arguments
make test_name         # Test: File name filter (-n)
make test_type         # Test: File type filter (-t)
make test_m            # Test: Modified time filter (-m)
make test_e            # Test: Execute command (-e)
make test_s            # Test: File size filter (-s)
make test_d            # Test: Directory depth filter (-d)
make test_n_t_e        # Test: Combination (-n "*.c" -t "f" -e cat)
```
