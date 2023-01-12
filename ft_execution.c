/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:02:48 by adamiens          #+#    #+#             */
/*   Updated: 2022/12/14 17:21:30 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	ft_count_pid(t_args *args)
{
	int	i;

	i = 0;
	while (args[i].command != NULL)
		i++;
	return (i);
}

void	ft_init_dup(t_args *args, int i, t_file *fd, int *tab_pid)
{
	int	ret;

	dup2(fd->pipe_tab[(i - 1) % 2][0], 0);
	dup2(fd->pipe_tab[i % 2][1], 1);
	ft_close_pipe(fd->pipe_tab);
	ret = execve(args[i].command[0], args[i].command, NULL);
	if (ret == -1)
		ft_execve_error(fd, args, tab_pid);
	exit(EXIT_FAILURE);
}

void	ft_open_pipe(t_file *fd, int i)
{
	close(fd->pipe_tab[i % 2][1]);
	close(fd->pipe_tab[i % 2][0]);
	pipe(fd->pipe_tab[i % 2]);
}

int	ft_get_exec(t_args *args, t_file *fd, int i, int *tab_pid)
{
	i++;
	while (args[i + 1].command)
	{
		ft_open_pipe(fd, i);
		tab_pid[i] = fork();
		if (tab_pid[i] == -1)
			ft_error(args, fd);
		else if (tab_pid[i] == 0)
			ft_init_dup(args, i, fd, tab_pid);
		dup2(fd->pipe_tab[i % 2][0], 0);
		i++;
	}
	ft_open_pipe(fd, i);
	if (fd->fd_out != -1)
		ft_end_read(args, fd, tab_pid, i);
	else
		i--;
	return (i);
}

void	ft_init_exec(t_args *args, t_file *fd)
{
	int	i;
	int	*tab_pid;
	int	start;

	i = ft_count_pid(args);
	tab_pid = malloc(sizeof(int) * i);
	i = 0;
	start = 0;
	pipe(fd->pipe_tab[0]);
	pipe(fd->pipe_tab[1]);
	if (fd->fd_in != -1)
		ft_first_read(args, fd, &tab_pid[i]);
	else
		start = 2;
	i = ft_get_exec(args, fd, i, tab_pid);
	while (i >= start)
	{
		ft_wait_end_child(args, tab_pid[i], fd);
		i--;
	}
	ft_close_pipe(fd->pipe_tab);
	free(tab_pid);
}
