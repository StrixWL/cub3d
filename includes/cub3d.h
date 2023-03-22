/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 01:56:57 by yabidi            #+#    #+#             */
/*   Updated: 2023/03/21 20:59:46 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include "header.h"

typedef struct t_file
{
	char			*line;
	int				len;
	struct t_file	*next;
}	t_file;

typedef struct t_settings
{
	char				*identifier;
	char				*value;
	int					size;
	struct t_settings	*next;
}	t_settings;

int			parsing(char *s, t_settings *settings);
int			fill_file(int fd, t_file *file);
int			fill_settings(t_settings *settings, t_file *file);
int			check_all(t_file *file);
t_file		*new_node_file(void);
char		*ft_strdup2(char *src);
char		*skip_spaces_and_emptylines(t_file **file);
char		*ft_strrchr(const char *str, int ch);
char		*get_next_line(int fd);
int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlen(const char *s);
char		*ft_strdup(char *src);
int			ft_strncmp(char *s1, char *s2, unsigned int n);
int			ft_strncmp2(char *s1, char *s2, unsigned int n);
void		skip_spaces(char **file);
void		free_file(t_file *file);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_atoi(const char *str);
char		**ft_split(char const *s, char c);
t_settings	*new_node_settings(void);
char		*ft_itoa(int n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*read_picture(int fd);
int			take_w_h(char *s, int *w, int *h);
int			check_map_and_nelements_array(t_file *file,
				char *check_elem, char *s);
void		free_empty_lines(t_file *file);
int			check_elements(char *s, char *check_elem);
int			fill_map(t_file *file, t_settings *settings);
int			check_line(t_file *file, char *s, char *s2, int *player);
int			is_multiplayer(char *keep_line, char *s, int player);
char		*remove_spaces(char *s);
void		remove_new_lines(t_file *file);

#endif