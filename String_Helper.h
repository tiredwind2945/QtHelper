namespace NARI {
    namespace StringHelper {

        // determine whether the string is utf-8 encoding
        static bool IsTextUTF8(const std::string & str)
        {
            char nBytes=0;  // UFT8����1-6���ֽڱ���,ASCII��һ���ֽ�
            unsigned char chr;
            bool bAllAscii = true; //���ȫ������ASCII, ˵������UTF-8

            for(int i = 0; i < str.length(); i++)
            {
                chr = str[i];

                // �ж��Ƿ�ASCII����,�������,˵���п�����UTF-8,ASCII��7λ����,
                // ����һ���ֽڴ�,���λ���Ϊ0,o0xxxxxxx
                if( (chr&0x80) != 0 )
                    bAllAscii= false;

                if(nBytes==0) // �������ASCII��,Ӧ���Ƕ��ֽڷ�,�����ֽ���
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
                else // ���ֽڷ��ķ����ֽ�,ӦΪ 10xxxxxx
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
