/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:33:51 by njeanbou          #+#    #+#             */
/*   Updated: 2024/05/29 17:20:37 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_para(t_params *para)
{
	t_params	*next;
	int			i;

	i = 0;
	if (para != NULL)
		return ;
	while (para->com[i] != NULL)
	{
		free(para->com[i]);
		i++;
	}
	next = para->next;
	free(para);
	para = NULL;
	free_para(next);
}

void	free_all(t_params *para, t_put *put)
{
	if (para != NULL)
		free_para(para);
	if (put != NULL)
	{
		if (put->input != NULL)
			free(put->input);
		if (put->output != NULL)
			free(put->output);
		free(put);
		put = NULL;
	}
}
