/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:10:28 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/18 14:31:54 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(char **str, t_lst *lst)
{
	int		valid;
	char	*old_path;
	char	curr_path[1024];

	old_path = getenv("OLDPWD");
	valid = 0;
	if (!str[1] || !ft_strncmp(str[1], "--", -1))
		chdir(lst->home_path);
	else if (get_nbargs(str) > 2)
	{
		printf("cd : too many arguments\n");
		return (ERROR);
	}
	else if (!ft_strncmp(str[1], "-", 1) && ft_strlen(str[1]) == 1)
	{
		getcwd(curr_path, 1024);
		printf("%s\n", old_path);
		chdir(old_path);
	}
	else
	{
		getcwd(curr_path, 1024);
		ft_strcpy(old_path, curr_path);
		valid = chdir(str[1]);
	}
	if (valid)
		perror(str[1]);
	return (SUCCESS);
}
