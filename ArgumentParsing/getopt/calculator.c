#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char **argv)
{
    int result;
    int a_flag, m_flag, d_flag, s_flag, b_flag, error_flag;
    a_flag = m_flag = s_flag = b_flag = error_flag = 0;
    double arg1, arg2;
    while((result = getopt(argc,argv,"amds")) != -1)
        switch (result){
            case 'a':
                a_flag = 1;
                break;
            case 'm':
                m_flag = 1;
                break;
            case 'd':
                d_flag = 1;
                break;
            case 's':
                s_flag = 1;
                break;
            case '?':
                fprintf(stderr,"-%c invalid option!\n",optopt);
                error_flag = 1;
                break;
            default:
                break;
        }
    if(error_flag) exit(EXIT_FAILURE);

    if(argc - optind != 2){
        fprintf(stderr,"Usage: %s [-amds] <num1> <num2>\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    if(a_flag + m_flag + d_flag + s_flag != 1){
        fprintf(stderr,"Usage: %s [-amds] <num1> <num2>\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    if(a_flag + m_flag + d_flag + s_flag == 0){
        fprintf(stderr,"Usage: %s [-amds] <num1> <num2>\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    
    arg1 = atof(argv[optind]);
    arg2 = atof(argv[optind+1]);

    if(a_flag)      printf("Addition: %.2lf\n",arg1+arg2);
    else if(m_flag) printf("Multiplication: %.2lf\n",arg1*arg2);
    else if(d_flag) printf("Division: %.2lf\n",arg1/arg2);
    else            printf("Subtraction: %.2lf\n",arg1-arg2);

    return 0;
}
