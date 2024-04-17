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
- Right exit error message (instead of perror)
- Env built-in parsing

## TO_DO

For execve :
    - need a have the path of the command
    - need to have the command with his args
exemple : cat Makefile
    /usr/bin/cat (check_path function)
    cat Makefile

- Commande du demon : ls | echo $PATH | cat
- Fix des pipes avec le heredoc, exemple de fail : << ls | cat
- heredoc avec commands derriere, exemple : << ls cat (copy the output into a file and use it instead of an infile)
- toutes les redirections de merdes du style : 
    - <infile commands > outfile
    - <<del commands > outfile
    - <<del commands
    - >commands > outfile

- Add syntax error

