/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:00:39 by afontele          #+#    #+#             */
/*   Updated: 2025/04/02 16:50:41 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

// the structs will change as we develop the project

typedef struct s_parsed_command
{
    int cmd_index; //index of the command in the list
    pid_t   pid; //pid of the child process - not sure if should store here or in the minishell struct - included in exec part
    int hd_nb; //number of heredoc - 0 if none
    char    **heredoc; //we need an array with the heredoc - NULL if none -included in exec part
    char    **delimiters; //we need an array with the delimiters - NULL if none
    char    *infile; //infile, NULL if none
    char    *outfile; //outfile, if pipe, NULL
    char    **args; //we need an array with the cmd and args to pass to execve
    struct s_parsed_command *next; //pointer to the next command in the list
}   t_pars_cmd;

typedef struct s_env //structure for the environment variables
{
    
    char    *title; //key of the variable
    char    *value; //value of the variable
    int     export; //1 if exported, 0 if not
    struct s_env *next; //pointer to the next variable in the list
}   t_env;

typedef struct s_minishell
{
    char   *user_input; //the line with the user input
    char **envp; //array of strings with the environment variables
    t_env *env; //call env_list ?
    t_env *exported; //call exp_list ?
    t_pars_cmd *cmd_list; //pointer to the first command in the list
    t_pars_cmd *command; //test
    int     cmd_nb; //number of commands in the list
    int     **pipe_ends; //array with the pipe[2] for each command
    //int    *pids; //array with the pids of the child processes - should I use pid_t?
    int     exit_code; //use a global variable to store the exit code (?)
}   t_minishell;

#endif