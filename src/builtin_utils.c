/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:18:08 by afontele          #+#    #+#             */
/*   Updated: 2025/03/27 16:52:40 by afontele         ###   ########.fr       */
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
    if (nb > LLONG_MAX || nb < LLONG_MIN)
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
void print_exported(t_pars_env *cur_exp_node)
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
    t_pars_env *cur_exp_node;
    char *value_str;

    cur_exp_node = data->exported;
    while (cur_exp_node)
    {
        if (ft_strncmp(cur_exp_node->title, arg, ft_strlen(cur_exp_node->title)) == 0)
        {
            if (cur_exp_node->value)
            {
                free(cur_exp_node->value);
                check_env(data, arg);
            }
            value_str = ft_strchr(arg, '=');  
            cur_exp_node->value = ft_strdup(value_str++); 
            return ;
        }
        cur_exp_node = cur_exp_node->next;
    }
    if (ft_strchr(arg, '='))
        add_env(data, arg);
    add_exp(data, arg);
}
//update de node or add a new one
void    check_env(t_minishell *data, char *arg)
{
    t_pars_env *cur_env_node;

    cur_env_node = data->env;
    while (cur_env_node)
    {
        if (ft_strncmp(cur_env_node->title, arg, ft_strlen(cur_env_node->title)) == 0)
        {
            if (cur_env_node->value)
                free(cur_env_node->value);
            cur_env_node->value = ft_strdup(ft_strchr(arg, '=') + 1);
            return ;
        }
        cur_env_node = cur_env_node->next;
    }
    add_env(data, arg);
}

void    remove_env(t_minishell *data, char *arg)
{
    t_pars_env *cur_env_node;
    t_pars_env *prev_env_node;

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
    t_pars_env *cur_exp_node;
    t_pars_env *prev_exp_node;

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

//cd utils
char    *ft_getenv(char *directory_name, t_minishell *data)
{
    t_pars_env *cur_env_node;

    cur_env_node = data->env;
    while (cur_env_node)
    {
        if (ft_strcmp(cur_env_node->title, directory_name) == 0)
            return (cur_env_node->value);
        cur_env_node = cur_env_node->next;
    }
    return (NULL);
}

void    set_env(char *title, char *value, t_minishell *data)
{
    t_pars_env *cur_env_node;

    cur_env_node = data->env;
    while (cur_env_node)
    {
        if (ft_strcmp(cur_env_node->title, title) == 0)
        {
            free(cur_env_node->value);
            cur_env_node->value = ft_strdup(value);
            return ;
        }
        cur_env_node = cur_env_node->next;
    }
}