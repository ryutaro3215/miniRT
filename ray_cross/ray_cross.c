/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cross.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:23:33 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/08/18 22:33:20 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ray_cross.h"
#include "../includes/color.h"

double	discriminant(t_rt *rt, t_vec3 screen_vec, t_object *object)
{
	t_vec3	dir;
	t_vec3	cam2sph;
	double	a;
	double	b;
	double	c;
	dir = vec3_norm(vec3_sub(screen_vec, *rt->scene->camera->view_point));
	cam2sph = vec3_sub(*rt->scene->camera->view_point, *object->center);
	a = vec3_dot(dir, dir);
	b = 2 * vec3_dot(cam2sph, dir);
	c = vec3_dot(cam2sph, cam2sph) - (object->diameter * object->diameter);
	return (b * b - 4 * a * c);
}

void	draw_sphere(t_rt *rt, double x, double y, t_object *nearest_obj)
{
	t_vec3	screen_vec;
	double	d;

	d = 0;

    screen_vec = vec3_init(2 * x / rt->width - 1.0, 2 * y / rt->height - 1.0, 0);
    d = discriminant(rt, screen_vec,nearest_obj);
    if (d >= 0)
    {
        // my_mlx_pixel_put(rt, x, y, int_to_hex_color(rt->scene->sphere->rgb));
        my_mlx_pixel_put(rt, x, y, phong_calc(rt->scene, screen_vec,nearest_obj));
    }
    else
        my_mlx_pixel_put(rt, x, y, 0x000000);
	
	
}

double	cross_ray_plane(t_object *object, t_vec3 screen_vec, t_camera *camera)
{
	t_vec3	dir;
	t_vec3	cam2pl;
	double	denominator;
	double	molecule;

	dir = vec3_norm(vec3_sub(screen_vec, *camera->view_point)); 
	cam2pl = vec3_sub(*camera->view_point, *object->p_in_the_plane);
	denominator = (vec3_dot(vec3_mul(dir,-1), *object->normal_vec));
	if (denominator == 0)
		return (-1);
	molecule = vec3_dot(cam2pl, *object->normal_vec);
	return (molecule / denominator);
}
bool judge_denominator(t_vec3 screen_vec,t_camera *camera,t_object *object)
{
    	t_vec3	dir;
	double	denominator;

	dir = vec3_norm(vec3_sub(screen_vec, *camera->view_point)); 
	denominator = -(vec3_dot(dir, *object->normal_vec));
    if(denominator < 0)
        return true;
    else
        return false;
}
void	draw_plane(t_rt *rt, double x,double y, t_object *nearest_obj)
{
	t_vec3	screen_vec;
	double	t;

	t = 0;
    screen_vec = vec3_init(2 * x / rt->width - 1.0, 2 * y / rt->height - 1.0, 0);
    t = cross_ray_plane(nearest_obj, screen_vec,rt->scene->camera);
    if(judge_denominator(screen_vec,rt->scene->camera,nearest_obj))
        *nearest_obj->normal_vec = vec3_mul(*nearest_obj->normal_vec,-1);
    if (t >= 0)
        my_mlx_pixel_put(rt, x, y, phong_calc(rt->scene, screen_vec,nearest_obj));
        // my_mlx_pixel_put(rt, x, y, int_to_hex_color(nearest_obj->rgb));
    else
        my_mlx_pixel_put(rt, x, y, 0x000000);
}

