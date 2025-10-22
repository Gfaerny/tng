  
  #include "../include/tng_make_file.hpp"

#include <filesystem>
  #include <fstream>
#include <streambuf>

  #define STRING(X , Y) do{std::string X = Y;} while(0);

  
//  #define gen_file do{for(auto it : arguments){files.open(it , std::ofstream::out);}}while(0);
//  #define gen_file_error do{if(files){files.open(it , std::ofstream::out);}}while(0);

      struct passwd *pw = getpwuid(getuid());
      const char *homedir = pw->pw_dir;

int tng_make_file(std::vector<std::string> arguments , std::string* config_filename ,std::string* license_filename)
{
  std::ofstream files;
  if(config_filename == nullptr)
  {
    if(license_filename == nullptr)
    {
      std::ofstream files;
      for(std::string r : arguments)
      {
        files.open(r);        
        if(!files.is_open())
        {
          std::cout << "tng error : file " << r << " can't get created.\n check directory or user permisions" ;
        }
      }
    }
  
    std::string license_file_path = "/usr/share/common-licenses/" + *license_filename;       
    
/// std::ofstream FN f;
    if(!std::filesystem::exists(license_file_path))
    {
      std::cout << "tng error : license file name (" << license_file_path <<") ccould't find.\n"; 
      return 0;
    }

    std::ifstream LCF (license_file_path);
    
    if(!LCF.is_open())
    {
      std::cout << "tng error : tng can't open license file for streaming\ncheck license filepath or user permision\n";
      return 0;      
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




  



