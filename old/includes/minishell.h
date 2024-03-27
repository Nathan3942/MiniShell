/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:51:36 by njeanbou          #+#    #+#             */
/*   Updated: 2024/03/18 17:53:20 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <readline/readline.h>
# include <readline/history.h>

# include <stdbool.h>
# include <stdio.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>

/* Constante */

/* Error messages */

// MINISHELL

// SYNTAX

// EXIT CMD

// CD CMD

/*sert a determiner comment les commandes doivent etre traiter
lors de l'analyse et l'execution*/
typedef enum e_operator {
	NONE,
	RDR_OUT_REMPLACE,
	RDR_OUT_APPEND,
	RDR_INPUT,
	RDR_INPUT_UNTIL,
	PIPE,
}				t_operator;

/*represente chaque commande ou declaration entree par le user*/
typedef struct s_statement {
	int					argc;
	char				**argv;
	t_operator			operator;
	struct s_statement	*next;
}						t_statement;

/*sert a stocker et gerer les variable d'environement*/
typedef struct s_vlst {
	char			*var_name;
	char			*var_value;
	bool			is_exported;
	struct s_vlst	*next;
}					t_vlst;

/*sert a stocker et gerer les donne globales du shell
(contient les autre structure)*/
typedef struct s_data {
	char		**envp;
	t_vlst		*envp_lst;
	t_statement	*head;
}				t_data;


//cmd
int		cmd_echo(t_statement *statement, bool has_n);
int		cmd_pwd(void);

//utils
char	*clean_input(char *s1, char const *set);
bool	is_valid_id(char *str);
bool	streq(char *str1, char	*str2);

t_vlst	*v_new_node(char *var_name, char *var_value, bool is_exported);
t_vlst	*v_lstlast(t_vlst *node);
void	v_lstadd_back(t_vlst **head, t_vlst *new);

#endif
