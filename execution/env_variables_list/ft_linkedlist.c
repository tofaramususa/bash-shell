/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linkedlist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:54:06 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/19 14:29:57 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * sort_list: is a function that sort linked list
 * @head: the head of linked lists
*/

void	sort_list(t_list *head)
{
	t_list	*current;
	t_list	*compare;
	char	*temp_content;
	char	*temp_value;

	current = head;
	while (current->next != NULL)
	{
		compare = current->next;
		while (compare != NULL)
		{
			if (ft_strcmp(current->key, compare->key) > 0)
			{
				temp_content = current->key;
				temp_value = current->value;
				current->key = compare->key;
				current->value = compare->value;
				compare->key = temp_content;
				compare->value = temp_value;
			}
			compare = compare->next;
		}
		current = current->next;
	}
}

/**
 * re_index: is a function that gives the index for the linked list
 * @head: pointer pointing to head of the linked list
*/
void	re_index(t_list *head)
{
	t_list	*prev;
	int		x;

	x = 0;
	prev = head;
	while (prev)
	{
		prev->index = x++;
		prev = prev->next;
	}
}

/**
 * first_element: remove element at index 0
 * @head: the linked list which contains the env
 * @index: index of list to be removed from the linked list
*/
static void	first_element(t_list **head)
{
	t_list	*current;

	current = *head;
	*head = current->next;
	simple_free(current);
}

/**
 * remove_element: is a function that removes an element at position of index
 * form the linked list
 * @head: the linked list which contains the env
 * @index: index of list to be removed from the linked list
*/
int	remove_element(t_list **head, int index)
{
	t_list	*current;
	t_list	*prev;

	current = *head;
	prev = NULL;
	if (index == 0)
		first_element(head);
	else
	{
		while (current != NULL)
		{
			if (current->index == index)
			{
				prev->next = current->next;
				simple_free(current->key);
				simple_free(current->value);
				simple_free(current);
				break ;
			}
			prev = current;
			current = current->next;
		}
	}
	return (re_index(*head), 0);
}

/**
 * linked_to_array: is a function that converts
 * @head: the head of the linked list
*/
char	**linked_to_array(t_list *head)
{
	t_list	*tmp;
	char	**copy_env;
	int		len;
	int		x;

	len = ft_lstsize(head);
	tmp = head;
	copy_env = malloc(sizeof(char *) * (len + 1));
	x = 0;
	while (tmp)
	{
		copy_env[x] = ft_strjoin(tmp->key, tmp->value);
		tmp = tmp->next;
		x++;
	}
	copy_env[x] = NULL;
	x = 0;
	return (copy_env);
}
