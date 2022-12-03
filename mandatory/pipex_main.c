/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 13:24:13 by adamiens          #+#    #+#             */
/*   Updated: 2022/12/03 19:03:47 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_file	*fd;
	t_args	*args;
	int		pipe_tab[2];

	args = ft_parsing(argc, argv, envp);
	fd = malloc(sizeof(t_file));
	ft_open_file(argc, argv, fd, args);
	pipe(pipe_tab);
	ft_first_read(pipe_tab, args, fd);
	ft_end_read(pipe_tab, args, fd);
	ft_free_struct(args);
	free(fd);
	return (0);
}
