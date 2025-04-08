/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tautin-- <tautin--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:07:17 by tautin--          #+#    #+#             */
/*   Updated: 2025/04/08 19:06:22 by tautin--         ###   ########.fr       */
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

void	append_list(t_node *current, char *input, int i, t_commande *control)
{
	t_node	*new;

	new = init_node();
	if (!new)
		return ;
	if (i == 0 && input != NULL)
	{
		current->data = input;
		current->index = 0;
		control->first = current;
	}
	else if (input != NULL)
	{
		current->next = new;
		new->data = input;
		new->previous = current;
		new->index = i;
	}
	else
	{
		current->next = new;
		new->previous = current;
		new->index = i;
		control->last = new;
	}
}
