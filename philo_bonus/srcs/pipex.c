#include <stdio.h>
#include "../include/philo_bonus.h"

void child_one(int *end, int *infile, char **av,char *path, char **envp)
{
        char **cmd_option;
    infile[0] = open(av[1], O_RDONLY );
    if (infile[0] < 0)
            ft_error(av[1]);
    close(end[0]);
    dup2(infile[0], STDIN_FILENO);
    close(infile[0]);
    printf("in child1, about to call dup2\n");

    dup2(end[1], STDOUT_FILENO); 
    close(end[1]);
//    close(end[0]);
    cmd_option = ft_split(av[2], ' ');
cmd_option[0]);
    execve(path, &cmd_option[0], envp);
    free_after_split(&cmd_option);
}

void child_two(int *end, int *outfile, char av[], char *path, char envp)
{
    char **cmd_option;

    outfile[1] = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (outfile[1] < 0)
        ft_error(av[4]);
    close(end[1]);
    dup2(outfile[1], STDOUT_FILENO);
//    close(outfile[1]);
    dup2 (end[0], STDIN_FILENO);
//    close(end[0]);
    cmd_option = ft_split(av[3], ' ');
    execve(path, &cmd_option[0], envp);
    free_after_split(&cmd_option);
}
void pipex(int *infile,char **av, char *path_cmd1, char *path_cmd2, char **envp)
{
    int end[2];
    pid_t child1;
    pid_t child2;

    if (pipe(end) < 0) 
        ft_error(NULL);
    child1 = fork();
    if (child1 == 0)
        child_one(end, infile, av, path_cmd1, envp);
    else if (child1 < 0)
        ft_error("fork");;
    waitpid(child1, NULL, 0);
//    close(end[0]); 
    close(end[1]);
    child2 = fork();
    if (child2 == 0)
        child_two(end, infile, av, path_cmd2, envp);
    else if (child2 < 0)
        ft_error("fork");
    waitpid(child2, NULL, 0);
    close(end[0]);
//    close(end[1]);
}

int main(int argc, char **argv)
{
    void pipex(int *infile,char **av, char *path_cmd1, char *path_cmd2, char **envp)
    pipex(argv)
}