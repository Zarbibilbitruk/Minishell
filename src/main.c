/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tautin-- <tautin--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:01:52 by tautin--          #+#    #+#             */
/*   Updated: 2025/03/17 18:34:57 by tautin--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void test(int signal)
{
    printf("signal : %d", signal);
}

int main(void){
    struct sigaction    action;
    action.sa_handler = test;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
}