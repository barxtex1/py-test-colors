#include "defs.h"


std::vector<std::string> split(const std::string& str, char seperator)
{
   std::vector<std::string> output;

    std::string::size_type prev_pos = 0, pos = 0;

    while((pos = str.find(seperator, pos)) != std::string::npos)
    {
        std::string substring( str.substr(prev_pos, pos-prev_pos) );

        output.push_back(substring);

        prev_pos = ++pos;
    }

    output.push_back(str.substr(prev_pos, pos-prev_pos));

    return output;
}

std::string decToHexa(int n)
{
    // char array to store hexadecimal number
    char hexaDeciNum[2];

    // counter for hexadecimal number array
    int i = 0;
    while (n != 0) {

        // temporary variable to store remainder
        int temp = 0;

        // storing remainder in temp variable.
        temp = n % 16;

        // check if temp < 10
        if (temp < 10) {
            hexaDeciNum[i] = temp + 48;
            i++;
        }
        else {
            hexaDeciNum[i] = temp + 87;
            i++;
        }

        n = n / 16;
    }

    std::string hexCode = "";
    if (i == 2) {
        hexCode.push_back(hexaDeciNum[0]);
        hexCode.push_back(hexaDeciNum[1]);
    }
    else if (i == 1) {
        hexCode = "0";
        hexCode.push_back(hexaDeciNum[0]);
    }
    else if (i == 0)
        hexCode = "00";

    // Return the equivalent
    // hexadecimal color code
    return hexCode;
}

int HexToDec(char num[]) {
   int len = strlen(num);
   int base = 1;
   int temp = 0;
   for (int i=len-1; i>=0; i--) {
      if (num[i]>='0' && num[i]<='9') {
         temp += (num[i] - 48)*base;
         base = base * 16;
      }
      else if (num[i]>='a' && num[i]<='f') {
         temp += (num[i] - 87)*base;
         base = base*16;
      }
   }
   return temp;
}

std::string hex2rgba(const std::string &hex_)
{
    try
    {
        std::string hex;
        if (hex_.size() == 3)
        {
            for (size_t i = 0; i < hex_.size(); i++)
            {
                hex += hex_[i];
                hex += hex_[i];
            }
        }
        else
        {
            hex = hex_;
        }
        std::string rgba;
        for (size_t i=0 ; i < hex.size(); i += 2)
        {
            std::string str = hex.substr(i,2);
            char * cstr = new char [str.length()+1];
            std::strcpy(cstr, str.c_str());
            rgba += std::to_string(HexToDec(cstr)) + ",";
            delete[] cstr;
        }
        rgba.erase(rgba.size()-1);
        return rgba;
    }
    catch (const char* e)
    {
        std::cout<< e <<std::endl;
    }
    return "0";
}

std::string rgba2rgb(const std::string &rgba)
{
    std::vector<std::string>values = split(rgba, ',');
    float alpha = std::stof(values[3]);
    int R = ((255 - alpha)/255) * 255 + (alpha/255) * std::stoi(values[0]);
    int G = ((255 - alpha)/255) * 255 + (alpha/255) * std::stoi(values[1]);
    int B = ((255 - alpha)/255) * 255 + (alpha/255) * std::stoi(values[2]);
    return std::to_string(R)+","+std::to_string(G)+","+std::to_string(B);
}

std::string rgba2hsl(const std::string &rgba, const bool &check)
{
    std::string rgb;
    if(check)
    {
        rgb = rgba2rgb(rgba);
    }
    else{
        rgb = rgba;
    }
    std::vector<std::string>values = split(rgb, ',');
    std::vector<float> values0_1(values.size());
    std::transform(values.begin(), values.end(), values0_1.begin(), [](const std::string& val)
    {
        return std::stof(val);
    });
    for (auto & val : values0_1)
    {
        val = val/255;
    }
    auto it_max = std::max_element(values0_1.begin(),values0_1.end());
    auto it_min = std::min_element(values0_1.begin(),values0_1.end());
    float L = (*it_max + *it_min)/2;
    float S;
    int H;
    if (*it_max == *it_min)
    {
        S = 0;
        H = 0;
    }
    else{
        if(L<=0.5)
        {
            S = (*it_max-*it_min)/(*it_max+*it_min);
        }
        else{
            S = (*it_max-*it_min)/(2.0 - *it_max - *it_min);
        }
        for (size_t i = 0; i < values0_1.size(); i++)
        {
            if(values0_1[i] == *it_max)
            {
                if(i == 0)
                {
                    H = ((values0_1[1]-values0_1[2])/(*it_max-*it_min))*60;
                }
                else if(i == 1)
                {
                    H = (2.0 + (values0_1[2]-values0_1[0])/(*it_max-*it_min))*60;
                }
                else if(i == 2)
                {
                    H = (4.0 + (values0_1[0]-values0_1[1])/(*it_max-*it_min))*60;
                }
            }
        }
    }
    return std::to_string(H)+","+std::to_string(S)+","+std::to_string(L);
}


std::string rgba2hex(const std::string &rgba)
{
    try
    {
        std::vector<std::string>values = split(rgba, ',');
        if ((std::stoi(values[0]) >= 0 && std::stoi(values[0]) <= 255)
            && (std::stoi(values[1]) >= 0 && std::stoi(values[1]) <= 255)
            && (std::stoi(values[2]) >= 0 && std::stoi(values[2]) <= 255)
            && (std::stoi(values[3]) >= 0 && std::stoi(values[3]) <= 255))
        {
            std::string hex = "#";
            hex += decToHexa(std::stoi(values[0]));
            hex += decToHexa(std::stoi(values[1]));
            hex += decToHexa(std::stoi(values[2]));
            hex += decToHexa(std::stoi(values[3]));

            return hex;
        }
        else{
            throw "The hex color code doesn't exist for rgba: "+rgba;
        }
    }
    catch (const char* e)
    {
        std::cout<< e <<std::endl;
    }
    return "0";
}
