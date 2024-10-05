/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 23:32:07 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/10/02 21:42:48 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shadow.h"
#include "../includes/ray_cross.h"

t_rgb check_color_is_valid(t_rgb a)
{
    if(a.r > 1.0)
        a.r = 1.0;
    if(a.r < 0.0)
        a.r = 0.0;
    if(a.g > 1.0)
        a.g = 1.0;
    if(a.g < 0.0)
        a.g = 0.0;
    if(a.b > 1.0)
        a.b = 1.0;
    if(a.b < 0.0)
        a.b = 0.0;
    return a;
}
// t_rgb check_color_is_valid(t_rgb a)
// {
//     if(a.r > 255)
//         a.r = 255;
//     if(a.r < 0.0)
//         a.r = 0.0;
//     if(a.g > 255)
//         a.g = 255;
//     if(a.g < 0.0)
//         a.g = 0.0;
//     if(a.b > 255)
//         a.b = 255;
//     if(a.b < 0.0)
//         a.b = 0.0;
//     return a;
// }
t_rgb   color_init2(double r, double g, double b)
{
    t_rgb   color;

    color.r = r;
    color.g = g;
    color.b = b;
    return (check_color_is_valid(color));
    // return color;
}

t_rgb color_mul(t_rgb a, t_rgb b)
{
    a.r *= b.r;
    a.g *= b.g;
    a.b *= b.b;
    return check_color_is_valid(a);
    // return a;
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
    // return a;
}
t_rgb nearest_objs_color(t_object *nearest_obj)
{
    t_rgb color;
    // int colorhex = nearest_obj->rgb->r | nearest_obj->rgb->b | nearest_obj->rgb->b;
    // double red = (double)(colorhex >> 16 & 0xff) / 255;
	// double green = (double)(colorhex >> 8 & 0xff) / 255;
	// double blue = (double)(colorhex & 0xff) / 255;
    // double red = nearest_obj->rgb->r/255.0;
    // double green = nearest_obj->rgb->g/255.0;
    // double blue = nearest_obj->rgb->b/255.0;
    double red = nearest_obj->rgb->r;
    double green = nearest_obj->rgb->g;
    double blue = nearest_obj->rgb->b;
    // color = color_init2(red,green,blue);
    color = check_color_is_valid(color_init2(red,green,blue));

    return color;
}
t_rgb get_light_color(t_rt *rt)
{
    t_rgb color;
    // double red = rt->scene->light->rgb->r/255.0;
    // double green = rt->scene->light->rgb->g/255.0;
    // double blue = rt->scene->light->rgb->b/255.0;
    double red = rt->scene->light->rgb->r;
    double green = rt->scene->light->rgb->g;
    double blue = rt->scene->light->rgb->b;
    // color = color_init2(red,green,blue);
    color = check_color_is_valid(color_init2(red,green,blue));
    return color;
}
t_rgb get_ambi_light_color(t_rt *rt)
{
    t_rgb color;
    // double red = rt->scene->ambi_light->rgb->r/255.0;
    // double green = rt->scene->ambi_light->rgb->g/255.0;
    // double blue = rt->scene->ambi_light->rgb->b/255.0;
    double red = rt->scene->ambi_light->rgb->r;
    double green = rt->scene->ambi_light->rgb->g;
    double blue = rt->scene->ambi_light->rgb->b;
    // color = color_init2(red,green,blue);
    color = check_color_is_valid(color_init2(red,green,blue));
    return color;
}
uint32_t color_ans(int r,int g , int b){
    	uint32_t	color;
    // printf("r:%d,g:%d,b:%d\n",r,g,b);
	color = 0;
	color |= b;
	color |= g << 8;
	color |= r << 16;
    // color = (r << 16) | (g  << 8) | b ;
	return (color);
}

uint32_t color2hex(t_rgb color)
{
    printf("color.r:%f,color.g:%f,color.b:%f\n",color.r*255,color.g*255,color.b*255);
    // printf("color.r:%f,color.g:%f,color.b:%f\n",color.r,color.g,color.b);
    // return (color_ans(color.r,color.g,color.b));
    return (color_ans(color.r*255,color.g*255,color.b*255));
}
int phong_calc(t_rt *rt, t_vec3 dir_vec, t_object *nearest_obj)
{
     double t = calc_distance(nearest_obj, dir_vec, rt->scene->camera->view_point);
    t_vec3 intersection = vec3_add(*rt->scene->camera->view_point, vec3_mul(dir_vec, t));
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
    // if(nearest_obj->type == SPHERE)
        // printf("nearest_obj->r : %f, nearest")
    t_rgb obj_color;
    obj_color = nearest_objs_color(nearest_obj);
        // printf("nearest_obj->type:%d\n",nearest_obj->type);
    t_rgb light_color;
    light_color = get_light_color(rt);
    // printf("light_color.r:%f,light_color.g:%f,light_color.b:%f\n",light_color.r,light_color.g,light_color.b);
    amb =  color_mul(obj_color ,color_mul_scalar(get_ambi_light_color(rt),rt->scene->ambi_light->ratio));
    // double amb = rt->scene->ambi_light->ratio * rt->scene->light->factor->ka;
    //拡散反射光
    double diff_deg = vec3_dot(normal, light_vec);
    // printf("diff_deg:%f\n",diff_deg);
    if(diff_deg < 0)
        diff_deg = 0;
    diff = color_mul_scalar(color_mul(obj_color,color_mul_scalar(light_color,rt->scene->light->bright_ratio)),diff_deg);


    //鏡面反射
    t_vec3 v = vec3_mul(dir_vec, -1);
    t_vec3 r = vec3_sub(vec3_mul(vec3_mul(normal, vec3_dot(normal, light_vec)), 2), light_vec);
	spec = color_mul_scalar(color_mul( rt->scene->light->factor->ks, color_mul_scalar(light_color,rt->scene->light->bright_ratio)), pow(vec3_dot(v, r), rt->scene->light->factor->shininess));

    if(vec3_dot(v,r) < 0)
        spec = color_init2(0.0,0.0,0.0);

    if(is_shadow(rt->scene, nearest_obj, dir_vec))
    {
        diff = color_init2(0.0,0.0,0.0);
        spec = color_init2(0.0,0.0,0.0);
    }

    return color2hex(color_add(amb,color_add(diff,spec)));
}
