/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_hub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:59:29 by afontele          #+#    #+#             */
/*   Updated: 2025/03/31 12:10:54 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    execve_hub(t_minishell *data, t_pars_cmd *cur_cmd)
{
    char    **envp;
    char    *path;
    char    *cmd_path;
    char    **paths;
    
    envp = get_envp(data);
    path = get_path(data, cur_cmd->args[0]);
    if (path == NULL)
        ft_error(data, "command not found"); // Error command not found
    paths = ft_split(path, ':');
    cmd_path = find_cmd(data, paths, cur_cmd->args[0]);
    if (cmd_path == NULL)
        ft_error(data, "command not found"); // Error command not found
    execve(cmd_path, cur_cmd->args, envp);
}

void    execute(t_minishell *data, t_pars_cmd *cur_cmd)
{
    if (!cur_cmd->args || !cur_cmd->args[0])
    {
        ft_error(data, "command not found"); // Error command not found
        data->exit_code = 127;
        //free
        return ;
    }
    if (is_builtin(cur_cmd->args[0]))
    {
        builtin_hub(data, cur_cmd);
        return ;
    }
    else
    {
        execute_with_path(data, cur_cmd);
        return ;
    }    
}

void    execute_with_path(t_minishell *data, t_pars_cmd *cmd)
{
    char *cmd_path;

    if (!check_full_path(cmd->args[0]))
    {
        cmd_path = ft_getenv("PATH", data);
        check_path_error(data, cmd_path);
        cmd_path = build_path(cmd_path, cmd->args[0]);
        check_path_error(data, cmd_path);
    }
    else
    {
        cmd_path = ft_strdup(cmd->args[0]);
        check_path_error(data, cmd_path);
    }
    if (execve(cmd_path, cmd->args, data->env->envp) == -1)
        execve_error(data, cmd_path);
    free(cmd_path);
}

char *build_path(char *path, char *cmd)
{
    char *full_path;
    char *tmp;
    char **possible_paths;
    int i;

    i = 0;
    possible_paths = ft_split(path, ':');
    if (!possible_paths)
        ft_error(data, "error malloc"); // Error allocating memory
    while (possible_paths[i])
    {
        tmp = ft_strjoin(possible_paths[i], "/");
        full_path = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(full_path, X_OK) == 0)
        {
            free(possible_paths);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    free(possible_paths);
    return (NULL);
}

void    execve_error(t_minishell *data, char *cmd_path)
{
    perror(data->cmd_list->args[0]);
    data->exit_code = 127;
    free(cmd_path);
    if (errno == ENOENT)
        data->exit_code = 127; // Error command not found
    else if (errno == EACCES)
        data->exit_code = 126; // Error permission denied
    else
        data->exit_code = 1; // Error other
}