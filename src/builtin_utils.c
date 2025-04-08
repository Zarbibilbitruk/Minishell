/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:18:08 by afontele          #+#    #+#             */
/*   Updated: 2025/04/09 00:26:35 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//exit utils
int ft_isnbr(char *str)
{
    int i;

    i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    long long nb = ft_atoll(str);
    if (nb == LLONG_MAX || nb == LLONG_MIN)
        return (0);
    return (1);
}

void print_exit_error(char *arg, char *msg)
{
    ft_putstr_fd("exit\n", 1);
    ft_putstr_fd("minishell: exit: ", 2);
    if (arg)
    {
        ft_putstr_fd(arg, 2);
        ft_putstr_fd(": ", 2);
    }
    ft_putstr_fd(msg, 2);
    ft_putstr_fd("\n", 2);
}

//should be handled in parse
int is_valid_identifier(char *s)
{
    if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
        return (0);
    for (int i = 1; s[i]; i++)
        if (!ft_isalnum(s[i]) && s[i] != '_')
            return (0);
    return (1);
}

void    remove_env(t_minishell *data, char *arg)
{
    t_env *cur_env_node;
    t_env *prev_env_node;

    cur_env_node = data->env;
    prev_env_node = NULL;
    while (cur_env_node)
    {
        if (ft_strcmp(cur_env_node->title, arg) == 0)
        {
            if (prev_env_node)
                prev_env_node->next = cur_env_node->next;
            else
                data->env = cur_env_node->next;
            free(cur_env_node->title);
            free(cur_env_node->value);
            free(cur_env_node);
            return ;
        }
        prev_env_node = cur_env_node;
        cur_env_node = cur_env_node->next;
    }
}

void    remove_exp(t_minishell *data, char *arg)
{
    t_env *cur_exp_node;
    t_env *prev_exp_node;

    cur_exp_node = data->exported;
    prev_exp_node = NULL;
    while (cur_exp_node)
    {
        if (ft_strcmp(cur_exp_node->title, arg) == 0)
        {
            if (prev_exp_node)
                prev_exp_node->next = cur_exp_node->next;
            else
                data->exported = cur_exp_node->next;
            free(cur_exp_node->title);
            free(cur_exp_node->value);
            free(cur_exp_node);
            return ;
        }
        prev_exp_node = cur_exp_node;
        cur_exp_node = cur_exp_node->next;
    }
}