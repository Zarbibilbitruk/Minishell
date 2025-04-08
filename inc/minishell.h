/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tautin-- <tautin--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:04:11 by tautin--          #+#    #+#             */
/*   Updated: 2025/04/08 17:20:50 by tautin--         ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "structs.h"
# include "libft/libft.h"

struct s_minishell t_minishell;

//libf
int ft_strcmp(char *s1, char *s2);
void ft_putstr_fd(char *s, int fd);
int ft_strncmp(const char *s1, const char *s2, size_t n);
long long ft_atoll(const char *str);
size_t ft_strlen(const char *s);
char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strdup(const char *s);
char *ft_strchr(const char *s, int c);

//init.c
void init_structs(t_minishell *data, char **envp);
void init_env(t_minishell *data, char **envp);
void add_env(t_minishell *data, char *env);
void init_exp(t_minishell *data, char **envp);
void add_exp(t_minishell *data, char *env);

// builtins.c
int is_builtin(t_pars_cmd *command);
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
void print_exported(t_pars_env *cur_exp_node);
void check_exp(t_minishell *data, char *arg);
void check_env(t_minishell *data, char *arg);
void remove_env(t_minishell *data, char *arg);
void remove_exp(t_minishell *data, char *arg);
char *ft_getenv(char *directory_name, t_minishell *data);
void set_env(char *title, char *value, t_minishell *data);

// exec.c
void exec_hub(t_minishell *data);
void    exec_cmd_hub(t_minishell *data);

// lists.c
t_node	*init_node(void);
void	append_list(t_node *current, char *input, int i, t_commande *control);

// pipes.c
void    create_pipes(t_minishell *data);
void    close_unused_pipes(t_minishell *data, t_pars_cmd *cur_cmd);
void    close_all_pipes(t_minishell *data);

// processes.c
void    create_processes(t_minishell *data);
void    first_child_process(t_minishell *data, t_pars_cmd *cur_cmd);
void    middle_child_process(t_minishell *data, t_pars_cmd *cur_cmd);
void    last_child_process(t_minishell *data, t_pars_cmd *cur_cmd);

//free.c
void free_pipes(t_minishell *data);
void ft_error(t_minishell *data, char *msg);

#endif
