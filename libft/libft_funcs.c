/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:34:27 by afontele          #+#    #+#             */
/*   Updated: 2025/03/21 11:34:31 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//funcs to include in libft
#include "libft.h"

//ft_atoll

//ft_strcmp
int ft_strcmp(char *s1, char *s2)
{
    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return ((unsigned char)*s1 - (unsigned char)*s2);
}
