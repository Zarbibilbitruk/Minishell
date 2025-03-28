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
#include "../inc/minishell.h"

//ft_atoll
long long ft_atoll(const char *str)
{
    long long res;
    int sign;

    res = 0;
    sign = 1;
    while (*str == ' ' || *str == '\t' || *str == '\n'
        || *str == '\v' || *str == '\f' || *str == '\r')
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9')
    {
        res = res * 10 + *str - '0';
        str++;
    }
    return (res * sign);
}

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

//ft_putstr_fd
void ft_putstr_fd(char *s, int fd)
{
    write(fd, s, ft_strlen(s));
}

//ft_strncmp
int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    while (n && *s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
        n--;
    }
    if (n == 0)
        return (0);
    return ((unsigned char)*s1 - (unsigned char)*s2);
}

//ft_strlen
size_t ft_strlen(const char *s)
{
    size_t i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

//ft_substr
char *ft_substr(char const *s, unsigned int start, size_t len)
{
    char *sub;
    size_t i;

    if (!s)
        return (NULL);
    if (ft_strlen(s) < start)
        return (ft_strdup(""));
    sub = (char *)malloc(sizeof(char) * (len + 1));
    if (!sub)
        return (NULL);
    i = 0;
    while (i < len && s[start + i])
    {
        sub[i] = s[start + i];
        i++;
    }
    sub[i] = '\0';
    return (sub);
}

//ft_strdup
char *ft_strdup(const char *s)
{
    char *dup;
    size_t i;

    dup = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
    if (!dup)
        return (NULL);
    i = 0;
    while (s[i])
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}