/*
* This file is part of Stecrypt.
*
* Stecrypt is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Stecrypt is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with Stecrypt.  If not, see <http://www.gnu.org/licenses/>.
*/

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

void XORImage::readB(bool &t1, bool &t2, int px) {
    // calculate pixel position
    int p_x = px % image.width(),
        p_y = px / image.width();

    QRgb colors = image.pixel(p_x, p_y);
    int green = qGreen(colors), blue = qBlue(colors);
    t1 = green % 2 == 1;
    t2 = blue  % 2 == 1;
}

void XORImage::write() {
    if (number == 0) {
        error = 4;
        return;
    }

    QString t = text + QChar(1);
    // we must have |t| divisible by 8
    while (t.length() % 8 != 0)
        t += QChar(0);

    // encrypting happens below
    // we assume `number` is 8bytes-long `unsigned long long` type
    unsigned long long n1=0, n2=0;
    QString t2(t.length(), QChar(1));
    for (int i=0; i<t.length(); i+=8) {
        n1 = (unsigned long long)t[i].toAscii();
        for (unsigned j=1; j<8; j++) {
            n1 <<= 8LL;
            n1 += (unsigned long long)t[i+j].toAscii();
        }
        n1 = n1 ^ number; // now we have 8 bytes of text encrypted

        // getting bytes from the number
        for (unsigned int j=0; j<8; j++) {
            n2 = n1 <<        j  * 8;
            n2 = n2 >> 7 * 8;
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

void XORImage::read() {
    if (number == 0) {
        error = 4;
        return;
    }
    text.clear();

    int px=0, size=image.width() * image.height();
    bool running = true;
    while (px < size  &&  running) {
        unsigned long long n1=0, n2=0;

        // it takes 32 pixels to write 8 bytes of text
        // because 8bytes = 64 bits and there are 2 bits per pixel
        // so 32 pixels
        // whereas 1 letter of text (==1B) is 4 pixels
        for (int n=0; n<8; n++) {

            // below is loop which reads one byte
            bool t1, t2;
            uchar b;
            std::bitset<8> bs(0);
            for (int i=0; i<4; i++, px++) {
                readB(t1, t2, px);
                bs.set(i*2, t1);
                bs.set(i*2+1, t2);
            }
            b = bs.to_ulong();
            n1 <<= 8;
            n1 += b;
        }

        n1 = n1 ^ number;
        // getting bytes from the number
        for (unsigned int j=0; j<8; j++) {
            n2 = n1 <<        j  * 8;
            n2 = n2 >> 7 * 8;
            if (n2<15) {
                running = false;
                break;
            }

            text.append(QChar(int(n2)));
        }
    }
}
