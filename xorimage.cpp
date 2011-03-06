#include "xorimage.h"

XORImage::XORImage(unsigned int textmaxlength, QImage &i) :
        text_max_length(textmaxlength), image(i)
{
    error = 0;
    number = 0;
}

void XORImage::bitset(unsigned long long v) {
    unsigned long long v2 = v << 32;
    bitset<32> bs1(v >> 32),  // 32 bits on the left side
               bs2(v2 >> 32); // 32 bits on the right side

    // the only way to get bitset of `unsigned long long`
    bitset<64> bs(bs1.to_string() + bs2.to_string());
}

void XORImage::write() {
    if (number == 0) {
        error = 4;
        return;
    }

    QString t = text + QChar(0);
    // we must have |t| divisible by 8
    while (t.length() % 8 != 0)
        t += QChar(0);

    // encrypting happens below
    // we assume `number` is 8bytes-long `unsigned long long` type
    unsigned long long n1=0, n2=0;
    QString t2(t.length(), QChar(0));
    for (int i=0; i<t.length(); i+=8) {
        n1 = t[i].toAscii();
        for (unsigned j=1; j<8; j++) {
            n1 <<= 8;
            n1 += t[i+j].toAscii();
        }
        n1 = n1 ^ number; // now we have 8 bytes of text encrypted

        // getting bytes from the number
        for (unsigned int j=0; j<8; j++) {
            n2 = n1 <<        j  * 8;
            n2 = n2 >> ((8-1)-j) * 8;
            t2[i+j] = QChar(int(n2));
        }
    }
    // now `t2` contains encrypted text

    //for i in t2: this->writeB(i)
    //check for image capacity
    for (int i=0; i<t2.size(); i++) {
        bitset<8> bs(t2[i]);
    }
}

