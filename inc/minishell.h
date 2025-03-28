/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tautin-- <tautin--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:04:11 by tautin--          #+#    #+#             */
/*   Updated: 2025/03/28 20:39:21 by tautin--         ###   ########.fr       */
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
# include "structs.h"
# include "libft/libft.h"

// builtins.c
void is_builtin(t_minishell *data);
void builtin_hub(t_minishell *data);
void builtin_pwd(t_minishell *data);
void builtin_echo(t_minishell *data);
void builtin_exit(t_minishell *data);
void builtin_env(t_minishell *data);
void builtin_export(t_minishell *data);
void builtin_unset(t_minishell *data);
void builtin_cd(t_minishell *data);

// builtin_utils.c
int ft_isnbr(char *str);
void print_exit_error(char *arg, char *msg);
void init_env(t_minishell *data, char **envp);
void add_env(t_minishell *data, char *env);
void init_exp(t_minishell *data, char **envp);
void add_exp(t_minishell *data, char *env);
void print_exported(t_parsed_env *cur_exp_node);
void check_exp(t_minishell *data, char *arg);
void check_env(t_minishell *data, char *arg);
void remove_env(t_minishell *data, char *arg);
void remove_exp(t_minishell *data, char *arg);
char *ft_getenv(char *directory_name, t_minishell *data);
void set_env(char *title, char *value, t_minishell *data);

// exec.c
void exec_hub(t_minishell *data);


// double linked list parser and other for now
t_node	*init_node(void);
void	append_list(t_node *current, char *input, int i);

#endif