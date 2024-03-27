/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:16:00 by njeanbou          #+#    #+#             */
/*   Updated: 2024/03/18 18:08:43 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	streq(char *str1, char	*str2)
{
	size_t	i;

	if ((str1 && !str2) || (!str1 && str2))
		return (false);
	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (false);
		i++;
	}
	return (true);
}


bool	is_valid_id(char *str)
{
	size_t	i;

	i = 0;
	if (streq(str, "="))
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (ft_isdigit(str[i]) || str[i] == '!' || str[i] == '@'
			|| str[i] == '{' || str[i] == '}' || str[i] == '-')
			return (false);
		i++;
	}
	return (true);
}
