/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_echo_exit_unset.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:34:22 by afontele          #+#    #+#             */
/*   Updated: 2025/04/09 11:34:44 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void builtin_pwd(t_minishell *data, t_pars_cmd *cmd)
{
    char *cwd;

    if (cmd->args[1])
    {
        ft_putstr_fd("minishell: pwd: too many arguments\n", 2); //msg: pwd: doesn't take arguments
        data->exit_code = 1;
        return ;
    }
    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("pwd");
        data->exit_code = 1;
        return ;
    }
    printf("%s\n", cwd);
    data->exit_code = 0;
    free(cwd);
}
//break into smaller functions
void builtin_echo(t_minishell *data, t_pars_cmd *cmd)
{
    int i = 1;
    int n_flag = 0;

    while (cmd->args[i] && ft_strncmp(cmd->args[i], "-n", 2) == 0)
    {
        int j = 1;
        while (cmd->args[i][j] == 'n')
            j++;
        if (cmd->args[i][j] != '\0') 
            break;
        n_flag = 1;
        i++;
    }
    while (cmd->args[i])
    {
        ft_putstr_fd(cmd->args[i], 1);
        if (cmd->args[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (!n_flag)
        ft_putstr_fd("\n", 1);

    data->exit_code = 0;
}

void builtin_exit(t_minishell *data, t_pars_cmd *cmd)
{
    if (cmd->args[1] == NULL)
    {
        data->exit_code = 0;
        //free everything
        ft_putstr_fd("exit\n", 1);
        exit(0);
    }
    else if (cmd->args[1] && !ft_isnbr(cmd->args[1]))
    {
        data->exit_code = 2;
        print_exit_error(cmd->args[1], "numeric argument required");
        //free everything
        exit(2);
    }
    else if (cmd->args[1] && cmd->args[2])
    {
        data->exit_code = 1;
        print_exit_error(NULL, "too many arguments");
    }
    else
    {
        /*data->exit_code = ft_atoll(cmd->args[1]) % 256; //include atoll in libft
        ft_putstr_fd("exit\n", 1);
        exit(data->exit_code);*/
        exit((unsigned char)ft_atoll(cmd->args[1]));
    }
}

void    builtin_unset(t_minishell *data, t_pars_cmd *cmd)
{
    int i;

    i = 1;
    while (cmd->args[i])
    {
        if (!is_valid_identifier(cmd->args[i]))
        {
            ft_putstr_fd("unset: `", 2);
            ft_putstr_fd(cmd->args[i], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            data->exit_code = 1;
        }
        else
        {
            remove_env(data, cmd->args[i]);
            remove_exp(data, cmd->args[i]);
            data->exit_code = 0;
        }
        i++;
    }
}