/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:52:31 by njeanbou          #+#    #+#             */
/*   Updated: 2024/05/30 17:48:45 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*get_input(t_data *data)
{
	char	*raw_input;
	char	*input;
	int		fd;

	raw_input = readline("minishell$ ");
	input = clean_input(raw_input);
	free(raw_input);
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
		input = get_input(data);
		if (input != NULL)
		{
			add_history(input);
			error = set_para(&para, input, &lstenv, &put);
			if (error == 0 && para->com[0] != NULL)
			{
				print_all(&para, &lstenv, &put);
				ms_exec_loop(data, para, put, &lstenv);
				printf("exec ok\n");
			}
			else
				print_error(error);
			if (ft_strequal(para->com[0], "exit") == 0)
				ms_exit(para, put, &lstenv, &data);
			free_all(&para, &put);
			if (data->exit == true)
			{
				printf("Exit\n");
				exit (EXIT_SUCCESS);
			}
		}
	}
	free(data);
	return (0);
}
