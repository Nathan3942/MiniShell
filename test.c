/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:23:08 by njeanbou          #+#    #+#             */
/*   Updated: 2024/03/06 15:57:55 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>



char	*commande_extract(void)
{
	char	*input;

	input = readline(">");
	if (!input)
		return (NULL);
	return (input);
}

int	main(void)
{
	char	*cmd;

	cmd = commande_extract();
	printf("%s", cmd);
	return (0);
}