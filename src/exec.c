/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:55:12 by afontele          #+#    #+#             */
/*   Updated: 2025/04/07 22:19:14 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void   exec_hub(t_minishell *data)
{
    if (!data->cmd_list)
        return ;
    //printf("[DEBUG] Executing %d command(s)\n", data->cmd_nb);
    generate_heredocs(data);
    if (data->cmd_nb == 1)
    {
        if (is_builtin(data->cmd_list))
            single_builtin(data, data->cmd_list);
        else
            exec_uniq_cmd(data);  // handles redirections, fork, execve
    }
    else
        exec_cmd_hub(data);
}

void    exec_cmd_hub(t_minishell *data)
{
    int i;
    
    i = 0;
    if (data->cmd_nb < 2)
        return ;
    data->pipe_ends = (int **)malloc(sizeof(int *) * (data->cmd_nb - 1));
    if (!data->pipe_ends)
        ft_error(data, "error malloc"); // Error allocating memory
    while (i < data->cmd_nb - 1)
    {
        data->pipe_ends[i] = (int *)malloc(sizeof(int) * 2);
        if (!data->pipe_ends[i])
            ft_error(data, "error malloc"); // Error allocating memory
        i++;
    }
    create_pipes(data);
    create_processes(data);
    free_pipes(data);
}
 //separate redirection setup from command execution for cleaner design
void exec_uniq_cmd(t_minishell *data)
{
    int status;
    t_pars_cmd *cmd;

    cmd = data->cmd_list;
    if (cmd->infile && !open_infile(cmd, data))
        return;
    if (cmd->outfile && !open_outfile(cmd, data))
        return;
    cmd->pid = fork();
    if (cmd->pid == -1)
        ft_error(data, "error fork"); // Error forking process
    if (cmd->pid == 0)
            execute(data, cmd);
    waitpid(cmd->pid, &status, 0);
    if (WIFEXITED(status))
        data->exit_code = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        data->exit_code = 128 + WTERMSIG(status); // bash behavior
}
