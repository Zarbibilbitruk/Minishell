/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:17:20 by afontele          #+#    #+#             */
/*   Updated: 2025/04/09 00:26:40 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void builtin_env(t_minishell *data, t_pars_cmd *cmd)
{
    t_env *cur_env_node;
    cur_env_node = data->env;
    if (!cur_env_node)
    {
        data->exit_code = 1;
        return ;
    }
    if (cmd->args[1])
    {
        ft_putstr_fd("env: too many arguments\n", 2); //msg: env: doesn't take arguments
        data->exit_code = 1;
        return ;
    }
    while (cur_env_node)
    {
        if (cur_env_node->value)
            printf("%s=%s\n", cur_env_node->title, cur_env_node->value);
        cur_env_node = cur_env_node->next;
    }  
    data->exit_code = 0;
}

void builtin_export(t_minishell *data, t_pars_cmd *cmd)
{
    int i;

    i = 1;
    if (!cmd->args[i] || (ft_strcmp(cmd->args[i], "--") == 0 && !cmd->args[i + 1]))
    {
        print_exported(data->exported);
        data->exit_code = 0;
        return ;
    }
    if (ft_strcmp(cmd->args[i], "--") == 0 && cmd->args[i + 1])
        i++;
    if (ft_strncmp(cmd->args[i], "-", 1) == 0 && cmd->args[i][1] != '\0')
    {
        ft_putstr_fd("export: invalid option\n", 2); //OPTIONS ARE NOT ALLOWED
        data->exit_code = 1;
        return ;
    }
    while (cmd->args[i])
    {
        if (!is_valid_identifier(cmd->args[i]))
        {
            ft_putstr_fd("export: `", 2);
            ft_putstr_fd(cmd->args[i], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            data->exit_code = 1;
        }
        check_exp(data, cmd->args[i]);
        i++;
    }
    data->exit_code = 0;
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