/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:09:25 by njeanbou          #+#    #+#             */
/*   Updated: 2024/03/12 16:31:19 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strncpy(char *dest, const char *str, size_t n)
{
	size_t	i;

	i = 0;
	while (str[i] && i < n)
	{
		dest[i] = str[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*clean_input(char *s1, char const *set)
{
	size_t	beg;
	size_t	end;
	char	*input_clean;

	if (!s1 || !set)
		return (NULL);
	beg = 0;
	while (s1[beg] != '\0' && ft_strchr(set, s1[beg]) != NULL)
		beg++;
	end = ft_strlen(s1 + beg);
	while (end > beg && ft_strchr(set, s1[(beg + end) - 1]) != NULL)
		end--;
	input_clean = (char *)malloc ((end + 1) * sizeof(char));
	if (!input_clean)
		return (NULL);
	ft_strncpy(input_clean, (s1 + beg), end);
	free(s1);
	return (input_clean);
}
