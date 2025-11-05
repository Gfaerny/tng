
#include <cstdlib>
#include <fstream>
#include <string>
#include <sys/types.h>

std::string extention_type(std::string filename)
{
  std::string file_extention_name = "";
  for(char it :filename)
  {
    if(it != '.')    
    {
      file_extention_name += it;
    }

    else if(it == '.')
    {
      if(file_extention_name != "")
        file_extention_name = "";       
    }
    
  }
}



const u_int16_t type_num(std::string file_extention) 
{

  file_extention[0] = '';
  
  if (file_extention == "c" || "cpp" || "css")
  {
    
  }
  
  
}
