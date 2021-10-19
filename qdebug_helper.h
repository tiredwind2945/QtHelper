/****************************************************************************
**
** Author:              wangjun
** E-Mail:              tiredwind@foxmail.com
** Phone Number:        15256527665
** Creation Time:       2021/07/19
**
** Description:
** This file is used to output special QDebug infomation
**
** If you want to block all QDebug infomation, add this to .pro file:
** -- DEFINES += QT_NO_DEBUG_OUTPUT
**
** Copyright (c)
** 2010 - 2021 All rights reserved
**
****************************************************************************/

#ifndef QDEBUG_HELPER_H
#define QDEBUG_HELPER_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QApplication>


static const char * logCommands[] = {
    "\033[0m",
    "\033[1m",
    "\033[2m",
    "\033[30m",
    "\033[31m",
    "\033[32m",
    "\033[33m",
    "\033[34m",
    "\033[35m",
    "\033[36m",
    "\033[37m",
    "\033[40m",
    "\033[41m",
    "\033[42m",
    "\033[43m",
    "\033[44m",
    "\033[45m",
    "\033[46m",
    "\033[47m",
};

enum LogType {
    Reset = 0,

    Bold,
    Unbold,

    FrontBlack,
    FrontRed,
    FrontGreen,
    FrontYellow,
    FrontBlue,
    FrontPurple,
    FrontCyan,
    FrontWhite,
    BackBlack,
    BackRed,
    BackGreen,
    BackYellow,
    BackBlue,
    BackPurple,
    BackCyan,
    BackWhite,

    TypeCount
};

namespace NARI {
    namespace QDebugHelper
    {
        template <typename T>
        static void ColorfulQDebug(T output, LogType color = BackGreen)
        {
            qDebug() << logCommands[color] << output << "\033[0m";
        }

        // only in terminal, in QtCreator is invalid
        static void ClearScreen()
        {
            system ("clear");
        }

        // output to file
        static void OutputToFile(const QString & info, const QString & path = QCoreApplication::applicationDirPath())
        {
            QFile file(path + "qdebug_output.txt");
            if(file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                file.write(info.toUtf8());
                file.close();
                ColorfulQDebug("The infomation has been written to the file: " + path);
            }
        }
    }
}

#endif // QDEBUG_HELPER_H
