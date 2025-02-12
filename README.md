# find
A (partial) find rewrite in C

## Use cases

### 1 - Call without arguments

Should print all files and directories in working directory recursively.

### 2 - Call with parameter -n

Should print all files where the given parameter name matches (regex) the file name.

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