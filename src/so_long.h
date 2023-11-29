/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:24:13 by jrim              #+#    #+#             */
/*   Updated: 2022/05/10 21:53:51 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# define TILES 60
# define ELM "01PEC"

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_EXIT 17

# define KEY_EXIT 53
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_UP 126
# define KEY_DW 125
# define KEY_LF 123
# define KEY_RT 124

# define DIR_UP 0
# define DIR_DW 1
# define DIR_LF 2 
# define DIR_RT 3

# define RED "\\033[0;31m"
# define GRN "\\033[0;32m"
# define YLW "\\033[0;33m"
# define BLU "\\033[0;36m"
# define DFL "\\033[0;37m"

typedef struct s_img
{
	void	*ptr;
	int		*data;
	int		h;
	int		w;
}			t_img;

typedef struct s_val
{
	int		_p;
	int		_e;
	int		_c;
}			t_val;

typedef struct s_map
{
	t_val	*val;
	int		rows;
	int		cols;
	int		*c_pos;
	char	**coord;
}			t_map;

typedef struct s_player
{
	t_img	p_img;
	int		step;
	int		c_tot;
	int		c_cur;
	int		x_pos;
	int		y_pos;
	int		x_end;
	int		y_end;
	int		dir;
}			t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img_dlf;
	t_img		road;
	t_img		wall;
	t_img		exit;
	t_img		collec;
	t_player	player;
	t_map		maps;
	int			end;
}				t_game;

// so_long.c
int		key_press(int key, t_game *game);
int		main_loop(t_game *game);
void	end_check(t_game *game, t_player *player);
int		game_end(t_game *game);

// _map_gen.c
void	map_gen(t_game *game);

// _map_read.c
void	map_read(t_game *game, char *map_file);
void	_map_cnt(t_game *game, char *map_file);
void	_map_malloc(t_game *game);
void	_map_save(t_game *game, char *map_file);

// _map_check.c
void	map_check(t_game *game, char **map);
void	_init_val(t_val **val);
void	_check_elm(t_game *game, char **map);

// _init.c
void	game_init(t_game *game);
void	_init_img(t_game *game);
void	_init_p(t_game *game, t_player *player);
void	_init_c(t_game *game, t_map *map);

// _move.c
void	move(t_game *game, t_player *player, int new_dir);
void	_alt_dir(t_game *game, t_player *player, int new_dir);
int		_stuck(char **map, t_player *player, int new_dir);
void	_alt_tile(t_player *player, char **map);
void	_alt_pos(t_player *player, int new_dir);

// _collec.c
void	collec(t_game *game, t_player *player);
void	_collec_msg(t_player *player);
void	_alt_collec(t_game *game, int c_pos);

// _utils.c
void	msg_err(char *msg);
void	msg_dfl(char *msg1, int num, char *msg2);
void	*file_to_img(t_game *game, char *str);
void	put_img(t_game *game, void *img_ptr, int x, int y);

#endif
