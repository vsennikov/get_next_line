/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:10:49 by vsenniko          #+#    #+#             */
/*   Updated: 2024/09/27 12:17:36 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*free_all(char *saver, char *buffer)
{
	if (buffer == NULL && saver != NULL)
		free(saver);
	else if (saver == NULL && buffer != NULL)
		free(buffer);
	else if (buffer == NULL && saver == NULL)
		return (NULL);
	else
	{
		free(saver);
		free(buffer);
	}
	return (NULL);
}

char	*check_for_end(char *saver, char *line)
{
	if (saver != NULL && saver[0] != '\0')
	{
		line = return_line(saver);
		if (line == NULL)
			return (free_all(saver, NULL));
		saver = reorganise_saver(saver);
	}
	else
	{
		line = NULL;
		if (saver != NULL)
			free(saver);
		saver = NULL;
	}
	return (line);
}

char	*read_file(int fd, size_t buff_size, char **saver, int read_all)
{
	int		found_nl;
	int		end_of_file;
	char	*buff;
	char	*line;

	found_nl = 0;
	end_of_file = -1;
	while (found_nl != 1 && end_of_file != 0)
	{
		buff = init_buf(buff_size);
		if (buff == NULL)
			return (free_all(*saver, buff));
		end_of_file = read(fd, buff, buff_size);
		found_nl = check_nl(buff);
		if (end_of_file != 0)
		{
			*saver = transfer_str(*saver, buff, end_of_file);
			if (*saver == NULL)
				return (free_all(*saver, buff));
		}
		else
			free(buff);
	}
	return (check_for_end(saver, line));
}

char	*get_next_line(int fd)
{
	size_t		buff_s;
	static char	*saver;
	char		*line;
	static int	read_all;

	buff_s = BUFFER_SIZE;
	line = NULL;
	if (fd < 0 || buff_s == 0 || read(fd, line, 0) == -1)
	{
		if (saver != NULL)
		{
			free (saver);
			saver = NULL;
		}
		return (NULL);
	}
	line = read_file(fd, buff_s, &saver, read_all);
	if (line != NULL && line[0] == '\0')
		return (free_all(saver, line));
	else if (line == NULL)
		return (NULL);
	if (read_all)
		free(saver);
	return (line);
}
