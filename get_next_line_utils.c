/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:27:05 by vsenniko          #+#    #+#             */
/*   Updated: 2024/09/26 12:49:12 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_nl(char *buff)
{
	int	i;

	i = 0;
	while (buff[i] != '\0')
	{
		if (buff[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*init_buf(size_t buff_size)
{
	char	*buff;

	buff = (char *)malloc(buff_size * sizeof(char) + 1);
	if (buff == NULL)
		return (NULL);
	buff[buff_size] = '\0';
	return (buff);
}

char	*transfer_str(char *old, char *buff, size_t buff_size)
{
	char	*saver;
	int		i;
	int		j;

	i = 0;
	while (old != NULL && old[i])
		i++;
	saver = init_buf(buff_size + (size_t) i);
	if (saver == NULL)
		return (NULL);
	i = 0;
	if (old != NULL)
	{
		while (old[i])
		{
			saver[i] = old[i];
			i++;
		}
		free(old);
	}
	j = 0;
	while ((size_t) j < buff_size)
		saver[i++] = buff[j++];
	saver[i] = '\0';
	free(buff);
	return (saver);
}

char	*return_line(char *saver)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	while (saver[i] && saver[i] != '\n')
		i++;
	line = (char *)malloc(i * sizeof(char) + 1);
	if (line == NULL)
		return (line);
	line[i] = '\0';
	i = 0;
	while (saver[i] && saver[i] != '\n')
	{
		line[i] = saver[i];
		i++;
	}
	if (check_nl(saver) == 1)
		line[i] = '\n';
	return (line);
}

char	*reorganise_saver(char *saver)
{
	int		i;
	int		j;
	char	*new_saver;

	i = 0;
	j = 0;
	while (saver[i] != '\n' && saver[i])
		i++;
	if (check_nl(saver) == 1)
		i += 1;
	j = i;
	while (saver[j])
		j++;
	new_saver = (char *)malloc(j * sizeof(char) + 1);
	if (new_saver == NULL)
		return (NULL);
	j = 0;
	while (saver[i])
		new_saver[j++] = saver[i++];
	new_saver[j] = '\0';
	return (new_saver);
}
