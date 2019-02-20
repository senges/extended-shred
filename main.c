#include "main.h"

int r_flag = 0; /* recursive flag */
int v_flag = 0; /* verbose flag */
int z_flag = 0; /* replace by zeros flag */
int u_flag = 0; /* remove file flag */
int f_flag = 0; /* force flag */
int n_flag = 0; /* overwrite default n iterations */
int m_flag = 0; /* Multi process (must be tested) */

/* shred options */
char * s_opt = NULL;

/* Properly exiting program */
void die() {
    // Handle child process
    exit(EXIT_FAILURE);
}

/* Prints command usage */
void usage(const char *executable)
{
    fprintf(stderr, "Usage: %s [-r] [-zuvf] [-n iteration] [-e path] expr\n", executable);
    die();
}

/* build shred options command line */
void build_options()
{
    int i = 0;
    int size = v_flag + z_flag + u_flag + f_flag + 2;

    s_opt = malloc(sizeof(char) * size);

    s_opt[i++] = '-';
    
    if (v_flag) s_opt[i++] = 'v';
    if (z_flag) s_opt[i++] = 'z';
    if (u_flag) s_opt[i++] = 'u';
    if (f_flag) s_opt[i++] = 'f';
    //if (n_flag) s_opt[i++] = 'n';

}

/* Check if argument is valid number */
int is_number(const char *arg)
{
    /* Make sure not to exceed uint16_t max value */
    assert(pow(2, 16) > strlen(arg));

    uint16_t i;
    for (i = 0; i < strlen(arg); ++i)
        if (isdigit(arg[i]) == 0) 
            return 0;

    return 1;
}

/* Shred targeted file */
int shred_me(const char *path)
{
    return (s_opt == NULL) ? execlp("shred", "shred", path, NULL) : execlp("shred", "shred", s_opt, path, NULL);
}

/* Browse files, recursivly if needed */
int browse(const char *pathname)
{
    int32_t code = 0;
    char path[PATH_MAX];

    struct stat st;
    DIR *dir = NULL;
    struct dirent *cur_dir = NULL;

    /* Should we follow symbolic links ? */
    code = (OPT_FOLLOW_LINKS) ? lstat(pathname, &st) : stat(pathname, &st);

    if (code)
        perror("lstat");

    assert(code != -1);

    if (S_ISDIR(st.st_mode) && r_flag)
    {

        dir = opendir(pathname);

        if (dir == NULL)
            perror("opendir");

        assert(dir != NULL);

        while ((cur_dir = readdir(dir)) != NULL)
            if (strcmp(cur_dir->d_name, ".") != 0 && strcmp(cur_dir->d_name, "..") != 0)
            {
                snprintf(path, PATH_MAX, "%s/%s", pathname, cur_dir->d_name);
                browse(path);
            }

        closedir(dir);
    }

    else if (S_ISREG(st.st_mode))
        shred_me(pathname);

    return 0;
}

int main(int argc, char **argv)
{

    if (argc < 1)
	usage(argv[0]);

    int opt;
    while ((opt = getopt(argc, argv, "rvzufmn:")) != -1)
    {
        switch (opt)
        {
        case 'r':
            r_flag = 1;
            break;
        case 'v':
            v_flag = 1;
            break;
        case 'z':
            z_flag = 1;
            break;
        case 'u':
            u_flag = 1;
            break;
        case 'f':
            f_flag = 1;
            break;
        case 'n':
            if (is_number(optarg) == 0)
                usage(argv[0]);

            n_flag = atoi(optarg);
            break;
        case '?':
            usage(argv[0]);
        }
    }

    /* Path remains */
    assert(argc - optind > 0);

    printf("%s\n", argv[optind]);

    if (r_flag || v_flag || z_flag || u_flag || f_flag)
        build_options();

    browse(argv[optind]);

    return 0;
}
