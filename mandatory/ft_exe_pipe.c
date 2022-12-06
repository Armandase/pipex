/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:38:08 by adamiens          #+#    #+#             */
/*   Updated: 2022/12/04 12:02:05 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void	ft_error(t_args *args, t_file *fd)
{
	perror("Error");
	ft_free_struct(args);
	free(fd);
	exit(1);
}

void	ft_wait_end_child(t_args *args, int pid, t_file *fd)
{
	int	wstatus;
	int	id;

	id = 0;
	id = waitpid(pid, &wstatus, 0);
	if (id == -1)
	{
		perror("Error");
		free(fd);
		ft_free_struct(args);
		exit(1);
	}
}

void	ft_first_read(int pipe_tab[2], t_args *args, t_file *fd)
{
	int	tmp;

	tmp = fork();
	if (tmp == -1)
		ft_error(args, fd);
	else if (tmp == 0)
	{
		dup2(fd->fd_in, 0);
		dup2(pipe_tab[1], 1);
		close(pipe_tab[0]);
		execve(args[0].path, args[0].command, NULL);
		perror("Error");
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(pipe_tab[0], 0);
		close(pipe_tab[1]);
		ft_wait_end_child(args, tmp, fd);
	}
}

void	ft_end_read(int pipe_tab[2], t_args *args, t_file *fd)
{
	int	tmp;

	tmp = fork();
	if (tmp == -1)
		ft_error(args, fd);
	else if (tmp == 0)
	{
		dup2(pipe_tab[0], 0);
		dup2(fd->fd_out, 1);
		close(pipe_tab[0]);
		execve(args[1].path, args[1].command, NULL);
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(pipe_tab[0], 0);
		close(pipe_tab[1]);
		ft_wait_end_child(args, tmp, fd);
	}
}
