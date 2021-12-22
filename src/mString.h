/*
 РЕЗКАЯ КАК ПОНОС И ЛЁГКАЯ КАК ПЁРЫШКО ЗАМЕНА STRING
 Документация:
 GitHub: https://github.com/GyverLibs/mString
 Возможности:
 - Практически полный аналог String, но статический
 - Есть несколько встроенных функций парсинга строк

 AlexGyver, alex@alexgyver.ru
 https://alexgyver.ru/
 MIT License

 Версии:
 v1.0 - релиз
 */

#ifndef mString_h
#define mString_h

#include <string>
#include <string.h>
#include "f28004x_device.h"         // f28004x Headerfile Include File
using namespace std;

#define DEC 10
#define HEX 16

char* mUtoa(Uint32 value, char *buffer, bool clear);
char* mLtoa(int32 value, char *buffer, bool clear);
char* mFtoa(double value, Uint16 decimals, char *buffer);

template<Uint16 _MS_SIZE>
class mString
{
public:
    char buf[_MS_SIZE];

    mString()
    {
        clear();
    }

    Uint16 length()
    {
        return strlen(buf);
    }

    void clear()
    {
        buf[0] = '\0';
    }

    // add
    mString& add(const char c)
    {
        int len = length();
        if (len + 1 >= _MS_SIZE)
            return *this;
        buf[len++] = c;
        buf[len] = '\0';
        return *this;
    }
    mString& add(const char *data)
    {
        if (length() + strlen(data) >= _MS_SIZE)
            return *this;
        strcat(buf, data);
        return *this;
    }
    mString& add(Uint16 value)
    {
        return add((int32) value);
    }
    mString& add(int32 value)
    {
        char vBuf[11];
        ltoa(value, vBuf, DEC);
        return add(vBuf);
    }
    mString& add(int16 value)
    {
        return add((int32) value);
    }
    mString& add(double value, Uint16 dec = 2)
    {
        char vBuf[20];
        mFtoa(value, dec, vBuf);
        return add(vBuf);
    }
    mString& add(mString data)
    {
        return add(data.buf);
    }
    mString& add(string data)
    {
        return add(data.c_str());
    }

    // add +=
    mString& operator +=(const char c)
    {
        return add(c);
    }
    mString& operator +=(const char *data)
    {
        return add(data);
    }
    mString& operator +=(Uint32 value)
    {
        return add(value);
    }
    mString& operator +=(int32 value)
    {
        return add(value);
    }
    mString& operator +=(Uint16 value)
    {
        return add(value);
    }
    mString& operator +=(int16 value)
    {
        return add(value);
    }
    mString& operator +=(double value)
    {
        return add(value);
    }
    mString& operator +=(mString data)
    {
        return add(data.buf);
    }
    mString& operator +=(string data)
    {
        return add(data);
    }

    // +
    mString operator +(const char c)
    {
        return (*this).add(c);
    }
    mString operator +(const char *data)
    {
        return (*this).add(data);
    }
    mString operator +(Uint32 value)
    {
        return (*this).add(value);
    }
    mString operator +(int32 value)
    {
        return (*this).add(value);
    }
    mString operator +(Uint16 value)
    {
        return (*this).add(value);
    }
    mString operator +(int16 value)
    {
        return (*this).add(value);
    }
    mString operator +(double value)
    {
        return (*this).add(value);
    }
    mString operator +(mString data)
    {
        return (*this).add(data);
    }
    mString operator +(string data)
    {
        return (*this).add(data);
    }

    // assign
    mString& operator =(const char c)
    {
        clear();
        return add(c);
    }
    mString& operator =(const char *data)
    {
        clear();
        return add(data);
    }
    mString& operator =(Uint32 value)
    {
        clear();
        return add(value);
    }
    mString& operator =(int32 value)
    {
        clear();
        return add(value);
    }
    mString& operator =(Uint16 value)
    {
        clear();
        return add(value);
    }
    mString& operator =(int16 value)
    {
        clear();
        return add(value);
    }
    mString& operator =(double value)
    {
        clear();
        return add(value);
    }
    mString& operator =(string data)
    {
        clear();
        return add(data);
    }

    // compare
    bool operator ==(const char c)
    {
        return (buf[0] == c && buf[1] == 0);
    }
    bool operator ==(const char *data)
    {
        return !strcmp(buf, data);
    }
    bool operator ==(Uint32 value)
    {
        char valBuf[11];
        return !strcmp(buf, utoa(value, valBuf, DEC));
    }
    bool operator ==(Uint16 value)
    {
        char valBuf[6];
        return !strcmp(buf, utoa(value, valBuf, DEC));
    }
    bool operator ==(int32 value)
    {
        char valBuf[11];
        return !strcmp(buf, ltoa(value, valBuf, DEC));
    }
    bool operator ==(int16 value)
    {
        char valBuf[6];
        return !strcmp(buf, ltoa(value, valBuf, DEC));
    }
    bool operator ==(float value)
    {
        char valBuf[20];
        return !strcmp(buf, mFtoa(value, 2, valBuf));
    }
    bool operator ==(mString data)
    {
        return !strcmp(buf, data.buf);
    }
    bool operator ==(string data)
    {
        return !strcmp(buf, data.c_str());
    }

