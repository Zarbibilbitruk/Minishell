/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:27:05 by afontele          #+#    #+#             */
/*   Updated: 2023/12/11 10:29:39 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem_ptr;
	size_t	total_size;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	total_size = size * count;
	mem_ptr = malloc(total_size);
	if (mem_ptr == NULL)
		return (mem_ptr);
	ft_bzero(mem_ptr, total_size);
	return (mem_ptr);
}
