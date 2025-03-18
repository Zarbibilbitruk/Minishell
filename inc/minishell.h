/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:04:11 by tautin--          #+#    #+#             */
/*   Updated: 2025/03/18 20:28:17 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/****************/
/* Lib includes */
/****************/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>

// create a file structs.h (?)
// the structs will change as we develop the project

typedef struct s_parsed_command
{
    char    *command;
    int     buitlin;
    char    **args; //// will we use an array of str to store the variables?
}   t_parsed_command;

typedef struct s_parsed_env
{
    char    *title;
    char    *value;
    struct s_parsed_env *next; // will we use a linked list to store the variables?
}   t_parsed_env;

typedef struct s_minishell
{
    t_parsed_env *env;
    t_parsed_command *command;
    int     exit_status;
}   t_minishell;

// builtins.c
void is_builtin(t_minishell *data);
void builtin_hub(t_minishell *data);
void builtin_echo(t_minishell *data);
void builtin_pwd(t_minishell *data);
void builtin_exit(t_minishell *data);

// builtin_utils.c
int ft_isnbr(char *str);
void print_exit_error(char *arg, char *msg);
void ft_putstr_fd(char *s, int fd);
long long ft_atoll(const char *str);

#endif