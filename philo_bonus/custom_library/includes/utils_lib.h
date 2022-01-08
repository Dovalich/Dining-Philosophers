/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:14:48 by nammari           #+#    #+#             */
/*   Updated: 2022/01/08 11:04:25 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_LIB_H
# define UTILS_LIB_H

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>

bool			is_num(char *str);
unsigned long	ft_strlen(char *str);
bool			is_bigger_than_ulong_max(char *str);
unsigned long	atoul(char *str);
char			*ft_ultoa(unsigned long num);
void			ft_putstr_fd(char *str, int fd);
int				ft_strcmp(const char *s1, const char *s2);

#endif