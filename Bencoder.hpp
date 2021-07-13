#ifndef BENCODE_H_
#define BENCODE_H_

#include <vector>
#include <map>
#include <string>
#include <any>

class Bencoder {

    public:
        Bencoder(std::vector<unsigned char> _bytes) : bytes(_bytes) {}
    
        std::any Decode();

    private:
        int pos = 0;
        bool has_next_object = false;
        const std::vector<unsigned char> bytes;

        const static unsigned char number_start          = 'i';
        const static unsigned char number_end            = 'e';
        const static unsigned char list_start            = 'l';
        const static unsigned char list_end              = 'e';
        const static unsigned char dictionary_start      = 'd';
        const static unsigned char dictionary_end        = 'e';
        const static unsigned char byte_string_divider   = ':';
        
        long _DecodeNumber();
        std::any _DecodeObject();
        std::vector<std::any> _DecodeList();
        std::vector<unsigned char> _DecodeByteString();
        std::map<std::string, std::any> _DecodeDictionary();
};

#endif