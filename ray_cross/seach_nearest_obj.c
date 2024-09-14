/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seach_nearest_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:08:42 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/09/14 17:36:56 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ray_cross.h"

// TODO　うまく描画されない・・？

double calc_cy_d(t_object *obj, t_vec3 dir, t_vec3 *source_point)
{
    double	a;
	double	b;
	double	c;
    a = vec3_mag(vec3_cross(dir, *obj->axic_vec));
    a*=a;
     b = 2 * vec3_dot(vec3_cross(dir, *obj->axic_vec), vec3_cross(vec3_sub(*source_point, *obj->center), *obj->axic_vec));

     c = vec3_mag(vec3_cross(vec3_sub(*source_point, *obj->center),  *obj->axic_vec));
	c = c * c - (obj->diameter/2) *(obj->diameter/2);

	return b * b - 4 * a * c;

}
double  calc_cy_t(t_object *obj, t_vec3 dir,  int flag,t_vec3 *source_point)
{
    double	a;
	double	b;
	double	c;
	double	d;
    a = vec3_mag(vec3_cross(dir, *obj->axic_vec));
    a*=a;
     b = 2 * vec3_dot(vec3_cross(dir, *obj->axic_vec), vec3_cross(vec3_sub(*source_point, *obj->center), *obj->axic_vec));

     c = vec3_mag(vec3_cross(vec3_sub(*source_point, *obj->center),  *obj->axic_vec));
	c = c * c - (obj->diameter/2) *(obj->diameter/2);

	d = b * b - 4 * a * c;

    if(flag == 1)
        return (-b + sqrt(d)) / (2 * a);
    
    return (-b - sqrt(d)) / (2 * a);
}
t_vec3  *calc_cy_intersections(t_object *obj, t_vec3 dir, t_vec3 *source_point)
{
	double	d;
	t_vec3	*intersections;
	d = calc_cy_d(obj, dir, source_point);
	if (d < 0)
		return (NULL);
	intersections = (t_vec3 *)malloc(sizeof(t_vec3) * 2);
	if (intersections == NULL)
		return (NULL);

    intersections[0] = vec3_add(*source_point,vec3_mul(dir,calc_cy_t(obj, dir, 0,source_point)));
	intersections[1] = vec3_add(*source_point,vec3_mul(dir,calc_cy_t(obj, dir, 1,source_point)));
	return (intersections);
}
double calc_cy_distance(t_object *object, t_vec3 dir, t_vec3 *source_point)
{

    t_vec3  *intersections;
    double h_outer;
    double h_inner;
    double  distance;

    intersections = calc_cy_intersections(object, dir, source_point);
    if (intersections == NULL)
        return (-1);
    h_outer = vec3_dot(vec3_sub(intersections[0],*object->center), *object->axic_vec);
    h_inner = vec3_dot(vec3_sub(intersections[1],*object->center), *object->axic_vec);
	if (h_outer >= 0 && h_outer <= object->height)
        distance = calc_cy_t(object, dir,  0,source_point);
    else if(h_inner>= 0 && h_inner <= object->height)
		distance = calc_cy_t(object, dir,  1,source_point);
    else
        distance = -1;
    free(intersections);
	return (distance);
}
double calc_sp_distance(t_object *object, t_vec3 dir, t_vec3 *source_point)
{
    
    t_vec3	sph2source;
    double	a;
    double	b;
    double	c;
	double	t;
    sph2source = vec3_sub(*source_point, *object->center);
    a = vec3_dot(dir, dir);
    b = 2 * vec3_dot(sph2source, dir);
    c = vec3_dot(sph2source, sph2source) - (object->diameter * object->diameter);
    if(b * b - 4 * a * c < 0)
        return -1;
	t = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
	return (t);
}

double calc_pl_distance(t_object *object, t_vec3 dir, t_vec3 *source_point)
{
    
	t_vec3	cam2pl;
	double	denominator;
	double	molecule;

	cam2pl = vec3_sub(*source_point, *object->p_in_the_plane);
	denominator = (vec3_dot(vec3_mul(dir,-1), *object->normal_vec));
	if (denominator == 0)
		return (-1);
	molecule = vec3_dot(cam2pl, *object->normal_vec);
	return (molecule / denominator);
}

double calc_distance(t_object *obj, t_vec3 dir, t_vec3 *source_point)
{
    if(obj->type == SPHERE)
        return (calc_sp_distance(obj, dir, source_point));
    else if(obj->type == PLANE)
        return(calc_pl_distance(obj, dir, source_point));
    else if(obj->type == CYLINDER)
        return(calc_cy_distance(obj, dir, source_point));
    return 0;
}

t_object *seach_nearest_obj(t_rt *rt, double x, double y)
{
    t_object    *nearest_obj;
    t_object    *obj;
    double      distance;
    double      min_distance;
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
    min_distance = DISTANCE_MAX;
    obj = rt->scene->object;
    nearest_obj = obj;
    while(obj)
    {
        distance = calc_distance(obj, dir, rt->scene->camera->view_point);   
        if(distance < 0)
        {
            obj = obj->next;
            continue;
        }
        if(distance < min_distance)
        {
            min_distance = distance;
            nearest_obj = obj;
        }
        obj = obj->next;
    }

    return (nearest_obj);
}
