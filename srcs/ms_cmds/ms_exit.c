/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:41:27 by njeanbou          #+#    #+#             */
/*   Updated: 2024/05/28 14:26:44 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env(t_env **env)
{
	if ((*env) != NULL)
	{
		free((*env)->env_name);
		free((*env)->env_value);
		free_env(&(*env)->next);
	}
	return ;
}

void	ms_exit(t_params **para, t_put **put, t_env **env)
{
	printf("lalalaala\n");
	free_all(para, put);
	printf("lololo");
	free_env(env);
	printf("kakakaa");
	exit(EXIT_SUCCESS);
}
