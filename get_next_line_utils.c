/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:27:05 by vsenniko          #+#    #+#             */
/*   Updated: 2024/09/22 17:37:49 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_form_buff(char *buf, char *line)
{
	int	i;

	i = 0;
	while (buf[i] != '\0' && buf[i] != '\n')
		i++;
	line = (char *)malloc(i * sizeof(char) + 2);
	if (line == NULL)
		return (NULL);
	line[i + 1] = '\0';
	i = 0;
	while (buf[i] != '\0' && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
		line[i] = '\n';
	return (line);
}