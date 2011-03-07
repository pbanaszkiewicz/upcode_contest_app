#include "xorimage.h"
#include <QColor>

XORImage::XORImage(unsigned int textmaxlength, QImage &i) :
        text_max_length(textmaxlength), image(i)
{
    error = 0;
    number = 0;
}

void XORImage::writeB(bool t1, bool t2, int px) {
    // calculate pixel position
    int p_x = px % image.width(),
        p_y = px / image.width();

    QRgb colors = image.pixel(p_x, p_y);
    int green = qGreen(colors), blue = qBlue(colors);
    if (t1 && green % 2 != 1) green++;
    else if (!t1 && green % 2 != 0) green--;

    if (t2 && blue % 2 != 1) blue++;
    else if (!t2 && blue % 2 != 0) blue--;

    image.setPixel(p_x, p_y, qRgb(qRed(colors), green, blue));
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
    for (int i=0, px=0; i<t2.size(); i++) {
        std::bitset<8> bs((int) t2[i].toAscii());
        for (int j=0; j<8; j+=2) {
            writeB(bs.test(j), bs.test(j+1), px);
            px++;
        }
    }
}

