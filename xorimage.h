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

#ifndef XORIMAGE_H
#define XORIMAGE_H

#include <QImage>
#include <QString>
#include <QChar>
#include <bitset>

class XORImage
{
public:
    XORImage(unsigned int textmaxlength, QImage &i);
    void setImage(QImage &i) { image = i; }
    void setNumber(unsigned long long n) { number = n; }
    void setText(QString t) {
        text = t;
        if (unsigned(text.length()) > text_max_length) error = 1;
    }
    QString getText() { return text; }

    void write();
    void read();
    unsigned int getError() { return error; }
    // 0 - no errors
    // 1 - image bad format
    // 2 - text too long
    // 3 - image too small
    // 4 - number not set

private:
    unsigned int text_max_length;
    unsigned long long number;
    QString text;
    QImage &image;
    int error;

    void writeB(bool, bool, int);
    void readB(bool &, bool &, int);
};

#endif // XORIMAGE_H
