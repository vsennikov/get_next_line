/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:27:05 by vsenniko          #+#    #+#             */
/*   Updated: 2024/09/24 14:35:07 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

t_list	*init_new(size_t buff_size)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->buff = malloc(buff_size * sizeof(char) + 1);
	if (node->buff == NULL)
		return (NULL);
	node->buff[buff_size] = '\0';
	return (node);
}

void	*free_lst(t_list **lst)
{
	t_list	*tmp;
	t_list	*current;

	current = *lst;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		free(tmp->buff);
		free(tmp);
	}
	lst = NULL;
	return (NULL);
}

int	check_for_nl_end(char *buff, size_t buff_size)
{
	size_t	i;

	i = 0;
	while (buff[i] != '\0')
	{
		if (buff[i] == '\n')
			return (1);
		i++;
	}
	if (i != buff_size)
		return (2);
	return (0);
}

char	*get_line(t_list **lst, size_t buff_size)
{
	char	*line;
	int		i;
	int		y;
	t_list	*current;

	current = *lst;
	i = 0;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	line = malloc(i * buff_size + 1);
	if (line == NULL)
		return (NULL);
	current = *lst;
	y = 0;
	while (current != NULL)
	{
		i = 0;
		while (current->buff[i] != '\0')
		{
			if (current->buff[i] == '\n')
			{
				line[y] = '\n';
				y++;
				line[y] = '\0';
				return (line);
			}
			line[y] = current->buff[i];
			y++;
			i++;
		}
		current = current->next;
	}
	line[y] = '\0';
	free_lst(lst);
	return (line);
}

char	*add_to_node(t_list **lst, int fd, size_t buff_size)
{
	t_list	*node;
	int		check_flag;

	check_flag = 0;
	while (check_flag != 1 && check_flag != 2)
	{
		node = init_new(buff_size);
		if (node == NULL)
			return (free_lst(lst));
		read(fd, node->buff, buff_size);
		ft_lstadd_back(lst, node);
		check_flag = check_for_nl_end(node->buff, buff_size);
	}
	return (get_line(lst, buff_size));
}