    // convert & parse
    char operator [](Uint16 index) const
    {
        return buf[index];
    }
    char& operator [](Uint16 index)
    {
        return buf[index];
    }
    char charAt(Uint16 index)
    {
        return buf[index];
    }
    void setCharAt(Uint16 index, char c)
    {
        buf[index] = c;
    }
    int32 toInt(Uint16 from = 0)
    {
        return atol(buf + from);
    }
    Uint32 toUint(Uint16 from = 0)
    {
        return atol(buf + from);
    }
    float toFloat(Uint16 from = 0)
    {
        return atof(buf + from);
    }
    const char* c_str()
    {
        return buf;
    }

    // ...
    bool startsWith(const char *data, Uint16 offset = 0)
    {
        return strlen(data) == strspn(buf + offset, data);
    }

    // get substring (from to) to arr
    void substring(Uint16 from, Uint16 to, char *arr)
    {
        char backup = buf[++to];
        buf[to] = '\0';
        strcpy(arr, buf + from);
        buf[to] = backup;
    }

    // split by div (replace div to \0)
    int split(char **ptrs, char div = ',')
    {
        int i = 0, j = 1;
        ptrs[0] = buf;
        while (buf[i])
        {
            if (buf[i] == div)
            {
                buf[i] = '\0';
                ptrs[j++] = buf + i + 1;
            }
            i++;
        }
        return j;
    }

    // remove amount chars from the end
    void truncate(Uint16 amount)
    {
        Uint16 len = length();
        if (amount >= len)
            clear();
        else
            buf[len - amount] = '\0';
    }

    // same to String erase
    void erase(Uint16 index, Uint16 count)
    {
        Uint16 len = length();
        if (index >= len)
            return;
        if (count <= 0)
            return;
        if (count > len - index)
        {
            count = len - index;
        }
        char *writeTo = buf + index;
        len = len - count;
        strncpy(writeTo, buf + index + count, len - index);
        buf[len] = 0;
    }

    void toLowerCase()
    {
        if (!length())
            return;
        for (char *p = buf; *p; p++)
            *p = tolower(*p);
    }

    void toUpperCase()
    {
        if (!length())
            return;
        for (char *p = buf; *p; p++)
            *p = toupper(*p);
    }

    int indexOf(char ch, Uint16 fromIndex = 0)
    {
        if (fromIndex >= length())
            return -1;
        const char *temp = strchr(buf + fromIndex, ch);
        return (temp == NULL) ? -1 : (temp - buf);
    }

    int indexOf(char *ch, Uint16 fromIndex = 0)
    {
        if (fromIndex >= length())
            return -1;
        const char *temp = strstr(buf + fromIndex, ch);
        return (temp == NULL) ? -1 : (temp - buf);
    }

    int parseBytes(char *data, int len, char div = ',', char ter = '\0')
    {
        int b = 0, c = 0;
        data[b] = 0;
        while (true)
        {
            if (buf[c] == div)
            {
                b++;
                c++;
                if (b == len)
                    return b;
                data[b] = 0;
                continue;
            }
            if (buf[c] == ter || b == len)
                return b + 1;
            data[b] *= 10;
            data[b] += buf[c] - '0';
            c++;
        }
    }
    int parseInts(int *data, int len, char div = ',', char ter = '\0')
    {
        int b = 0, c = 0;
        data[b] = 0;
        while (true)
        {
            if (buf[c] == div)
            {
                b++;
                c++;
                if (b == len)
                    return b;
                data[b] = 0;
                continue;
            }
            if (buf[c] == ter || b == len)
                return b + 1;
            data[b] *= 10;
            data[b] += buf[c] - '0';
            c++;
        }
    }
    //cast operators
    operator const char*()
    { // теперь mString автоматом переконвертируется в cstring (const char *) если будет нужно
        return this->c_str();
    }
    /*
     Пример:
     void printString(const char * cstr){cout<<cstr;}
     mString<16> mStr = "Hello";

     Было:
     printString(mStr.c_str());
     Стало:
     printString(mStr);

     */

    operator bool()
    {
        return (this->length());
    }
    /* Теперь строка может возвращать bool
     Пример:
     Было:
     if(str.length())
     {
     doSomeMagic();
     }

     Стало:
     if(str)
     {
     doSomeMagic();
     }
     */
private:
};
#endif
