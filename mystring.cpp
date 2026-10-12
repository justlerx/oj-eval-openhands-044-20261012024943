#include <string>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class mystring
{
private:
    char *ch = nullptr;
    int len = 0;

public:
    mystring()
    {
        ch = nullptr;
        len = 0;
    }
    
    mystring(int _len, char c)
    {
        len = _len;
        ch = new char[len];
        for (int i = 0; i < len; i++) {
            ch[i] = c;
        }
    }
    
    mystring(string &c)
    {
        len = c.length();
        ch = new char[len];
        for (int i = 0; i < len; i++) {
            ch[i] = c[i];
        }
    }
    
    ~mystring()
    {
        delete[] ch;
        ch = nullptr;
        len = 0;
    }
    
    char operator[](int x) const
    {
        if (x < 0 || x >= len) {
            return '\0';
        }
        return ch[x];
    }
    
    bool operator<(const mystring &other) const
    {
        int min_len = (len < other.len) ? len : other.len;
        for (int i = 0; i < min_len; i++) {
            if (ch[i] < other.ch[i]) return true;
            if (ch[i] > other.ch[i]) return false;
        }
        return len < other.len;
    }
    
    bool operator==(const mystring &other) const
    {
        if (len != other.len) return false;
        for (int i = 0; i < len; i++) {
            if (ch[i] != other.ch[i]) return false;
        }
        return true;
    }
    
    mystring& operator+=(const mystring &other)
    {
        char *new_ch = new char[len + other.len];
        for (int i = 0; i < len; i++) {
            new_ch[i] = ch[i];
        }
        for (int i = 0; i < other.len; i++) {
            new_ch[len + i] = other.ch[i];
        }
        delete[] ch;
        ch = new_ch;
        len += other.len;
        return *this;
    }
    
    mystring operator+(const mystring &other) const
    {
        mystring result = *this;
        result += other;
        return result;
    }
    
    void out() const
    {
        for (int i = 0; i < len; i++) {
            cout << ch[i];
        }
    }
    
    int get_len() const
    {
        return len;
    }
    
    mystring substr(int pos, int n) const
    {
        if (pos >= len) {
            return mystring();
        }
        int substr_len = (pos + n <= len) ? n : len - pos;
        mystring result(substr_len, ' ');
        for (int i = 0; i < substr_len; i++) {
            result.ch[i] = ch[pos + i];
        }
        return result;
    }
    
    mystring& insert(int pos, const mystring &str)
    {
        if (pos > len) pos = len;
        if (pos < 0) pos = 0;
        
        int new_len = len + str.len;
        char *new_ch = new char[new_len];
        
        // Copy characters before pos
        for (int i = 0; i < pos; i++) {
            new_ch[i] = ch[i];
        }
        
        // Copy str characters
        for (int i = 0; i < str.len; i++) {
            new_ch[pos + i] = str.ch[i];
        }
        
        // Copy characters after pos
        for (int i = pos; i < len; i++) {
            new_ch[str.len + i] = ch[i];
        }
        
        delete[] ch;
        ch = new_ch;
        len = new_len;
        
        return *this;
    }
    
    mystring& erase(int pos, int n)
    {
        if (pos >= len) return *this;
        if (pos < 0) pos = 0;
        
        int end_pos = (pos + n < len) ? pos + n : len;
        int erase_len = end_pos - pos;
        
        if (erase_len <= 0) return *this;
        
        int new_len = len - erase_len;
        char *new_ch = new char[new_len];
        
        // Copy characters before pos
        for (int i = 0; i < pos; i++) {
            new_ch[i] = ch[i];
        }
        
        // Copy characters after the erased portion
        for (int i = end_pos; i < len; i++) {
            new_ch[pos + (i - end_pos)] = ch[i];
        }
        
        delete[] ch;
        ch = new_ch;
        len = new_len;
        
        return *this;
    }
};

string str_in1, str_in2;
int n, id;
int main()
{
    cin >> id;
    if (id == 1)
    {
        mystring str1(100,'a');
        str1.out(); puts("");
        // cout << str1 << endl;
    }
    else if (id == 2)
    {
        cin >> str_in1;
        mystring str2 = str_in1;
        cin >> n;
        for (int i = 0, x; i < n; ++ i)
        {
            cin >> x;
            cout << str2[x] << endl;
        }
    }
    else if (id == 3)
    {
        cin >> str_in1 >> str_in2;
        mystring str2 = str_in1;
        mystring str3 = str_in2;
        cout << (int)(str2 < str3) << endl;
    }
    else if (id == 4)
    {
        cin >> str_in1 >> str_in2;
        mystring str2 = str_in1;
        mystring str3 = str_in2;
        str2.ADD(str3);
        str2.out(); puts("");
        // cout << str2 << endl;
    }
    else
    {
        cin >> str_in1 >> str_in2;
        mystring str2 = str_in1;
        mystring str3 = str_in2;
        cin >> n;
        for (int i = 0, x; i < n; ++ i)
        {
            cin >> x;
            cout << str3[x] << endl;
        }
        cout << str2.get_len() << " " << str3.get_len() << endl;
        cout << (int)(str2 < str3) << endl;
        str2.ADD(str3);
        str2.out(); puts("");
        // cout << str2 << endl;
        cout << str2.get_len() << endl;
    }
    return 0;
}