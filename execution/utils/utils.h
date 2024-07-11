/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:14:39 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/11 12:19:24 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include "../../minishell.h"

int		ft_strlen(const char *s);
char	*ft_substr(char *s, int start, int len);
int		ft_isalpha_num(char c);
char	*ft_strdup(char *s1);
char	**ft_split(const char *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
int		isalpha_underscore(int c, int flag);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	ft_putendl_fd(char *s, int fd);
char	*ft_itoa(int n);
char	*ft_strtrim(char *s1, char *set);
int		my_atoi(char *str);

#endif
