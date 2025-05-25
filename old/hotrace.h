/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:33:41 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/25 14:13:21 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

// 1 billion rose challenge
# define BUFFER_SIZE 1048576
# define INT_MAX 2147483647
# define LONGLONG_MAX 9223372036854775807
# define SIZE 16777619
# define WRITE_SIZE 2048

# define P 67
# define M 16777619

# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdint.h>

typedef struct s_longlong
{
	long long			hash;
	struct s_longlong	*next;
}	t_longlong;

typedef struct s_HashNode
{
	char				*key;
	char				*value;
	struct s_HashNode	*next;
}	t_HashNode;

typedef struct s_HashMap
{
	t_HashNode	**table;
}	t_HashMap;

typedef struct s_cases
{
	int			*i;
	char		*line;
	t_longlong	**hashlist;
	t_HashMap	*hashmap;
	char		**key;
	long long	*hash;
}	t_cases;

typedef struct s_data
{
	long long	hash;
	int			bytes;
	int			buff_i;
	int			offset;
	int			i;
	int			ret;
	char		*key;
}	t_data;

size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlcat(char *dest, char *src, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

void		ft_write(int fd, const char *str, size_t len);

size_t		ft_strlen(const char *str);

void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);

char		*ft_strdup(const char *s);
char		*ft_strndup(const char *s, size_t len);

char		*ft_strchr(const char *s, int c);
char		*ft_strnchr(const char *s, int c, size_t len);

long long	hashing(char *key);
t_longlong	*append_hashlist(t_longlong **hashlist, t_longlong *tail,
				long long hash);
int			append_hashmap(t_HashNode **node, char *key, char *value);
int			print_value(t_HashNode *node, char *key);
int			parsing(t_HashMap *hashmap, t_longlong **hashlist);

#endif