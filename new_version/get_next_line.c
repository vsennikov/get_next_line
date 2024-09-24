/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:10:49 by vsenniko          #+#    #+#             */
/*   Updated: 2024/09/24 19:40:15 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_for_nl(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

t_list	*save_rest(char *buffer, t_list *left, int position)
{
	int	i;
	int	j;

	i = 0;
	j = position;
	while (buffer[j++])
		i++;
	left = init_new((size_t) i);
	if (left == NULL)
		return (NULL);
	i = 0;
	while (buffer[position])
		left->buff[i++] = buffer[position++];
	return (left);
}

char	*return_line(t_list **lst, size_t buff_size)
{
	int		lst_size;
	int		i;
	t_list	*curreent;
	char	*line;
	int		j;

	lst_size = ft_lstsize(*lst);
	i = 0;
	j = 0;
	curreent = *lst;
	line = malloc(lst_size * buff_size);
	if (line == NULL)
		return (NULL);
	while (lst_size - 1 != 0)
	{
		while (curreent->buff[j])
			line[i++] = curreent->buff[j++];
		curreent = curreent->next;
		lst_size -= 1;
	}
	j = 0;
	while (curreent->buff[j] != '\n' && curreent->buff[j] != '\0')
		line[i++] = curreent->buff[j++];
	line[i] = '\0';
	return (line);
}

char	*read_and_save(int fd, size_t buff_size, t_list **lst, t_list *left)
{
	t_list	*node;
	int		found_new_line;
	int		end_of_file;
	char	*line;

	found_new_line = 0;
	node = init_new(buff_size);
	if (node == NULL)
		return (NULL);
	end_of_file = 1;
	while (found_new_line != -1 && end_of_file != 0)
	{
		end_of_file = read(fd, node->buff, buff_size);
		//check if we have found \n
		found_new_line = check_for_nl(node->buff);
		ft_lstadd_back(lst, node);
		if (found_new_line != -1)
			//func to save rest into static
			left = save_rest(node->buff, left, found_new_line);
	}
	//func to return string from list
	line = return_line(lst, buff_size);
	//next func to clean lst
	free_lst(lst);
	return (line);
}

char	*get_next_line(int fd)
{
	static int		flag;
	static t_list	*left;
	t_list			*lst;
	size_t			buff_s;
	char			*line;

	buff_s = BUFFER_SIZE;
	line = NULL;
	left = NULL;
	lst = left;
	flag = 0;
	if (fd < 0 || buff_s == 0 || read(fd, line, 0) == -1)
		return (NULL);
	//left doesnt save the value from previous call. Why? 
	line = read_and_save(fd, buff_s, &lst, left);
	flag += 1;
	return (line);
}
