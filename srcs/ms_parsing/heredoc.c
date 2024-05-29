/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 04:04:52 by njeanbou          #+#    #+#             */
/*   Updated: 2024/05/29 14:52:08 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*heredoc(char *exit)
{
	char	*doctmp;
	char	*doc;

	doctmp = NULL;
	while (1)
	{
		doc = readline("heredoc> ");
		if (ft_strstr(doc, exit) == doc && ft_strlen(doc) == ft_strlen(exit))
			break ;
		doctmp = ft_strjoin_c(doctmp, doc, '\n');
	}
	return (doctmp);
}

void	ft_doc(t_params **para)
{
	t_params	*head;
	char		*tmp;
	int			i;
	char		*exit;

	i = 0;
	head = *para;
	exit = NULL;
	if (head->inp_red == entre2)
	{	
		while (head->com[i] != NULL)
		{
			if (head->com[i][0] == '<')
				exit = head->com[i + 1];
			i++;
		}
		tmp = heredoc(exit);
		if (tmp != NULL)
			head->com[--i] = tmp;
		else
			head->com[--i] = NULL;
	}
}
