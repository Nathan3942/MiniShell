/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:00:51 by njeanbou          #+#    #+#             */
/*   Updated: 2024/03/27 15:58:36 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    *clean_input(char *raw_input)
{
	char	*input;

	if (!raw_input)
		return NULL;

	int len = ft_strlen(raw_input);
	int beg = 0;
	while (raw_input[beg] == ' ' || raw_input[beg] == '\t')
		beg++;
	while (len > beg && (raw_input[len - 1] == ' ' || raw_input[len - 1] == '\t'))
		len--;
	input = (char *)malloc((len - beg + 1) * sizeof(char));
	if (!input)
		return NULL;
	ft_strncpy(input, raw_input + beg, len - beg);
	return (input);
}
