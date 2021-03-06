/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:13:12 by mbrignol          #+#    #+#             */
/*   Updated: 2020/01/18 11:58:10 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		lens1;
	char	*str;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return ((char *)s1);
	i = 0;
	while (s1[i] != '\0' && ft_strchr((char *)set, (char)s1[i]) != NULL)
		i++;
	lens1 = ft_strlen((char *)&s1[i]);
	if (lens1 != 0)
	{
		while (ft_strchr((char *)set, (char)s1[i + lens1 - 1]) != NULL)
			lens1--;
	}
	if (!(str = malloc(sizeof(char) * (lens1 + 1))))
		return (NULL);
	ft_strlcpy(str, &s1[i], lens1 + 1);
	str[lens1] = '\0';
	return (str);
}
