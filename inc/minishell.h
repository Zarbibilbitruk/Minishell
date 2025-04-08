/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:04:11 by tautin--          #+#    #+#             */
/*   Updated: 2025/04/09 00:27:58 by afontele         ###   ########.fr       */
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

/* MAIN.C */
void    main_loop(t_minishell *data, char **envp);

/* EXECVE_HUB.C */
void    execute(t_minishell *data, t_pars_cmd *cur_cmd);
void    resolve_and_exec(t_minishell *data, t_pars_cmd *cmd);
char *build_path(t_minishell *data ,char *path, char *cmd);
void    execve_error(t_minishell *data, char *cmd_path);
int check_full_path(char *cmd);

/* SETUP_EXEC.C */
void    setup_exec(t_minishell *data);
void    multiple_cmds(t_minishell *data);
void    exec_uniq_cmd(t_minishell *data);

/* PROCESSES.C */
void    create_processes(t_minishell *data);
void    setup_child(t_minishell *data, t_pars_cmd *cur_cmd);
void wait_loop(t_minishell *data);

/* PIPES.C */
void    create_pipes(t_minishell *data);
void    close_unused_pipes(t_minishell *data, t_pars_cmd *cur_cmd);
void    close_all_pipes(t_minishell *data);

/* REDIRECTIONS */
int setup_redirections(t_pars_cmd *cmd, t_minishell *data);
int open_infile(t_pars_cmd *cmd, t_minishell *data);
int open_outfile(t_pars_cmd *cmd, t_minishell *data, int mode);

/* HEREDOC.C */
void write_heredoc_file(t_minishell *data, char *filename, char *delimiter);
void generate_heredocs(t_minishell *data);
char *last_heredoc_path(t_pars_cmd *cmd);
void redirect_heredoc(t_minishell *data, t_pars_cmd *cmd);

/* BUILTINS.C */
int is_builtin(t_pars_cmd *command);
void single_builtin(t_minishell *data, t_pars_cmd *cmd);
void builtin_hub(t_minishell *data, t_pars_cmd *cmd);
void builtin_pwd(t_minishell *data, t_pars_cmd *cmd);
void builtin_echo(t_minishell *data, t_pars_cmd *cmd);

/* CD.C */
void cd_update_pwd(t_minishell *data, char *old_pwd);
void cd_home(t_minishell *data, char *old_pwd);
void cd_dash(t_minishell *data, t_pars_cmd *cmd, char *old_pwd);
void cd_to_path(t_minishell *data, char *path, char *old_pwd);
void builtin_cd(t_minishell *data, t_pars_cmd *cmd);

/* ENV_EXP.C */
void builtin_env(t_minishell *data, t_pars_cmd *cmd);
void builtin_export(t_minishell *data, t_pars_cmd *cmd);
void print_exported(t_env *cur_exp_node);
void check_exp(t_minishell *data, char *arg);
void check_env(t_minishell *data, char *arg);

#endif