t_vec3	*get_intersections(t_rt *rt, t_vec3 dir, t_vec3 cam2cyl)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vec3	*intersections;

	a = vec3_dot(dir, dir) - pow(vec3_dot(dir, *rt->scene->object->axic_vec), 2);
	b = 2 * (vec3_dot(dir, cam2cyl) - vec3_dot(dir, *rt->scene->object->axic_vec)
			* vec3_dot(*rt->scene->object->axic_vec, cam2cyl));
	c = vec3_dot(cam2cyl, cam2cyl) - pow(vec3_dot(*rt->scene->object->axic_vec, cam2cyl), 2)
		- rt->scene->object->diameter / 2 * rt->scene->object->diameter / 2;
	d = b * b - 4 * a * c;
	if (d < 0)
		return (NULL);
	intersections = (t_vec3 *)malloc(sizeof(t_vec3) * 2);
	if (intersections == NULL)
		return (NULL);
	intersections[0] = vec3_add(*rt->scene->camera->view_point, 
			vec3_mul(dir, ((-b - sqrt(d)) / (2 * a))));
	intersections[1] = vec3_add(*rt->scene->camera->view_point,
			vec3_mul(dir, ((-b + sqrt(d)) / (2 * a))));
	return (intersections);
}

bool	is_height_range(t_rt *rt, t_vec3 *intersections)
{
	bool	is_intersect_p1;
	bool	is_intersect_p2;
	t_vec3	axic;
	t_vec3	cyl_top;
	t_vec3	cyl_bottom;

	cyl_top = vec3_add(*rt->scene->camera->view_point, 
			vec3_mul(*rt->scene->object->axic_vec, rt->scene->object->height / 2));
	cyl_bottom = vec3_sub(*rt->scene->camera->view_point, 
			vec3_mul(*rt->scene->object->axic_vec, rt->scene->object->height / 2));
	axic = *rt->scene->object->axic_vec;
	is_intersect_p1 = vec3_dot(vec3_sub(intersections[0], cyl_bottom), axic) >= 0 &&
		vec3_dot(vec3_sub(intersections[0], cyl_top), axic) <= 0;
	is_intersect_p2 = vec3_dot(vec3_sub(intersections[1], cyl_bottom), axic) >= 0 &&
		vec3_dot(vec3_sub(intersections[1], cyl_top), axic) <= 0;
	if ( is_intersect_p1|| is_intersect_p2)
		return (true);
	else
		return (false);
}

bool	discriminant_cylinder(t_rt *rt, t_vec3 screen_vec)
{
	t_vec3	dir;
	t_vec3	cam2cyl;
	t_vec3	*intersections;
	bool	flag;
	
	dir = vec3_norm(vec3_sub(screen_vec, *rt->scene->camera->view_point));
	cam2cyl = vec3_sub(*rt->scene->camera->view_point, *rt->scene->object->center);
	intersections = get_intersections(rt, dir, cam2cyl);
	if (intersections == NULL)
		return (false);
	flag = is_height_range(rt, intersections);
	free(intersections);
	if (flag == true)
		return (true);
	else
		return (false);
}

void	draw_cylinder(t_rt *rt,double x, double y, t_object *nearest_obj)
{
	t_vec3	screen_vec;
	bool	is_drawable;

    screen_vec = vec3_init(2 * x / rt->width - 1.0, 2 * y / rt->height - 1.0, 0);
    is_drawable = discriminant_cylinder(rt, screen_vec);
    if (is_drawable == true)
        my_mlx_pixel_put(rt, x, y, phong_calc(rt->scene, screen_vec,nearest_obj));
        // my_mlx_pixel_put(rt, x, y, int_to_hex_color(nearest_obj->rgb));
    else
        my_mlx_pixel_put(rt, x, y, 0x000000);
}

void draw_object(t_rt *rt)
{
    double	x;
	double	y;

    x = 0;
    y = 0;

    while(y < rt->height)
    {
        while(x < rt->width)
        {
            t_object *nearest_obj;
            nearest_obj = NULL;
            nearest_obj = seach_nearest_obj(rt, x, y);
            if(nearest_obj->type == SPHERE)
                draw_sphere(rt,x,y,nearest_obj);
            else if(nearest_obj->type == PLANE)
                draw_plane(rt,x,y,nearest_obj);
            else if(nearest_obj->type == CYLINDER)
                draw_cylinder(rt,x,y,nearest_obj);
            x++;
        }
        x = 0;
        y++;
    }
    // draw_cylinder(rt);
}
