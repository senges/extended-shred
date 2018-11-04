#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <dirent.h>
#include <assert.h>

#include <math.h>
#include <ctype.h>

#include <sys/types.h>
#include <sys/stat.h>

#if !defined( PATH_MAX )
    #define PATH_MAX 256
#endif // !defined( PATH_MAX )

#define OPT_FOLLOW_LINKS 1
#define OPT_APPARENT_SIZE 0

// #define TEST_PATH "/home/l3/senges/Public/TEST"
#define TEST_PATH "/dev/null"
