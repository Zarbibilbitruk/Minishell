/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:01:52 by tautin--          #+#    #+#             */
/*   Updated: 2025/04/02 20:55:28 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** DOCUMENTATION **
 * main.c:
 *      - initializes the minishell struct
 *      - loop:
 *         - promp for input
 *         - parse the input
 *         - lexes and validates syntax
 *         - exec cmg
 *         - wait for the command to finish
 *         - free memory
 */
#include "../inc/minishell.h"

/*void test(int signal)
{
    printf("signal : %d", signal);
}*/
// TODO: add free_cmd_list(), free_pipe_ends() here before reinitializing
//loop that will keep the minishell running - return the prompt to user
void main_loop(t_minishell *data, char **envp)
{
    while (1)
    {
        init_structs(data);
        data->user_input = readline("minishell$> ");
        if (!data->user_input)
        {
            printf("exit\n");
            break;
        }
        if (data->user_input[0] != '\0')
            add_history(data->user_input);
        //init_structs
        //parse the command
        //execute the command
        exec_hub(data);
        //wait for the command to finish
        //free the structs
        free(data->user_input);
    }
}

int main(int ac, char **av, char **envp)
{
    (void)av;
    
    //I think we need to create a function to handle the signals and call it inside the main loop
    /*struct sigaction    action;
    action.sa_handler = test;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);*/
    //allocating memory for the struct
    t_minishell *data;

    data = malloc(sizeof(t_minishell)); //alloc mem inside the loop?
    if (!data)
        return (1);
    if (ac != 1)
    {
        printf("Error: minishell don't take arguments\n");
        return (1);
    }
    init_structs(data);
    init_env(data, envp);
    init_exp(data, envp);
    main_loop(data, envp); //do I need to pass the ac and av?
    //free all the memory allocated
    return (data->exit_code);
}
