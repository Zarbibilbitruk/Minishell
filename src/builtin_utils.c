/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:18:08 by afontele          #+#    #+#             */
/*   Updated: 2025/04/07 16:47:43 by afontele         ###   ########.fr       */
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

//learn how to put quotes in the value
void print_exported(t_env *cur_exp_node)
{
    while (cur_exp_node)
    {
        ft_putstr_fd("export ", 1);
        ft_putstr_fd(cur_exp_node->title, 1);
        ft_putstr_fd("=", 1);
        ft_putstr_fd(cur_exp_node->value, 1);
        ft_putstr_fd("\n", 1);
        cur_exp_node = cur_exp_node->next;
    }
}

void check_exp(t_minishell *data, char *arg)
{
    t_env *cur_exp_node;
    char *key;
    char *value_str;

    if (!is_valid_identifier(arg))
    {
        ft_putstr_fd("minishell: export: `", 2);
        ft_putstr_fd(arg, 2);
        ft_putstr_fd("': not a valid identifier\n", 2);
        data->exit_code = 1;
        return;
    }
    value_str = ft_strchr(arg, '=');
    if (value_str)
        key = ft_substr(arg, 0, value_str - arg);
    else
        key = ft_strdup(arg);
    cur_exp_node = data->exported;
    while (cur_exp_node)
    {
        if (ft_strcmp(cur_exp_node->title, key) == 0)
        {
            if (value_str)
            {
                free(cur_exp_node->value);
                cur_exp_node->value = ft_strdup(value_str + 1);
                check_env(data, arg);
            }
            free(key);
            return;
        }
        cur_exp_node = cur_exp_node->next;
    }
    if (value_str)
        add_env(data, arg);
    add_exp(data, arg);
    free(key);
}

//update de node or add a new one
void    check_env(t_minishell *data, char *arg)
{
    t_env *cur_env_node;
    char *key;
    char *value_str;

    cur_env_node = data->env;
    key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
    value_str = ft_strchr(arg, '=');
    while (cur_env_node)
    {
        if (ft_strcmp(cur_env_node->title, key) == 0)
        {
            if (cur_env_node->value)
            {
                free(cur_env_node->value);
                free(key);
            }
            cur_env_node->value = value_str;
            return ;
        }
        cur_env_node = cur_env_node->next;
    }
    free(key);
    free(value_str);
    add_env(data, arg);
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

