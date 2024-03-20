# MINISHELL

As beautiful as a shell..


<details><summary>TODO</summary>

## TO-FIX

- [x] Fix when there is space and then enter is press
- [x] Fix double prompt if CTRL+C during command execution
- [x] The MAKE command not working properly
- [x] Exit code to store and can echo with $?
- [x] Make command path working
- [x] PWD command not working properly
- [ ] Return value not valid sometimes
- [x] Make env var working
- [ ] Add pipe (IN CONSTRUCTION)
- [ ] Redirections
- [ ] Parsing
- [x] Sort in ascii when exporting a variable
- [x] Sort in ascii if export without args
- [x] Unset command
- [x] Segfault if $$
- [ ] Exit code and exit function fix 
- [ ] Quotes and double quotes
- [x] Cd with ~

//use open in a fork

## BONUS

- [x] && and & working properly
- [x] wildcard for echo working (echo *)

 </details>

## To keep if needed


 ```C
else if (!ft_strncmp(input, "&&", 2) || !ft_strncmp(input, "& ", 2))
{
	if (!ft_strncmp(input, " & ", 3))
		commands = ft_split(input, '&');
	else if (!ft_strncmp(input, " && ", 4))
		commands = ft_split2(input, "&&");
	exec_and(commands, *args);
}
 ```


```C
t_com	*init_stack(t_com *com, char **str)
{
	t_com	*head;
	int		tmp;

	head = NULL;
	tmp = 0;
	while (tmp != get_nbargs(str))
	{
		if (!com)
		{
			com = ft_lst_new(ft_atoi(str[tmp]), 0);
			head = com;
		}
		else
		{
			while (com && com->next != NULL)
				com = com->next;
			ft_lstadd_back(com, ft_atoi(str[tmp]));
		}
		tmp++;
	}
	com = head;
	return (com);
}

```
