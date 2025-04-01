/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tautin-- <tautin--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:07:17 by tautin--          #+#    #+#             */
/*   Updated: 2025/03/28 20:39:40 by tautin--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*init_node(void)
{
    t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->index = 0;
	new->data = NULL;
	new->next = NULL;
	new->previous = NULL;

	return (new);
}

void	append_list(t_node *current, char *input, int i)
{
	t_node	*new;

	new = init_node();
	if (!new)
		return ;
	new->index = i;
	new->data = input;
	if (i != 0)
	{
		new->previous = current;
		current->next = new;
	}
}