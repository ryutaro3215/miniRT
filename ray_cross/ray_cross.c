/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cross.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:23:33 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/09/29 20:11:36 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ray_cross.h"
#include "../includes/color.h"

t_vec3	*get_intersections(t_rt *rt, t_vec3 dir, t_vec3 cam2cyl, t_object *object)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vec3	*intersections;

	a = vec3_dot(dir, dir) - pow(vec3_dot(dir, *object->axic_vec), 2);
	b = 2 * (vec3_dot(dir, cam2cyl) - vec3_dot(dir, *object->axic_vec)
			* vec3_dot(*object->axic_vec, cam2cyl));

	c = vec3_dot(cam2cyl, cam2cyl) - pow(vec3_dot(*object->axic_vec, cam2cyl), 2)
		- object->diameter / 2 * object->diameter / 2;
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


bool	discriminant_cylinder(t_rt *rt, t_vec3 dir, t_object *object)
{
	t_vec3	cam2cyl;
	t_vec3	*intersections;
	bool	flag;	

	cam2cyl = vec3_sub(*rt->scene->camera->view_point, *object->center);
	intersections = get_intersections(rt, dir, cam2cyl, object);
	if (intersections == NULL)
		return (false);
     t_vec3 center2inner = vec3_sub(intersections[1],*object->center);
    t_vec3 center2outer = vec3_sub(intersections[0],*object->center);
    
    double h_outer = vec3_dot(center2outer, *object->axic_vec);
    double h_inner = vec3_dot(center2inner, *object->axic_vec);
   if( h_outer>=0 && h_outer <= object->height)
    {
        flag = true;
        t_vec3 projection_on_axis_outer = vec3_mul(*object->axic_vec, h_outer);
        *object->normal_vec = vec3_norm(vec3_sub(center2outer, projection_on_axis_outer));
    }
    else if ( h_inner>=0 &&  h_inner <= object->height)
    {
        flag = true;
        t_vec3 projection_on_axis_inner = vec3_mul(*object->axic_vec, h_inner);
        *object->normal_vec = vec3_norm(vec3_sub(projection_on_axis_inner,center2inner));
    }
    else
        flag = false;
	free(intersections);
    return (flag);
}

void	draw_cylinder(t_rt *rt,double x, double y, t_object *nearest_obj)
{
	bool	is_drawable;

    double d1 = rt->width / 2 / tan((rt->scene->camera->view_degree / 2)/(180 * 3.14159265358979323846));
    t_vec3 cam_center = vec3_mul(*rt->scene->camera->nr_vec, d1);
    
    t_vec3 esx;
	esx.x = cam_center.z / sqrt(cam_center.z * cam_center.z + cam_center.x * cam_center.x);
	esx.y = 0;
	esx.z = -cam_center.x / sqrt(cam_center.z * cam_center.z + cam_center.x * cam_center.x);
	t_vec3 esy;
    esy = vec3_norm(vec3_cross(vec3_mul(cam_center, -1),esx));
    t_vec3 xx = vec3_mul(esx,  x - (rt->width - 1) / 2);
    t_vec3 yy = vec3_mul(esy, (rt->height - 1) / 2 - y);
    t_vec3 dir = vec3_norm(vec3_add(cam_center, vec3_add(xx, yy)));
    is_drawable = discriminant_cylinder(rt, dir,nearest_obj);

    if (is_drawable == true)
        my_mlx_pixel_put(rt, x, y, phong_calc(rt, dir,nearest_obj));
    else
        my_mlx_pixel_put(rt, x, y, 0x000000);
}

double	discriminant(t_rt *rt, t_vec3 dir, t_object *object)
{
	t_vec3	cam2sph;
	double	a;
	double	b;
	double	c;
	cam2sph = vec3_sub(*rt->scene->camera->view_point, *object->center);
	a = vec3_dot(dir, dir);
	b = 2 * vec3_dot(cam2sph, dir);
	c = vec3_dot(cam2sph, cam2sph) - (object->diameter * object->diameter);
	return (b * b - 4 * a * c);
}

void	draw_sphere(t_rt *rt, double x, double y, t_object *nearest_obj)
{
	double	d;
        double d1 = rt->width / 2 / tan((rt->scene->camera->view_degree / 2)/(180 * 3.14159265358979323846));
    t_vec3 cam_center = vec3_mul(*rt->scene->camera->nr_vec, d1);
    	t_vec3 esx;
	esx.x = cam_center.z / sqrt(cam_center.z * cam_center.z + cam_center.x * cam_center.x);
	esx.y = 0;
	esx.z = -cam_center.x / sqrt(cam_center.z * cam_center.z + cam_center.x * cam_center.x);
	t_vec3 esy;
    esy = vec3_norm(vec3_cross(vec3_mul(cam_center, -1),esx));
    t_vec3 xx = vec3_mul(esx,  x - (rt->width - 1) / 2);
    t_vec3 yy = vec3_mul(esy, (rt->height - 1) / 2 - y);
    t_vec3 dir = vec3_norm(vec3_add(cam_center, vec3_add(xx, yy)));
	d = 0;
    d = discriminant(rt, dir,nearest_obj);
    if (d >= 0)
        my_mlx_pixel_put(rt, x, y, phong_calc(rt, dir,nearest_obj));
    else
        my_mlx_pixel_put(rt, x, y, 0x000000);
}

double	cross_ray_plane(t_object *object, t_vec3 dir, t_rt *rt)
{
	t_vec3	cam2pl;
	double	denominator;
	double	molecule;

	cam2pl = vec3_sub(*rt->scene->camera->view_point, *object->p_in_the_plane);
	denominator = (vec3_dot(vec3_mul(dir,-1), *object->normal_vec));
	if (denominator == 0)
		return (-1);
	molecule = vec3_dot(cam2pl, *object->normal_vec);
	return (molecule / denominator);
}
bool judge_denominator(t_vec3 dir,t_camera *camera,t_object *object)
{
	double	denominator;
if(camera)
;
	denominator = -(vec3_dot(dir, *object->normal_vec));
    if(denominator < 0)
        return true;
    else
        return false;
}

void	draw_plane(t_rt *rt, double x,double y, t_object *nearest_obj)
{
	double	t;
    double d = rt->width / 2 / tan((rt->scene->camera->view_degree / 2)/(180 * 3.14159265358979323846));
    t_vec3 cam_center = vec3_mul(*rt->scene->camera->nr_vec, d);
    
    	t_vec3 esx;  
	esx.x = cam_center.z / sqrt(cam_center.z * cam_center.z + cam_center.x * cam_center.x);
	esx.y = 0;
	esx.z = -cam_center.x / sqrt(cam_center.z * cam_center.z + cam_center.x * cam_center.x);
	t_vec3 esy;
    esy = vec3_norm(vec3_cross(vec3_mul(cam_center, -1),esx));
    t_vec3 xx = vec3_mul(esx,  x - (rt->width - 1) / 2);
    t_vec3 yy = vec3_mul(esy, (rt->height - 1) / 2 - y);    
    t_vec3 dir = vec3_norm(vec3_add(cam_center, vec3_add(xx, yy)));
    
    t = cross_ray_plane(nearest_obj, dir,rt);
    if(judge_denominator(dir,rt->scene->camera,nearest_obj))
        *nearest_obj->normal_vec = vec3_mul(*nearest_obj->normal_vec,-1);
    if (t >= 0)
        my_mlx_pixel_put(rt, x, y, phong_calc(rt, dir,nearest_obj));
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
