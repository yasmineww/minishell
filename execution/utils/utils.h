/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:14:39 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/07 20:53:07 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stdlib.h>

int		ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
char	**ft_split(const char *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
#endif
