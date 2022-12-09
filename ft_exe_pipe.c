/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:38:08 by adamiens          #+#    #+#             */
/*   Updated: 2022/12/08 18:59:54 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <unistd.h>

void	ft_close_pipe(int pipe_tab[2][2])
{
	close(pipe_tab[0][0]);
	close(pipe_tab[0][1]);
	close(pipe_tab[1][0]);
	close(pipe_tab[1][1]);
}

void	ft_wait_end_child(t_args *args, int pid, t_file *fd)
{
	int	wstatus;
	int	id;

	id = 0;
	id = waitpid(pid, &wstatus, 0);
	if (id == -1)
	{
		perror("Wait pid error");
		free(fd);
		ft_free_struct(args);
		exit(1);
	}
}

void	ft_first_read(int pipe_tab[2][2], t_args *args, t_file *fd, int *tab_pid)
{
	*tab_pid = fork();
	if (*tab_pid == -1)
		ft_error(args, fd);
	else if (*tab_pid == 0)
	{
		dup2(fd->fd_in, 0);
		dup2(pipe_tab[0][1], 1);
		ft_close_pipe(pipe_tab);
		execve(args[0].command[0], args[0].command, NULL);
		perror("Execve error");
		exit(EXIT_FAILURE);
	}
	dup2(pipe_tab[0][0], 0);
}

void	ft_end_read(int pipe_tab[2][2], t_args *args, t_file *fd, int *tab_pid, int i)
{
	tab_pid[i] = fork();
	if (tab_pid[i] == -1)
		ft_error(args, fd);
	else if (tab_pid[i] == 0)
	{
		dup2(pipe_tab[(i - 1) % 2][0], 0);
		dup2(fd->fd_out, 1);
		ft_close_pipe(pipe_tab);
		execve(args[i].command[0], args[i].command, NULL);
		perror("Execve error");
		exit(EXIT_FAILURE);
	}
	ft_close_pipe(pipe_tab);
	if (fd->fd_in != -1)
		close(fd->fd_in);
	if (fd->fd_out != -1)
		close(fd->fd_out);
}
