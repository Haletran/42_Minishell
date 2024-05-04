/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:10:30 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/04 15:59:02 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int handle_n_option(char **str, int *i, int *flag)
{
    int check = 1;
    if (!ft_strncmp(str[*i], "-n", 2))
    {
        while (str[1][check] == 'n')
            check++;
        if (check == (int)ft_strlen(str[1]))
        {
            (*flag)++;
            (*i)++;
        }
    }
    return (SUCCESS);
}

int	ft_echo(char **str, t_lst *mnsh)
{
    int		i;
    int		flag;
	(void)mnsh;

    i = 1;
    flag = 0;
    if (!str[1])
    {
        printf("\n");
        return (SUCCESS);
    }
    handle_n_option(str, &i, &flag);
    while (str[i])
    {
        if (str[i + 1] == NULL)
            ft_printf_fd(1, "%s", str[i]);
        else
            ft_printf_fd(1, "%s ", str[i]);
        i++;
    }
    if (flag == 0)
        printf("\n");
    return (SUCCESS);
}
