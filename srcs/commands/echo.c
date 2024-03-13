/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:25:16 by njeanbou          #+#    #+#             */
/*   Updated: 2024/03/13 18:19:10 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
        {
            if (str[i + 1])
            {
                ft_putchar_fd(str[i + 2], STDOUT_FILENO);
                i += 3;
            }
            else
            {
                ft_putchar_fd(str[i], STDOUT_FILENO);
                break ;
            }
        }
        else
        {
            ft_putchar_fd(str[i], STDOUT_FILENO);
            i++;
        }
	}
}

int	cmd_echo(t_statement *statement, bool has_n)
{
	int	i;

	i = 1;
	if (has_n)
		i++;
	while (statement->argv[i] && i != statement->argc)
	{
		print(statement->argv[i]);
		if (!statement->argv[i + 1] || statement->operator != RDR_INPUT)
			break ;
		ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
    if (!has_n)
        write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}