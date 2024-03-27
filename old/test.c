/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:23:08 by njeanbou          #+#    #+#             */
/*   Updated: 2024/03/18 18:15:22 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "includes/minishell.h" // Assurez-vous que le chemin d'inclusion est correct

// Définition des fonctions utilisées dans le test
void initialize_environment(t_data *data);
void print_environment(t_data *data);

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		dest = malloc(sizeof(char));
		if (dest == NULL)
			return (NULL);
		dest[0] = '\0';
	}
	else
	{
		if (start + len > ft_strlen(s))
			len = ft_strlen(s) - start;
		dest = malloc(sizeof(char) * (len + 1));
		if (dest == NULL)
			return (NULL);
		i = 0;
		while (++i - 1 < len)
			*(dest + i - 1) = *(s + start + i - 1);
		*(dest + i - 1) = '\0';
	}
	return (dest);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*str != '\0')
	{
		i++;
		str++;
	}
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	while ((char)c != *str)
	{
		if (!*str)
			return (NULL);
		str++;
	}
	return ((char *)str);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = ft_strlen(s);
	write(fd, s, i);
}

void	ft_putendl_fd(char *s, int fd)
{
	size_t	i;

	i = ft_strlen(s);
	write(fd, s, i);
	write(fd, "\n", 1);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

bool	streq(char *str1, char	*str2)
{
	size_t	i;

	if ((str1 && !str2) || (!str1 && str2))
		return (false);
	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (false);
		i++;
	}
	return (true);
}


bool	is_valid_id(char *str)
{
	size_t	i;

	i = 0;
	if (streq(str, "="))
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (ft_isdigit(str[i]) || str[i] == '!' || str[i] == '@'
			|| str[i] == '{' || str[i] == '}' || str[i] == '-')
			return (false);
		i++;
	}
	return (true);
}

t_vlst	*v_new_node(char *var_name, char *var_value, bool is_exported)
{
	t_vlst	*new_node;

	new_node = (t_vlst *)malloc (sizeof(t_vlst));
	new_node->var_name = var_name;
	new_node->var_value = var_value;
	new_node->is_exported = is_exported;
	new_node->next = NULL;
	return (new_node);
}

t_vlst	*v_lstlast(t_vlst *node)
{
	while (node)
	{
		if (!node->next)
			break ;
		node = node->next;
	}
	return (node);
}

void	v_lstadd_back(t_vlst **head, t_vlst *new)
{
	t_vlst	*temp;

	if (head)
	{
		if (!*head)
			*head = new;
		else
		{
			temp = v_lstlast(*(head));
			temp->next = new;
		}
	}
}

static void	invalid_identifer(char *var_name)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(var_name, STDERR_FILENO);
	ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
}

int	unset_var(char *var_name, t_vlst **head)
{
	t_vlst	*temp;
	t_vlst	*next_node;

	temp = *head;
	if (ft_strchr(var_name, '='))
	{
		invalid_identifer(var_name);
		return (EXIT_FAILURE);
	}
	while (temp && temp->next != NULL)
	{
		if (streq(var_name, temp->next->var_name))
		{
			next_node = temp->next->next;
			free(temp->next->var_name);
			free(temp->next->var_value);
			free(temp->next);
			temp->next = next_node;
			break ;
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

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

static int	single_export(t_data *data)
{
	t_vlst	*temp;

	temp = data->envp_lst;
	while (temp != NULL)
	{
		if (temp->is_exported)
			printf("declare -x %s=\"%s\"\n", temp->var_name, temp->var_value);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

static int	export_bad_identifier(char *identifier)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(identifier, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

bool	is_onstr(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == c)
			return (true);
		i++;
	}
	return (false);
}

static void	loop_and_export(char *var_name, t_data *data)
{
	t_vlst	*temp;

	temp = data->envp_lst;
	while (temp != NULL)
	{
		if (streq(var_name, temp->var_name))
		{
			temp->is_exported = true;
			break ;
		}
		temp = temp->next;
	}
}

int	cmd_export(t_statement *statement, t_data *data)
{
	int		exit_status;
	size_t	i;

	if (statement->argc == 1)
		return (single_export(data));
	exit_status = EXIT_SUCCESS;
	i = 0;
	while (statement->argv[++i])
	{
		if (!is_valid_id(statement->argv[i]))
			exit_status = export_bad_identifier(statement->argv[i]);
		else if (is_onstr(statement->argv[i], '='))
		{
			save_user_vars(statement->argv[i], &data->envp_lst, true);
			continue ;
		}
		else
			loop_and_export(statement->argv[i], data);
	}
	return (exit_status);
}

int main() {
    t_data data;
    t_statement statement;

    // Initialisation des données de test
    initialize_environment(&data);
    statement.argc = 2; // Nombre d'arguments de la commande
    statement.argv = (char **)malloc((statement.argc + 1) * sizeof(char *));
    statement.argv[0] = "export"; // Nom de la commande
    statement.argv[1] = "VAR1=value1"; // Premier argument
    //statement.argv[2] = "VAR2"; // Deuxième argument
    statement.argv[2] = NULL; // Marqueur de fin d'arguments

    // Exécution de la commande export
    int exit_status = cmd_export(&statement, &data);

    // Affichage du résultat et de l'environnement après l'exécution
    if (exit_status == EXIT_SUCCESS) {
        printf("Export réussi.\n");
        print_environment(&data);
    } else {
        printf("Export échoué avec le code de sortie %d.\n", exit_status);
    }

    // Libération de la mémoire
    free(statement.argv);

    return 0;
}

// Fonction pour initialiser l'environnement de test
void initialize_environment(t_data *data) {
    // Exemple d'initialisation de quelques variables d'environnement
    data->envp_lst = malloc(sizeof(t_vlst));
    data->envp_lst->var_name = "VAR1";
    data->envp_lst->var_value = "value1";
    data->envp_lst->is_exported = true;
    data->envp_lst->next = malloc(sizeof(t_vlst));
    data->envp_lst->next->var_name = "VAR2";
    data->envp_lst->next->var_value = "value2";
    data->envp_lst->next->is_exported = true;
    data->envp_lst->next->next = NULL;
}

// Fonction pour afficher l'environnement
void print_environment(t_data *data) {
    printf("Environnement :\n");
    t_vlst *temp = data->envp_lst;
    while (temp != NULL) {
        printf("Variable: %s=%s, Exported: %s\n", temp->var_name, temp->var_value, temp->is_exported ? "true" : "false");
        temp = temp->next;
    }
}
