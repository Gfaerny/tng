    #include <cstdio>
    #include <fstream>
    #include <iostream>
    int main(int argc,char* argv[])

{
   std::string FileName = argv[1];
   std::ofstream file;
   file.open(FileName);

    std::cout << FileName << std::endl;
    if (!file.is_open())
    {
       std::cout << "tng: Error for while making file check your permission" << std::endl;
        return 1;
    }
    std::cout << "tng: Done" << std::endl;
    file.close();
    return 0;
}
