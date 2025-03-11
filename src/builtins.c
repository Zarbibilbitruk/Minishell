/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:47:11 by afontele          #+#    #+#             */
/*   Updated: 2025/03/11 20:11:05 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// In this file, we will implement the builtins functions: echo -n, cd, pwd, export, unset, env, exit
//I code this functions as the parsing would be done using strings, but I'll change if we use linked lists

#include "minishell.h"

void is_builtin(t_minishell *data)
{
    if ((ft_strcmp(data.command->args[0], "echo") == 0)
    || (ft_strcmp(data.command->args[0], "cd") == 0)
    || (ft_strcmp(data.command->args[0], "pwd") == 0)
    || (ft_strcmp(data.command->args[0], "export") == 0)
    || (ft_strcmp(data.command->args[0], "unset") == 0)
    || (ft_strcmp(data.command->args[0], "env") == 0)
    || (ft_strcmp(data.command->args[0], "exit") == 0))
        data.command->builtin = 1;
    else
        data.command->builtin = 0;
}

void builtin_hub(t_minishell *data)
{
    if (data.command->builtin == 0)
        return ;
    else if (ft_strcmp(data.command->args[0], "echo") == 0)
        builtin_echo(data);
    else if (ft_strcmp(data.command->args[0], "cd") == 0)
        builtin_cd(command, env);
    else if (ft_strcmp(data.command->args[0], "pwd") == 0)
        builtin_pwd();
    else if (ft_strcmp(data.command->args[0], "export") == 0)
        builtin_export(command, env);
    else if (ft_strcmp(data.command->args[0], "unset") == 0)
        builtin_unset(command, env);
    else if (ft_strcmp(data.command->args[0], "env") == 0)
        builtin_env(env);
    else if (ft_strcmp(data.command->args[0], "exit") == 0)
        builtin_exit(command, env);
}

void builtin_pwd(t_minishell *data)
{
    char *cwd;

    if (data.command->args[1])
    {
        ft_putstr_fd("pwd: too many arguments\n", 2); //msg: pwd: doesn't take arguments
        data.exit_status = 1;
        return ;
    }
    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("pwd");
        data.exit_status = 1;
        return ;
    }
    printf("%s\n", cwd);
    data.exit_status = 0;
    free(cwd);
}

void builtin_echo(t_minishell *data)
{
    int i = 1;
    int n_flag = 0;

    // Detect multiple `-n` flags
    // check the -nnnnn ?
    while (data->command->args[i] && ft_strncmp(data->command->args[i], "-n", 2) == 0)
    {
        int j = 1;
        while (data->command->args[i][j] == 'n')
            j++;
        if (data->command->args[i][j] != '\0') 
            break;
        n_flag = 1;
        i++;
    }
    while (data->command->args[i])
    {
        ft_putstr_fd(data->command->args[i], 1);
        if (data->command->args[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (!n_flag)
        ft_putstr_fd("\n", 1);

    data->exit_status = 0;
}
