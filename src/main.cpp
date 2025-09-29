    #include <cstdint>
    #include <cstdio>
    #include <fstream>
    #include <string>
    #include <string.h>
    #include <vector>

    std::string arg1 = "";

    bool TNG_CONFIG = false;
    bool TNG_LICENSE = false;


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
    if(argv[1]  == nullptr)
    {
        printf("hf\n");
        return 1;
    }
    

    for(int8_t i  = 0 ;i < argc - 1 ; i++)
    {
        std::fprintf( stderr ,"%d\n" , i );
    
        if (strcmp (argv[i] ,"-c") || strcmp(argv[i] , "--config"))
        {
            TNG_CONFIG = true;
            printf("hi");
        }
            
        else if (strcmp(argv[i] , "-l") || strcmp(argv[i] , "--license") )
        {
            printf("hi");
            TNG_LICENSE = true;
        }
///     here we store non-option argument's
        TNG_ARG_STACK.push_back(argv[i]);

    }
   
        if (arg1 == "--help" || arg1 == "-h")
        {
            if(argc > 2 == 1)
            {
                fprintf
                    (
                        stderr ,
                        "tng Warrning :You have to use --help option alone for tng result"
                    );
                
            }

            print_usage();
            return 0;
        }

        for(int8_t i = 0; i < TNG_ARG_STACK.size() ; i++)
        {
            if(TNG_CONFIG || TNG_LICENSE)
            {
                printf("it true");
                
            }

        }
        
        

            std::string FileName = argv[argc];
            std::ofstream file;
            file.open(FileName);

            if (!file.is_open())
            {
    ///            std::cout << "tng: Error while making file. $s check your permission" << std::endl;
    
                return 1;
            }

            file.close();

        return 0;
    }

    
