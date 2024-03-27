/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:00:51 by njeanbou          #+#    #+#             */
/*   Updated: 2024/03/27 16:05:00 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t len = 0;
	while (*str++)
		len++;
	return len;
}

char    *ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t i = 0;

	while (i < n && src[i])
	{
		dest[i] = src[i];
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

static char *get_input(void)
{
    char    *raw_input;
    char    *input;

    raw_input = readline("minishell: ");
    input = clean_input(raw_input);
    return (input);
}

int main(void)
{
	char	*inp;

	while (1)
	{
		inp = get_input();
		if (inp)
		{
			printf("%s\n", inp);
			add_history(inp);
			free(inp);
		}
	}
	return 0;
}
