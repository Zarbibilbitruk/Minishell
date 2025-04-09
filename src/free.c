/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:24:55 by afontele          #+#    #+#             */
/*   Updated: 2025/04/09 11:53:54 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    free_pipes(t_minishell *data)
{
    int i;

    i = 0;
    if (data->pipe_ends == NULL)
        return ;
    while (i < data->cmd_nb - 1)
    {
        free(data->pipe_ends[i]);
        i++;
    }
    free(data->pipe_ends);
}

void free_arraystr(char **arr)
{
    int i = 0;
    while (arr && arr[i])
        free(arr[i++]);
    free(arr);
}

void cleanup_heredocs(t_minishell *data)
{
	t_pars_cmd *cmd = data->cmd_list;
	int i;

	while (cmd)
	{
		if (cmd->heredoc)
		{
			for (i = 0; cmd->heredoc[i]; i++)
			{
				unlink(cmd->heredoc[i]);
				free(cmd->heredoc[i]);
			}
			free(cmd->heredoc);
			cmd->heredoc = NULL;
		}
		cmd = cmd->next;
	}
}