/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:27:05 by vsenniko          #+#    #+#             */
/*   Updated: 2024/09/24 18:31:19 by vsenniko         ###   ########.fr       */
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
	node->next = NULL;
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
	return (NULL);
}