/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:10:16 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/13 22:36:32 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_back(t_list **stack_a, char **content)
{
	t_list	*node;
	t_list	*temp;

	node = malloc (sizeof(t_list));
		puts ("add");
	if (!node)
		return ;
	node->cmd = content;
	node->next = NULL;
	if ((*stack_a) == NULL)
	{
		*stack_a = node;
		return ;
	}
	temp = *stack_a;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = node;
}

void	store_cmd(char *input, t_list *cmd)
{
	char	**s;
	int		i;

	i = 0;
	s = ft_split(input, '|');
	if (s == NULL)
		return ;
	while (s[i])
	{
		add_back(&cmd, &s[i]);
		free(s[i]);
		s[i] = NULL;
		i++;
	}
	free(s);
}

int	main ()
{
	char	*input;
	t_list	**cmd;

	cmd = NULL;
	while (1)
	{
		input = readline("Minishell$ ");
		add_history(input);
		syntax_error(input);
		puts ("main");
		store_cmd(input, *cmd);
		t_list *current = cmd;  // Added this line
        while (current->next)  // Changed this line
        {
			puts ("ok");
            printf("%s\n", current->cmd);  // Changed this line
            current = current->next;  // Changed this line
        }
        printf("%s\n", current->cmd);  // Changed this line
    }
}
