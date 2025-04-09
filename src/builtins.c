/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:47:11 by afontele          #+#    #+#             */
/*   Updated: 2025/04/09 11:34:40 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//IMPORTANT: Make a func to print error if optionas are included with the command
// In this file, we will implement the builtins functions: echo -n, cd, pwd, export, unset, env, exit
// I coded this functions as the parsing would be done using strings, but I'll change if we use linked lists

#include "../inc/minishell.h"

int is_builtin(t_pars_cmd *command)
{
    if (!command || !command->args || !command->args[0])
        return 0;
    if ((ft_strcmp(command->args[0], "echo") == 0)
    || (ft_strcmp(command->args[0], "cd") == 0)
    || (ft_strcmp(command->args[0], "pwd") == 0)
    || (ft_strcmp(command->args[0], "export") == 0)
    || (ft_strcmp(command->args[0], "unset") == 0)
    || (ft_strcmp(command->args[0], "env") == 0)
    || (ft_strcmp(command->args[0], "exit") == 0))
        return 1;
    else
        return 0;
}

void single_builtin(t_minishell *data, t_pars_cmd *cmd)
{
    int fd_in;
    int fd_out;

    fd_in = dup(STDIN_FILENO);
    fd_out = dup(STDOUT_FILENO);
    if (fd_in == -1 || fd_out == -1)
    {
        perror("dup");
        return ;
    }
    if (!setup_redirections(cmd, data))
    {
        dup2(fd_in, STDIN_FILENO);
        dup2(fd_out, STDOUT_FILENO);
        close(fd_in);
        close(fd_out);
        return ;
    }
    builtin_hub(data, cmd);
    dup2(fd_in, STDIN_FILENO);
    dup2(fd_out, STDOUT_FILENO);
    close(fd_in);
    close(fd_out);
}

void builtin_hub(t_minishell *data, t_pars_cmd *cmd)
{
    if (!cmd || !cmd->args || !cmd->args[0])
        return ;
    if (ft_strcmp(cmd->args[0], "echo") == 0)
        builtin_echo(data, cmd);
    else if (ft_strcmp(cmd->args[0], "cd") == 0)
        builtin_cd(data, cmd);
    else if (ft_strcmp(cmd->args[0], "pwd") == 0)
        builtin_pwd(data, cmd);
    else if (ft_strcmp(cmd->args[0], "export") == 0)
        builtin_export(data, cmd);
    else if (ft_strcmp(cmd->args[0], "unset") == 0)
        builtin_unset(data, cmd);
    else if (ft_strcmp(cmd->args[0], "env") == 0)
        builtin_env(data, cmd);
    else if (ft_strcmp(cmd->args[0], "exit") == 0)
        builtin_exit(data, cmd);
}
