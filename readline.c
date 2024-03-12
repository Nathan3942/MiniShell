/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:10:33 by njeanbou          #+#    #+#             */
/*   Updated: 2024/03/11 18:45:33 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*input;
	char	cwd[1024];
	size_t	cwd_len;
	char	*prompt;

	getcwd(cwd, sizeof(cwd));
	cwd_len = strlen(cwd);
	prompt = (char *)malloc (cwd_len + 3);
	strcpy(prompt, cwd);
	strcat(prompt, "> ");
	while (1)
	{
		input = readline(prompt);
		if (input)
			add_history(input);
		//printf("%s : %s\n", cwd, input);
	}
	free(input);
	return (0);
}
