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
    pair<const char*, long> get_data_for() const {
        return pair<const char*, long>(data, size);
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
    Sstring reverse() {
        Sstring temp(size);
        const char* d = data_tail;
        d--;
        char* t = temp.data;
        while (d >= data) {
            *t++ = *d--;
        }
        return temp;
    }
    Sstring& trim() {
        while (*data == '0') {
            data++;
            size--;
        }
        return *this;
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
        char* tmp = new char[st_size + size];
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
        if (pointer == 100) {
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
    delete[] m;
    return is;
}
bool operator <(const Sstring& a, const Sstring& b) {
    return a.size < b.size;
};
bool operator >(const Sstring& a, const Sstring& b) {
    return not operator<(a, b);
};
class Snumber : public Sstring {
protected:
    char sight;
public:
    Snumber() {
        size = 0;
        sight = 1;
        data = new char[1];
        data[0] = '\0';
        data_tail = data;
    };
    Snumber(const char* p) {
        size = Count_size(p);
        char* res = Copy(p);
        data_tail = res + size;
        data = res;
        if (*data == '-') {
            sight = -1;
            data++;
            size--;
        }
        else
            sight = 1;
    };
    Snumber(long p) {
        size = p;
        data = allocate(p);
        data_tail = data + size;
        sight = 0;
    };
    Snumber(const Sstring& p) {
        pair <const char*, long>temp = p.get_data_for();
        data = Copy(temp.first);
        size = temp.second;
        data_tail = data + temp.second;
        if (*data == '-') {
            sight = -1;
            data++;
            size--;
        }
        else
            sight = 1;
    }
    Snumber& trim(Snumber& p) {
        if (*p.data == '0')
            p.data++;
        return p;
    }
    bool operator < (Snumber& p) const {
        Snumber num1 = *this;
        Snumber num2 = p;
        if (*num1.data == '-')
            num1.data++;
        if (*num2.data == '-')
            num2.data++;
        while (*num1.data != '\0' && *num2.data != '\0')
            if (*num2.data < *num1.data)
                return false;
            else
                return true;
        if (*num1.data == '\0')
            return true;
        else
            return false;
    };
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
        pair<const char*, long> dat = a.get_data_for();
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
    friend ostream& operator<<(ostream& os, const Snumber& st);
    Snumber operator +(const Snumber& a) {
        Snumber num1 = *this;
        Snumber num2 = a;
        if (num1.size < num2.size) {
            Snumber tnum1 = num1;
            Snumber temp = (num2.size);
            for (int i = 0; i < num2.size - tnum1.size; i++) {
                *temp.data++ = '0';
            }
            while (*tnum1.data != '\0')
                *temp.data++ = *tnum1.data++;
            temp.data = temp.data_tail - temp.size;
            num1 = temp;
        }
        if (num1.size > num2.size) {
            Snumber tnum2 = num2;
            Snumber temp(num1.size);
            for (int i = 0; i < num1.size - tnum2.size; i++) {
                *temp.data++ = '0';
            }
            while (*tnum2.data != '\0')
                *temp.data++ = *tnum2.data++;
            temp.data = temp.data_tail - temp.size;
            num2 = temp;
        }
        char temp = 0;
        char sg1 = num1.sight;
        char sg2 = num2.sight;
        char an_s;
        if (sg1 != sg2) {
            if (num1 < num2) {
                an_s = sg2;
            }
            else
                an_s = sg1;
        }
        else
            an_s = sg1;
        num1 = num1.reverse();
        num2 = num2.reverse();
        Snumber answ(max(num1.size, num2.size) + 1);
        while (answ.data != answ.data_tail - 1){
            char dig1 = (*num1.data++ - '0') * num1.sight;
            char dig2 = (*num2.data++ - '0') * num2.sight;
            char sum_res = abs(max(dig1,dig2) + min(dig1,dig2) + temp*an_s);
            temp = sum_res / 10;
            if (sum_res < 0) {
                sum_res = 10 - sum_res;
            }
            *answ.data++ = (char)(sum_res % 10 + '0');
        }
        *answ.data = temp + '0';
        answ.data = answ.data - max(num1.size, num2.size);
        Sstring an = answ.reverse();
        an = an.trim();
        Snumber ans = an;
        ans.sight = an_s;
        return ans;
    }
};
ostream& operator <<(ostream& os, const Snumber& st) {
    if (st.sight == -1)
        os << '-';
        os << st.data;
    return os;
};
int main()
{
    Sstring a;
    Sstring b;
    a = "5";
    b = "16";
    Snumber num1 = a;
    Snumber num2 = b;
    while (true) {
        Snumber c = num1 + num2;
        cout << c << endl;
        cin >> num1 >> num2;
    }
}