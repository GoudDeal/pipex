/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:36:42 by dcyprien          #+#    #+#             */
/*   Updated: 2021/12/07 16:25:47 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
// PATH -> endroits separes par des :

// cat -> /usr/bin/cat

// execve pour lancer les commandes en leur donnant fichier1 comme argument

char	*get_path(char *cmd, char **envp)
{	
	char	**path;
	char	*tmp;
	int		i;

	i = 0;
	path = NULL;
	while (ft_strncmp("PATH=", envp[i], 5))
		i++;
	if (!ft_strncmp("PATH=", envp[i], 5))
		path = ft_split(&envp[i][5], ':');
	i = -1;
	while (path[++i])
	{
		tmp = ft_strcat(path[i], cmd);
		if (access(tmp, F_OK | X_OK) == 0)
		{
			i = 0;
			while (path[i])
				free(path[i++]);
			return (tmp);
		}
		free(tmp);
	}
	return (NULL);
}

int	main(int ac, char **av, char **envp)
{
	int		fdin;
	int		fdout;
	char	*cmd1;
	char	*cmd2;

	if (ac == 5)
	{
		fdin = open(av[1], O_RDONLY, O_CREAT);
		fdout = open(av[4], O_CREAT, O_WRONLY, O_TRUNC, 0644);
		cmd1 = get_path(av[2], envp);
		cmd2 = get_path(av[3], envp);
		printf("%s\n%s\n", cmd1, cmd2);
	}
	return (0);
}
