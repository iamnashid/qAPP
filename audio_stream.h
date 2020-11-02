#ifndef __AUDIO_STREAM_H__
#define __AUDIO_STREAM_H__

#include <iostream>
#include "parser.h"

class audio_stream : public Parser
{
    public:
        audio_stream(std::string url_str) 
        {
            this->url = url_str;
        }
        static std::size_t play_stream(void *buffer, std::size_t size, std::size_t nmemb, void *userp);
        void process_stream();
};

#endif