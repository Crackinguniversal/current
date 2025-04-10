#ifndef FDF_H
# define FDF_H

# include "../src/mlx/mlx.h"
# include "../gnl/get_next_line.h"
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <unistd.h>
# include <stdarg.h>
# include "../libft/libft.h"
# define WIDTH 1400
# define LENGTH 1000
# define WIDTH1 1300
# define LENGTH1 900

typedef struct s_fdf
{
	char	*filename;
	char	***matrix;
	int		**intmatrix;
	int		fd;
	int		yln;
	int		xwd;
	int		color;
	int		i;
	int		j;
}	t_fdf;

typedef struct s_img
{
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		ln;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	char	*filename;
	char	***matrix;
	int		**intmatrix;
	int		yln;
	int		xwd;
	int		zoom;
	char	*str;
	int		xshift;
	int		yshift;
	float	xangle;
	float	yangle;
	float	zangle;
}	t_mlx;

typedef struct s_draw
{
	float	x;
	float	x1;
	float	y;
	float	y1;
	float	z;
	float	z1;
}	t_draw;

typedef struct s_coordinate
{
	float	x;
	float	y;
	float	z;
	float	angle;
}	t_coordinate;

#endif
