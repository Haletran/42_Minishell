# MINISHELL

As beautiful as a shell..

![80%](https://progress-bar.dev/80)

## TO_FIX
- Leaks if ./minishell is launched in minishell
- heredoc with pipes (looping indefinitely)
- Need to do the redirections of output and input
- Simple quotes and double quotes
- Echo built-ins might need to change to accomodate parsing
- Parsing to get better input and output
- Exit code of commands
- Right exit error message (instead of error)
- Env built-in parsing
- Fix heredoc not one after the others

## TO_DO

For execve :
    - need a have the path of the command
    - need to have the command with his args
exemple : cat Makefile
    /usr/bin/cat (check_path function)
    cat Makefile



