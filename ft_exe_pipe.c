/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:38:08 by adamiens          #+#    #+#             */
/*   Updated: 2022/12/02 17:25:29 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

void	ft_wait_end_child(t_args *args, int *pid, t_file *fd)
{
	int	wstatus;
	int	id;
	int	i;

	i = ft_count_pid(args) - 1;
	while (i > 0)
	{
		id = 0;
		id = waitpid(pid[i], &wstatus, 0);
		if (id == -1)
		{
			perror("Error");
			free(fd);
			ft_free_struct(args);
			exit(1);
		}
		i--;
	}
}

void	ft_first_read(int pipe_tab[2][2], t_args *args, t_file *fd, int *tab_pid)
{
	int	tmp;

	tmp = fork();
	if (tmp == -1)
		ft_error(args, fd);
	else if (tmp == 0)
	{
		dup2(fd->fd_in, 0);
		dup2(pipe_tab[0][1], 1);
		close(pipe_tab[0][0]);
		execve(args[0].path, args[0].command, NULL);
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(pipe_tab[0][0], 0);
		close(pipe_tab[0][1]);
		ft_wait_end_child(args, tab_pid, fd);
	}
}

void	ft_end_read(int pipe_tab[2][2], t_args *args, t_file *fd, int *tab_pid, int i)
{
	int	tmp;

	tmp = fork();
	if (tmp == -1)
		ft_error(args, fd);
	else if (tmp == 0)
	{
		dup2(fd->fd_out, 1);
		dup2(pipe_tab[(i % 2) - 1][0], 0);
		close(pipe_tab[0][0]);
		execve(args[i].path, args[i].command, NULL);
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(pipe_tab[0][0], 0);
		close(pipe_tab[0][1]);
		ft_wait_end_child(args, tab_pid, fd);
	}
}
