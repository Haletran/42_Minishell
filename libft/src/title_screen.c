/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aska <aska@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:45:10 by aska              #+#    #+#             */
/*   Updated: 2024/02/27 20:20:16 by aska             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	title_screen(char *title, char *color)
{
	int			i;
	t_alphanode	*chara;
	t_alphanode	*tmp;

	if (title == NULL)
		return ;
	chara = NULL;
	i = 0;
	while (title[i] != 0)
		title_triage(title[i++], &chara);
	i = 0;
	ft_putstr_fd(color, 1);
	while (i != FONT_ROW)
	{
		tmp = chara;
		while (tmp != NULL)
		{
			ft_putstr_fd(tmp->letter[i], 1);
			tmp = tmp->next;
		}
		ft_putstr_fd("\n", 1);
		i++;
	}
	ft_putstr_fd(CRESET, 1);
	title_freeway(&chara);
}

void	title_triage(char c, t_alphanode **chara)
{
	if ((c >= 65 && c <= 76) || (c >= 97 && c <= 108))
		for_a_to_l(c, chara);
	else if ((c >= 77 && c <= 88) || (c >= 109 && c <= 120))
		for_m_to_x(c, chara);
	else if ((c >= 48 && c <= 59) || (c >= 89 && c <= 90) || (c >= 121
			&& c <= 122))
		for_y_to_9(c, chara);
	else
		for_symbol(c, chara);
}

char	**letter_creation(const char *model)
{
	char	**letter;

	letter = ft_split(model, '\n');
	if (letter == NULL)
		return (NULL);
	return (letter);
}

void	title_freeway(t_alphanode **chara)
{
	t_alphanode	*tmp;
	int			i;

	tmp = *chara;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->letter[i] != NULL)
			free(tmp->letter[i++]);
		free(tmp->letter);
		tmp = tmp->next;
	}
	delete_all_alphanodes(chara);
}
