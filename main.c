/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:52:31 by njeanbou          #+#    #+#             */
/*   Updated: 2024/05/28 17:16:25 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*get_input(void)
{
	char	*raw_input;
	char	*input;

	raw_input = readline("minishell$ ");
	input = clean_input(raw_input);
	return (input);
}

int	main(int argc, char **argv, char **env)
{
	t_params	*para;
	t_env		*lstenv;
	t_put		*put;
	char		*input;
	int			error;

	t_data *data = NULL;
    data = malloc(sizeof(t_data));

	error = 0;
	if (argc > 1 && argv[1] == NULL)
		exit(EXIT_FAILURE);
	lstenv = set_env(env);
	while (1)
	{
		input = NULL;
		para = (t_params *)malloc (sizeof(t_params));
		put = (t_put *) malloc (sizeof(t_put));
		put->input = NULL;
		put->output = NULL;
		input = get_input();
		//printf("lala%s\n", input);
		if (input != NULL)
		{
			add_history(input);
			error = set_para(&para, input, &lstenv, &put);
			if (error == 0)
			{
				//print_all(&para, &lstenv, &put);
				ms_exec_loop(data, para, put, &lstenv);
				free_all(&para, &put);
			}
			else
				print_error(error);
		}
	}
	return (0);
}
