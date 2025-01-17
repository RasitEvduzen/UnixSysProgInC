#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

//amM:ds
int main(int argc, char* argv[])
{
    int result;
    int a_flag, m_flag, M_flag, d_flag, s_flag, err_flag;
    char* M_arg;


    a_flag = m_flag = M_flag = d_flag = s_flag = err_flag = 0;
    opterr = 0;

    while((result = getopt(argc, argv, "amM:ds")) != -1)
    {
        switch(result)
        {
            case 'a':
                a_flag = 1;
                break;
            case 'm':
                m_flag = 1;
                break;
            case 'M':
                M_flag = 1;
                M_arg = optarg;
                break;
            case 'd':
                d_flag = 1;
                break;
            case 's':
                s_flag = 1;
                break;
            case '?':
                if(optopt == 'M')
                    fprintf(stderr, "-M option must have an argument!\n");
                else
                    fprintf(stderr, "-%c invalid option!\n", optopt);
                err_flag = 1;
        }
    }

    if(err_flag)
        exit(EXIT_FAILURE);

    if(argc - optind != 2)
    {
        fprintf(stderr, "Two arguments must be specified!\n");
        exit(EXIT_FAILURE);
    }


    if(a_flag + d_flag + m_flag + s_flag != 1)
        "only one option must be specified except -M\n";

    double arg1 = atof(argv[optind]);
    double arg2 = atof(argv[optind + 1]);
    double cal_result;
    

    if(a_flag)
        cal_result = arg1 + arg2;
    else if(m_flag)
        cal_result = arg1 * arg2;
    else if(d_flag)
        cal_result = arg1 / arg2;
    else 
        cal_result = arg1 - arg2;

    if(M_flag)
        printf("%s: %f\n",M_arg, cal_result);
    else    
        printf("%f\n",cal_result);

}