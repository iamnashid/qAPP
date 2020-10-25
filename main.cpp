/***
   * Project Name : qAPP
   * Description : an easy to use Quran Reading program in Qt5, supports translations in indian languages as well
   *               Specs :- Offline mode [TODO] , Multi-language , easy to use
   * Build-Dependencies : libcurl , qt5 libs, nlohmann json : https://github.com/nlohmann/json/
   * Developer : Nashid
   * Project Status : Alpha
   *
   * Functions Description:-
   *
   * void help_menu() 
   *    Show help menu and exit
   *
   * int check_option(char *argv[], int x)
   *    check the arguments passed to the program and process it accordingly
   *
   * bool isSurah(char *arg)
   *    check if the given argument is surah , true if the argument contains only intigers
   *
   * int isInt(char *arg)
   *    check if the given argument is Integers , related to ayah processing
   *    return true if all chars except ':' are integers
   *
   * std::string curl_process()
   *    make a GET request to API and return the result in std::string form
   *
   * std::size_t WriteMemoryCallback(char* , std::size_t, std::size_t, std::string)
   *    Function to store the contents of GET Request into MEMORY instead of stdout
   *
   * std::size_t write_data(void* , std::size_t, std::size_t, void*)
   *    Function to store the contents of GET request into FILE instead of stdout
   *
   * void process_request(int requestType)
   *    show ayah or surah in GUI mode , if requestType = 0 , show ayah
   *    else if requestType = 1 , show surah
   *
   * void getayah(std::string str_buffer)
   *    accept GET request result of ayah and display it in GUI mode
   *
   * void getsurah(std::string str_buffer)
   *    accept GET request result of surah and display it in GUI mode
   *
   * void tr_help() { defined in headerfile translations.h }
   *    show available translations
   *
   * std::string request_edition(std::string arg)
   *    check the arg and return the appropriate translation , if arg is invalid return " " which is pure quran without translation
   *
   *
***/
  
#include <QtWidgets/QApplication>
#include <QtCore/QString>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTextEdit>
#include <QtGui/QTextCursor>
#include <QtGui/QTextBlockFormat>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include "json.hpp"
#include "translations.h"
#include <iomanip>
#include <cstdlib>
#include <vector>

using json = nlohmann::json;

void help_menu();
int check_option(int argc, char *argv[], int x);
bool isSurah(char *arg);
bool isInt(char *arg);


class Parser {
protected:
    std::string url;
    std::string curl_process();
    static std::size_t WriteMemoryCallback(char *in, std::size_t size, std::size_t nmemb, std::string *out);
    static std::size_t write_data(void *ptr, std::size_t size, std::size_t nmemb, void *stream);
};

class GUI : protected Parser 
{
public:
    GUI(std::string link)
    {
        this->url = link;
    }
    void process_request(int requestType);
    void getayah(std::string buffer);
    void getsurah(std::string buffer);
};

class CLI : protected Parser 
{
public:
    void main_menu();
};


int main(int argc, char *argv[])
{
    QApplication qCLI(argc, argv);
    if(argc == 1)
    {
        std::cout << "\n\033[1;31m No arguments provided , use '--h' for help menu \033[0m" << std::endl;
        exit(0);
    }
    for(int x=1;x<argc;x++)
    {
        // check for "--" in arguement
        if(argv[x][0] == '-' && argv[x][1] == '-' && argc >= 2)
        {
            x = check_option(argc, argv, x);
            break;
        }
        else
        {
            help_menu();
            exit(0);
        }
    }
    return qCLI.exec();
}

std::size_t Parser::WriteMemoryCallback(char *in, std::size_t size, std::size_t nmemb, std::string *out)
{
    std::size_t total_size = size * nmemb;
    if(total_size)
    {
        out->append(in, total_size);
        return total_size;
    }
    return 0;
}

std::size_t write_data(void *ptr, std::size_t size, std::size_t nmemb, void *stream)
{
    std::size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

std::string Parser::curl_process()
{
    std::string str_buffer;
    CURL *curl_handler = curl_easy_init();
    CURLcode res;

    if(curl_handler)
    {
        curl_easy_setopt(curl_handler, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl_handler, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl_handler, CURLOPT_WRITEDATA, &str_buffer);
        res = curl_easy_perform(curl_handler);
        if(res != CURLE_OK)
        {
            std::cerr << " curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            exit(1);
        } 
        else 
        {   
            curl_easy_cleanup(curl_handler);
            return str_buffer;
        } 
    }
    return ("Null");
}

void GUI::process_request(int requestType)
{
    if(requestType == 0)
    {
        this->getayah(this->curl_process());
    } else if(requestType == 1) {
        this->getsurah(this->curl_process());
    }
}

void GUI::getayah(std::string buffer)
{
    json j_parsed = json::parse(buffer);
    QTextEdit *gui = new QTextEdit();
    gui->setText(QString::fromStdString(j_parsed["data"]["surah"]["englishName"].get<std::string>()) + " " + "(" + QString::fromStdString(j_parsed["data"]["surah"]["englishNameTranslation"].get<std::string>()) + ")" + "\n");
    QTextCursor cursor = gui->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignCenter);
    cursor.mergeBlockFormat(textBlockFormat);
    gui->setTextCursor(cursor);
    gui->append(QString::fromStdString(j_parsed["data"]["text"].get<std::string>()));
    gui->setReadOnly(true);
    QWidget *widget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(gui);
    widget->setLayout(layout);
    widget->show();
}

