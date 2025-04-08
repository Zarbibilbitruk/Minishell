/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:45:20 by afontele          #+#    #+#             */
/*   Updated: 2025/04/07 16:47:47 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void   add_exp(t_minishell *data, char *env)
{
    t_env *new;
    t_env *tmp;
    char *has_value;

    new = malloc(sizeof(t_env));
    if (!new)
        ft_error(data, "error malloc"); // Error allocating memory
    has_value = ft_strchr(env, '=');
    if (!has_value)
    {
        new->title = ft_strdup(env);
        new->value = NULL;
    }
    else
    {
        new->title = ft_substr(env, 0, has_value - env);
        new->value = ft_strdup(has_value + 1);
    }
    new->next = NULL;
    if (!data->exported)
    {
        data->exported = new;
        return ;
    }
    tmp = data->exported;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

void   add_env(t_minishell *data, char *env)
{
    t_env *new;
    t_env *tmp;

    new = malloc(sizeof(t_env));
    if (!new)
        ft_error(data, "error malloc"); // Error allocating memory
    new->title = ft_substr(env, 0, ft_strchr(env, '=') - env);
    new->value = ft_strdup(ft_strchr(env, '=') + 1);
    new->next = NULL;
    if (!data->env)
    {
        data->env = new;
        return ;
    }
    tmp = data->env;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

void    set_env(t_env *list, char *title, char *value)
{
    t_env *cur_node;

    cur_node = list;
    while (cur_node)
    {
        if (ft_strcmp(cur_node->title, title) == 0)
        {
            free(cur_node->value);
            cur_node->value = ft_strdup(value);
            return ;
        }
        cur_node = cur_node->next;
    }
}

char    *ft_getenv(char *directory_name, t_minishell *data)
{
    t_env *cur_env_node;

    cur_env_node = data->env;
    while (cur_env_node)
    {
        if (ft_strcmp(cur_env_node->title, directory_name) == 0)
            return (cur_env_node->value);
        cur_env_node = cur_env_node->next;
    }
    return (NULL);
}