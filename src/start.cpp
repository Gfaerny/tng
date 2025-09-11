  #include <fstream>
  #include <cstdio>


  
  bool Tng_S()
{
  std::ofstream Config_file;
  Config_file.open("/home/gfaerny/.config/tng/tng.conf");
  if(Config_file.is_open())
  {
    return false;
  }
  else
  {
    return false;
  }
  return true;
};
