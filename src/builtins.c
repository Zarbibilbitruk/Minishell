/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:47:11 by afontele          #+#    #+#             */
/*   Updated: 2025/04/07 22:23:04 by afontele         ###   ########.fr       */
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

void builtin_pwd(t_minishell *data, t_pars_cmd *cmd)
{
    char *cwd;

    if (cmd->args[1])
    {
        ft_putstr_fd("minishell: pwd: too many arguments\n", 2); //msg: pwd: doesn't take arguments
        data->exit_code = 1;
        return ;
    }
    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("pwd");
        data->exit_code = 1;
        return ;
    }
    printf("%s\n", cwd);
    data->exit_code = 0;
    free(cwd);
}
//break into smaller functions
void builtin_echo(t_minishell *data, t_pars_cmd *cmd)
{
    int i = 1;
    int n_flag = 0;

    while (cmd->args[i] && ft_strncmp(cmd->args[i], "-n", 2) == 0)
    {
        int j = 1;
        while (cmd->args[i][j] == 'n')
            j++;
        if (cmd->args[i][j] != '\0') 
            break;
        n_flag = 1;
        i++;
    }
    while (cmd->args[i])
    {
        ft_putstr_fd(cmd->args[i], 1);
        if (cmd->args[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (!n_flag)
        ft_putstr_fd("\n", 1);

    data->exit_code = 0;
}

void builtin_exit(t_minishell *data, t_pars_cmd *cmd)
{
    if (cmd->args[1] == NULL)
    {
        data->exit_code = 0;
        //free everything
        ft_putstr_fd("exit\n", 1);
        exit(0);
    }
    else if (cmd->args[1] && !ft_isnbr(cmd->args[1]))
    {
        data->exit_code = 2;
        print_exit_error(cmd->args[1], "numeric argument required");
        //free everything
        exit(2);
    }
    else if (cmd->args[1] && cmd->args[2])
    {
        data->exit_code = 1;
        print_exit_error(NULL, "too many arguments");
    }
    else
    {
        /*data->exit_code = ft_atoll(cmd->args[1]) % 256; //include atoll in libft
        ft_putstr_fd("exit\n", 1);
        exit(data->exit_code);*/
        exit((unsigned char)ft_atoll(cmd->args[1]));
    }
}

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

void    builtin_unset(t_minishell *data, t_pars_cmd *cmd)
{
    int i;

    i = 1;
    while (cmd->args[i])
    {
        if (!is_valid_identifier(cmd->args[i]))
        {
            ft_putstr_fd("unset: `", 2);
            ft_putstr_fd(cmd->args[i], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            data->exit_code = 1;
        }
        else
        {
            remove_env(data, cmd->args[i]);
            remove_exp(data, cmd->args[i]);
            data->exit_code = 0;
        }
        i++;
    }
}

