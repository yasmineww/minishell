/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:27:34 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/30 15:58:05 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cases(char *ptr, int i)
{
	if (ptr[i] == '|')
		return (1);
	if (special_last(ptr))
		return (1);
	if (two_specials(ptr))
		return (1);
	return (0);
}

int	syntax_error(char *ptr)
{
	int	i;

	i = 0;
	while (check_space(&ptr[i]))
		i++;
	if (cases(ptr, i))
		return (1);
	return (0);
}

int	count_quote(char *input, int i, int count)
{
	while (input[i])
	{
		if (input[i] == '\'')
		{
			count++;
			i++;
			while (input[i] && input[i] != '\'')
				input[i++] *= -1;
			if (input[i] == '\'')
				count++;
		}
		else if (input[i] == '\"')
		{
			count++;
			i++;
			while (input[i] && input[i] != '\"')
				input[i++] *= -1;
			if (input[i] == '\"')
				count++;
		}
		if (input[i])
			i++;
	}
	return (count);
}

int	quotes_syntax_error(char *input)
{
	int	num;

	num = count_quote(input, 0, 0);
	if (num % 2 != 0)
		return (1);
	return (0);
}

int	parsing(t_mini *mini, char *input)
{
	char	*tmp;

	tmp = input;
	while ((*tmp >= 9 && *tmp <= 13) || *tmp == 32)
		tmp++;
	if (!*tmp)
	{
		free(input);
		return (1);
	}
	if (quotes_syntax_error(input) || syntax_error(input))
	{
		error_message(input, &mini->status);
		return (1);
	}
	tmp = add_space(input);
	split_cmd(&mini->list, tmp);
	free(input);
	input = NULL;
	return (0);
}
