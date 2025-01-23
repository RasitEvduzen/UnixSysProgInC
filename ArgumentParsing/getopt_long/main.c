#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define ALL     1
#define LENGTH 'l'
#define NUMBER  3

int main(int argc, char *argv[])
{
    int result;
    int a_flag, b_flag, all_flag, length_flag, number_flag, err_flag;

    a_flag = b_flag = all_flag = length_flag = number_flag = err_flag = 0;
    opterr = 0;

    struct option options[] ={
        
        {"all",no_argument, &a_flag, ALL},
        {"length",required_argument, NULL, LENGTH},
        {"number",optional_argument, NULL, NUMBER},
        {0,0,0,0},

    };

    char *b_arg, *length_arg, *number_arg = NULL;

    while((result = getopt_long(argc,argv,"ab:l:",options,NULL)) != -1)
    {
        switch(result)
        {

            case 'b':
                b_flag = 1;
                b_arg = optarg;
                break;
            case ALL:
                all_flag = 1;
                break;
            case LENGTH:
                length_flag = 1;
                length_arg = optarg;
                break;
            case NUMBER:
                number_flag = 1;
                number_arg = optarg;
                break;
            case '?':
                if (optopt == 'b')
                    fprintf(stderr,"-b option without argument!\n");
                else if(optopt == LENGTH)
                    fprintf(stderr,"--length option without argument!\n");
                else if(optopt != 0)
                    fprintf(stderr, "-%c invalid option!\n",optopt);
                else 
                    fprintf(stderr, "invalid long options!\n");
                err_flag = 1;
        }

    }

    if(err_flag)
        exit(EXIT_FAILURE);

    if(a_flag)
        printf("-a option given\n");
    if(b_flag)
        printf("-b option given with argument \"%s\"\n",b_arg);
    if(all_flag)
        printf("--all option given\n");
    if(length_flag)
        printf("--length option given with argument \"%s\"\n",length_arg);
    if(number_flag)
        if(number_arg)
            printf("--number option given with argument \"%s\"\n",number_arg);
        else
            printf("--number option given without argument\n");

    if(optind != argc)
        printf("arguments without options:\n");
    
    for(int i = optind; i < argc; ++i)
        puts(argv[i]);
}
