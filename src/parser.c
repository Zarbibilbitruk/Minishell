/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tautin-- <tautin--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:39:14 by tautin--          #+#    #+#             */
/*   Updated: 2025/04/08 19:08:02 by tautin--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		correct_input(char *s)
{
	/*
	lexer essentiellement
	*/
}

static t_commande	*init_control(void)
{
	t_commande	*new;

	new = malloc(sizeof(t_commande));
	if(!new)
		return (NULL);
	new->first = NULL;
	new->last = NULL;
	new->nb_instruction = 0;
	return (new);
}

t_commande	*parser(char *input)
{
	char **inputs;
	int i;
	t_node	*node;
	t_commande	*control;

	inputs = ft_split(input, ' ');
	if (!inputs)
		return ;
	i = 0;
	control = init_control();
	if (!control)
		return (NULL);
	node = init_node();
	if (!node)
		return (NULL);
	while (inputs[i])
	{
		if(correct_input(inputs[i])) //fonction a faire
			append_list(node, inputs[i], i, control);
		i++;
	}
	append_list(node, NULL, i, control);
	control->nb_instruction = i;
	return (control);
}

