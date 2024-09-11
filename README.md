# Minishell

==> Project made in collaboration with [@Aska](https://github.com/Askandrie)

## Project Overview

Minishell is a simple shell program written in C that aims to replicate the basic functionalities of the Bash shell. This project is developed as a part of the curriculum at 42 School, adhering to the NORM V3 coding standards. Minishell provides an interactive command-line interface for users to execute various shell commands.

## Features

- Recreation of builtins commands such as `ls`, `echo`, `pwd`, `cd`, `env`, `export`, `unset`, and `exit`.
- Handling of environment variables.
- Support for input/output redirection.
- Implementation of pipes to allow command chaining.
- Signal handling (e.g., `Ctrl+C` to interrupt processes).
- Command history using up and down arrow keys.
- Error handling and informative messages for invalid commands or syntax.

## Installation

1. Clone the repository:
  ```
git clone https://github.com/Haletran/42_Minishell
```

## Usage

To start the Minishell, simply run the compiled executable:

```
./minishell
```
You will be presented with a prompt where you can type and execute commands, similar to how you would in Bash. For example:

```sh
minishell$ ls -l
minishell$ pwd
minishell$ cd /path/to/directory
minishell$ echo "Hello, World!"
minishell$ export MY_VAR=value
minishell$ env
minishell$ unset MY_VAR
minishell$ cat < input.txt > output.txt
minishell$ command1 | command2
minishell$ exit
```
## Project Structure

- src/ : Contains the source code files for the Minishell program.
- include/ : Contains the header files.
- Makefile : The makefile to build the project.

## Code Style
The project adheres to the NORM V3 coding standards as specified by 42 School. I know i know...

