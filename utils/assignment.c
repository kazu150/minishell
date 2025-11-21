/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:18:52 by cyang             #+#    #+#             */
/*   Updated: 2025/11/21 15:19:42 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_assignment(const char *s)
{
    int i;

    if (!s || !s[0])
        return (0);
    i = 0;
    // 找到 '='
    while (s[i] && s[i] != '=')
        i++;
    if (!s[i]) // 沒有等號
        return (0);
    // key 長度為 i（可以為 0 但要檢查合法性）
    if (i == 0)
        return (0);
    // 檢查 key 的合法性：首字元為 letter or '_'，其後字元為 alnum or '_'
    if (!(ft_isalpha((unsigned char)s[0]) || s[0] == '_'))
        return (0);
    for (int j = 1; j < i; j++)
        if (!(ft_isalnum((unsigned char)s[j]) || s[j] == '_'))
            return (0);
    return (1);
}

void	parse_assignment(const char *s, char **out_key, char **out_value)
{
    char *eq = ft_strchr(s, '=');

    *out_key = ft_substr(s, 0, eq - s);
    *out_value = ft_strdup(eq + 1);
}

int	set_env_var(t_env **env_list, char *key, char *value, int exported)
{
    t_env *cur;

    if (!env_list || !key)
        return (0);
    cur = *env_list;
    while (cur)
    {
        if (!ft_strcmp(cur->key, key))
        {
            free(cur->value);
            cur->value = ft_strdup(value);
            cur->exported = exported ? 1 : cur->exported; // 如果要 exported，強制設 1；否則保留原值或設 0?
            if (!exported)
                cur->exported = 0; // assignment without export -> ensure 0
            return (1);
        }
        cur = cur->next;
    }
    // not found -> add new
    t_env *node = new_env(key, value);
    if (!node)
        return (0);
    node->exported = exported ? 1 : 0;
    add_env_back(env_list, node);
    return (1);
}