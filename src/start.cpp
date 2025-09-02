  #include <fstream>
  #include <cstdio>

  bool Tng_S()
{
  std::ofstream Config_file;
  Config_file.open("ciii");
  if(!Config_file.is_open())
  {
   return false; 
  }
  else
  {
    return true;
  }
  
};
