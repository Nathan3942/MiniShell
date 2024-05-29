/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptit_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:02:34 by ichpakov          #+#    #+#             */
/*   Updated: 2024/05/29 16:22:57 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_exec(t_params *cmds, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = cmds->com;
	path = get_path(s_cmd[0], env);
	execve(path, s_cmd, env);
	ft_putstr_fd("error: command not found: ", 2);
	ft_putendl_fd(s_cmd[0], 2);
	exit(0);
}

static int	ms_redir_exec(t_data *data, t_params *cmds, t_put *puts, t_env **env)
{
	int	p_fd[2];
	int	status;

	if (!data || !cmds || !puts || !env)
		return (exec_error(1));
	if (cmds->inp_red == entre1)
		ms_input(data, puts);
	if (cmds->inp_red == PIPE)
	{
		if (pipe(p_fd) == -1)
			return (exec_error(0));
	}
	data->pid = fork();
	if (data->pid == -1)
		return (exec_error(1));
	if (data->pid == 0)
	{
		if (cmds->out_red == PIPE)
		{
			// if (dup2(p_fd[1], 1) == -1 || close(p_fd[0]) == -1 || close(p_fd[1]) == -1)
			// 	return (exec_error(0));
			if (dup2(p_fd[1], STDOUT_FILENO) == -1)
				return (exec_error(0));
			close(p_fd[0]);
			close(p_fd[1]);
		}
		else if (cmds->out_red == sortie1)
			ms_output(data, puts, 1);
		else if (cmds->out_red == sortie2)
			ms_output(data, puts, 2);
		ms_exec_class(cmds, puts, env);
		exec_error(2);
	}
	// if (cmds->out_red == PIPE)
	// 	close(p_fd[1]);
	else
	{
		if (waitpid(data->pid, &status, 0) == -1)
		{
			perror("waitpid");
			return (exec_error(1));
		}
		if (cmds->out_red == PIPE)
		{
			close(p_fd[1]);
			if (dup2(p_fd[0], STDIN_FILENO) == -1)
				return (exec_error(0));
			close(p_fd[0]);
		}
		// if (cmds->out_red == PIPE)
		// 	close(p_fd[0]);
	}
	// if (cmds->out_red == PIPE)
	// {
	// 	if (dup2(p_fd[0], 0) == -1 || close(p_fd[0]) == -1)
	// 		return (exec_error(0));
	// }
	return (WIFEXITED(status) && WEXITSTATUS(status));
}


int	ms_exec_loop(t_data *data, t_params *cmds, t_put *puts, t_env **env)
{
	t_params	*t_cmds;
	int			status;

	t_cmds = cmds;
	while (t_cmds != NULL)
	{
		status = ms_redir_exec(data, t_cmds, puts, env); //renvoie l'etat du resultat 
		printf("commande suivante\n");
		t_cmds = t_cmds->next;
	}
	return (status);
}
