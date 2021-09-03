/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 10:39:39 by mdiallo           #+#    #+#             */
/*   Updated: 2021/02/02 10:40:45 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char				*ft_check_read(char *readline, char **line, int value_read)
{
	unsigned int	index;
	char			*tmp;

	index = 0;
	while (readline[index])
	{
		if (readline[index] == '\n')
			break ;
		index++;
	}
	if (index < ft_strlen(readline))
	{
		*line = ft_substr(readline, 0, index);
		tmp = ft_substr(readline, index + 1, ft_strlen(readline));
		free(readline);
		readline = ft_strdup(tmp);
		free(tmp);
	}
	else if (value_read == 0)
	{
		*line = readline;
		readline = NULL;
	}
	return (readline);
}

char				*ft_read(char *buffer, char *readline)
{
	char			*tmp;

	if (readline)
	{
		tmp = ft_strjoin(readline, buffer);
		free(readline);
		readline = ft_strdup(tmp);
		free(tmp);
	}
	else
		readline = ft_strdup(buffer);
	return (readline);
}

int					get_next_line(int fd, char **line)
{
	static char		*readline[4096];
	char			buffer[BUFFER_SIZE + 1];
	int				value_read;

	while ((value_read = read(fd, buffer, BUFFER_SIZE)))
	{
		if (value_read == -1)
			return (-1);
		buffer[value_read] = '\0';
		readline[fd] = ft_read(buffer, readline[fd]);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (value_read <= 0 && !readline[fd])
	{
		*line = ft_strdup("");
		return (value_read);
	}
	readline[fd] = ft_check_read(readline[fd], line, value_read);
	if (value_read <= 0 && !readline[fd])
		return (value_read);
	return (1);
}
