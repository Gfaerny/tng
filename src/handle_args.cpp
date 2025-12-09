#include "../include/handle_args.hpp"
#include "../include/tng_make_file.hpp"



std::string config_filename = "" , license_name = "";
int iit = 0;

static bool license_bool = false , config_bool = false;

int handle_args( std::vector<std::string> tng_args_vec)
{
  for(auto it: tng_args_vec)
  {
    ++iit;

    if(it == "-h" || it == "--help")
    {
      if(iit > 1)
      {
      std::printf ("you have to use -h or --help option alone\n"
                   "use --help or -h option's to see usage");
      return 0;
      }
      else 
      {
        std::printf("tng usage : tng -[OPTIONS] [OPTION_CONFIG_NAME] [FILENAME]\n"
                    
                    "-c    or    --config  :   use your writed config's file for adding it to files that going to created\n\n\n"
                    "-l    or    --license :   use you writted or available license for adding them to you file\n\n\n"
                    "-h    or    --help    :   use it to see this massage and tng gotta exit\n");
///     we got more thing to explain
      }
        
    }
    else if(it == "-c" || "--config")
    {
      if(tng_args_vec[iit].empty())
      {
        std::printf ("no config file selected\nuse --help or -h option's to see usage");
        texit;
      }
      else
      {
        config_filename = tng_args_vec[iit];
        tng_args_vec.erase(tng_args_vec.begin() + iit);
        config_bool  = true;
      }
    }
    else if(it == "-l" || it == "-license")
    {
      if(tng_args_vec[iit].empty())      
      {
        std::printf ( "no license file selected\nuse --help or -h option's for see usage");
        texit;
      }
      else
      {
        license_name = tng_args_vec[iit];
        tng_args_vec.erase(tng_args_vec.begin() + iit);
        license_bool = true;
      }
    }

    
  }

  tng_make_file(tng_args_vec , config_bool , license_bool);
  
    
return 0;
}  
