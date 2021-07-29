/****************************************************************************
**
** Author:              wangjun
** E-Mail:              tiredwind@foxmail.com
** Phone Number:        15256527665
** Creation Time:       2021/07/29
**
** Description:
**
** At namespace scope, static gives a name internal linkage, meaning that it
** is only accessible within the translation unit that contains the
** definition. Without static, it has external linkage, and is accessible in
** any translation unit.
**
** So you'd use static (or, alternatively, an unnamed namespace) when writing
** a function that's only intended for use within this unit; the internal
** linkage means that other units can define different functions with the
** same name without causing naming conflicts.
**
** Non-static functions (and global names in general) are better declared in
** a header, to make sure that every translation unit that uses them gets
** the same declaration.
**
****************************************************************************/


#include <QTextCodec>

namespace NARI {
    namespace StringHelper {

        // determine whether the string is utf-8 encoding
        static bool IsTextUTF8(const std::string & str)
        {
            char nBytes=0;
            unsigned char chr;
            bool bAllAscii = true;

            for(int i = 0; i < str.length(); i++)
            {
                chr = str[i];

                if( (chr&0x80) != 0 )
                    bAllAscii= false;

                if(nBytes==0)
                {
                    if(chr>=0x80)
                    {
                        if(chr>=0xFC&&chr<=0xFD)   nBytes = 6;
                        else if(chr>=0xF8)         nBytes = 5;
                        else if(chr>=0xF0)         nBytes = 4;
                        else if(chr>=0xE0)         nBytes = 3;
                        else if(chr>=0xC0)         nBytes = 2;
                        else
                        {
                            return false;
                        }
                        nBytes--;
                    }
                }
                else
                {
                    if( (chr&0xC0) != 0x80 )
                    {
                        return false;
                    }
                    nBytes--;
                }
            }

            if( nBytes > 0 )
                return false;

            if( bAllAscii )
                return false;

            return true;
        }


        // utf-8 to gb18030
        static QByteArray Utf82Gbk(const char * str)
        {
            QTextCodec * utf8 = QTextCodec::codecForName("utf8");
            QTextCodec * gbk = QTextCodec::codecForName("gb18030");
            QString tmp = utf8->toUnicode(str);

            return gbk->fromUnicode(tmp);
        }

        // gb18030 to utf-8
        static QByteArray Gbk2Utf8(const char * str)
        {
            QTextCodec * utf8 = QTextCodec::codecForName("utf8");
            QTextCodec * gbk = QTextCodec::codecForName("gb18030");
            QString tmp = gbk->toUnicode(str);

            return utf8->fromUnicode(tmp);
        }


        // std::string to const * char
        static std::string Char2String(const char * str)
        {
            std::string s(str);
            return s;
        }

        // const char * to std::string
        static const char * String2Char(const std::string & str)
        {
            const char* c_s = str.c_str();
            return c_s;
        }

        // char * to QString
        static QString Char2QString(const char * str)
        {
            QString string = QString(QLatin1String(str));
            return string;
        }

        // QString to char *
        static char * QString2Char(const QString & str)
        {
            char *s;
            QByteArray ba = str.toLatin1();
            s = ba.data();
            return s;
        }



        // remove all spaces/whitespace in QString
        static QString RemoveSpace(const QString & str)
        {
            auto string = str.simplified().replace(" ", "");
            return string;
        }

        // std::string segmentation
        static std::vector<std::string> StringSplit(const std::string & str, std::string pattern)
        {
            std::vector<std::string> vec_split;
            if ("" == str)
                return vec_split;
            std::string strs = str + pattern;
            int pos = strs.find(pattern);
            while (pos != std::string::npos)
            {
                std::string x = strs.substr(0,pos);
                vec_split.push_back(x);
                strs = strs.substr(pos + pattern.size(), strs.size());
                pos = strs.find(pattern);
            }

            return vec_split;
        }

        // remove the specified character from the string
        static void RemoveSpecifiedChar(std::string & str, char r_str)
        {
            str.erase(std::remove(str.begin(), str.end(), r_str), str.end());
        }

        // remove the suffix of the file name
        static std::string RemoveFileSuffix(const std::string & str)      // "test.jpg" -> "test"
        {
            auto name = str.substr(0, str.rfind("."));
            retuen name;
        }

        // get suffix name of file name
        static std::string GetSuffixName(const std::string & str)        // "test.jpg" -> "jpg"
        {
            auto suffix = str.substr(test_text.find(".") + 1);
            return suffix;
        }
    }
}
