#ifndef __INTERFACES_H__
#define __INTERFACES_H__

class GUI : protected Parser 
{
public:
    GUI(const std::string link)
    {
        this->url = link;
    }
    void process_request(int requestType);
    void getayah(std::string buffer);
    void getsurah(std::string buffer);
};

#endif