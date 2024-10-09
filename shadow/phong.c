/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 23:32:07 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/10/09 23:07:30 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shadow.h"
#include "../includes/ray_cross.h"

// t_rgb check_color_is_valid(t_rgb a)
// {
//     if(a.r > 1.0)
//         a.r = 1.0;
//     if(a.r < 0.0)
//         a.r = 0.0;
//     if(a.g > 1.0)
//         a.g = 1.0;
//     if(a.g < 0.0)
//         a.g = 0.0;
//     if(a.b > 1.0)
//         a.b = 1.0;
//     if(a.b < 0.0)
//         a.b = 0.0;
//     return a;
// }
t_rgb check_color_is_valid(t_rgb a)
{
    if(a.r > 255)
        a.r = 255;
    if(a.r < 0.0)
        a.r = 0.0;
    if(a.g > 255)
        a.g = 255;
    if(a.g < 0.0)
        a.g = 0.0;
    if(a.b > 255)
        a.b = 255;
    if(a.b < 0.0)
        a.b = 0.0;
    return a;
}


uint32_t color2hex(t_rgb color)
{
    // printf("color.r:%f,color.g:%f,color.b:%f\n",color.r*255,color.g*255,color.b*255);
    printf("color.r:%f,color.g:%f,color.b:%f\n",color.r,color.g,color.b);
    return (color_ans(color.r,color.g,color.b));
    // return (color_ans(color.r*255,color.g*255,color.b*255));
}
// 拡散反射光の計算
t_rgb calc_diffuse( t_vec3 normal, t_vec3 light_vec, t_rt *rt)
{
    double diff_deg;
    t_rgb obj_color;
    t_rgb light_color;

    light_color = get_light_color(rt);
    obj_color = nearest_objs_color(rt->scene->object);
    diff_deg = vec3_dot(normal, light_vec);
    if (diff_deg < 0)
        diff_deg = 0;
    return color_mul_scalar(color_mul(obj_color, color_mul_scalar(light_color, rt->scene->light->bright_ratio)), diff_deg);
}

// 鏡面反射の計算
t_rgb calc_specular(t_vec3 normal, t_vec3 light_vec, t_vec3 dir_vec, t_rt *rt)
{
    t_vec3 v;
    t_vec3 r;
    t_rgb light_color;
    double spec_deg;

    light_color = get_light_color(rt);
    v = vec3_mul(dir_vec, -1);
    r = vec3_sub(vec3_mul(vec3_mul(normal, vec3_dot(normal, light_vec)), 2), light_vec);
    spec_deg = vec3_dot(v, r);
    if (spec_deg < 0)
        return color_init2(0.0, 0.0, 0.0);
    
    return color_mul_scalar(color_mul(rt->scene->light->factor->ks, color_mul_scalar(light_color, rt->scene->light->bright_ratio)), pow(spec_deg, rt->scene->light->factor->shininess));
}

// アンビエント光の計算
t_rgb calc_ambient(t_rt *rt)
{
    t_rgb obj_color;
    obj_color = nearest_objs_color(rt->scene->object);
    return color_mul(obj_color, color_mul_scalar(get_ambi_light_color(rt), rt->scene->ambi_light->ratio));
}

// 法線ベクトルの取得
t_vec3 get_normal(t_object *nearest_obj, t_vec3 intersection)
{
    if (nearest_obj->type == SPHERE)
        return vec3_norm(vec3_sub(intersection, *nearest_obj->center));
    else
        return *nearest_obj->normal_vec;
}

// phong_calc 関数
int phong_calc(t_rt *rt, t_vec3 dir_vec, t_object *nearest_obj)
{
    t_vec3 intersection;
    t_vec3 normal;
    t_vec3 light_vec;
    t_rgb diff;
    t_rgb spec;

    intersection = vec3_add(*rt->scene->camera->view_point, vec3_mul(dir_vec, calc_distance(nearest_obj, dir_vec, rt->scene->camera->view_point)));
    normal = get_normal(nearest_obj, intersection);
    light_vec = vec3_norm(vec3_sub(*rt->scene->light->light_point, intersection));
    diff = calc_diffuse(normal, light_vec, rt);
    spec = calc_specular(normal, light_vec, dir_vec, rt);

    if (is_shadow(rt->scene, nearest_obj, dir_vec))
    {
        diff = color_init2(0.0, 0.0, 0.0);
        spec = color_init2(0.0, 0.0, 0.0);
    }

    return color2hex(color_add(calc_ambient(rt), color_add(diff, spec)));
}
