#!/usr/bin/g++
#include "CLI11.hpp"
#include "functions.cpp"


std::regex reg_hex(R"(^([0-9a-f]{3}|[0-9a-f]{6}|[0-9a-f]{8})$)");
std::regex reg_rgba(R"(^([0-9]{1,3},){3}[0-9]{1,3}$)");


class Color
{
private:
    std::vector<std::vector<std::string>>Colors;
public:
    Color(){};
    void setColor_hex(const std::string &hex)
    {
        std::vector<std::string>temp;
        std::string rgba = hex2rgba(hex);
        std::string hsl;
        if(hex.size() != 8)
        {
            hsl = rgba2hsl(rgba,false);
        }
        else{
            hsl = rgba2hsl(rgba,true);
        }
        temp.emplace_back(rgba);
        temp.emplace_back("#"+hex);
        temp.emplace_back(hsl);
        Colors.emplace_back(temp);
    }
    void setColor_rgba(const std::string &rgba)
    {
        std::vector<std::string>temp;
        std::string hex = rgba2hex(rgba);
        std::string hsl = rgba2hsl(rgba,true);
        temp.emplace_back(rgba);
        temp.emplace_back(hex);
        temp.emplace_back(hsl);
        Colors.emplace_back(temp);
    }
    void setSaturation(const std::string &hsl)
    {
        Colors.back()[2] = hsl;
    }
    std::vector<std::vector<std::string>> getColors()
    {
        return Colors;
    }
};


