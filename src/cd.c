/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:48:45 by afontele          #+#    #+#             */
/*   Updated: 2025/04/09 11:51:25 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void cd_update_pwd(t_minishell *data, char *old_pwd)
{
    char *new_pwd;

    new_pwd = getcwd(NULL, 0);
    if (!new_pwd)
    {
        perror("getcwd");
        data->exit_code = 1;
        return ;
    }
    set_env(data->env, "PWD", new_pwd);
    set_env(data->exported, "PWD", new_pwd);
    set_env(data->env, "OLDPWD", old_pwd);
    set_env(data->exported, "OLDPWD", old_pwd);
    free(new_pwd);
}

void    cd_home(t_minishell *data, char *old_pwd)
{
    char *home;

    home = ft_getenv("HOME", data);
    if (!home || chdir(home) == -1)
    {
        perror("cd");
        data->exit_code = 1;
        return ;
    }
    free(home);
    set_env(data->env, "OLDPWD", old_pwd);
    set_env(data->exported, "OLDPWD", old_pwd);
}

void    cd_dash(t_minishell *data, char *old_pwd)
{
    char *prev_oldpwd;

    prev_oldpwd = ft_getenv("OLDPWD", data);
    if (!prev_oldpwd)
    {
        ft_putstr_fd("minishell: cd: OLDPWD not set", 2);
        data->exit_code = 1;
        free(prev_oldpwd);
        return ;
    }
    if (chdir(prev_oldpwd) == -1)
    {
        perror("cd");
        data->exit_code = 1;
        free(prev_oldpwd);
        return ;
    }
    ft_putstr_fd(prev_oldpwd, 1);
    ft_putstr_fd("\n", 1);
    free(prev_oldpwd);
    set_env(data->env, "OLDPWD", old_pwd);
    set_env(data->exported, "OLDPWD", old_pwd);
}

void    cd_to_path(t_minishell *data, char *path, char *old_pwd)
{
    if (chdir(path) == -1)
    {
        perror("cd");
        data->exit_code = 1;
        return ;
    }
    cd_update_pwd(data, old_pwd);
}

void builtin_cd(t_minishell *data, t_pars_cmd *cmd)
{
    char *old_pwd;
    
    if (cmd->args[2])
    {
        ft_putstr_fd("cd: too many arguments\n", 2);
        data->exit_code = 1;
        return ;
    }
    old_pwd = getcwd(NULL, 0);
    if (!old_pwd)
    {
        perror("getcwd");
        data->exit_code = 1;
        return ;
    }
    if (!cmd->args[1] || ft_strcmp(cmd->args[1], "~") == 0)
        cd_home(data, old_pwd);
    else if (ft_strcmp(cmd->args[1], "-") == 0)
        cd_dash(data, old_pwd);
    else
        cd_to_path(data, cmd->args[1], old_pwd);
    free(old_pwd);
}