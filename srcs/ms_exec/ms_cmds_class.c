/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmds_class.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 23:17:22 by ichpakov          #+#    #+#             */
/*   Updated: 2024/05/30 16:32:51 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	echo_checker(char **cmd)
{
	int	i;

	i = 1;
	if (!ft_strcmp(cmd[0], "echo"))
		return (0);
	while (ft_strcmp(cmd[i], "-n"))
		i++;
	if (cmd[i][0] == '-')
		return (0);
	return (i);
}

static int	count_env_maillon(t_env *env)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (env->is_exported == true)
	{
		while (env->env_name[i] != '\0')
		{
			len++;
			i++;
		}
		i = 0;
		if (env->env_value != NULL)
		{
			while (env->env_value[i] != '\0')
			{
				len++;
				i++;
			}
		}
	}
	return (len + 1);
}

char	**get_env(t_env **env)
{
	char	**ex_env;
	int		len;
	int		i;
	t_env	*head;

	head = *env;
	len = ft_lstsize_env(head);
	ex_env = (char **)malloc ((len + 1) * sizeof(char *));
	i = 0;
	while (head != NULL)
	{
		len = count_env_maillon(head);
		ex_env[i] = (char *)malloc ((len + 1) * sizeof(char));
		ex_env[i] = ft_strjoin_c(head->env_name, head->env_value, '=');
		i++;
		head = head->next;
	}
	ex_env[i] = NULL;
	return (ex_env);
}

int	ms_exec_class(t_params *cmds, t_put *put, t_env **env, t_data **data)
{
	if (ft_strequal(cmds->com[0], "echo") == 0 && cmds->com[1] != NULL)
	{
		if (cmds->com[1][0] == '-')
		{
			if (echo_checker(cmds->com) == 0)
				return (exec_error(3));
			else
				ms_echo(cmds);
		}
	}
	if (ft_strequal(cmds->com[0], "cd") == 0)
		ms_cd(cmds, env);
	else if (ft_strequal(cmds->com[0], "pdw") == 0)
		ms_pwd();
	else if (ft_strequal(cmds->com[0], "export") == 0)
		ms_export(cmds, env);
	else if (ft_strequal(cmds->com[0], "unset") == 0)
		ms_unset(cmds, env);
	else if (ft_strequal(cmds->com[0], "env") == 0)
		ms_env(env);
	// else if (ft_strequal(cmds->com[0], "exit") == 0)
	// 	ms_exit(cmds, put, env, data);
	else
		ms_exec(cmds, get_env(env));
	return (0);
}

