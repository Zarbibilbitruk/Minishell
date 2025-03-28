/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:16:16 by afontele          #+#    #+#             */
/*   Updated: 2023/12/11 14:21:09 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	if (!s1 || !set)
		return (0);
	j = 0;
	while (s1[j] && ft_strchr(set, s1[j]))
		j++;
	i = ft_strlen(s1 + j);
	while (i > 0 && ft_strchr(set, s1[j + i - 1]))
		i--;
	return (ft_substr(s1, j, i));
}
