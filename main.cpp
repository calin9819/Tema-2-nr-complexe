#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>
using namespace std;

ifstream f("in.txt");
ofstream g("out.txt");

class Complex {
private:
    double real, imag;

public:

    Complex() {
        real = 0;
        imag = 0;
    }

    Complex(double r, double i) {
        real = r;
        imag = i;
    }

    Complex(const Complex &c) {
        this->real = c.real;
        this->imag = c.imag;
    }

    ~Complex() {

    }
    friend class Vector_De_Complex;
    friend ostream & operator << (ostream &out, const Complex &c);
    friend istream & operator >> (istream &in,  Complex &c);
    Complex operator+(const Complex&) const;
    Complex operator*(const Complex&) const;
    bool operator< (const Complex&) const;
    bool operator== (const Complex&) const;
    bool operator!= (const Complex&) const;
    Complex &operator= (const Complex&);
    double modul() {
        return sqrt(real * real + imag * imag);
    }

    void adun(Complex c) {
        real += c.real;
        imag += c.imag;
    }

    void impart(Complex c) {
        Complex d((this->real * c.real - this->imag * c.imag) / c.modul(),
                  (c.real * this->imag - this->real * c.imag) / c.modul());
        real = d.real;
        imag = d.imag;
    }

};

class Vector_De_Complexe {
public:
    int lungime;
    double *module;
    Complex *v;


    Vector_De_Complexe() {
        v = NULL;
        module = NULL;
        lungime = 0;
    }

    Vector_De_Complexe(const Vector_De_Complexe& s) {
        lungime = s.lungime;
        v = new Complex[lungime + 1];
        for (int i = 1; i <= lungime; i++) {
            v[i] = s.v[i];
        }
    }

    ~Vector_De_Complexe() {
        if (lungime != 0) {
            delete []v;
            delete []module;
        }
    }

    Complex& operator[] (int x) {
        return v[x];
    }

    friend ostream & operator << (ostream &out, const Vector_De_Complexe &c);
    friend istream & operator >> (istream &in,  Vector_De_Complexe &c);
    Complex operator* (const Vector_De_Complexe& c) const;
    Vector_De_Complexe operator= (const Vector_De_Complexe& c);
    Vector_De_Complexe operator+ (const Vector_De_Complexe&) const;

    void determinareModule() {
        module = new double[lungime + 1];
        for (int i = 1; i <= lungime; i++)
            module[i] = v[i].modul();
    }

    void sortareDupaModule() {
        for (int i = 1; i < lungime; i++)
            for (int j = i + 1; j <= lungime; j++)
                if (module[i] - module[j] > 0) {
                    double auxD = module[i];
                    module[i] = module[j];
                    module[j] = auxD;
                    Complex aux = v[i];
                    v[i] = v[j];
                    v[j] = aux;
                }
    }


    Complex sumaElemente() {
        Complex suma;
        for (int i = 1; i <= lungime; i++)
            suma = suma + v[i];
        return suma;
    }
};

ostream & operator << (ostream &out, const Complex &c) {
    out << c.real;
    out << '+' << c.imag << 'i';
    return out;
}

istream & operator >> (istream &in,  Complex &c) {
    in >> c.real;
    in >> c.imag;
    return in;
}

ostream & operator << (ostream &out, const Vector_De_Complexe &c) {
    for (int i = 1; i <= c.lungime; i++)
        out << c.v[i] << ' ';
    return out;
}

istream & operator >> (istream &in,  Vector_De_Complexe &c) {
    int lungime;
    in >> lungime;
    c.v = new Complex[lungime + 1];
    c.lungime = lungime;
    for (int i = 1; i <= lungime; i++)
        in >> c.v[i];
    return in;
}

Complex &Complex::operator=(const Complex& c)  {
    this->real = c.real;
    this->imag = c.imag;
    return *this;
}

Vector_De_Complexe Vector_De_Complexe::operator=(const Vector_De_Complexe& s) {
    if (v != NULL) delete []v;
    lungime = s.lungime;
    v = new Complex[lungime + 1];
    for (int i = 1; i <= s.lungime; i++)
        v[i] = s.v[i];
    return *this;
}

Complex Complex::operator+ (const Complex& c) const {
    Complex z;
    z.real = (this->real + c.real);
    z.imag = (this->imag + c.imag);
    return z;
}

Complex Complex::operator* (const Complex& c) const {
    Complex z;
    z.real = (this->real * c.real - this->imag * c.imag);
    z.imag = (this->imag * c.real + c.imag * this->real);
    return z;
}

bool Complex::operator< (const Complex& c) const {
    if (this->real < c.real) return 1;
    if (this->real == c.real)
        if (this->imag < c.imag) return 1;
    return 0;
}

bool Complex::operator== (const Complex& c) const {
    if (this->real == c.real && this->imag == c.imag) return 1;
    return 0;
}

bool Complex::operator!= (const Complex& c) const {
    if (this->real != c.real) return 1;
    if (this->imag != c.imag) return 1;
    return 0;
}

Complex Vector_De_Complexe::operator* (const Vector_De_Complexe& c) const {
    Complex z;
    for (int i = 1; i <= lungime; i++)
        z = z + (v[i] * c.v[i]);
    return z;
}

Vector_De_Complexe Vector_De_Complexe::operator+(const Vector_De_Complexe& c) const {
    int lg = lungime + c.lungime;
    Vector_De_Complexe rezultat;
    rezultat.v = new Complex[lg+2];
    rezultat.lungime = lg;
    for (int i = 1; i <= lungime; i++)
        rezultat.v[i] = v[i];
    for (int i = 1; i <= c.lungime; i++)
        rezultat.v[lungime + i] = c.v[i];
    return rezultat;
}

int main() {


    /*int n;
    Complex sir[100];

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> sir[i];
    for (int i = 1; i <= n; i++)
        cout << sir[i] << ' ';

    f >> n;
    for (int i = 1; i <= n; i++)
        f >> sir[i];
    for (int i = 1; i <= n; i++)
        g << sir[i] << ' ';

    */
    Vector_De_Complexe s;
    cin >> s;
    cout << s << '\n';

    s.determinareModule();
    for (int i = 1; i <= s.lungime; i++)
        cout << s.module[i] << ' ';

    cout << '\n';
    Complex c = s.sumaElemente();
    cout << c << '\n';

    Vector_De_Complexe copie;
    copie = s;
    cout << copie << '\n';

    copie.determinareModule();
    copie.sortareDupaModule();
    cout << copie << '\n';

    Complex produs = copie * s;
    cout << produs << '\n';

    copie = copie + s;
    cout << copie;
    return 0;
}
