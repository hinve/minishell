/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:55:18 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/02 17:17:22 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_current_directory(void)
{
	char	*buffer;
	size_t	size;

	buffer = NULL;
	size = 0;
	buffer = getcwd(buffer, size);
	if (!buffer)
	{
		perror("getcwd failed");
		return (NULL);
	}
	return (buffer);
}

void	ft_pwd(void)
{
	char	*path;

	path = get_current_directory();
	printf("%s\n", path);
	free(path);
}
