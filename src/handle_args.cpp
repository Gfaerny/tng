#include "../include/handle_args.hpp"
#include <cerrno>
#include <csignal>
#include <iostream>
#include <vector>
#define texit return 0;


std::string config_filename = "" , license_name = "";
int iit = 0;


int handle_args( std::vector<std::string> tng_args_vec)
{

  for(auto it: tng_args_vec)
  {
    ++iit;

    if(it == "-h" || it == "--help")
    {

      if(iit > 1)
      {
      std::cout << "you have to use -h or --help option alone" << '\n' << "use --help or -h option's to see usage";
      return 0;
      }
      else
      {
        std::cout << "tng usage : tng -[OPTIONS] [OPTION_CONFIG_NAME] [FILENAME]" <<'\n'
        << "available options :"<<  '\n'
        << "-c    or    --config  :   use your writed config's file for adding it to files that going to created"<< '\n'
        <<'\n'
        <<'\n'
        << "-l    or    --license :   use you writted or available license for adding them to you file"
        <<'\n'
        <<'\n'
        << "-h    or    --help    :   use it to see this massage and tng gotta exit"<<'\n';
///     we got more thing to explain
      }
        
    }
    else if(it == "-c" || "--config")
    {
      if(tng_args_vec[iit].empty())
      {
        std::cout << "no config file selected" << '\n' << "use --help or -h option's to see usage";
        texit;
      }
      else
      config_filename = tng_args_vec[iit];
    }
    else if(it == "-l" || it == "-license")
    {
      if(tng_args_vec[iit].empty())      
      {
        std::cout << "no license file selected" << '\n' << "use --help or -h option's for see usage";
        texit;
      }
      else
      license_name = tng_args_vec[iit];
    }
    
  }

  tng_make_file(tng_args_vec);
  
  
    
return 0;
}  
