# MINISHELL

As beautiful as a shell..

![85%](https://progress-bar.dev/85)

## TO_FIX
- GUILLEMETS 
- REDIRECTIONS infile outfile type not accurate
- HEREDOC not working anymore
- Syntax error if ;; or other behind command
- Echo -n fix 
- jojo | echo $?
- gerer les out et in better because some problem (PIPES block redirection)

## TO_DO

- toutes les redirections de merdes du style : 
    - <infile commands > outfile
    - <<del commands > outfile
    - <<del commands
    - >commands > outfile

// bash lt tous les infiles outfiles
// fork si pipes builtins

## MODIFIACTION bapasqui

- dans ruler pour les exit_codes
- dans redirect_rules pour print les bon messages d'erreur
- create command because found path when shouldn't (unset PATH)
80 / 101 BUITLINS
218 / 423 TOTAL

## Links 

- https://www.gnu.org/software/bash/manual/html_node/Builtin-Index.html
- https://www.gnu.org/software/bash/manual/bash.html
- https://www.linux.org/threads/bash-01-script-basics.37797/#post-143818
- https://www.linux.org/threads/bash-02-%E2%80%93-variables-and-such.38200/
- https://www.linux.org/threads/bash-03-%E2%80%93-command-line-processing.38676/
- https://se.ifmo.ru/~ad/Documentation/Bash_Shell/bash3-CHP-7-SECT-3.html