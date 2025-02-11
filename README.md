# find
A (partial) find rewrite in C

## Use cases

### 1 - Call without arguments

Should print all files and directories in working directory recursively.

### 2 - Call with parameter -n

Should print all files where the given parameter name matches (regex) the file name

### 3 - Call with parameter -t

Should only print files with the same type as the given parameter

### 4 - Call with parameter -m n

Prints out all files of which has last been modified less than or more than n days ago. With n being a positive or negative integer.

### 5 - Call with parameter -e command

Executes the specified command for all found files. For example calling with "-exec cat" prints the content of all found files. 