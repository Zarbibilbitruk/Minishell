/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:17:44 by afontele          #+#    #+#             */
/*   Updated: 2025/04/01 14:41:24 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*mem_ptr;
	size_t			i;

	mem_ptr = s;
	i = 0;
	while (i < n)
	{
		mem_ptr[i] = '\0';
		i++;
	}
}
