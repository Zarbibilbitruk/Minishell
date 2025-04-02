/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:55:12 by afontele          #+#    #+#             */
/*   Updated: 2025/04/02 21:53:48 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void   exec_hub(t_minishell *data)
{
    if (!data->cmd_list)
        return ;
    //printf("[DEBUG] Executing %d command(s)\n", data->cmd_nb);
    if (data->cmd_nb == 1)
    {
        if (is_builtin(data->cmd_list))
            builtin_hub(data, data->cmd_list);
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
    t_pars_cmd *cur_cmd;

    cur_cmd = data->cmd_list;
    if (data->cmd_list->infile)
        open_infile(data);
    if (data->cmd_list->outfile)
        open_outfile(data);
    data->cmd_list->pid = fork();
    if (data->cmd_list->pid == -1)
        ft_error(data, "error fork"); // Error forking process
    if (data->cmd_list->pid == 0)
            execute(data, cur_cmd);
    waitpid(data->cmd_list->pid, &status, 0);
    if (WIFEXITED(status))
    data->exit_code = WEXITSTATUS(status);
else if (WIFSIGNALED(status))
    data->exit_code = 128 + WTERMSIG(status); // bash behavior

}
