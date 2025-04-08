/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:13:49 by afontele          #+#    #+#             */
/*   Updated: 2025/04/09 00:11:07 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char *gen_heredoc_filename(int index)
{
	char *num = ft_itoa(index);
	char *name = ft_strjoin("hd_tmp", num);
	free(num);
	return (name);
}

void write_heredoc_file(t_minishell *data, char *filename, char *delimiter)
{
	int fd; 
	char *line;
	
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		ft_error(data, "heredoc open");
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
}

void generate_heredocs(t_minishell *data)
{
	t_pars_cmd *cmd;
	int hd_count;
	int i;

	i = 0;
	hd_count = 0;
	cmd = data->cmd_list;
	while (cmd)
	{
		if (cmd->delimiters)
		{
			cmd->heredoc = malloc(sizeof(char *) * (cmd->hd_nb + 1));
			if (!cmd->heredoc)
				ft_error(data, "malloc heredoc");
			while (i < cmd->hd_nb)
			{
				char *filename = gen_heredoc_filename(hd_count++);
				write_heredoc_file(data, filename, cmd->delimiters[i]);
				cmd->heredoc[i] = filename;
				i++;
			}
			cmd->heredoc[cmd->hd_nb] = NULL;
		}
		cmd = cmd->next;
	}
}

char *last_heredoc_path(t_pars_cmd *cmd)
{
	int i = 0;
	if (!cmd->heredoc)
		return NULL;
	while (cmd->heredoc[i + 1])
		i++;
	return cmd->heredoc[i];
}

void redirect_heredoc(t_minishell *data, t_pars_cmd *cmd)
{
	char *path;
	int fd_hd;
	
	path = last_heredoc_path(cmd);
	if (!path)
		return ;
	fd_hd = open(path, O_RDONLY);
	if (fd_hd == -1)
    {
        ft_putchar_fd("minishell: here_doc ", 2);
        perror(path);
        data->exit_code = 1;
    }
	if (dup2(fd_hd, STDIN_FILENO) == -1)
		ft_error(data, "dup2 heredoc");
	close(fd_hd);
}
