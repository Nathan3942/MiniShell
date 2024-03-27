/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:52:31 by njeanbou          #+#    #+#             */
/*   Updated: 2024/03/27 16:04:38 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char *get_input(void)
{
    char    *raw_input;
    char    *input;

    raw_input = readline("minishell: ");
    input = clean_input(raw_input);
    return (input);
}

int main(int argc, char **argv)
{
    t_params    *para;
    char        *input;

    if (argc > 1)
        perror(EXIT_FAILURE);
    while (1)
    {
        input = get_input();
        add_history(input);
    }
    
}

