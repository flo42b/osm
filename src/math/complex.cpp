/**
 *  OSM
 *  Copyright (C) 2018  Pavel Smokotnin

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "./complex.h"

const complex complex::i = {0, 1};

float complex::abs() const noexcept
{
    return sqrtf(powf(real, 2) + powf(imag, 2));
}

float complex::absSquared() const noexcept
{
    return real * real + imag * imag;
}
float complex::arg() const noexcept
{
    return atan2f(imag, real);
}
const complex complex::conjugate() const
{
    complex rc;
    rc.real = real;
    rc.imag = -1 * imag;
    return rc;
}

const complex complex::normalize() const
{
    complex rc {real, imag};
    rc /= abs();
    return rc;
}
//TODO: use vector
const complex complex::rotate(const float &a) const
{
    complex rc;
    rc.real = real * cos(a) - imag * sin(a);
    rc.imag = real * sin(a) + imag * cos(a);
    return rc;
}
//TODO: use vector
void complex::polar(const float &phase)
{
    real = cos(phase);
    imag = sin(phase);
}

void complex::polar(const complex &x, const complex &y)
{
    float tanx = x.imag / x.real;
    float tany = y.imag / y.real;

    float cosx, sinx, cosy, siny;

    if (x.real >= 0) {
        cosx = 1 / sqrt(1 + tanx * tanx);
        sinx = tanx * cosx;
    } else {
        cosx = -1 / sqrt(1 + tanx * tanx);
        sinx = tanx * cosx;
    }

    if (y.real >= 0) {
        cosy = 1 / sqrt(1 + tany * tany);
        siny = tany * cosy;
    } else {
        cosy = -1 / sqrt(1 + tany * tany);
        siny = tany * cosy;
    }

    real = cosx * cosy + sinx * siny;
    imag = sinx * cosy - cosx * siny;
}

complex &complex::operator=(const float &r)
{
    real = r;
    imag = 0.0;
    return *this;
}

const complex complex::operator+(const float &r) const
{
    complex rc;
    rc.real = real + r;
    rc.imag = imag;
    return rc;
}
const complex complex::operator+(const complex &c) const
{
    complex rc;
    rc.real = real + c.real;
    rc.imag = imag + c.imag;
    return rc;
}

complex &complex::operator+=(const float &r)
{
    real += r;
    return *this;
}
complex &complex::operator+=(const complex &c)
{
    real += c.real;
    imag += c.imag;
    return *this;
}

const complex complex::operator-(const float &r) const
{
    complex rc;
    rc.real = real - r;
    rc.imag = imag;
    return rc;
}
const complex complex::operator-(const complex &c) const
{
    complex rc;
    rc.real = real - c.real;
    rc.imag = imag - c.imag;
    return rc;
}

complex &complex::operator-=(const float &r)
{
    real -= r;
    return *this;
}
complex &complex::operator-=(const complex &c)
{
    real -= c.real;
    imag -= c.imag;
    return *this;
}

const complex complex::operator/(const float &r) const
{
    complex rc;
    rc.real = real / r;
    rc.imag = imag / r;
    return rc;
}
const complex complex::operator/(const complex &c) const
{
    complex rc;
    float d = c.real * c.real + c.imag * c.imag;

    rc.real = (real * c.real + imag * c.imag) / d;
    rc.imag = (imag * c.real - real * c.imag) / d;

    return rc;
}
complex &complex::operator/=(const float &r)
{
    real /= r;
    imag /= r;
    return *this;
}
complex &complex::operator/=(const complex &c)
{
    float r = real, d = c.real * c.real + c.imag * c.imag;

    real = (real * c.real + imag * c.imag) / d;
    imag = (imag * c.real - r * c.imag) / d;

    return *this;
}

complex complex::operator*(const float &r) const
{
    complex rc;
    rc.real = real * r;
    rc.imag = imag * r;
    return rc;
}
complex complex::operator*(const complex &c) const
{
    complex rc;
    rc.real = real * c.real - imag * c.imag;
    rc.imag = real * c.imag + imag * c.real;
    return rc;
}

complex &complex::operator*=(const float &r)
{
    real *= r;
    imag *= r;
    return *this;
}
complex &complex::operator*=(const complex &c)
{
    float r = real;
    real = real * c.real - imag * c.imag;
    imag = r * c.imag + imag * c.real;
    return *this;
}
bool complex::operator==(const complex &c) const
{
    return (real == c.real && imag == c.imag);
}
bool complex::operator!=(const complex &c) const
{
    return (real != c.real || imag != c.imag);
}

bool complex::operator<(const complex &c) const
{
    return absSquared() < c.absSquared();
}
QDebug operator<<(QDebug dbg, const complex &c)
{
    dbg.nospace() << "Complex value: r:"
                  << c.real << " i:" << c.imag << " ";

    return dbg.maybeSpace();
}
