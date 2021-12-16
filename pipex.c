/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:36:42 by dcyprien          #+#    #+#             */
/*   Updated: 2021/12/16 13:22:50 by user42           ###   ########.fr       */
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
		printf("p = %p\n", path[i]);
		if (tmp != NULL)
		{
			if (access(tmp, F_OK | X_OK) == 0)
			{
				i = 0;
				free_malloc(path, cmd, 1);
				return (tmp);
			}
		}
		free(tmp);
	}
	return (NULL);
}

pid_t	ft_first_command(char **av, int *pipefd, int *fd, char **envp)
{
	pid_t	pid;
	char	**cmd;
	char	*path;
	int		i;

	i = 0;
	cmd = ft_split(av[2], ' ');
	path = get_path(cmd[0], envp);
	pid = fork();
	while (cmd[i])
		{
			printf("path = %p\n", &path);
			printf("cmd = %p\n", cmd[i]);
			i++;
		}
	if (pid < 0)
		stop("fork");
	if (pid == 0)
	{
		if (fd[0] < 0)
			stop("Failed to open input file");
		close(pipefd[0]);
		dup2(fd[0], STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		
		if (path && cmd[0])
		{
			
			execve(path, cmd, envp);
			free_malloc(cmd, path, 2);
		}
		else
			error_cmd(cmd, path);
	}
	return (pid);
}

pid_t	ft_second_command(char **av, int *pipefd, int *fd, char **envp)
{
	pid_t		pid;
	char		**cmd;
	char		*path;
	int			i;

	i = -1;
	cmd = ft_split(av[3], ' ');
	path = get_path(cmd[0], envp);
	pid = fork();
	if (pid < 0)
		stop("fork");
	if (pid == 0)
	{
		if (fd[1] < 0)
			stop("Failed to open output file");
		close(pipefd[1]);
		dup2(fd[1], STDOUT_FILENO);
		dup2(pipefd[0], STDIN_FILENO);
		if (path && cmd[0])
		{
			execve(path, cmd, envp);
			while (cmd[i++])
				free(cmd[i]);
			free(path);
		}
		else
			error_cmd(cmd, path);
	}
	return (pid);
}

int	main(int ac, char **av, char **envp)
{
	int			fds[2];
	int			pipefd[2];
	int			status;
	pid_t		first_pid;
	pid_t		second_pid;

	if (ac != 5)
		usage();
	else
	{
		if (pipe(pipefd) < 0)
			stop(NULL);
		fds[0] = open(av[1], O_RDONLY | O_CREAT, 0644);
		fds[1] = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		first_pid = ft_first_command(av, pipefd, fds, envp);
		second_pid = ft_second_command(av, pipefd, fds, envp);
		close(fds[0]);
		close(fds[1]);
		waitpid(first_pid, &status, WNOHANG);
		waitpid(second_pid, &status, WNOHANG);
	}
	return (0);
}
