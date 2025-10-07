    #include "makefile.h"
    #include <cstdint>
    #include <cstdio>
    #include <iomanip>
    #include <string>
    #include <string.h>
    #include <vector>
    #include <print>
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
            std::cout << "what fuck 1";
        printf("tng error : few argument's\n");
        print_usage();
        return 1;
    }


    for(int8_t i  = 1 ;i < argc ; i++)
    {
        std::cout << "hi this is argv[i]" << argv[i] << "\n" <<std::endl;
        if (std::string(argv[i]) == "-c" || std::string(argv[i]) == "--config")
        {
            TNG_CONFIG = true;
        }
        else if (std::string(argv[i]) == "-l" || std::string (argv[i]) == "--license")
        {
            TNG_LICENSE = true;
        }
        else if(std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help")
        {
            if(i > 2)
            {
                printf("tng error : if you want to use -h or --help option use it alone\n");
                return 1;
            }
            else
            {
                print_usage();
            }

        }
        else
        {
            TNG_ARG_STACK.push_back(argv[i]);
        }
    }


   ///     std::cout << TNG_CONFIG << " =   TNG_CONFIG " << "TNG_LICENSE = "<< TNG_LICENSE << std::endl;
   ///     printf("it true\nso it work now");


        TNG_MAKE_FILE(TNG_ARG_STACK,  TNG_CONFIG, TNG_LICENSE);

        for(std::string r : TNG_ARG_STACK)
        {
            std::cout << r << "\n";
        }



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


