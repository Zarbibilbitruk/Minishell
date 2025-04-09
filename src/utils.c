/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:27:44 by afontele          #+#    #+#             */
/*   Updated: 2025/04/09 11:01:23 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

long long	ft_atoll(const char *str)
{
	long long	res = 0;
	int			sign = 1;

	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		sign = (*str++ == '-') ? -1 : 1;
	while (*str >= '0' && *str <= '9')
	{
		if (res > (LLONG_MAX - (*str - '0')) / 10)
			return (sign == 1 ? LLONG_MAX : LLONG_MIN); // or handle error
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}


unsigned int ft_strcmp(char *s1, char *s2)
{
    unsigned int i;

    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}