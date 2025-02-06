#include "../headers/FDF.h"

/*
                    __first Stage Parsing__
1. parsing by get_next_line and it will be ready store it in 2d array
2. now u have the total y find the total x throug reading until null terminator every " " should hundeled
3. after that start to send them to the function that will print them
4, y have now the value of x y and z calculate the space and print them
*/

/*
                    __second stage turn one window__
1. start mlx and be ready to accept

4. until now until develop but u can run it to see the out come
*/

#define true 1
#define false 0
typedef struct
{
    char *line;
    int  z;
    int  fd;
    int  x;
    int  y;
}t_info;

typedef struct
{
    void *mlx;
    void *win;
}t_data;


typedef struct 
{
    void *img;
    void *addr;
    int bite_p_bixel;
    int len;
    int endian;
}t_img;
/*
x′=x⋅cos(θ)−y⋅sin(θ)
y′=x⋅sin⁡(θ)+y⋅cos⁡(θ)
*/
void get_image(t_info *info, t_img *img)
{
    unsigned int *dst;
    float x;
    float y;
    float angle;
    float xx;
    float yy;

    angle = (120/180.0f);
    yy= y = info ->y * sinf(angle) + (float)info->z;
    xx = x = info ->x * cosf(angle) + (float)info->z;
    // xx = x *cosf(30) - y * sin(30);
    // yy = x * sin(190) + y * cos(190);
    dst = img->addr + img->len * (int)yy * 16 + (int)xx * (img->bite_p_bixel* 2);
    dst[0] = 0x88008;
    ft_printf("(%d,%d,%d)\n", info->x, info->y, info->z);
}

int get_map(t_info *info, t_data *data, t_img *img)
{
    char **z;
    int i;

    i = 0;
    while ((info->line = get_next_line(info->fd)) != NULL)// we will print row by row
        {
            if(!info->line)
                return (0);
            z = ft_split(info->line, ' ');
            if(!z)
                return(0);
            info->y++;
            while(z[i])
            {
                info->z =ft_atoi(z[i]);
                get_image(info,img);
                i++;
                info->x++;
            }
            write (1, "\n", 1);
            info->x = 0;
            i = 0;
        }
    return (1);
}

int main (int arg, char **argv)
{
    t_info info;
    t_data data;
    t_img img;
    char **z;
    int i;

    i = 0;
    info.y = 0;
    info.x = 0;
    if (arg == 2)
    {
        data.mlx = mlx_init();
        data.win = mlx_new_window(data.mlx, 700, 700, "isometric");
        if (!data.win || !data.mlx)
            return (ft_printf("Error: MLX error\n"));
        img.img = mlx_new_image(data.mlx, 700, 700);
        img.addr = mlx_get_data_addr(img.img, &img.bite_p_bixel, &img.len, &img.endian);
        if (!img.addr|| !img.img)
            return (ft_printf("Error: MLX image error\n"));
        info.fd = open(argv[1], O_RDONLY);
        if (info.fd < 0)
            return (ft_printf("Error: check file\n"));
        if (get_map(&info, &data, &img) == false)
            return (0);
        mlx_put_image_to_window(data.mlx, data.win , img.img, 100, 100);
        mlx_loop(data.mlx);
    }
}
