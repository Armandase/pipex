/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:34:42 by adamiens          #+#    #+#             */
/*   Updated: 2022/11/30 16:12:28 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

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

int	ft_cpy_path(char **directory, char *argv, t_args *args , int i)
{
	int		j;
	char	*tmp;
	char	*str;

	j = 0;
	while (directory[j])
	{
		tmp = ft_strjoin(directory[j], "/");
		str = ft_strjoin(tmp, argv);
		free(tmp);
		if (access(str, X_OK) == 0)
		{
			args[i - 2].path = ft_strdup(str);
			free(str);
			break ;
		}
		else
			free(str);
		j++;
	}
	free(argv);
	if (!(directory[j]))
		return (0);
	return (1);
}
