/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_hub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:59:29 by afontele          #+#    #+#             */
/*   Updated: 2025/04/07 16:52:50 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    execute(t_minishell *data, t_pars_cmd *cur_cmd)
{
    if (!cur_cmd->args || !cur_cmd->args[0])
    {
        print_cmd_not_found(data, NULL);
        exit(data->exit_code);
        //need to free?
    }
    if (is_builtin(cur_cmd))
    {
        builtin_hub(data, cur_cmd);
        return ;
    }
    else
    {
        resolve_and_exec(data, cur_cmd);
        return ;
    }    
}

void    resolve_and_exec(t_minishell *data, t_pars_cmd *cmd)
{
    char *cmd_path;
    char *path;

    if (!check_full_path(cmd->args[0]))
    {
        path = ft_getenv("PATH", data);
        if (!path || !*path)
        {
            print_cmd_not_found(data, cmd->args[0]);
            exit(data->exit_code);
        }
        cmd_path = build_path(data, path, cmd->args[0]);
        if (!cmd_path)
        {
            print_cmd_not_found(data, cmd->args[0]);
            exit(data->exit_code);
        }
    }
    else
    {
        cmd_path = ft_strdup(cmd->args[0]);
        if (access(cmd_path, X_OK) == -1)
        {
            print_cmd_not_found(data, cmd->args[0]);
            free(cmd_path);
            exit(data->exit_code);
        }
    }
    if (execve(cmd_path, cmd->args, data->envp) == -1)
        execve_error(data, cmd_path);
    free(cmd_path);
}

char *build_path(t_minishell *data ,char *path, char *cmd)
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
            free_arraystr(possible_paths);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    free_arraystr(possible_paths);
    return (NULL);
}
//should I exit the program if execve fail?
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

int check_full_path(char *cmd)
{
    if (cmd[0] == '/')
        return (1);
    return (0);
}