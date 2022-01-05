#ifndef FILE_LIB_HPP
#define FILE_LIB_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

class File{
    private:
        std::string filepath;
        std::shared_ptr<std::ifstream> readstream;
        std::shared_ptr<std::ofstream> writestream;
    
    public:
        File(std::string filepath);
        ~File();

        long getByteSize();
        std::shared_ptr<std::vector<char>> readAllBytes();
        std::shared_ptr<std::vector<char>> readBytes(long from, long to);
        
        template <typename TResult>
        // Liest eine Reihe von Bytes und nutzt den reinterpret_cast, um den gewünschten Typ zurück zu geben.
        // Die Indizes from und to sind inklusive! d.h. (35, 37) liest Byte[35,36,37].
        std::shared_ptr<TResult> readBytesAs(long from, long to){
            auto byte_ptr = this->readBytes(from, to);
            auto result_ptr = reinterpret_cast<TResult*>((*byte_ptr).data());
            return std::make_shared<TResult>(*result_ptr);
        }

        std::shared_ptr<std::vector<std::shared_ptr<std::string>>> readAllLines();
        std::shared_ptr<std::string> readAllText();

        void appendBytes(int byteCount, char* bytes);
        void appendString(std::string &text);

    private:
        bool openRead();
        bool openWrite(bool appending);
        void closeAll(bool isResponsible);
};

#endif