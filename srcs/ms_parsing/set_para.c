/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_para.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:11:22 by njeanbou          #+#    #+#             */
/*   Updated: 2024/05/29 13:34:05 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_com(t_params *para, t_put *put)
{
	int			i;
	int			z;

	i = 0;
	z = 0;
	while (para->com[i] != NULL)
	{
		if (para->com[i][0] != '<' && para->com[i][0] != '>')
		{
			if (ft_strstrbool(para->com[i], put->input) == 1
				&& ft_strstrbool(para->com[i], put->output) == 1)
				z++;
		}
		i++;
	}
	return (z);
}

char	**set_com(t_params *para, int len, t_put *put)
{
	char		**com;
	int			i;
	int			z;

	com = (char **)malloc ((len + 1) * sizeof(char *));
	i = 0;
	z = 0;
	while (para->com[i] != NULL)
	{
		if (para->com[i][0] != '<' && para->com[i][0] != '>')
		{
			if (ft_strstrbool(para->com[i], put->input) == 1
				&& ft_strstrbool(para->com[i], put->output) == 1)
			{
				com[z] = ft_strdup(para->com[i]);
				z++;
			}
		}
		i++;
	}
	com[z] = NULL;
	return (com);
}

void	refactor_com(t_params *para, t_put *put)
{
	char		**com;
	int			z;

	z = 0;
	while (para != NULL)
	{
		z = count_com(para, put);
		com = set_com(para, z, put);
		para->com = com;
		if (para->next != NULL)
			para->out_red = PIPE;
		para = para->next;
		if (para != NULL)
			para->inp_red = PIPE;
	}
}

void	init_com(t_params **para, char **com, t_put **put, t_env **env)
{
	t_params	*head;
	int			i;

	i = 0;
	head = *para;
	while (com[i] != NULL && com[i][0] != '|')
		i++;
	head->com = (char **)malloc ((i + 1) * sizeof(char *));
	i = 0;
	while (com[i] != NULL && com[i][0] != '|')
	{
		head->com[i] = ft_strdup(com[i]);
		i++;
	}
	head->com[i] = NULL;
	set_put(put, para);
	set_enum(para);
	ft_doc(para);
	set_var(para, env);
	set_varbis(para, env);
}

int	set_para(t_params **param, char *input, t_env **env, t_put **put)
{
	char		**inp_sep;
	t_params	*para;
	int			i;

	para = *param;
	inp_sep = split_para(input);
	if (ft_error(inp_sep) != 0)
		return (ft_error(inp_sep));
	init_com(&para, inp_sep, put, env);
	para->next = NULL;
	i = 0;
	while (inp_sep[i] != NULL)
	{
		if (inp_sep[i][0] == '|')
		{
			para->next = (t_params *)malloc (sizeof(t_params));
			para = para->next;
			para->next = NULL;
			init_com(&para, inp_sep + i + 1, put, env);
		}
		i++;
	}
	para = *param;
	refactor_com(para, *put);
	return (0);
}
