/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:14:39 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/24 17:15:46 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stdlib.h>
#include "../../minishell.h"
int		ft_strlen(const char *s);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
// char	*ft_strdup(const char *s);
char	**ft_split(const char *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
// int		ft_strcmp(const char *s1, const char *s2);
int		isalpha_underscore(int c);
char	**ft_freew(char **s);
void	ft_bzero(void *s, size_t n);

#endif
