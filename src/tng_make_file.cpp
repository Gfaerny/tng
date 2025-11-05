
#include "../include/tng_make_file.hpp"

#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <streambuf>

#define STRING(X , Y) do{std::string X = Y;} while(0);


const char* type(const char* r)
{
  const char* last_dot = nullptr;
  const char* p = r;

  while (*p != '\0')
  {
      if (*p == '.')
          last_dot = p;
        ++p;
  }

  if (last_dot == nullptr || *(last_dot + 1) == '\0')
      return nullptr;
  return last_dot + 1;
}





//  #define gen_file do{for(auto it : arguments){files.open(it , std::ofstream::out);}}while(0);
//  #define gen_file_error do{if(files){files.open(it , std::ofstream::out);}}while(0);

struct passwd *pw = getpwuid(getuid());
const char *homedir = pw->pw_dir;

void tng_make_file(std::vector<std::string> arguments , std::string* config_filename ,std::string* license_filename)
{
/// we gonna use one object of ofstream class for lower binrary
  std::ofstream files;

  if(config_filename == nullptr)
  {

    if(license_filename == nullptr)
    {
      for(std::string r : arguments)
      {
        files.open(r);
        if(!files.is_open())
        {
          std::printf ("tng error : file  %s can't get created.\n check directory or user permisions",r.c_str()) ;
          EXIT_FAILURE;
        }
        files.close();
      }
    EXIT_SUCCESS;
    }

    std::string license_file_path = "/usr/share/common-licenses/" + *license_filename;

    if(!std::filesystem::exists(license_file_path))
    {
      std::printf ("tng error : license file name (%s) ccould't find.\n" , license_file_path.c_str());
      EXIT_FAILURE;
    }

    std::ifstream LCF (license_file_path);

    if(!LCF.is_open())
    {
      std::printf ("tng error : tng can't open license file for streaming\ncheck license filepath or user permision\n");
      EXIT_FAILURE;
    }

    for(std::string r : arguments)
    {

    /// this section stand for if we don't order option --no-comment
      
      std::ifstream ifr(r);
      std::filebuf *license_stream_buffer = LCF.rdbuf();
      std::filebuf *target_file_buffer = ifr.rdbuf();

      char copy_license_buffer = license_stream_buffer->sbumpc();

      
      
      
      while(copy_license_buffer != EOF)
      {
            
      }

      }
    }
  }
  else
  {

  }

}


///       add config file's or license file's to

///         arguments.erase();
            std::ofstream file;
///            file.open(arguments[i] , std::ofstream::out);
///  file.close();
}








