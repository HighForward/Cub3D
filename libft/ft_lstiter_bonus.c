/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:07:10 by mbrignol          #+#    #+#             */
/*   Updated: 2019/11/20 15:57:16 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list *after;

	if (lst)
	{
		while (lst)
		{
			if (lst->next)
				after = lst->next;
			else
				after = NULL;
			(*f)(lst->content);
			lst = after;
		}
	}
}