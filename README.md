# MINISHELL

As beautiful as a shell..

![87%](https://progress-bar.dev/93)
![Progress](https://progress-bar.dev/425/?title=Tester&scale=473&width=100)

## TO_FIX
- Syntax error if ;; or other behind command
- SIGSEV if not closed quotes/dquotes
- leaks if path command like /usr/bin/ls
- cat | ls (not giving the prompt back)

# LEAKS

```
[~] MINISHELL > export test=/usr/bin/ls
[~] MINISHELL > $test
==264994== 12 bytes in 1 blocks are definitely lost in loss record 3 of 64
==264994==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==264994==    by 0x115BE1: ft_strdup (in /data/MINISH/minishell)
==264994==    by 0x10E4EE: fill_command (create_command.c:57)
==264994==    by 0x10E861: create_command (create_command.c:114)
==264994==    by 0x11346C: parsing_organiser (organizer.c:27)
==264994==    by 0x10A3AB: render_prompt (main.c:37)
==264994==    by 0x10A4D7: main (main.c:57)
==264994== 
```




## Links 

- https://www.gnu.org/software/bash/manual/html_node/Builtin-Index.html
- https://www.gnu.org/software/bash/manual/bash.html
- https://www.linux.org/threads/bash-01-script-basics.37797/#post-143818
- https://www.linux.org/threads/bash-02-%E2%80%93-variables-and-such.38200/
- https://www.linux.org/threads/bash-03-%E2%80%93-command-line-processing.38676/
- https://se.ifmo.ru/~ad/Documentation/Bash_Shell/bash3-CHP-7-SECT-3.html