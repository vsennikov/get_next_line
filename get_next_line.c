/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:10:49 by vsenniko          #+#    #+#             */
/*   Updated: 2024/09/24 17:01:45 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		*next_line;
	size_t			buff_s;
	char			*line;
	t_list			**lst;
	static t_list	*smt;

	buff_s = BUFFER_SIZE;
	line = NULL;
	//add check for file permission
	if (fd < 0 || buff_s == 0 || read(fd, line, 0) == -1)
		return (NULL);
	smt = NULL;	
	if (smt == NULL)
		*lst = NULL;
	else
		*lst = smt;
	return (add_to_node(lst, fd, buff_s, smt));
}

