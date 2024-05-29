/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:51:36 by njeanbou          #+#    #+#             */
/*   Updated: 2024/05/29 17:21:25 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <readline/readline.h>
# include <readline/history.h>

# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

typedef enum e_operator {
	none,
	PIPE,
	entre1,
	entre2,
	sortie1,
	sortie2,
}		t_operator;

typedef struct s_put {
	char	*input;
	char	*output;
}	t_put;

typedef struct s_params {
	char			**com;
	t_operator		inp_red;
	t_operator		out_red;
	struct s_params	*next;
}			t_params;

typedef struct s_env {
	char			*env_name;
	char			*env_value;
	bool			is_exported;
	struct s_env	*next;
}			t_env;

typedef struct s_data
{
	int		p_fd[2];
	int		fd_in;
	int		fd_out;
	pid_t	pid;
}			t_data;

//cmd
int		ms_cd(t_params *para, t_env **env);
int		ms_echo(t_params *para);
int		ms_env(t_env **env);
void	ms_exit(t_params *para, t_put *put, t_env **env);
int		ms_export(t_params *para, t_env **env);
int		ms_pwd(void);
int		ms_unset(t_params *para, t_env **env);

//parsing
int		set_para(t_params **param, char *input, t_env **env, t_put **put);
void	set_put(t_put **put, t_params **para);
char	*heredoc(char *exit);
void	ft_doc(t_params **para);
void	set_var(t_params **para, t_env **env);
void	set_enum(t_params **para);
char	**set_cote(char **input);
char	**split_para(char *input);
int		error_quote(char *str);
int		count_quote(char *str, int *i);
int		count_red(char *str, int *i);
int		red_len(char *str, int *i);
int		quote_len(char *str, int *i);
int		ft_error(char **input);
void	print_error(int error);
void	set_varbis(t_params **para, t_env **env);

//error
int		exec_error(int num);

//exec
int		ms_exec_loop(t_data *data, t_params *cmds, t_put *puts, t_env **env);
int		ms_exec_class(t_params *cmds, t_put *puts, t_env **env);
void	ms_exec(t_params *cmds, char **env);
void	ms_input(t_data *data, t_put *puts);
void	ms_output(t_data *data, t_put *puts, int rdr);
void	close_file(int fd);
int		open_file(char *file, int in_or_out);
char	*get_path(char *cmd, char **env);

char	**get_env(t_env **env);

//utils
char	*clean_input(char *raw_input);
t_env	*set_env(char **env);
t_env	*new_node(char *env_name, char *env_value, bool export);
void	print_all(t_params **para, t_env **env, t_put **put);
void	print_com(t_params **para);
char	*recherche_env(char *str, t_env **env);
char	*ft_strjoin_sp(char const *s1, char *s2);
char	**split_var(char *str);
int		count_wd_var(char *str);
char	*clean_var(char *var);
void	free_all(t_params *para, t_put *put);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
int		ft_lstsize_env(t_env *lst);

#endif
