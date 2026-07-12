#include "../include/config.hpp"
#include <cstddef>
#include <memory_resource>
#include <vector>

#define RESET_TOKEN token = ""

/*
 * Config loader and config value setter
 */
int Config::load(const std::string &config_path)
{
    // We first try to open config file
    // We want config file be hardcoded but also can changed by argument
    // Thet hardcoded address = $HOME/.config/tng/tng.conf but also can changed by --config or -c option
    // Check tng.conf config file
    std::ifstream config_file(config_path);
    if (!std::filesystem::exists(config_path))
    {
        std::printf("tng error : config file (%s), do not exist", config_path.c_str());
        throw tng_error{.error_type_o = error_type::file_does_n_exist,
                        .error_massage = tepic_error_massages::C_FILE_N_EXIST(config_path)};
    }
    // Print witch config now got loaded
    std::printf("tng alert : config that used -> %s", config_path.c_str());
    std::string line{""};
    std::string seprated_word{""};
    int line_number{0};
    // Each line that provide one of extension file comment charecter defination got counted by this varable
    int extension_file_spec_counter{0};

    return 0;
}

template <typename T> void ConfigData::pushSectionElement(T SectionData, int *number)
{
    if (typeid(T) != typeid(std::vector<std::string>))
    {
        CountDataFilling++;
        Data.emplace_back();
        Data.back(SectionData);
    }

    // If SectionData type is not vector<string> so it's just string
    else
    {
        CountDataFilling++;
        Data.emplace_back();
        Data.back().first = SectionData;
    }
}