void GUI::getsurah(std::string buffer)
{
    json j_parsed = json::parse(buffer);
    int ayahs = j_parsed["data"]["ayahs"].size();
    std::vector<QString>parsed_data;
    int count = 1;
    for(int i=0;i<ayahs;i++)
    {
        parsed_data.push_back(QString::fromStdString(j_parsed["data"]["ayahs"][i]["text"].get<std::string>()));
    }
    QTextEdit *gui = new QTextEdit();
    gui->setText(QString::fromStdString(j_parsed["data"]["englishName"].get<std::string>()) + " ("+ QString::fromStdString(j_parsed["data"]["englishNameTranslation"].get<std::string>()) +")");
    gui->append("\n");
    for(QString ayah : parsed_data)
    {
        QString data =  QString::fromStdString(std::to_string(count)) + ". " + ayah;
        gui->append(data + "\n");
        count++;
    }
    gui->append("Edition : " + QString::fromStdString(j_parsed["data"]["edition"]["name"]));
    QTextCursor cursor = gui->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignCenter);
    cursor.mergeBlockFormat(textBlockFormat);
    gui->selectAll();
    gui->setFontPointSize(32);
    gui->setTextCursor(cursor);
    gui->setReadOnly(true);
    QWidget *widget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(gui);
    widget->setLayout(layout);
    widget->show();
}

void help_menu()
{
    std::cout << " Usage: qCLI [OPT] [arg] " << std::endl;
    std::cout << " OPTions:- " << std::endl;
    std::cout << "\t --o: " << std::endl;
    std::cout << "\t\t[arg]:- " <<std::endl;
    std::cout << "\t\t\t[surah] or [surah]:[ayah] for a single ayah with {optional[translation]} " << std::endl;
    std::cout << "\t\t\t[surah] and [ayah] must be integer " << std::endl;
    std::cout << "\t\t\tEg:- " << std::endl;
    std::cout << "\t\t\t   qCLI --o 1 , return surah Al-Fatiha without any translation " << std::endl;
    std::cout << "\t\t\t   qCLI --o 1:1 sahih , returns surah Al-Fatiha Verse 1 in saheeh international english translation" << std::endl;
    std::cout << "\t\t\t   qCLI --o 1 sahih , returns surah Al-Fatiha " << std::endl;
    std::cout << "\t --h : " << std::endl;
    std::cout << "\t\t show this help menu and exit " << std::endl;
    std::cout << "\t --i: " << std::endl;
    std::cout << "\t\t Not available yet " << std::endl;
    std::cout << "\t --t: " << std::endl;
    std::cout << "\t\t List of available translations " << std::endl;
}

int check_option(int argc, char *argv[], int x)
{
    std::string url_ayah = "https://api.alquran.cloud/v1/ayah/";
    std::string url_surah = "https://api.alquran.cloud/v1/surah/";
    std::string edition = "quran-simple-enhanced";

    if(argv[x][2] == 'i') // --i
    {
        std::cout << " Not Available yet " << std::endl;
        exit(0);
    } 
    else if(argv[x][2] == 'o' && argc >= 3) // --o
    {    
        if(isSurah(argv[x+1]))
        {
            if(atoi(argv[x+1]) == 0)
            {
                std::cout << "\n [surah] must be an integer , provided value = " << argv[x+1] << std::endl;
                exit(0);
            } else 
            {
                if(argc == 4)
                {
                    edition = return_edition(static_cast<std::string>(argv[x+2]));
                }
                url_surah.append(argv[x+1]);
                url_surah.append("/"+edition);
                GUI Surah_GUI(url_surah);
                Surah_GUI.process_request(1);
            }
        } 
        else 
        {
            if(!isInt(argv[x+1]))
            {
                std::cout << "\n [surah] and [ayah] must be an integer , provided value = " << argv[x+1] << std::endl;
                exit(0);
            } else {
                url_ayah.append(argv[x+1]);
                url_ayah.append("/en.sahih");
                GUI Ayah_GUI(url_ayah);
                Ayah_GUI.process_request(0);
            }
        }
    }
    else if(argv[x][2] == 'h')
    {
        help_menu();
        exit(0);
    }
    else if(argv[x][2] == 't')
    {
        tr_help();
        exit(0);
    } 
    else 
    {
        std::cout << " Invalid option provided or insufficient arguements , use --h to show help menu " << std::endl;
        exit(0);
    }
    return x;
}

bool isSurah(char *arg)
{
    for(int i=0;arg[i]!='\0';i++)
    {
        if(arg[i] == ':')
            return false;
    }
    return true;
}

bool isInt(char *arg)
{
    int arglen = strlen(arg);
    int intlen = 0;
    for(int i=0;arg[i]!= '\0';i++)
    {
        if((arg[i] >= '0' && arg[i] <= '9') && arglen > 2)
        {
            intlen++;
        }
        if(arg[i] == ':')
            continue;
    }
    if(intlen == arglen-1)
    {
        return true;
    }
    return false;
}