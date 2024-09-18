/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 23:32:07 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/09/18 23:33:01 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shadow.h"
#include "../includes/ray_cross.h"

t_rgb check_color_is_valid(t_rgb a)
{
    printf("a.r:%u,a.g:%u,a.b:%u\n",a.r,a.g,a.b);
    if(a.r > 1)
        a.r = 1;
    if(a.r < 0)
        a.r = 0;
    if(a.g > 1)
        a.g = 1;
    if(a.g < 0)
        a.g = 0;
    if(a.b > 1)
        a.b = 1;
    if(a.b < 0)
        a.b = 0;
    return a;
}
int color_calc(t_object *nearest_obj, double brightness)
{
    // int color_r = (int)(fmin(nearest_obj->rgb->r * brightness , 1.0) * 255);
    // int color_g = (int)(fmin(nearest_obj->rgb->g * brightness , 1.0) * 255);
    // int color_b = (int)(fmin(nearest_obj->rgb->b * brightness , 1.0) * 255);
    if(brightness < 0)
        brightness = 0;
    int color = (nearest_obj->rgb->r << 16) | (nearest_obj->rgb->b  << 8) | nearest_obj->rgb->b ;
    
    return color;
}
t_rgb   color_init2(double r, double g, double b)
{
    t_rgb   color;

    color.r = r;
    color.g = g;
    color.b = b;
    return (check_color_is_valid(color));
}

t_rgb color_mul(t_rgb a, t_rgb b)
{
    a.r *= b.r;
    a.g *= b.g;
    a.b *= b.b;
    return check_color_is_valid(a);
}

t_rgb color_mul_scalar(t_rgb a, double b)
{
    a.r *= b;
    a.g *= b;
    a.b *= b;
    return check_color_is_valid(a);
}
t_rgb color_add(t_rgb a, t_rgb b)
{
    a.r += b.r;
    a.g += b.g;
    a.b += b.b;
    return check_color_is_valid(a);
}
t_rgb nearest_objs_color(t_object *nearest_obj)
{
    t_rgb color;    
    int colorhex = (nearest_obj->rgb->r << 16) | (nearest_obj->rgb->b  << 8) | nearest_obj->rgb->b ;
    double red = (double)(colorhex >> 16 & 0xff) / 255;
	double green = (double)(colorhex >> 8 & 0xff) / 255;
	double blue = (double)(colorhex & 0xff) / 255;
    color = check_color_is_valid(color_init2(red,green,blue));
    
    return color;
}

uint32_t color_ans(int r,int g , int b){
    	uint32_t	color;

	color = 0;
	color |= b;
	color |= g << 8;
	color |= r << 16;
	return (color);
}

uint32_t color2hex(t_rgb color)
{
    return (color_ans(color.r*255,color.g*255,color.b*255));
}
// TODO　centerを使わないやり方にリファクタする
int phong_calc(t_rt *rt, t_vec3 dir_vec, t_object *nearest_obj)
{
	// t_vec3  dsc = vec3_mul(*rt->scene->camera->nr_vec, (double)rt->width / (2 * tan((float)rt->scene->camera->view_degree / 2)));
    // t_vec3 dir_vec = vec3_norm(vec3_add(screen_vec, dsc));
    t_vec3 intersection = vec3_add(*rt->scene->camera->view_point, vec3_mul(dir_vec, calc_distance(nearest_obj, dir_vec, rt->scene->camera->view_point)));
    t_vec3 normal;
    t_rgb diff;
    t_rgb spec;
    t_rgb amb;
    //正規化による方向ベクトルの算出
    if(nearest_obj->type == SPHERE)
        normal = vec3_norm(vec3_sub(intersection, *nearest_obj->center));
    if(nearest_obj->type == PLANE)
        normal = *nearest_obj->normal_vec;
    if(nearest_obj->type == CYLINDER)
        normal = *nearest_obj->normal_vec;
    t_vec3 light_vec = vec3_norm(vec3_sub(*rt->scene->light->light_point,intersection));
    // t_vec3 view_vec = vec3_norm(vec3_sub(intersection, *rt->scene->camera->view_point));
    t_rgb obj_color;
    obj_color = nearest_objs_color(nearest_obj);
    amb =  color_mul(obj_color ,color_mul_scalar(*rt->scene->light->rgb,rt->scene->light->bright_ratio));
    // double amb = rt->scene->ambi_light->ratio * rt->scene->light->factor->ka;
    double diff_deg = vec3_dot(normal, light_vec);
    if(diff_deg < 0)
        diff_deg = 0;
    diff = color_mul_scalar(color_mul(obj_color,color_mul_scalar(*rt->scene->light->rgb,rt->scene->light->bright_ratio)),diff_deg);

    t_vec3 v = vec3_mul(dir_vec, -1);
    t_vec3 r = vec3_sub(vec3_mul(vec3_mul(normal, vec3_dot(normal, light_vec)), 2), light_vec);
	spec = color_mul_scalar(color_mul( rt->scene->light->factor->ks, color_mul_scalar(*rt->scene->light->rgb,rt->scene->light->bright_ratio)), pow(vec3_dot(v, r), rt->scene->light->factor->shininess));
    // double spec = pow(vec3_dot(view_vec, vec3_reflect(vec3_mul(light_vec, -1), normal)), rt->scene->light->factor->shininess) * rt->scene->light->bright_ratio * rt->scene->light->factor->ks;
    
    if(vec3_dot(v,r) < 0)
        spec = color_init2(0.0,0.0,0.0);
    // printf("amb.r:%u,amb.g:%u,amb.b:%u\n",amb.r,amb.g,amb.b);
    // printf("diff.r:%u,diff.g:%u,diff.b:%u\n",diff.r,diff.g,diff.b);
    // printf("spec.r:%u,spec.g:%u,spec.b:%u\n",spec.r,spec.g,spec.b);
    if(is_shadow(rt->scene, nearest_obj, dir_vec))
    {
        diff = color_init2(0.0,0.0,0.0);
        spec = color_init2(0.0,0.0,0.0);
    }
    return color2hex(color_add(amb,color_add(diff,spec)));
}
