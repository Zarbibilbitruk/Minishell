/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:00:39 by afontele          #+#    #+#             */
/*   Updated: 2025/03/26 19:40:18 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

// the structs will change as we develop the project

typedef struct s_parsed_command
{
    t_parsed_command *next;
    int hd_nb; //number of heredoc - 0 if none
    char    **heredoc; //we need an array with the heredoc - NULL if none
    char    **delimiters; //we need an array with the delimiters - NULL if none
    char    *infile; //infile, NULL if none
    char    *outfile; //outfile, if pipe, NULL
    char    **args; //we need an array with the cmd and args to pass to execve
}   t_parsed_command;

typedef struct s_parsed_env
{
    char    **envp;
    char    *title;
    char    *value;
    struct s_parsed_env *next; // will we use a linked list to store the variables?
}   t_parsed_env;

typedef struct s_minishell
{
    char   *user_input; //the line with the user input
    t_parsed_env *env;
    t_parsed_env *exported;
    t_parsed_command *command_list; //pointer to the first command in the list
    int     cmd_nb; //number of commands in the list
    int     exit_code; //use a global variable to store the exit code (?)
}   t_minishell;

#endif