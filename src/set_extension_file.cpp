
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
  return file_extention_name;
}


/// use u_int16_t cause we have over 10000 file's extention name
const u_int16_t type_num(std::string file_extention) 
{
 
  if (file_extention == "c" || "cpp" || "css" || "cc" )
  {
    /*
    C-like comment
    -> //comment 
    -> /*coment*/
  return 1;
  }

  else if ()
  {
    
  }
  
  
}
