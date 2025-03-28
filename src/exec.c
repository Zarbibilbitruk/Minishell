/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:55:12 by afontele          #+#    #+#             */
/*   Updated: 2025/03/27 17:36:33 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_hub(t_minishell *data)
{
    if (data->cmd_nb == 1)
    {
        if (ft_isbuiltin(data->cmd_list))
            builtin_hub(data);
        else
            exec_cmd_hub(data);  // handles redirections, fork, execve
    }
    else
        exec_cmd_hub(data);
}

void    exec_cmd_hub(t_minishell *data)
{
    int i;
    
    i = 0;
    if (data->cmd_nb > 1)
    {
        data->pipe_ends = (int **)malloc(sizeof(int *) * (data->cmd_nb - 1));
        if (!data->pipe_ends)
            ft_error(data); // Error allocating memory
        while (i < data->cmd_nb - 1)
        {
            data->pipe_ends[i] = (int *)malloc(sizeof(int) * 2);
            if (!data->pipe_ends[i])
                ft_error(data); // Error allocating memory
            i++;
        }
        create_pipes(data);
    }
    create_processes(data);
    free_pipes(data);
}


