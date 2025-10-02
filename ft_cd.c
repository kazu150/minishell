/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:59:29 by kaisogai          #+#    #+#             */
/*   Updated: 2025/10/02 17:45:39 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

// int my_setenv(const char *name, const char *value) {
//     size_t nlen = strlen(name);
//     // 置換パス
//     for (size_t i = 0; environ[i]; i++) {
//         if (strncmp(environ[i], name, nlen) == 0 && environ[i][nlen] == '=') {
//             char *new_entry = malloc(nlen + 1 + strlen(value) + 1);
//             if (!new_entry) return -1;
//             sprintf(new_entry, "%s=%s", name, value);
//             // 古いエントリは putenv/setenv 由来なら free しない方が安全なこともある
//             environ[i] = new_entry;
//             return 0;
//         }
//     }
//     // 追加パス：配列を作り直す
//     size_t cnt = 0;
//     while (environ[cnt]) cnt++;

//     char **new_env = malloc(sizeof(char*) * (cnt + 2));
//     if (!new_env) return -1;

//     for (size_t i = 0; i < cnt; i++) new_env[i] = environ[i];

//     char *new_entry = malloc(nlen + 1 + strlen(value) + 1);
//     if (!new_entry) { free(new_env); return -1; }
//     sprintf(new_entry, "%s=%s", name, value);

//     new_env[cnt]   = new_entry;
//     new_env[cnt+1] = NULL;

//     environ = new_env;  // ★ 配列ごと差し替える
//     return 0;
// }
void	ft_cd(char *path)
{
	char *old_pwd  =	getcwd(NULL, 0);
	int res = chdir(path);
	if (res < 0)
		perror(ft_strjoin("cd: ", path));
	char *pwd  =	getcwd(NULL, 0);
	setenv("OLDPWD", old_pwd, 1);
	setenv("PWD", pwd, 1);
}
