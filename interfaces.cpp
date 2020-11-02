/***
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
***/

#include <QtWidgets/QApplication>
#include <QtCore/QString>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTextEdit>
#include <QtGui/QTextCursor>
#include <QtGui/QTextBlockFormat>
#include <vector>
#include <string>
#include <iostream>
#include "parser.h"
#include "interfaces.h"
#include "json.hpp"

using json = nlohmann::json;

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
    try
    {
        json j_parsed = json::parse(buffer);
        QTextEdit *gui = new QTextEdit();
        // surah Name and Name meaning
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
    } catch( nlohmann::detail::type_error &err)
    {
        std::cout << "\033[1;31m An error occured , make sure you entered valid surah and ayah \033[0m" << std::endl;
        exit(0);
    }
}

void GUI::getsurah(std::string buffer)
{
    try
    {
        json j_parsed = json::parse(buffer);
        int ayahs = j_parsed["data"]["ayahs"].size(); // Number of ayahs
        std::vector<QString>parsed_data;
        int count = 1;
        for(int i=0;i<ayahs;i++)
        {
            // push each ayah into vector
            parsed_data.push_back(QString::fromStdString(j_parsed["data"]["ayahs"][i]["text"].get<std::string>())); 
        }
        QTextEdit *gui = new QTextEdit();
        // surah Name and Name Meaning
        gui->setText(QString::fromStdString(j_parsed["data"]["englishName"].get<std::string>()) + " ("+ QString::fromStdString(j_parsed["data"]["englishNameTranslation"].get<std::string>()) +")");
        gui->append("\n");
        for(QString ayah : parsed_data)
        {
            QString data =  QString::fromStdString(std::to_string(count)) + ". " + ayah;
            gui->append(data + "\n");
            count++;
        }
        // Edition Name
        gui->append("Edition : " + QString::fromStdString(j_parsed["data"]["edition"]["name"]));
        QTextCursor cursor = gui->textCursor();
        QTextBlockFormat textBlockFormat = cursor.blockFormat();
        textBlockFormat.setAlignment(Qt::AlignCenter);
        cursor.mergeBlockFormat(textBlockFormat);
        gui->selectAll();
        // Set Font Size
        gui->setFontPointSize(32);
        gui->setTextCursor(cursor);
        gui->setReadOnly(true);
        QWidget *widget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout();
        layout->addWidget(gui);
        widget->setLayout(layout);
        widget->show();
    } catch( nlohmann::detail::type_error &err)
    {
        std::cout << "\033[1;31m An error occured , make sure you entered valid surah \033[0m" << std::endl;
        exit(0);
    }
}
