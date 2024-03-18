/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_lst_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:54:17 by njeanbou          #+#    #+#             */
/*   Updated: 2024/03/18 17:37:47 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	get_exported_state(char *var_name, t_vlst **head)
{
	t_vlst	*temp;

	temp = *head;
	while (temp != NULL)
	{
		if (streq(var_name, temp->var_name))
			return (temp->is_exported);
		temp = temp->next;
	}
	return (false);
}

char	**split_envp(char *env)
{
	char	**splitted;
	size_t	indexof_equal;

	splitted = malloc(3 * sizeof(char *));
	indexof_equal = ft_strchr(env, '=') - env;
	splitted[0] = ft_substr(env, 0, indexof_equal);
	splitted[1] = ft_substr(env, indexof_equal + 1,
			ft_strlen(&env[indexof_equal]));
	splitted[2] = NULL;
	return (splitted);
}

int	save_user_vars(char *statement, t_vlst **head, bool to_export)
{
	char	**line;

	line = split_envp(statement);
	if (get_exported_state(line[0], head) && !to_export)
		to_export = true;
	unset_var(line[0], head);
	v_lstadd_back(head, v_new_node(line[0], line[1], to_export));
	free(line);
	return (EXIT_SUCCESS);
}
