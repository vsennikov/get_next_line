/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:10:49 by vsenniko          #+#    #+#             */
/*   Updated: 2024/09/26 12:26:27 by vsenniko         ###   ########.fr       */
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

char	*init_buf(size_t buff_size, int call)
{
	char	*buff;

	buff = (char *)malloc((buff_size * call) * sizeof(char) + 1);
	if (buff == NULL)
		return (NULL);
	buff[buff_size * call] = '\0';
	return (buff);
}

char	*transfer_str(char *old, char *buff, int call, size_t buff_size)
{
	char	*saver;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (old != NULL && old[i])
		i++;
	saver = init_buf(buff_size + (size_t) i, 1);
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
	while (j < buff_size)
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
	while (saver[i] != '\n' && saver[i])
		i++;
	line = (char *)malloc(i * sizeof(char) + 1);
	if (line == NULL)
		return (line);
	line[i] = '\0';
	i = 0;
	while (saver[i] != '\n' && saver[i])
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

char	*read_file(int fd, size_t buff_size, char **saver)
{
	int		found_nl;
	int		end_of_file;
	char	*buff;
	int		call;
	char	*line;

	call = 1;
	found_nl = 0;
	end_of_file = -1;
	while (found_nl != 1 && end_of_file != 0)
	{
		buff = init_buf(buff_size, 1);
		if (buff == NULL)
			return (NULL);
		end_of_file = read(fd, buff, buff_size);
		found_nl = check_nl(buff);
		if (end_of_file != 0)
		{
			*saver = transfer_str(*saver, buff, call, end_of_file);
			if (*saver == NULL)
				return (NULL);
		}
		else
			free(buff);
		call++;
	}
	line = return_line(*saver);
	*saver = reorganise_saver(*saver);
	return (line);
}

char	*get_next_line(int fd)
{
	size_t			buff_s;
	static char		*saver;
	char			*line;

	buff_s = BUFFER_SIZE;
	line = NULL;
	if (fd < 0 || buff_s == 0 || read(fd, line, 0) == -1)
		return (NULL);
	line = read_file(fd, buff_s, &saver);
	if (line[0] == '\0')
	{
		return (NULL);
		free (line);
	}
	return (line);
}
