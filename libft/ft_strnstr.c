/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:07:54 by afontele          #+#    #+#             */
/*   Updated: 2023/12/11 14:11:52 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	l_len;
	char	*b_str;

	b_str = (char *)big;
	l_len = ft_strlen(little);
	i = 0;
	if (*little == 0)
		return (b_str);
	while ((i < len) && (b_str[i] != '\0'))
	{
		j = 0;
		while ((little[j] == b_str[i + j]) && (i + j < len)
			&& (b_str[i + j] != '\0') && (little[j] != '\0'))
			j++;
		if (j == l_len)
			return (b_str + i);
		i++;
	}
	return (0);
}
