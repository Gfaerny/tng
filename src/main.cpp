    #include "makefile.h"
#include <cstdint>
    #include <cstdio>
    #include <iomanip>
    #include <string>
    #include <string.h>
    #include <vector>
    #include <iostream>

    
    std::vector<std::string> TNG_ARG_STACK = {};

    char* Config_Name;
    char* License_Name;


void print_usage()
{
	  fprintf(stderr,
		"usage: tng [OPTIONS] [FILENAMES]\n"
		"\n"
		"options:\n"
		"  -h, --help                 show this help message\n"
		"  -c <configname> <file> , --config  <configname> <file>    use specified config for begining file comment\n"
    "  -l <licensename> <file> , --license <licensename> <file>  use specified license for \n"
		);
}



int main(int argc,char* argv[])
{

    bool TNG_LICENSE = false , TNG_CONFIG = false;

    if(argv[1]  == nullptr)
    {
        printf("tng error : few argument's\n");
        print_usage();
        return 1;
    }
    

    for(int8_t i  = 0 ;i < argc ; i++)
    {
        fprintf( stderr ,"%d\n" , i);
        fprintf(stderr ,"%s\n" , argv[i]);
        std::quoted(argv[i]);
        if (strcmp (argv[i] ,"-c") || strcmp(argv[i] , "--config"))
        {
            TNG_CONFIG = true;        
        }
            
        else if (strcmp(argv[i] , "-l") || strcmp(argv[i] , "--license") )
        {
            TNG_LICENSE = true;
        }
///     here we store non-option argument's
        else
        {
            TNG_ARG_STACK.push_back(argv[i]);
        }
    }
   
        if (strcmp(argv[1], "-h") || strcmp(argv[1], "--help"))
        {
            if(argc > 2)
            {
                fprintf
                    (
                        stderr ,
                        "tng Warrning :You have to use --help option alone for tng result"
                    );
                
            }

            print_usage();
        
        }

            
        std::cout << TNG_CONFIG << " =   TNG_CONFIG " << "TNG_LICENSE = "<< TNG_LICENSE << std::endl;
        printf("it true\nso it work now");
                
            
        TNG_MAKE_FILE(TNG_ARG_STACK,  TNG_CONFIG, TNG_LICENSE);
                

        /*
        TNG_MAKE_FILE(TNG_ARG_STACK , TNG_CONFIG ,TNG_LICENSE);        
        

            std::string FileName = argv[argc];
            std::ofstream file;
            file.open(FileName);

            if (!file.is_open())
            {
*/
        return 0;
    }

    
