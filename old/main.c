/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:51:14 by njeanbou          #+#    #+#             */
/*   Updated: 2024/03/25 16:14:46 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_input(void)
{
	char	*raw_input;
	char	*input;

	raw_input = readline("minishell$ ");
	input = clean_input(raw_input, " \t");
	return (input);
}	

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac > 1)
		perror(EXIT_FAILURE);
	

	return (0);
}
