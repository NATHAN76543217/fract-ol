#include "fractol.h"

int draw(t_data *data, t_coord point, int color)
{
    *(int *)(data->image.add_image + point.y * data->image.size_line + point.x) = (!color) ? rgb_int(0, 100, 0, 0) : 0;
    return (0);
}

int computing(t_data *data, t_f_coord org_coord, t_coord point)
{
    float z;
    float z0;
    int i;
    t_f_coord coord;
    float module;

    i = 0;
    z = org_coord.x + org_coord.y;
    z0 = z;
    while(i < 15)
    {
        coord.x = (coord.x*coord.x) - (coord.y*coord.y) + org_coord.x;
        coord.y = (2*coord.x*coord.y + org_coord.y);
        z =  coord.x + coord.y;
        module = sqrtf(coord.x * coord.x + coord.y * coord.y);
        if (module > 2)
        {
            draw(data, point, 1);
            i = 15;
        }
        i++;
    }
    if (i == 15)
        draw(data, point, 0);
    return (0);
}

int frame(t_data *data)
{
    t_coord point;
    t_f_coord coord;
    coord = (t_f_coord){};
    point = (t_coord){};

    printf("start frame\n");
    while (point.y < data->screen.y)
    {
        coord.y = -1 + (0.001 * point.y);
        while (point.x < data->screen.x)
        {
            coord.x = -1.5 * (0.001 * point.x);
            computing(data, coord, point);
            point.x++;
        }
        point.x = 0;
        point.y++;
    }
    mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->image.img, 0, 0);

    return (0);
}