/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:00:24 by user42            #+#    #+#             */
/*   Updated: 2021/12/16 13:20:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	usage(void)
{
	write(2, "Usage : ./pipex [file1] [command1] [command2] [file2]\n", 55);
	exit(EXIT_FAILURE);
}

void	stop(char *error)
{
	if (errno == 0)
		write(2, "Error\n", 6);
	else
		perror(error);
	exit(EXIT_FAILURE);
}

void	error_cmd(char **cmd, char *path)
{
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, " : command not found\n", 22);
	free_malloc(cmd, path, 2);
	exit(EXIT_FAILURE);
}

void	free_malloc(char **cmd, char *path, int mode)
{
	int	i;

	i = 0;
	if (mode == 2)
	{
		while (cmd[i])
		{
			free(cmd[i]);
			i++;
		}
		free(path);
	}
	if (mode == 1)
	{
		while (cmd[i])
		{
			free(cmd[i]);
			i++;
		}
	}
	if (mode == 3)
		free(path);
}
