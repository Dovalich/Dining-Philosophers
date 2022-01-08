/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:21:52 by nammari           #+#    #+#             */
/*   Updated: 2022/01/08 11:01:37 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_lib.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned long		i;
	unsigned char		*str1;
	unsigned char		*str2;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1 && s2)
		return (s2[0]);
	else if (s1 && !s2)
		return (s1[0]);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (s1[i] && s2[i] && str1[i] == str2[i])
		++i;
	return (str1[i] - str2[i]);
}
