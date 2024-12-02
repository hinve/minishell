/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:55:18 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/01 19:05:03 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_current_directory(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		perror("Error: getcwd failed");
	return (path);
}

void	ft_pwd(void)
{
	char	*path;

	path = get_current_directory();
	printf("%s\n", path);
	free(path);
}
