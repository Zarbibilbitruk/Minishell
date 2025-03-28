/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:36:18 by afontele          #+#    #+#             */
/*   Updated: 2025/03/27 17:50:10 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    create_processes(t_minishell *data)
{
    t_pars_cmd *cur_cmd;
    
    cur_cmd = data->cmd_list;
    while (cur_cmd)
    {
        cur_cmd->pid = fork();
        if (cur_cmd->pid == -1)
            ft_error(data); // Error forking
        if (cur_cmd->pid == 0)
        {
            close_unused_pipes(data, cur_cmd);
            if (cur_cmd->cmd_index == 0)
                first_child_process(data, cur_cmd);
            else if (cur_cmd->cmd_index == data->cmd_nb - 1)
                last_child_process(data, cur_cmd);
            else
                middle_child_process(data, cur_cmd);
            execute(data, cur_cmd);
        }
        cur_cmd = cur_cmd->next;
    }
    close_all_pipes(data);
    wait_loop(data);
}

//check if builtin
void    first_child_process(t_minishell *data, t_pars_cmd *cur_cmd)
{
    int fd_in;
    if (cur_cmd->infile)
    {
        fd_in = open(cur_cmd->infile, O_RDONLY, 0644);
        if (data->fd_in == -1)
        {
            ft_error(data); // Error opening infile
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


