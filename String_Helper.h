namespace NARI {
    namespace StringHelper {

        // determine whether the string is utf-8 encoding
        static bool IsTextUTF8(const std::string & str)
        {
            char nBytes=0;  // UFT8可用1-6个字节编码,ASCII用一个字节
            unsigned char chr;
            bool bAllAscii = true; //如果全部都是ASCII, 说明不是UTF-8

            for(int i = 0; i < str.length(); i++)
            {
                chr = str[i];

                // 判断是否ASCII编码,如果不是,说明有可能是UTF-8,ASCII用7位编码,
                // 但用一个字节存,最高位标记为0,o0xxxxxxx
                if( (chr&0x80) != 0 )
                    bAllAscii= false;

                if(nBytes==0) // 如果不是ASCII码,应该是多字节符,计算字节数
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
                else // 多字节符的非首字节,应为 10xxxxxx
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
        static QByteArray UTF82GBK(const char * str)
        {
            QTextCodec * utf8 = QTextCodec::codecForName("utf8");
            QTextCodec * gbk = QTextCodec::codecForName("gb18030");
            QString tmp = utf8->toUnicode(str);

            return gbk->fromUnicode(tmp);
        }

        // gb18030 to utf-8
        static QByteArray GBK2UTF8(const char * str)
        {
            QTextCodec * utf8 = QTextCodec::codecForName("utf8");
            QTextCodec * gbk = QTextCodec::codecForName("gb18030");
            QString tmp = gbk->toUnicode(str);

            return utf8->fromUnicode(tmp);
        }
    }
}
