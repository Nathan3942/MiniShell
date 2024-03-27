/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:51:36 by njeanbou          #+#    #+#             */
/*   Updated: 2024/03/27 16:46:57 by njeanbou         ###   ########.fr       */
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
typedef struct s_params {
    char    *com1;
    char    *com2;
    char    *red1;
    char    *red2;
    char    *input;
    char    *output;
    bool    has_n;
}           t_params;


//cmd
int		cmd_echo(t_params *para);
int		cmd_pwd(void);

//utils


#endif
