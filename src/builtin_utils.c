/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:18:08 by afontele          #+#    #+#             */
/*   Updated: 2025/03/20 18:27:35 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//env and export utils
void init_env(t_minishell *data, char **envp)
{
    int i;

    i = 0;
    if (envp[i] == NULL)
        return ;
    data->env = malloc(sizeof(t_parsed_env));
    data->env->envp = envp;
    data->env->next = NULL;
    while (envp[i])
    {
        if (i == 0)
        {
            data->env->title = ft_strndup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
            data->env->value = ft_strdup(ft_strchr(envp[i], '=') + 1);
        }
        else
            add_env(data, envp[i]);
        i++;
    }
}

void add_env(t_minishell *data, char *env)
{
    t_parsed_env *new;
    t_parsed_env *tmp;

    new = malloc(sizeof(t_parsed_env));
    new->envp = data->env->envp;
    new->title = ft_strndup(env, ft_strchr(env, '=') - env);
    new->value = ft_strdup(ft_strchr(env, '=') + 1);
    new->next = NULL;
    tmp = data->env;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

void init_exp(t_minishell *data, char **envp)
{
    int i;

    i = 0;
    if (envp[i] == NULL)
        return ;
    data->exported = malloc(sizeof(t_parsed_env));
    data->exported->envp = envp;
    data->exported->next = NULL;
    while (envp[i])
    {
        if (i == 0)
        {
            data->exported->title = ft_strndup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
            data->exported->value = ft_strdup(ft_strchr(envp[i], '=') + 1);
        }
        else
            add_exp(data, envp[i]);
        i++;
    }
}

void add_exp(t_minishell *data, char *env)
{
    t_parsed_env *new;
    t_parsed_env *tmp;

    new = malloc(sizeof(t_parsed_env));
    new->envp = data->exported->envp;
    new->title = ft_strndup(env, ft_strchr(env, '=') - env);
    new->value = ft_strdup(ft_strchr(env, '=') + 1);
    new->next = NULL;
    tmp = data->exported;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

char *ft_strndup(const char *s1, size_t n)
{
    char *str;
    size_t i;

    i = 0;
    str = malloc(sizeof(char) * (n + 1));
    if (!str)
        return (NULL);
    while (s1[i] && i < n)
    {
        str[i] = s1[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}
//learn how to put quotes in the value
void print_exported(t_parsed_env *cur_exp_node)
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
