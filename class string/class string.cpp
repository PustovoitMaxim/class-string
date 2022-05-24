#include <iostream>
#include <sstream>
#include <cstring>
using namespace std;
long Count_size(const char* data) {
    long size = 0;
    const char* start = data;
    while (*start++)
        size++;
    return size;

}
long Count_size(int data) {
    long size = 0;
    while (data > 0) {
        size++;
        data /= 10;
    }
    return size;
}
char* allocate(long size) {
    char* data = new char[size + 1];
    data[size] = '\0';
    return data;
}
char* Copy(const char* p) {
    long size = Count_size(p);
    char* data_tail = allocate(size);
    char* data = data_tail;
    while (*data_tail++ = *p++);
    data_tail--;
    return data;
}
char* Copy(long p) {
    long size = Count_size(p);
    char* data = allocate(size);
    while (p > 0) {
        *data++ = p % 10;
        p /= 10;
    }
    return data;
}
class Sstring {
protected:
    char* data;
    char* data_tail;
    long size;
public:
    pair<char*, long> get_data_for(Sstring& s) {
        return pair<char*, long>(s.data, s.size);
    }
    pair<const char*, long> get_data_for(const Sstring& s) const {
        return pair<const char*, long>(s.data, s.size);
    }
    Sstring() {
        size = 0;
        data = new char[1];
        data[0] = '\0';
        data_tail = data;
    };
    Sstring(const char* p) {
        size = Count_size(p);
        char* res = Copy(p);
        data_tail = res + size;
        data = res;
    };
    Sstring(long p) {
        size = p;
        data = allocate(p);
        data_tail = data + size;
    };
    Sstring(const Sstring& a) {
        data = a.data;
        data_tail = a.data_tail;
        size = a.size;
    };
    Sstring& reverse() {
        Sstring temp(size);
        const char* d = data_tail;
        d--;
        char* t = temp.data;
        while (d >= data) {
            *t++ = *d--;
        }
        return temp;
    }
    Sstring& operator = (const Sstring& a) {
        if (this->data != a.data)
        {
            this->data = a.data;
            this->data_tail = a.data_tail;
            this->size = a.size;
        };
        return  *this;
    };
    Sstring& operator = (const char* p) {
        size = Count_size(p);
        char* res = Copy(p);
        data_tail = res + size;
        data = res;
        return *this;
    };
    friend ostream& operator <<(ostream& os, const Sstring& st);
    Sstring& operator +(const Sstring& st) {
        char* tmp = new char[st.size + size];
        char* start1 = data;
        char* start2 = st.data;
        while (*tmp++ = *start1++);
        while (*tmp++ = *start2++);
        Sstring new_Str(tmp);
        return new_Str;
    };
    Sstring& operator +(char* st) {
        long st_size = Count_size(st);
        char* tmp = new char[st_size  + size];
        char* start1 = data;
        char* start2 = st;
        while (*tmp++ = *start1++);
        while (*tmp++ = *start2++);
        Sstring new_Str(tmp);
        return new_Str;
    };
    friend istream& operator >>(istream& is, Sstring& st);
    friend char* Copy(const char* p);
    friend char* allocate(long size);
    friend bool operator <(const Sstring& a, const Sstring& b);
};
ostream& operator <<(ostream& os, const Sstring& st) {
    os << st.data;
    return os;
};
istream& operator >>(istream& is, Sstring& st) {
    istream::sentry s(is);
    char* m = allocate(100);
    int pointer = 0;
    if (s) while (is.good()) {
        if (pointer == 100){
            string string1 = string(st.data);
            string string2 = string(m);
            string answ = string1 + string2;
            st = answ.c_str();
            m = allocate(100);
            pointer = 0;
        }
        char c = is.get();
        m[pointer++] = c;
        if (isspace(c))break;
    }
    m[pointer] = '\0';
    char* n = Copy(m);
    st.data = n;
    delete [] m;
    return is;
}
bool operator <(const Sstring& a, const Sstring& b) {
    return a.size < b.size;
};
bool operator >(const Sstring & a, const Sstring & b) {
        return not operator<(a, b);
};
class Snumber : public Sstring {
public:
    Snumber() {
        size = 0;
        data = new char[1];
        data[0] = '\0';
        data_tail = data;
    };
    Snumber(const char* p) {
        size = Count_size(p);
        char* res = Copy(p);
        data_tail = res + size;
        data = res;
    };
    Snumber (long p){
        size = p;
        data = allocate(p);
        data_tail = data + size;
    };
    Snumber (const Sstring& p){
        pair <const char*,long>temp = get_data_for(p);
        data = Copy(temp.first);
        size = temp.second;
        data_tail = data + temp.second;
    }
    friend Snumber sum(const Snumber& a, const Snumber& b);
    Snumber& operator = (const Snumber& a) {
        if (this->data != a.data)
        {
            this->data = a.data;
            this->data_tail = a.data_tail;
            this->size = a.size;
        };
        return  *this;
    };
    Snumber& operator = (const Sstring& a) {
        pair<const char*, long> dat = a.get_data_for(a);
        if (data != dat.first)
        {
            data = Copy(dat.first);
            data_tail = data + dat.second;
            size = dat.second;
        };
        return  *this;
    };
    Snumber& operator +(char* st) {
        long st_size = Count_size(st);
        char* tmp = new char[st_size + size];
        char* start1 = data;
        char* start2 = st;
        while (*tmp++ = *start1++);
        while (*tmp++ = *start2++);
        Snumber new_Str(tmp);
        return new_Str;
    };
};
Snumber sum(const Snumber& a, const Snumber& b) {
    Snumber num1 = a;
    Snumber num2 = b;
    if (num1.size < num2.size) {
        Snumber tnum1 = num1;
        Snumber temp = (num2.size);
        while (*tnum1.data != '\0')
            *temp.data++ = *tnum1.data++;
        while (*temp.data != '\0')
            *temp.data++ = '0';
        temp.data = temp.data_tail - temp.size;
        num1 = temp;
        //Sstring t = num1.reverse();
        //num1 = t;
    }
    if (num1.size > num2.size) {
        Snumber tnum2 = num2;
        Snumber temp(num1.size);
        while (*temp.data++ = *tnum2.data++ && *tnum2.data != '\0');
        while (*temp.data != '\0')
            *temp.data++ = '0';
        temp.data = temp.data_tail - temp.size;
        num2 = temp;
        //Sstring t = num2.reverse();
        //num2 = t;
    }
    char temp = 0;
    Snumber answ(max(num1.size, num2.size) + 1);
    while (answ.data != answ.data_tail - 1) {
        char dig1 = *num1.data++ - '0';
        char dig2 = *num2.data++ - '0';
        char sum_res = dig1 + dig2 + temp;
        temp = sum_res / 10;
        *answ.data++ = (char)(sum_res % 10 + '0');
    }
    *answ.data = temp + '0';
    answ.data = answ.data - max(num1.size, num2.size);
    Sstring an = answ.reverse();
    return an;
}
int main()
{
    Sstring a;
    Sstring b;
    b = "1";
    a = "1";
    Snumber num1 = a;
    Snumber num2 = b;
    cout << num1 <<" " << num2 << endl;
    Snumber c = sum(num1,num2);
    cout << c;
}