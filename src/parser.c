/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tautin-- <tautin--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:39:14 by tautin--          #+#    #+#             */
/*   Updated: 2025/03/28 19:52:35 by tautin--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    parser(char *input)
{
	char **inputs;
	int i;	

	inputs = ft_split(input, ' ');
	if (!inputs)
		return ;
	i = 0;
	while (inputs[i])
	{
		if(correct_input(inputs[i])) //fonction a faire
		{
			ft_calloc()
		}
		i++;
	}
}