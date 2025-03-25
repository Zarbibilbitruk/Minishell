/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:18:08 by afontele          #+#    #+#             */
/*   Updated: 2025/03/25 17:14:33 by afontele         ###   ########.fr       */
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
            data->env->title = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
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
    new->title = ft_substr(env, 0, ft_strchr(env, '=') - env);
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
            data->exported->title = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
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
    new->title = ft_substr(env, 0, ft_strchr(env, '=') - env);
    new->value = ft_strdup(ft_strchr(env, '=') + 1);
    new->next = NULL;
    tmp = data->exported;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
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

void check_exp(t_minishell *data, char *arg)
{
    t_parsed_env *cur_exp_node;

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
            cur_exp_node->value = ft_strdup(ft_strchr(arg, '=') + 1); 
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
    t_parsed_env *cur_env_node;

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
    t_parsed_env *cur_env_node;
    t_parsed_env *prev_env_node;

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
    t_parsed_env *cur_exp_node;
    t_parsed_env *prev_exp_node;

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
    t_parsed_env *cur_env_node;

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
    t_parsed_env *cur_env_node;

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