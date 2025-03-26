/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:55:12 by afontele          #+#    #+#             */
/*   Updated: 2025/03/26 19:48:21 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_hub(t_data *data)
{
    if (data->cmd_nb == 1)
    {
        if (ft_isbuiltin(data->cmd_list))
            ft_builtin(data);
        else
            ft_exec_cmd(data);  // handles redirections, fork, execve
    }
    else
        exec_pipe(data);
}

void exec_pipe(t_data *data)
{
    data->pipe_ends = ft_create_pipe_ends(data->cmd_nb - 1);
    if (!data->pipe_ends)
        ft_error(data); // Error handling
        return ;
    ft_exec_cmd(data);  // Fork each command, connect via pipes
}
