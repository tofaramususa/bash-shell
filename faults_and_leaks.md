29 Aug --
Segfaults:
echo $PATH > word.text | echo word - seems to be invalid read of size 8 with check and update heredoc


Leaks:
exit - garbage_collection function -- Conditional jump or move depends on uninitialised value(s)
==11476==    at 0x109018: free_env_list
 Address 0x4b32700 is 0 bytes inside a block of size 5 free'd
==11476==    at 0x4867AD0: free (in /usr/libexec/valgrind/vgpreload_memcheck-arm64-linux.so)
==11476==    by 0x1091BF: free_scommand (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==11476== Invalid free() / delete / delete[] / realloc()
==11476==    at 0x4867AD0: free (in /usr/libexec/valgrind/vgpreload_memcheck-arm64-linux.so)
==11476==    by 0x10BB33: free_t_char (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==11476== Conditional jump or move depends on uninitialised value(s)
==11476==    at 0x109184: free_scommand (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)

==14006== 32 bytes in 1 blocks are still reachable in loss record 21 of 82
==14006==    at 0x4865058: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-arm64-linux.so)
==14006==    by 0x1113C3: ft_lstnew (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x10D44B: check_and_replace (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x10CBC7: ft_export_to_linked (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x10CC9B: ft_export_print_linked (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x10EE4B: pipex_one_cmd (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x10FCAF: pipex (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x10941B: start_execution (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x10972F: main (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)

==14006== 534 bytes in 35 blocks are still reachable in loss record 38 of 82
==14006==    at 0x4865058: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-arm64-linux.so)
==14006==    by 0x1108EF: ft_strdup (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x1113DB: ft_lstnew (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x10DDB7: create_envlist (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x1096FF: main (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)

==14006== 68 bytes in 1 blocks are still reachable in loss record 27 of 82
==14006==    at 0x4865058: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-arm64-linux.so)
==14006==    by 0x1108EF: ft_strdup (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x1113EF: ft_lstnew (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x10D70F: create_envlist_util_2 (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x10D8DF: create_envlist_util (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x10DCEB: create_envlist (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x1096FF: main (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)

==14006== 60 bytes in 1 blocks are still reachable in loss record 26 of 82
==14006==    at 0x4865058: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-arm64-linux.so)
==14006==    by 0x1108EF: ft_strdup (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x1113EF: ft_lstnew (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x10D9CF: create_envlist_util (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x10DCEB: create_envlist (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x1096FF: main (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)

==14006== 1 bytes in 1 blocks are still reachable in loss record 1 of 82
==14006==    at 0x4865058: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-arm64-linux.so)
==14006==    by 0x1108EF: ft_strdup (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x1113EF: ft_lstnew (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x10D44B: check_and_replace (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x10CBC7: ft_export_to_linked (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x10CC9B: ft_export_print_linked (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x10EE4B: pipex_one_cmd (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x10FCAF: pipex (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x10941B: start_execution (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)
==14006==    by 0x10972F: main (in /workspaces/tofaramususa/Desktop/devcontainer/home/42Cursus/TheBash/minishell)

Functions: Check and Replace; create_envlist_util_2; create_envlist_util_2;