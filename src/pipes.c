/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:31:05 by afontele          #+#    #+#             */
/*   Updated: 2025/03/27 17:22:06 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    create_pipes(t_minishell *data)
{
    int i;

    i = 0;
    while (i < data->cmd_nb - 1)
    {
        if (pipe(data->pipe_ends[i]) == -1)
            ft_error(data); // Error creating pipe
        i++;
    }
}

void    close_unused_pipes(t_minishell *data, t_pars_cmd *cur_cmd)
{
    int i;

    i = 0;
    if (data->cmd_nb == 1)
        return ;
    while (i < data->cmd_nb - 1)
    {
        if (i != cur_cmd->cmd_index - 1)
            close(data->pipe_ends[i][0]);
        if (i != cur_cmd->cmd_index)
            close(data->pipe_ends[i][1]);
        i++;
    }
}

void    close_all_pipes(t_minishell *data)
{
    int i;

    i = 0;
    if (data->cmd_nb == 1)
        return ;
    while (i < data->cmd_nb - 1)
    {
        close(data->pipe_ends[i][0]);
        close(data->pipe_ends[i][1]);
        i++;
    }
}