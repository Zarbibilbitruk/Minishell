/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:08:03 by afontele          #+#    #+#             */
/*   Updated: 2025/04/09 11:03:22 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void print_cmd_not_found(t_minishell *data, char *cmd)
{
    if (!cmd)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(data->cmd_list->args[0], 2);
        ft_putstr_fd(": command not found\n", 2);
        data->exit_code = 127;
    }
}

void ft_error(t_minishell *data, char *msg)
{
    free_pipes(data);
    perror(msg);
    //free_processes(data);
    //free_commands(data);
    //free_env(data);
    //free_exported(data);
    //free(data);
}

void print_exit_error(char *arg, char *msg)
{
    ft_putstr_fd("exit\n", 1);
    ft_putstr_fd("minishell: exit: ", 2);
    if (arg)
    {
        ft_putstr_fd(arg, 2);
        ft_putstr_fd(": ", 2);
    }
    ft_putstr_fd(msg, 2);
    ft_putstr_fd("\n", 2);
}