#include "../include/handle_args.hpp"
#include "../include/tng_make_file.hpp"

std::vector<std::string> TNG_ARG_STACK ={};

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
    if(argc > 2)
    {
        printf("tng error : few argument's\n");
        print_usage();
        return 1;
    }

    for(auto i = 0 ; i < argc ; ++i)
    {
        TNG_ARG_STACK.push_back(argv[i]);
    }

    handle_args(TNG_ARG_STACK);

    tng_make_file(TNG_ARG_STACK,  TNG_CONFIG, TNG_LICENSE);
    for(std::string r : TNG_ARG_STACK)
    {
        std::cout << r << "\n";
    }

    return 0;
}


