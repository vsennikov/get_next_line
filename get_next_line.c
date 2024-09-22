/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:10:49 by vsenniko          #+#    #+#             */
/*   Updated: 2024/09/22 17:38:01 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		*line;
	size_t			buff_s;
	static char		*buffer;
	int				bytes_readed;

	buff_s = BUFFER_SIZE;
	buffer = (char *)malloc(buff_s * sizeof(char) + 1);
	if (buffer == NULL)
		return (NULL);
	buffer[buff_s] = '\0';
	bytes_readed = read(fd, buffer, buff_s);
	line = read_form_buff(buffer, line);
	if (line == NULL)
		return (NULL);
	return (line);
}