void MODEs(Color & colo, const std::string &MODE, const std::vector<std::string> & arguments)
{
    if(MODE == "lowest")
    {
        try
        {
            std::vector<std::vector<std::string>>temp_colors = colo.getColors();
            std::vector<std::string>values_rgba = split(temp_colors[0][0],',');
            int R_lowest = std::stoi(values_rgba[0]);
            int G_lowest = std::stoi(values_rgba[1]);
            int B_lowest = std::stoi(values_rgba[2]);
            int A_lowest = std::stoi(values_rgba[3]);

            std::string new_color_;
            for (auto & color_ : temp_colors)
            {
                values_rgba = split(color_[0],',');
                if (R_lowest > std::stoi(values_rgba[0]))
                {
                    R_lowest = std::stoi(values_rgba[0]);
                }
                if (G_lowest > std::stoi(values_rgba[1]))
                {
                    G_lowest = std::stoi(values_rgba[1]);
                }
                if (B_lowest > std::stoi(values_rgba[2]))
                {
                    B_lowest = std::stoi(values_rgba[2]);
                }
                if (A_lowest > std::stoi(values_rgba[3]))
                {
                    A_lowest = std::stoi(values_rgba[3]);
                }
            }
            colo.setColor_rgba(std::to_string(R_lowest)+","+std::to_string(G_lowest)+","+std::to_string(B_lowest)+","+std::to_string(A_lowest));

        } catch (std::exception & e) {
            std::cout<< e.what() <<std::endl;
        }

    }
    else if (MODE == "highest")
    {
        try {
            std::vector<std::vector<std::string>>temp_colors = colo.getColors();
            std::vector<std::string>values_rgba = split(temp_colors[0][0],',');
            int R_highest = std::stoi(values_rgba[0]);
            int G_highest = std::stoi(values_rgba[1]);
            int B_highest = std::stoi(values_rgba[2]);
            int A_highest = std::stoi(values_rgba[3]);

            std::string new_color_;
            for (auto & color_ : temp_colors)
            {
                values_rgba = split(color_[0],',');
                if (R_highest < std::stoi(values_rgba[0]))
                {
                    R_highest = std::stoi(values_rgba[0]);
                }
                if (G_highest < std::stoi(values_rgba[1]))
                {
                    G_highest = std::stoi(values_rgba[1]);
                }
                if (B_highest < std::stoi(values_rgba[2]))
                {
                    B_highest = std::stoi(values_rgba[2]);
                }
                if (A_highest < std::stoi(values_rgba[3]))
                {
                    A_highest = std::stoi(values_rgba[3]);
                }
            }
            colo.setColor_rgba(std::to_string(R_highest)+","+std::to_string(G_highest)+","+std::to_string(B_highest)+","+std::to_string(A_highest));

        } catch (std::exception & e) {
            std::cout<< e.what() <<std::endl;
        }

    }
    else if(MODE == "mix-saturate")
    {
        try
        {
            std::vector<std::vector<std::string>>temp_colors = colo.getColors();
            std::vector<std::vector<std::string>>values_hsl;
            float new_saturation = 0.0;
            for (auto & color_ : temp_colors)
            {
                values_hsl.emplace_back(split(color_[2],','));
            }
            std::vector<std::string> last_hsl = values_hsl.back();
            values_hsl.pop_back();
            for (auto & value : values_hsl)
            {
                new_saturation += std::stof(value[1]);
            }
            new_saturation = new_saturation/values_hsl.size();
            last_hsl[1] = std::to_string(new_saturation);
            colo.setSaturation(last_hsl[0]+","+last_hsl[1]+","+last_hsl[2]);
        }
        catch (std::exception & e)
        {
            std::cout<< e.what() <<std::endl;
        }
    }
    else
    {
        try
        {
            std::smatch m;
            std::vector<std::string>temp_rgba;
            std::vector<std::string>values_rgba;
            std::vector<int>new_color_vector(4);
            std::string new_color_;
            for (auto & arg : arguments)
            {
                if (std::regex_search(arg, m, reg_hex))
                {
                    temp_rgba.emplace_back(hex2rgba(m[0]));
                }
                else if (std::regex_search(arg, m, reg_rgba))
                {
                    temp_rgba.emplace_back(m[0]);
                }
                else{
                    std::cerr << "Invalid argument: " << arg << std::endl;
                }
            }
            if(!temp_rgba.empty())
            {
                for (auto & rgba_ : temp_rgba)
                {
                    values_rgba = split(rgba_,',');
                    if (values_rgba.size() == 3)
                    {
                        new_color_vector[0] += std::stoi(values_rgba[0]);
                        new_color_vector[1] += std::stoi(values_rgba[1]);
                        new_color_vector[2] += std::stoi(values_rgba[2]);
                    }
                    else if(values_rgba.size() == 4)
                    {
                        new_color_vector[0] += std::stoi(values_rgba[0]);
                        new_color_vector[1] += std::stoi(values_rgba[1]);
                        new_color_vector[2] += std::stoi(values_rgba[2]);
                        new_color_vector[3] += std::stoi(values_rgba[3]);
                    }
                }
                for (auto & value : new_color_vector)
                {
                    value = value/temp_rgba.size();
                    new_color_ += std::to_string(value)+",";
                }
                new_color_.erase(new_color_.size()-1);
                colo.setColor_rgba(new_color_);
            }

        } catch (const std::exception & e)
        {
            std::cout<< e.what() << std::endl;
        }
    }
}




int main(int argc, char** argv)
{
    CLI::App app{"App description"};

    // Define options
    std::string MODE;
    std::vector<std::string>arguments;
    app.add_option("-m,--mode", MODE, "select mode: [mix, lowest, highest, mix-saturate]");
    app.add_option("...", arguments, "other arguments can be used as values");

    CLI11_PARSE(app, argc, argv);

    Color c;
    std::fstream read_file("colors.txt",std::ios::in);
    if(read_file.is_open())
    {
        std::string line;
        std::smatch m;
        while (getline (read_file, line))
        {
          if (std::regex_search(line, m, reg_hex))
          {
              c.setColor_hex(m[0]);
          }
          else if (std::regex_search(line, m, reg_rgba))
          {
              c.setColor_rgba(m[0]);
          }
        }
    }
    else
    {
        std::cout<<"Could not find file with specified name"<<std::endl;
    }

    MODEs(c,MODE,arguments);
    std::vector<std::vector<std::string>>all_colors = c.getColors();
    for (size_t i = 0; i < all_colors.size(); i++)
    {
        std::cout<< "Color number "<<i+1<<" - "<< "RGBA: " << all_colors[i][0] << " HEX: " << all_colors[i][1] << " HSL: " << all_colors[i][2] << std::endl;
    }



    return 0;
}
