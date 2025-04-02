/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:03:09 by afontele          #+#    #+#             */
/*   Updated: 2025/04/02 15:32:40 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//TEST MY PROGRAM
void init_input(t_minishell *data)
{
    data->command->args = ft_split(data->user_input, ' ');
    if (!data->command->args)
        ft_error(data, "error malloc"); // Error allocating memory
    data->command->next = NULL;
    data->command->cmd_index = 0;
    data->command->hd_nb = 0;
    data->command->infile = NULL;
    data->command->outfile = NULL;
    data->command->heredoc = NULL;
    data->command->delimiters = NULL;
    data->command->pid = 0;
    data->cmd_nb = 1;
    
}

void init_cmd(t_minishell *data)
{
    t_pars_cmd *cur_cmd_node;

    cur_cmd_node = malloc(sizeof(t_pars_cmd));
    if (!cur_cmd_node)
        ft_error(data, "error malloc"); // Error allocating memory
    data->cmd_list = cur_cmd_node;
    data->cmd_list->next = NULL;
    data->cmd_nb = 0;
}

void add_cmd(t_minishell *data, char *cmd)
{
    t_pars_cmd *new;
    t_pars_cmd *tmp;

    new = malloc(sizeof(t_pars_cmd));
    new->args = ft_split(cmd, ' ');
    new->next = NULL;
    tmp = data->cmd_list;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

void    init_structs(t_minishell *data, char **envp)
{
    data->user_input = NULL;
    data->env = NULL;
    data->exported = NULL;
    data->cmd_list = NULL; //included in the parser (some parts will be included in the exec part)
    data->cmd_nb = 0; //included in the parser
    data->pipe_ends = NULL; //icluded in the pipe manager
    data->pids = NULL; //I think I'll include in each node of the command list
    data->exit_code = 0;
    init_env(data, envp);
    init_exp(data, envp);
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
    data->envp = envp;
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