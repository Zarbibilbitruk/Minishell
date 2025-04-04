/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:03:09 by afontele          #+#    #+#             */
/*   Updated: 2025/04/02 20:56:27 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    init_structs(t_minishell *data)
{
    data->user_input = NULL;
    data->cmd_list = NULL; //included in the parser (some parts will be included in the exec part)
    data->cmd_nb = 0; //included in the parser
    data->pipe_ends = NULL; //icluded in the pipe manager
}

void init_env(t_minishell *data, char **envp)
{
    int i;
    t_env *cur_env_node;

    i = 0;
    /*if (envp[i] == NULL)
        return (NULL);*/
    cur_env_node = malloc(sizeof(t_env));
    if (!cur_env_node)
        ft_error(data, "error malloc"); // Error allocating memory
    data->env = cur_env_node;
    data->envp = envp;
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

void   add_env(t_minishell *data, char *env)
{
    t_env *new;
    t_env *tmp;

    new = malloc(sizeof(t_env));
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
    t_env *cur_exp_node;

    i = 0;
    /*if (envp[i] == NULL)
        return (NULL);*/
    cur_exp_node = malloc(sizeof(t_env));
    if (!cur_exp_node)
        ft_error(data, "error malloc"); // Error allocating memory
    data->exported = cur_exp_node;
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

void   add_exp(t_minishell *data, char *env)
{
    t_env *new;
    t_env *tmp;

    new = malloc(sizeof(t_env));
    new->title = ft_substr(env, 0, ft_strchr(env, '=') - env);
    new->value = ft_strdup(ft_strchr(env, '=') + 1);
    new->next = NULL;
    tmp = data->exported;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}