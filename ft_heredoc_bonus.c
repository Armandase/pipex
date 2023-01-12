/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 09:13:54 by adamiens          #+#    #+#             */
/*   Updated: 2022/12/15 09:25:48 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/get_next_line.h"
#include "libft/libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

void	ft_heredoc_verif(char **argv, char **directory, t_args *args)
{
	int		i;
	int		offset;

	offset = 3;
	i = 3;
	while (argv[i + 1])
	{
		if (ft_strlen(argv[i]) == 0)
		{
			write(2, "Error : Empty command\n", 22);
			i++;
			offset++;
		}
		args[i - offset].command = ft_split(argv[i], ' ');
		ft_cpy_path(args[i - offset].command, directory);
		i++;
	}
}

t_args	*ft_heredoc_pars(int argc, char **argv, char **envp)
{
	char	**directory;
	t_args	*args;

	if (argc < 5)
	{
		write(2, "Error : missing parameters", 27);
		exit(1);
	}
	args = ft_calloc(sizeof(t_args), (argc - 3));
	directory = ft_get_path(envp);
	ft_heredoc_verif(argv, directory, args);
	ft_free_strs(directory);
	return (args);
}

char	*ft_cpychr(char *buffer)
{
	int		i;
	char	*ret;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		ret[i] = buffer[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

t_file	*ft_heredoc(char **argv, int argc)
{
	char	*buffer;
	char	*cmp;
	int		fd_buf[2];
	t_file	*fd;

	fd = malloc(sizeof(t_file));
	if (pipe(fd_buf) == -1)
		perror("Error");
	buffer = get_next_line(0);
	cmp = ft_cpychr(buffer);
	while (ft_strncmp(argv[2], cmp, ft_strlen(argv[2]) + 1) != 0)
	{
		ft_putstr_fd(buffer, fd_buf[1]);
		free(buffer);
		buffer = get_next_line(0);
		free(cmp);
		cmp = ft_cpychr(buffer);
	}
	free(cmp);
	fd->fd_in = fd_buf[0];
	close(fd_buf[1]);
	ft_open_file(argc, argv, fd, 1);
	free(buffer);
	return (fd);
}
