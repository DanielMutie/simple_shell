# Simple Shell Project

This is a simple shell project that implements a basic command line interpreter in the style of a UNIX shell. The shell provides a prompt for the user to enter commands and executes them. It supports various features such as executing commands with arguments, handling the PATH environment variable, built-in commands like `exit` and `env`, and more.

## Compilation

To compile the shell, use the following command:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive Mode

Run the shell in interactive mode by executing the compiled binary:

```bash
$ ./hsh
($) /bin/ls
file1.txt file2.txt directory
($) exit
$
```

### Non-Interactive Mode

You can also run the shell in non-interactive mode by passing commands via standard input or by using a file:

```bash
$ echo "/bin/ls" | ./hsh
file1.txt file2.txt directory
$
$ cat command_list.txt
/bin/ls
/bin/ls -l
$ cat command_list.txt | ./hsh
file1.txt file2.txt directory
total 12
-rw-r--r-- 1 user user     0 Aug 21 10:00 file1.txt
-rw-r--r-- 1 user user     0 Aug 21 10:00 file2.txt
drwxr-xr-x 2 user user  4096 Aug 21 10:00 directory
$
```

## Supported Commands and Features

The shell supports the following commands and features:

- Running external commands and displaying their output.
- Executing commands with arguments.
- Handling the PATH environment variable to find executables.
- Built-in `exit` command to exit the shell.
- Built-in `env` command to display the current environment variables.
- `$$` expands to the process ID of the shell.
- `$?` expands to the exit status of the last executed command.
- Handling of comments using `#`.
- Separating commands using `;`.
- Handling of logical operators `&&` and `||`.
- Alias support using the `alias` built-in command.

## Tasks

The project is divided into multiple tasks, each building on the previous one. You can find the implementation details for each task in the respective task files.

## Repo

For more information and code implementation, check out the GitHub repository: [simple_shell](https://github.com/DanielMutie/simple_shell)

## Note

This shell project aims to provide a basic understanding of how shells work and includes a subset of features found in typical UNIX shells. It's designed for educational purposes and may not cover all possible edge cases and features found in professional shells.
