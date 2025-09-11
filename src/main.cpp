    #include <cstdio>
    #include <fstream>
    #include <iostream>
    #include <start.h>

    /// why god
    #define TNG_NOARG_ERROR {printf ("tng: Error , you get not argument.add flag --help for more info \n");}
    #define TNG_HELPARG {printf ("tng\nUsage : tng [FILENAME]... [OPTION]...\nConfigable crossplatform cli filemaker\n   -c, --nano config file  \n   -h, --help       display this help and exit\n");}


    std::string arg1 = "";
    int main(int argc,char* argv[])

{
    if(argv[1] == nullptr)
    {
        TNG_NOARG_ERROR;
        return 1;
    } 
    
    else
    {
        arg1 = argv[1];
    }
    
    if (arg1 == "--help" || arg1 == "-h")
    {
        TNG_HELPARG;
        return 0;
    }
    else
    {
        std::string FileName = argv[1];
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
