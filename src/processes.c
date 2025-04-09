/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:36:18 by afontele          #+#    #+#             */
/*   Updated: 2025/04/08 23:53:04 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    create_processes(t_minishell *data)
{
    t_pars_cmd *cur_cmd;
    
    cur_cmd = data->cmd_list;
    while (cur_cmd)
    {
        cur_cmd->pid = fork();
        if (cur_cmd->pid == -1)
            ft_error(data, "error forking"); // Error forking
        if (cur_cmd->pid == 0)
        {
            setup_child(data, cur_cmd);
            /*close_unused_pipes(data, cur_cmd);
            if (cur_cmd->cmd_index == 0)
                first_child_process(data, cur_cmd);
            else if (cur_cmd->cmd_index == data->cmd_nb - 1)
                last_child_process(data, cur_cmd);
            else
                middle_child_process(data, cur_cmd);*/
            execute(data, cur_cmd);
            exit(data->exit_code); // exit the child process
        }
        cur_cmd = cur_cmd->next;
    }
    close_all_pipes(data);
    wait_loop(data);
}

void setup_child(t_minishell *data, t_pars_cmd *cur_cmd)
{
    int idx;

    idx = cur_cmd->cmd_index;
    if (data->cmd_nb > 1)
    {
        if (idx > 0)
        {
            if (dup2(data->pipe_ends[idx - 1][0], STDIN_FILENO) == -1)
                ft_error(data, "error dup2"); // Error duplicating pipe
        }
        if (idx < data->cmd_nb - 1)
        {
            if (dup2(data->pipe_ends[idx][1], STDOUT_FILENO) == -1)
                ft_error(data, "error dup2"); // Error duplicating pipe
        }
    }
    close_unused_pipes(data, cur_cmd);
    if (!setup_redirections(cur_cmd, data))
        exit(1); // exit the child process
}

/*void    first_child_process(t_minishell *data, t_pars_cmd *cur_cmd)
{
    int fd_in;
    if (cur_cmd->infile)
    {
        fd_in = open(cur_cmd->infile, O_RDONLY, 0644);
        if (fd_in == -1)
        {
            ft_error(data, "error opening infile"); // Error opening infile
            data->exit_code = 1;
        }
    }
    else
    {
        // HERE_DOC
    }
    dup2(fd_in, STDIN_FILENO);
    close(fd_in);
    if (data->cmd_nb > 1) //check how to handle single cmd
    {
        dup2(data->pipe_ends[0][1], STDOUT_FILENO);
        close(data->pipe_ends[0][1]);
    }
}

void middle_child_process(t_minishell *data, t_pars_cmd *cur_cmd)
{
    dup2(data->pipe_ends[cur_cmd->cmd_index - 1][0], STDIN_FILENO);
    close(data->pipe_ends[cur_cmd->cmd_index - 1][0]);
    dup2(data->pipe_ends[cur_cmd->cmd_index][1], STDOUT_FILENO);
    close(data->pipe_ends[cur_cmd->cmd_index][1]);
}

void last_child_process(t_minishell *data, t_pars_cmd *cur_cmd)
{
    int fd_out;

    dup2(data->pipe_ends[cur_cmd->cmd_index - 1][0], STDIN_FILENO);
    close(data->pipe_ends[cur_cmd->cmd_index - 1][0]);
    if (cur_cmd->outfile)
    {
        fd_out = open(cur_cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out == -1)
        {
            ft_error(data, "error opening outfile"); // Error opening outfile
            data->exit_code = 1;
        }
    }
    dup2(fd_out, STDOUT_FILENO);
    close(fd_out);
}*/
void wait_loop(t_minishell *data)
{
    t_pars_cmd *cur_cmd;
    int status;

    cur_cmd = data->cmd_list;
    while (cur_cmd)
    {
        waitpid(cur_cmd->pid, &status, 0);
        if (WIFEXITED(status))
            data->exit_code = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            data->exit_code = 128 + WTERMSIG(status);
        //fprintf(stderr, "[DEBUG] Child %d exited with status %d\n", cur_cmd->pid, data->exit_code);
        cur_cmd = cur_cmd->next;
    }
}
