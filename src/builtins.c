/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:47:11 by afontele          #+#    #+#             */
/*   Updated: 2025/03/20 18:33:24 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// In this file, we will implement the builtins functions: echo -n, cd, pwd, export, unset, env, exit
// I coded this functions as the parsing would be done using strings, but I'll change if we use linked lists

#include "minishell.h"

void is_builtin(t_minishell *data)
{
    if ((ft_strcmp(data->command->args[0], "echo") == 0)
    || (ft_strcmp(data->command->args[0], "cd") == 0)
    || (ft_strcmp(data->command->args[0], "pwd") == 0)
    || (ft_strcmp(data->command->args[0], "export") == 0)
    || (ft_strcmp(data->command->args[0], "unset") == 0)
    || (ft_strcmp(data->command->args[0], "env") == 0)
    || (ft_strcmp(data->command->args[0], "exit") == 0))
        data->command->builtin = 1;
    else
        data->command->builtin = 0;
}

void builtin_hub(t_minishell *data)
{
    if (data->command->builtin == 0)
        return ;
    else if (ft_strcmp(data->command->args[0], "echo") == 0)
        builtin_echo(data);
    else if (ft_strcmp(data->command->args[0], "cd") == 0)
        builtin_cd(data);
    else if (ft_strcmp(data->command->args[0], "pwd") == 0)
        builtin_pwd(data);
    else if (ft_strcmp(data->command->args[0], "export") == 0)
        builtin_export(data);
    else if (ft_strcmp(data->command->args[0], "unset") == 0)
        builtin_unset(data);
    else if (ft_strcmp(data->command->args[0], "env") == 0)
        builtin_env(data);
    else if (ft_strcmp(data->command->args[0], "exit") == 0)
        builtin_exit(data);
}

void builtin_pwd(t_minishell *data)
{
    char *cwd;

    if (data->command->args[1])
    {
        ft_putstr_fd("pwd: too many arguments\n", 2); //msg: pwd: doesn't take arguments
        data->exit_status = 1;
        return ;
    }
    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("pwd");
        data->exit_status = 1;
        return ;
    }
    printf("%s\n", cwd);
    data->exit_status = 0;
    free(cwd);
}

void builtin_echo(t_minishell *data)
{
    int i = 1;
    int n_flag = 0;

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

void builtin_exit(t_minishell *data)
{
    if (data->command->args[1] == NULL)
    {
        data->exit_status = 0;
        //free everything
        ft_putstr_fd("exit\n", 1);
        exit(0);
    }
    else if (data->command->args[1] && !ft_isnbr(data->command->args[1]))
    {
        data->exit_status = 2;
        print_exit_error(data->command->args[1], "numeric argument required");
        //free everything
        exit(2);
    }
    else if (data->command->args[1] && data->command->args[2])
    {
        data->exit_status = 1;
        print_exit_error(NULL, "too many arguments");
    }
    else
    {
        data->exit_status = ft_atoll(data->command->args[1]) % 256; //include atoll in libft
        ft_putstr_fd("exit\n", 1);
        exit(data->exit_status);
    }
}

void builtin_env(t_minishell *data)
{
    t_parsed_env *cur_env_node;
    cur_env_node = data->env;
    if (!data->env->envp)
    {
        data->exit_status = 1;
        return ;
    }
    if (data->command->args[1])
    {
        ft_putstr_fd("env: too many arguments\n", 2); //msg: env: doesn't take arguments
        data->exit_status = 1;
        return ;
    }
    while (cur_env_node)
    {
        printf("%s=%s\n", cur_env_node->title, cur_env_node->value);
        cur_env_node = cur_env_node->next;
    }  
    data->exit_status = 0;
}

void builtin_export(t_minishell *data)
{
    int i;
    t_parsed_env *cur_exp_node;

    cur_exp_node = data->exported;
    i = 1;
    if (!data->command->args[i])
    {
        print_exported(data->exported);
        data->exit_status = 0;
        return ;
    }
    /*can take a list of arguments
    - first search to see if he argument is already in the exp list
    - if the argument contains an =, it will be added to the exp and env list
    - if the argument doesn't contain an =, it will be only added to the exp list
    - if the argument is already in the env list, it will be updated (if not in env and add a value include to env)
    - if the argument is already in the exported list, it will be updated
    */
}
