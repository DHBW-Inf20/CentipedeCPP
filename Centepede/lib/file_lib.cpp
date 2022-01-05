#include "file_lib.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <memory>

File::File(std::string filepath){
    this->filepath = std::string(filepath);
    this->readstream = std::make_shared<std::ifstream>();
    this->writestream = std::make_shared<std::ofstream>();
}

File::~File(){
    this->filepath = nullptr;
    this->readstream->close();
    this->writestream->close();
    this->readstream = nullptr;
    this->writestream = nullptr;
}

long File::getByteSize(){
    bool isResponsible = this->openRead();

    // aktuelle Position sichern:
    std::ifstream::pos_type pos = this->readstream->tellg();
    // ans Ende der Datei springen:
    this->readstream->seekg(0, this->readstream->end);
    // Position ist jetzt gleich der Dateilänge:
    std::ifstream::pos_type len = this->readstream->tellg();
    long lenght = len;
    this->readstream->seekg(0, this->readstream->end);
    // wieder an die Ursprungsposition zurück springen:
    this->readstream->seekg(pos, this->readstream->end);

    this->closeAll(isResponsible);
    return lenght;
}

std::shared_ptr<std::vector<char>> File::readAllBytes(){
    bool isResponsible = this->openRead();

    // Länge der Datei herausfinden.
    auto filesize = this->getByteSize();
    // Leere Datei.
    if (filesize == 0) {
        this->closeAll(isResponsible);
        return std::make_shared<std::vector<char>>();
    }

    // Buffer für die Bytes.
    auto result = std::make_shared<std::vector<char>>(filesize);

    // Von Anfang bis Ende lesen.
    this->readstream->seekg(0, std::ios::beg);
    this->readstream->read(&(*result)[0], filesize);

    this->closeAll(isResponsible);
    return result;
}

std::shared_ptr<std::vector<char>> File::readBytes(long from, long to){
    if(from > to){
        std::logic_error fromBiggerTo("Der Parameter 'from' muss kleiner oder gleich 'to' sein.");
        throw fromBiggerTo;
    }

    bool isResponsible = this->openRead();

    // Länge der Datei herausfinden:
    auto filesize = this->getByteSize();
    if(to >= filesize){
        std::logic_error outOfBounds("Der angegebene Abschnitt geht über das Dateiende hinaus!");
        throw outOfBounds;
    }

    long length = (to - from) + 1;

    // buffer
    auto result = std::make_shared<std::vector<char>>(length);

    // Von from bis to lesen:
    this->readstream->seekg(from, std::ios::beg);
    this->readstream->read(&(*result)[0], length);

    this->closeAll(isResponsible);
    return result;
}

std::shared_ptr<std::vector<std::shared_ptr<std::string>>> File::readAllLines(){
    auto lines = std::make_shared<std::vector<std::shared_ptr<std::string>>>();

    bool isResponsible = this->openRead();
    std::string line;
    while(getline(*this->readstream, line, '\n')){
        // Zeile für Zeile laden und speichern.
        lines->push_back(std::make_shared<std::string>(line));
    }
    this->closeAll(isResponsible);

    return lines;
}

std::shared_ptr<std::string> File::readAllText(){
    std::shared_ptr<std::string> text = std::make_shared<std::string>();

    bool isResponsible = this->openRead();
    std::string line;
    char endOfLine = '\n';
    while(getline(*this->readstream, line, endOfLine)){
        // Zeile für Zeile laden und speichern.
        *text += line + endOfLine;
    }
    this->closeAll(isResponsible);

    return text;
}

bool File::openRead(){
    // Falls bereits geöffnet einfach so lassen.
    if(this->readstream->is_open()){
        return false;
    }

    // Sonst eventuell geöffnete Schreib-Verbindung schließen.
    this->writestream->close();
    // Dann versuche Lesend zu öffnen.
    this->readstream->open(this->filepath, std::ios::binary);

    // Falls nicht erfolgreich einen Fehler werfen.
    if(!this->readstream->is_open()){
        // Wenn die Datei nicht gefunden wurde.
        this->writestream->close();
        std::logic_error fileNotFound("Die angegebene Datei wurde nicht gefunden");
        throw fileNotFound;
    }

    return true;
}

bool File::openWrite(bool appending){
    // Falls bereits geöffnet einfach so lassen.
    if(this->readstream->is_open()){
        return false;
    }

    // Sonst eventuell geöffnete Lese-Verbindung schließen.
    this->readstream->close();
    // Dann versuche Schreibend zu öffnen.
    if(appending){
        this->writestream->open(this->filepath, std::ios::binary | std::ios::app);
    }
    else{
        this->writestream->open(this->filepath, std::ios::binary);
    }

    // Falls nicht erfolgreich einen Fehler werfen.
    if(!this->writestream->is_open()){
        // Wenn die Datei nicht gefunden wurde.
        this->readstream->close();
        std::logic_error fileNotFound("Die angegebene Datei wurde nicht gefunden");
        throw fileNotFound;
    }

    return true;
}

void File::closeAll(bool isResponsible){
    if(!isResponsible){
        return;
    }
    this->readstream->close();
    this->writestream->close();
}

void File::appendBytes(int byteCount, char* bytes){
    bool isResponsible = this->openWrite(true);

    for(int i = 0; i < byteCount; i++){
        *this->writestream << bytes[i];
    }

    this->closeAll(isResponsible);
}

void File::appendString(std::string &text){
    bool isResponsible = this->openWrite(true);

    *this->writestream << text;

    this->closeAll(isResponsible);
}
