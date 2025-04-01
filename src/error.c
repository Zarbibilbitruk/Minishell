/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:08:03 by afontele          #+#    #+#             */
/*   Updated: 2025/03/31 12:10:11 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void check_path_error(t_minishell *data, char *cmd)
{
    if (!cmd)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(data->cmd_list->args[0], 2);
        ft_putstr_fd(": command not found\n", 2);
        data->exit_code = 127;
        free(cmd);
    }
}