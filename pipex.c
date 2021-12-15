/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:36:42 by dcyprien          #+#    #+#             */
/*   Updated: 2021/12/15 17:52:13 by user42           ###   ########.fr       */
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
	{
		path = ft_split(&envp[i][5], ':');
	}
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

void	ft_first_command(char *path, char **av, int *pipefd, int *fd, char **envp)
{
	pid_t	pid;
	char	**cmd;

	cmd = NULL;
	cmd = ft_split(av[2], ' ');
	pid = fork();
	if (pid < 0)
		terminate("fork");
	if (pid == 0)
	{
		if (fd[0] < 0)
			terminate("Failed to open infile");
		close(pipefd[0]);
		dup2(fd[0], STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		if(path && cmd[0])
			execve(path, cmd, envp);
		else
			error_cmd(cmd[0]);
	}
}

void	ft_second_command(char *path, char **av, int *pipefd, int *fd, char **envp)
{
	pid_t		pid;
	char		**cmd;

	cmd = NULL;
	cmd = ft_split(av[3], ' ');
	pid = fork();
	if (pid < 0)
		terminate("fork");
	if (pid == 0)
	{
		if (fd[1] < 0)
			terminate("Failed to open outfile");
		close(pipefd[1]);
		dup2(fd[1], STDOUT_FILENO);
		dup2(pipefd[0], STDIN_FILENO);
		if(path && cmd[0])
			execve(path, cmd, envp);
		else
			error_cmd(cmd[0]);
	}
}

int	main(int ac, char **av, char **envp)
{
	int		fds[2];
	char	*cmd_one;
	char	*cmd_two;
	int		pipefd[2];
	int		status;

	if (ac != 5)
		usage();
	else
	{
		if (pipe(pipefd) < 0)
			terminate(NULL);
		fds[0] = open(av[1], O_RDONLY | O_CREAT, 0644);
		fds[1] = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		cmd_one = get_path(av[2], envp);
		cmd_two = get_path(av[3], envp);
		ft_first_command(cmd_one, av, pipefd, fds, envp);
		ft_second_command(cmd_two, av, pipefd, fds, envp);
		free(cmd_one);
		free(cmd_two);
		close(fds[0]);
		close(fds[1]);
		waitpid(-1, &status, 0);
		waitpid(-1, &status, 0);
	}
	return (0);
}
