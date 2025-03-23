#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <getopt.h>


#define DEFAULT_LINE_CHARACTERS 16


bool disp_text(FILE *fp);
bool disp_octal(FILE *fp, int n_argc);
bool disp_hex(FILE *fp, int n_argc);
int check_number(const char *str);

int main(int argc, char **argv)
{
    int result;
    int t_flag, o_flag, x_flag, n_flag, error_flag;
    int n_arg;
    FILE *fp;
    t_flag = o_flag = x_flag = n_flag = error_flag = 0;
    n_arg = DEFAULT_LINE_CHARACTERS;
    opterr = 0;

    while((result = getopt(argc,argv,"toxn:")) != -1)
        switch(result){
            case 't':
                t_flag = 1;
                break;
            case 'o':
                o_flag = 1;
                break;
            case 'x':
                x_flag = 1;
                break;
            case 'n':
                n_flag = 1;
                if((n_arg = check_number(optarg)) < 0){
                    fprintf(stderr,"-n argument is invalid!..\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case '?':
                if(optopt == 'n') fprintf(stderr,"-%c option must have an argument!\n",optopt);
                else fprintf(stderr,"-%c invalid option!\n",optopt);
                error_flag = 1;
                break;
        }
    if(error_flag) exit(EXIT_FAILURE);
    if(t_flag + o_flag + x_flag >1){
        fprintf(stderr,"only one of -[tox] option may be specified!...\n");
        exit(EXIT_FAILURE);
    }
    if(t_flag + o_flag + x_flag == 0) t_flag = 1; 
    if(t_flag && n_flag){
        fprintf(stderr,"-n option cannot be used with -t option!..\n");
        exit(EXIT_FAILURE);
    }
    if(argc - optind == 0)    {
        fprintf(stderr,"File must be specified!..\n");
        exit(EXIT_FAILURE);
    }
    if(argc - optind > 1){
        fprintf(stderr,"Too many file specified!..\n");
        exit(EXIT_FAILURE);
    }
    if((fp = fopen(argv[optind], t_flag ? "r" : "rb")) == NULL){
        fprintf(stderr,"Cannot open file: %s\n",argv[optind]);
        exit(EXIT_FAILURE);
    }
    if(t_flag)
        result = disp_text(fp);
    else if(o_flag)
        result = disp_octal(fp, n_arg);
    else
        result = disp_hex(fp, n_arg);
    
    if(!result){
        fprintf(stderr,"Cannor read file: %s\n",argv[optind]);
        exit(EXIT_FAILURE);
    }
    fclose(fp);

    return 0;
}


bool disp_text(FILE *fp)
{
    int ch;
    while((ch = fgetc(fp)) != EOF)
        putchar(ch);
    return feof(fp);
}

bool disp_octal(FILE *fp, int n_argc)
{
    int ch;
    size_t i;
    for(i = 0; (ch = fgetc(fp) != EOF); ++i){
        if(i % n_argc == 0)
            printf("%08zo ",i);
        printf("%03o ",ch);
        if(i % n_argc == n_argc - 1)
            putchar('\n');
    }
    putchar('\n');
    return feof(fp);
}

bool disp_hex(FILE *fp, int n_argc)
{
    size_t i;
    int ch;
    for(i = 0; (ch = fgetc(fp)) != EOF; ++i){
        if(i % n_argc == 0){
            if(i != 0)
                putchar('\n');
            printf("%08zx ",i);
        }
        printf("%02X ",ch);
    }
    putchar('\n');
    return feof(fp);
}



int check_number(const char *str)
{
    const char *temp;
    int result;
    while(isspace(*str)) ++str;
    temp = str;
    while(isdigit(*temp)) ++str;
    if(*str != '\0') return -1;
    result = atoi(str);
    if(!result) return -1;
    return result;
}