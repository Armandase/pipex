/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 13:09:58 by adamiens          #+#    #+#             */
/*   Updated: 2022/11/29 10:51:52 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <unistd.h>

void	ft_exit_error(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	exit(1);
}

char	*ft_find_path(char **envp)
{
	int		i;
	char	*ret;
	size_t	len;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 4) == 0)
		{
			len = ft_strlen(envp[i]) + 1;
			ret = malloc(sizeof(char) * len);
			if (!ret)
				return (NULL);
			ft_strlcpy(ret, envp[i], len);
			return (ret);
		}
		i++;
	}
	return (NULL);
}

char	**ft_get_path(char **envp)
{
	int		len;
	char	*tmp;
	char	*path;
	char	**directory;

	path = ft_find_path(envp);
	if (!path)
		exit(1);
	directory = ft_split(path, ':');
	free(path);
	if (!directory)
		exit(1);
	len = ft_strlen(directory[0]);
	tmp = ft_substr(directory[0], 5, len);
	if (!tmp)
		ft_exit_error(directory);
	free(directory[0]);
	directory[0] = tmp;
	return (directory);
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	ft_cpy_path(char **directory, char **argv, int i, char **ret)
{
	int		j;
	char	*tmp;
	char	*str;

	j = 0;
	while (directory[j])
	{
		tmp = ft_strjoin(directory[j], "/");
		str = ft_strjoin(tmp, argv[i]);
		free(tmp);
		if (access(str, X_OK) == 0)
		{
			ret[i - 2] = ft_strdup(str);
			free(str);
			break ;
		}
		else
			free(str);
		j++;
	}
	if (!(directory[j]))
	{
		if (ret)
			free_strs(ret);
		ft_exit_error(directory);
	}
}

char	**ft_verif_args(char **argv, char **directory)
{
	int		i;
	char	**ret;

	ret = ft_calloc(3, sizeof(char *));
	if (!ret)
		ft_exit_error(directory);
	i = 2;
	while (argv[i + 1])
	{
		ft_cpy_path(directory, argv, i, ret);
		i++;
	}
	ret[i - 2] = NULL;
	return (ret);
}

void	ft_parsing(char **argv, char **envp)
{
	char	**directory;
	char	**args;
	t_args	*arguments;

	arguments = malloc(sizeof(t_args) * 3);
	directory = ft_get_path(envp);
	args = ft_verif_args(argv, directory);
	arguments[0].command = args[0];
	arguments[1].command = args[1];
	arguments[2].command = NULL;
	free(args);
	int i = 0;
	while (directory[i])
	{
		free(directory[i]);
		i++;
	}
	free(directory);
	i = 0;
	while (arguments[i].command)
	{
		ft_printf("%s\n", arguments[i].command);
		free(arguments[i].command);
		i++;
	}
	free(arguments[2].command);
	free(arguments);
}
