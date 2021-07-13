#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "Bencoder.hpp"

std::any Bencoder::Decode() {

    return Bencoder::_DecodeObject();
}

std::any Bencoder::_DecodeObject() {

    std::any object;

    switch (Bencoder::bytes[Bencoder::pos]) {

        case Bencoder::number_start:
            object = Bencoder::_DecodeNumber();
            break;
    
        case Bencoder::list_start:
            object = Bencoder::_DecodeList();
            break;

        case Bencoder::dictionary_start:
            object = Bencoder::_DecodeDictionary();
            break;

        default:
            object = Bencoder::_DecodeByteString();
            break;
    }
    
    return object;
}

long Bencoder::_DecodeNumber() {

    int number = 0;
    int num_digits = 0;

    while(Bencoder::bytes[++Bencoder::pos] != 'e') ++num_digits;

    Bencoder::pos -= num_digits;
    for (int pos_weight = std::pow(10, num_digits - 1); pos_weight > 0; pos_weight /= 10)
        number += (Bencoder::bytes[Bencoder::pos++] - '0') * pos_weight;

    Bencoder::pos += 1; // Move to the start of the next object?

    return number;
}

std::vector<unsigned char> Bencoder::_DecodeByteString() {

    int num_digits = 0;
    int string_length = 0;
    std::vector<unsigned char> byte_string;
    
    while (Bencoder::bytes[Bencoder::pos++] != Bencoder::byte_string_divider) ++num_digits;

    Bencoder::pos -= num_digits + 1;
    for (int pos_weight = std::pow(10, num_digits - 1); pos_weight > 0; pos_weight /= 10)
        string_length += (Bencoder::bytes[Bencoder::pos++] - '0') * pos_weight;

    byte_string.resize(string_length);
    std::copy(Bencoder::bytes.begin() + Bencoder::pos + 1, 
              Bencoder::bytes.begin() + Bencoder::pos + string_length + 1,
              byte_string.begin());

    Bencoder::pos += 1;

    return byte_string;
}

std::vector<std::any> Bencoder::_DecodeList() {

    std::vector<std::any> list;

    Bencoder::pos++;
    do list.push_back(Bencoder::_DecodeObject());
    while(Bencoder::bytes[Bencoder::pos] != Bencoder::list_end);

    return list;
}

std::map<std::string, std::any> Bencoder::_DecodeDictionary() {

    std::map<std::string, std::any> list;

    return list;
}

int main() {
    std::string _bytes = "l62:Sicario.Day.Of.The.Soldado.2018.1080p.WEBRip.x264-[YTS.AM].mp4e";
    std::vector<unsigned char> bytes(_bytes.begin(), _bytes.end());

    Bencoder bencoder(bytes);
    std::any byte_string = bencoder.Decode();
}