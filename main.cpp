/***
   * Project Name : qAPP
   * Description : an easy to use Quran Reading program in Qt5, supports translations in indian languages as well
   *               Specs :- Offline mode [TODO] , Multi-language , easy to use
   * Build-Dependencies : libcurl , qt5 libs, nlohmann json : https://github.com/nlohmann/json/
   * Developer : Nashid
   * Project Status : Beta
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
***/

#include <QtWidgets/QApplication>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <cstdio>
#include "parser.h"
#include "interfaces.h"
#include "translations.h"

void help_menu();
int check_option(int argc, char *argv[], int x);
bool isSurah(char *arg);
bool isInt(char *arg);
void process_option(int argc, char *argv[], int x);

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
    std::cout << "\t --t: " << std::endl;
    std::cout << "\t\t List of available translations " << std::endl;
}

int check_option(int argc, char *argv[], int x)
{

    if(argv[x][2] == 'o' && argc >= 3) // --o
    {    
        process_option(argc,argv,x);
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

void process_option(int argc, char *argv[], int x)
{
    std::string url_ayah = "https://api.alquran.cloud/v1/ayah/";
    std::string url_surah = "https://api.alquran.cloud/v1/surah/";
    std::string edition = "quran-simple-enhanced";

    if(isSurah(argv[x+1]))
    {
        if(!isInt(argv[x+1]))
        {
            std::cout << "\n [surah] must be an integer , provided value = " << argv[x+1] << std::endl;
            exit(0);
        } 
        else 
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
        } 
        else 
        {                
            if(argc == 4)
            {
                edition = return_edition(static_cast<std::string>(argv[x+2]));
            }
            url_ayah.append(argv[x+1]);
            url_ayah.append("/"+edition);
            GUI Ayah_GUI(url_ayah);
            Ayah_GUI.process_request(0);
        }
    }
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

