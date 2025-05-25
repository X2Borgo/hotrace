/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:33:41 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/25 16:00:52 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

// 1 billion rose challenge
# define BUFFER_SIZE 1048576
# define WRITE_SIZE 2048
# define SIZE 16777619

# define P 67
# define M 16777619

# define INT_MAX 2147483647
# define LONGLONG_MAX 9223372036854775807

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

extern int	g_char_values[256];

// core_hash.c - Performance critical hash operations
long long	hashing(char *key);
int			ft_strcmp(const char *s1, const char *s2);
t_HashNode	*create_hash_node(char *key, char *value);
int			existing_nodes(t_HashNode *node, char *key, char *value,
				t_HashNode **last);
int			append_hashmap(t_HashNode **node, char *key, char *value);

// memory_ops.c - Optimized memory operations
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *s);
char		*ft_strchr(const char *s, int c);

// parsing_core.c - Core parsing functions
int			reading(char *buff, int len, int offset);
int			init_len(char *line, char *buff, int *buff_i, char *c);
int			handle_cases(t_cases *data, char *line);
int			buff_cycle(t_cases *input_case, char *buff, int *buff_i, int bytes);
int			byte_cycle(t_data *data, char *buff, t_HashMap *hashmap,
				t_longlong **hashlist);

// parsing_utils.c - Parsing utilities
int			case_key(char *line, t_longlong **hashlist, char **key,
				long long *hash);
void		line_message(char *line, char *message);
int			parsing(t_HashMap *hashmap, t_longlong **hashlist);
t_longlong	*append_hashlist(t_longlong **hashlist, t_longlong *tail,
				long long hash);
int			print_value(t_HashNode *node, char *key);

// io_memory.c - I/O and memory management
void		ft_write(int fd, const char *str, size_t len);
void		free_hashmap(t_HashMap *hashmap, t_longlong *hashlist);
void		free_hashlist(t_longlong *hashlist);
void		init_hash_lookup(void);

#endif