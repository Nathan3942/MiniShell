/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:43:01 by njeanbou          #+#    #+#             */
/*   Updated: 2024/03/06 15:17:39 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>

void	ls(void)
{
	DIR				*dossier;
	struct dirent	*entre;
	int				i;

	i = 0;
	//modifier "." selon le dossier on se trouver le user dans le shell
	dossier = opendir(".");
	if (!dossier)
		return ;
	entre = readdir(dossier);
	while (entre != NULL)
	{
		entre = readdir(dossier);
		if (entre != NULL)
		{
			if (entre->d_name[0] != '.')
				printf("%s\n", entre->d_name);
		}
		i++;
	}
	closedir(dossier);
}

int	main(void)
{
	ls();
	return (0);
}
