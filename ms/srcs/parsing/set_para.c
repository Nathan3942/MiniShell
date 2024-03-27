/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_para.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:11:22 by njeanbou          #+#    #+#             */
/*   Updated: 2024/03/27 17:21:54 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_pipe(char **input)
{
	int	pos;

	pos = 0;
	while (input[pos])
	{
		if (input[pos][0] == '|')
			return (pos);
		pos++;
	}
	return (pos);
}

static void	chr_cmd(char **inp, int pos, t_params *para)
{
	int	i;

	i = 0;
	while (inp[i])
	{
		if (inp[i] == "echo" || inp[i] == "cd" || inp[i] == "pwd"
			|| inp[i] == "export" || inp[i] == "unset" || inp[i] == "env"
			|| inp[i] == "exit")
		{
			if (i < pos && para->com1 == NULL)
				para->com1 = inp[i];
			else if (pos < i && para->com1 != NULL)
				para->com2 = inp[i];
		}
		i++;
		return ;
	}
}

void	set_para(char *input, t_params *para)
{
	char	**inp_sep;
	int		pos_pipe;

	inp_sep = ft_split(input, ' ');
	pos_pipe = has_pipe(inp_sep);
	chr_cmd(inp_sep, pos_pipe, &para);
}
