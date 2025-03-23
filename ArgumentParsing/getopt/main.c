#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int result;
    char *c_arg, *e_arg;
    int a_flag, b_flag, c_flag, d_flag, e_flag, error_flag;
    a_flag = b_flag = c_flag = d_flag = e_flag = error_flag = 0;
    opterr = 0;     // For user defined error message

    while((result = getopt(argc,argv,"abc:de:")) != -1) // getopt() returns -1 when there are no more options to parse
        switch (result){
            case 'a':
                a_flag = 1;
                break;
            case 'b':
                b_flag = 1;
                break;
            case 'c':
                c_flag = 1;
                c_arg = optarg;
                break;
            case 'd':
                d_flag = 1;
                break;
            case 'e':
                e_flag = 1;
                e_arg = optarg;
                break;
            case '?':
                if(optopt == 'c' || optopt == 'e') fprintf(stderr,"-%c option must have an argument!\n",optopt);
                else fprintf(stderr,"-%c invalid option!\n",optopt);
                error_flag = 1;
                break;
            default:
                break;
        }
    if(error_flag) exit(EXIT_FAILURE);

    if(a_flag) printf("-a option given\n");                           // Option with no argument
    if(b_flag) printf("-b option given\n");                           // Option with no argument
    if(c_flag) printf("-c option given with argument: %s\n",c_arg);   // Option with argument
    if(d_flag) printf("-d option given\n");                           // Option with no argument
    if(e_flag) printf("-e option given with argument: %s\n",e_arg);   // Option with argument

    if(optind != argc){
    printf("\nArguments without option:\n");                          
        for(int i = optind; argv[i]; ++i)                             // Arguments without option
            printf("%s \n",argv[i]);
    }

    return 0;
}
