/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:12:31 by afontele          #+#    #+#             */
/*   Updated: 2023/12/11 14:39:32 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			str = &((char *)s)[i];
		i++;
	}
	if (c == '\0')
		str = &((char *)s)[i];
	return (str);
}
