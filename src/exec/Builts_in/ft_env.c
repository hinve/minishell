/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:27:37 by mjeannin          #+#    #+#             */
/*   Updated: 2024/11/21 15:32:13 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_shell *data)
{
	t_env	*current;

	current = data->env;
	if (!current || !current->value || current->value[0] == '\0')
	{
		printf("Value is empty or not set\n");
		return (status(data, 1));
	}
	while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (status(data, 0));
}
