    #include <cstdint>
    #include <cstdio>
    #include <fstream>
    #include <iostream>
    #include <MassagePrint.h>
    #include <string.h>
    #include <stack>

std::string arg1 = "";
    
bool TNG_CONFIG = false;
bool TNG_LICENSE = false;

std::stack<char *> TNG_ARG_STACK = {};

int main(int argc,char* argv[])

{   

    if(argv[1] == nullptr)
    {
        TNG_MSG_NOARG_ERROR();
        return 1;
    }    
    else
    {
        arg1 = argv[1];
    }

    for(int8_t i  = 0 ;i < argc ; i++)
    {
///     this is for test    std::cout << i << " " << argv[i] << "\n";            

        if (strcmp (argv[i] ,"-c") || strcmp(argv[i] , "--c") || strcmp (argv[i], "-C"))
        {
            TNG_CONFIG == true;
        }
        else if(strcmp(argv[i] , "-l") || strcmp(argv[i] , "--l") )
        {
            TNG_LICENSE = true;
        }
    
///     here we store non-option argument's 
        TNG_ARG_STACK.push(argv[i]);
    }

    
    if (arg1 == "--help" || arg1 == "-h")
    {
        TNG_MSG_HELPARG();
        return 0;
    }
    else
    {
        std::string FileName = argv[argc];
        std::ofstream file;
        
        file.open(FileName);
    
        std::cout << FileName << std::endl;
        if (!file.is_open())
        {
            std::cout << "tng: Error for while making file.check your permission" << std::endl;
            return 1;
        }
        std::cout << "tng: File named : "<< arg1 <<" just got created." << std::endl;
        file.close();
    }
    
    return 0;
}
