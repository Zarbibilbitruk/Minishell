/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:04:11 by tautin--          #+#    #+#             */
/*   Updated: 2025/04/07 15:55:53 by afontele         ###   ########.fr       */
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
# include <errno.h>
# include "structs.h"
# include "../libft/libft.h"


//TEST
void init_input(t_minishell *data);

/* main.c */
void main_loop(t_minishell *data, char **envp);

//init.c
void init_structs(t_minishell *data);
void init_env(t_minishell *data, char **envp);
void add_env(t_minishell *data, char *env);
void init_exp(t_minishell *data, char **envp);
void add_exp(t_minishell *data, char *env);

// builtins.c
int is_builtin(t_pars_cmd *command);
void builtin_hub(t_minishell *data, t_pars_cmd *cmd);
void builtin_pwd(t_minishell *data, t_pars_cmd *cmd);
void builtin_echo(t_minishell *data, t_pars_cmd *cmd);
void builtin_exit(t_minishell *data, t_pars_cmd *cmd);
void builtin_env(t_minishell *data);
void builtin_export(t_minishell *data);
void builtin_unset(t_minishell *data);
void builtin_cd(t_minishell *data);

// builtin_utils.c
int ft_isnbr(char *str);
void print_exit_error(char *arg, char *msg);
void print_exported(t_env *cur_exp_node);
void check_exp(t_minishell *data, char *arg);
void check_env(t_minishell *data, char *arg);
void remove_env(t_minishell *data, char *arg);
void remove_exp(t_minishell *data, char *arg);
char *ft_getenv(char *directory_name, t_minishell *data);
void    set_env(t_env *list, char *title, char *value);
int is_valid_identifier(char *s);

// exec.c
void exec_hub(t_minishell *data);
void    exec_cmd_hub(t_minishell *data);

/* execve_hub */
void    execute(t_minishell *data, t_pars_cmd *cur_cmd);
void    execve_hub(t_minishell *data, t_pars_cmd *cur_cmd);
void    resolve_and_exec(t_minishell *data, t_pars_cmd *cmd);
char *build_path(t_minishell *data, char *path, char *cmd);
void execve_error(t_minishell *data, char *cmd_path);

/* path.c */
int check_full_path(char *cmd);

/* error.c */
void check_path_error(t_minishell *data, char *cmd);

// lists.c
//t_node	*init_node(void);
//void	append_list(t_node *current, char *input, int i);

// pipes.c
void    create_pipes(t_minishell *data);
void    close_unused_pipes(t_minishell *data, t_pars_cmd *cur_cmd);
void    close_all_pipes(t_minishell *data);

// processes.c
void    create_processes(t_minishell *data);
void    first_child_process(t_minishell *data, t_pars_cmd *cur_cmd);
void    middle_child_process(t_minishell *data, t_pars_cmd *cur_cmd);
void    last_child_process(t_minishell *data, t_pars_cmd *cur_cmd);
void wait_loop(t_minishell *data);

//free.c
void free_pipes(t_minishell *data);
void ft_error(t_minishell *data, char *msg);
void ft_free_arraystr(char **arr);

/* utils.c */
long long   ft_atoll(const char *str);
unsigned int ft_strcmp(char *s1, char *s2);

#endif
