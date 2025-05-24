/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:33:41 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/24 15:47:35 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

# define BUFFER_SIZE (1 << 17) // 256 KB
// TODO: provare se allocare dinamicamente funziona meglio ( > 18 )
# define INT_MAX 2147483647
# define LONGLONG_MAX 9223372036854775807
# define SIZE 1000003

# define P 67
# define M 1000003
# define CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_ "

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct s_longlong
{
	long long			hash;
	struct s_longlong	*next;
}	t_longlong;

typedef struct s_HashNode {
    char	*key;
    char	*value;
    struct s_HashNode* next;
}	t_HashNode;

typedef struct s_HashMap {
    t_HashNode	*table[SIZE];
}	t_HashMap;

int     ft_putchar(char c);
int     ft_putnbr(int n);

size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

size_t	ft_strlen(const char *str);

void	*ft_memset(void *s, int c, size_t n);

void	*ft_calloc(size_t nmemb, size_t size);

char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t len);

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free_1(char const *s1, char const *s2);

char	*ft_strchr(const char *s, int c);
char	*ft_strnchr(const char *s, int c, size_t len);

char	*get_next_line(int fd);

#endif