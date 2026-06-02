#ifndef EXCEPTION_H
#define EXCEPTION_H



class DeckFileNotFound : public std::exception{
public:
    const char* what() const noexcept override {
        return "Deck File Error: File not found";
    }
};


class DeckFileFormatError : public std::exception{
    int m_line;
public:
    DeckFileFormatError(int line) : m_line(line){};

    const char* what() const noexcept override {
        std::string str = "Deck File Error: File format error in line " + std::to_string(m_line);
        return str.c_str();
    }

};


class DeckFileInvalidSize : public std::exception{
    const char* what() const noexcept override{
        return "Deck File Error: Deck size is invalid";
    }
};
#endif //EXCEPTION_H
