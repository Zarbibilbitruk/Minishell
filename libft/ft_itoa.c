/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:24:06 by afontele          #+#    #+#             */
/*   Updated: 2023/12/11 11:53:22 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr < 1)
		len++;
	while (nbr)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

static long	neg_nbr(long n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

static char	*create_str(size_t n)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	int				sign;
	int				len;
	char			*str;

	sign = 0;
	if (n < 0)
		sign = 1;
	len = str_len(n);
	str = create_str(len);
	if (!str)
		return (NULL);
	str[len] = '\0';
	nbr = neg_nbr(n);
	while (len--)
	{
		str[len] = '0' + nbr % 10;
		nbr /= 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}
