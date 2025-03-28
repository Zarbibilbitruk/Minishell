/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:01:52 by tautin--          #+#    #+#             */
/*   Updated: 2025/03/27 20:57:10 by afontele         ###   ########.fr       */
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
#include "minishell.h"

void test(int signal)
{
    printf("signal : %d", signal);
}

//loop that will keep the minishell running - return the prompt to user
//maybe include the loop inside the main function
void main_loop(t_minishell *data, char **envp, int ac, char **av)
{
    while (1)
    {
        data->user_input = readline("minishell$ ");
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
        //wait for the command to finish
        //free the structs
        free(data->user_input);
    }
}

int main(int ac, char **av, char **envp)
{
    //I think we need to create a function to handle the signals and call it inside the main loop
    struct sigaction    action;
    action.sa_handler = test;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
    //allocating memory for the struct
    t_minishell *data;

    data = malloc(sizeof(t_minishell)); //alloc mem inside the loop?
    init_structs(data, envp);
    if (!data)
        return (1);
    if (ac != 1)
    {
        printf("Error: minishell don't take arguments\n");
        return (1);
    }
    main_loop(data, envp, ac, av); //do I need to pass the ac and av?
    //free all the memory allocated
    return (data->exit_code);
}
