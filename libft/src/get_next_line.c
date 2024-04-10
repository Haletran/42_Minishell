/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:59:29 by ygaiffie          #+#    #+#             */
/*   Updated: 2023/12/27 11:51:40 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*residual[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (NULL);
	if (residual[fd] == NULL)
	{
		residual[fd] = ft_calloc(1, 1);
		if (!residual[fd])
			return (NULL);
	}
	residual[fd] = ft_read(fd, residual[fd]);
	if (!residual[fd])
		return (ft_free(residual[fd]));
	if (residual[fd][0] == 0)
	{
		free(residual[fd]);
		residual[fd] = NULL;
		return (NULL);
	}
	line = ft_substr(residual[fd], 0, ft_strlen_endc(residual[fd], '\n') + 1);
	if (line == 0)
		return (ft_free(residual[fd]));
	residual[fd] = fill_bucket(residual[fd]);
	return (line);
}

char	*ft_read(int fd, char *static_buffer)
{
	int		bytes_read;
	char	*buffer;

	bytes_read = -1;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	while (bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (ft_free(static_buffer));
		}
		buffer[bytes_read] = 0;
		static_buffer = ft_strjoin_f(static_buffer, buffer);
		if (static_buffer == NULL)
			return (ft_free(buffer));
		if (ft_strchr(buffer, '\n') != 0 || bytes_read < BUFFER_SIZE)
			break ;
	}
	free(buffer);
	return (static_buffer);
}

char	*fill_bucket(char *buffer)
{
	int		i;
	char	*mod_bucket;
	char	*mod_buffer;

	i = 1;
	if (buffer != NULL)
	{
		mod_buffer = ft_strchr(buffer, '\n');
		if (!mod_buffer)
			return (ft_free(buffer));
		while (mod_buffer[i] != '\0')
			i++;
		mod_bucket = ft_substr(mod_buffer, 1, i);
		if (mod_bucket[0] == '\0')
		{
			free(mod_bucket);
			return (ft_free(buffer));
		}
		else
			free(buffer);
		return (mod_bucket);
	}
	ft_free(buffer);
	return (NULL);
}

int	ft_strlen_endc(const char *str, int c)
{
	size_t	i;

	if (str == 0)
		return (0);
	i = 0;
	while (str[i] != 0 && str[i] != c)
		i++;
	return (i);
}
