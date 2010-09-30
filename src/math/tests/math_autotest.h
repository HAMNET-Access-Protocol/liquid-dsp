/*
 * Copyright (c) 2007, 2009 Joseph Gaeddert
 * Copyright (c) 2007, 2009 Virginia Polytechnic Institute & State University
 *
 * This file is part of liquid.
 *
 * liquid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * liquid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with liquid.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __MATH_AUTOTEST_H__
#define __MATH_AUTOTEST_H__

#include "autotest/autotest.h"
#include "liquid.h"

// 
// AUTOTEST: Gamma
//
void xautotest_gamma()
{
    float tol = 1e-3f;
    CONTEND_DELTA(liquid_gammaf(0.1f), 9.51350769866873f, tol);
    CONTEND_DELTA(liquid_gammaf(0.2f), 4.59084371199880f, tol);
    CONTEND_DELTA(liquid_gammaf(0.5f), 1.77245385090552f, tol);
    CONTEND_DELTA(liquid_gammaf(1.5f), 0.886226925452758f, tol);
    CONTEND_DELTA(liquid_gammaf(2.5f), 1.329340388179140f, tol);
}

// 
// AUTOTEST: Factorial
//
void autotest_factorial()
{
    float tol = 1e-3f;
    CONTEND_DELTA(liquid_factorialf(0), 1,   tol);
    CONTEND_DELTA(liquid_factorialf(1), 1,   tol);
    CONTEND_DELTA(liquid_factorialf(2), 2,   tol);
    CONTEND_DELTA(liquid_factorialf(3), 6,   tol);
    CONTEND_DELTA(liquid_factorialf(4), 24,  tol);
    CONTEND_DELTA(liquid_factorialf(5), 120, tol);
    CONTEND_DELTA(liquid_factorialf(6), 720, tol);
}

// 
// AUTOTEST: nchoosek
//
void autotest_nchoosek()
{
    float tol = 1e-3f;

    // nchoosek(6, k)
    CONTEND_DELTA(liquid_nchoosek(6,    0),      1,     tol);
    CONTEND_DELTA(liquid_nchoosek(6,    1),      6,     tol);
    CONTEND_DELTA(liquid_nchoosek(6,    2),     15,     tol);
    CONTEND_DELTA(liquid_nchoosek(6,    3),     20,     tol);
    CONTEND_DELTA(liquid_nchoosek(6,    4),     15,     tol);
    CONTEND_DELTA(liquid_nchoosek(6,    5),      6,     tol);
    CONTEND_DELTA(liquid_nchoosek(6,    6),      1,     tol);

    // nchoosek(7, k)
    CONTEND_DELTA(liquid_nchoosek(7,    0),      1,     tol);
    CONTEND_DELTA(liquid_nchoosek(7,    1),      7,     tol);
    CONTEND_DELTA(liquid_nchoosek(7,    2),     21,     tol);
    CONTEND_DELTA(liquid_nchoosek(7,    3),     35,     tol);
    CONTEND_DELTA(liquid_nchoosek(7,    4),     35,     tol);
    CONTEND_DELTA(liquid_nchoosek(7,    5),     21,     tol);
    CONTEND_DELTA(liquid_nchoosek(7,    6),      7,     tol);
    CONTEND_DELTA(liquid_nchoosek(7,    7),      1,     tol);

    // test very large numbers
    CONTEND_DELTA(liquid_nchoosek(124,  5),     225150024,  5000);
}

// 
// AUTOTEST: Bessel function of the first kind
//
void autotest_besselj_0()
{
    float tol = 1e-3f;
    CONTEND_DELTA(besselj_0(0.0f),  1.0f, tol);
    CONTEND_DELTA(besselj_0(0.1f),  0.997501562066040f, tol);
    CONTEND_DELTA(besselj_0(0.2f),  0.990024972239576f, tol);
    CONTEND_DELTA(besselj_0(0.5f),  0.938469807240813f, tol);
    CONTEND_DELTA(besselj_0(1.0f),  0.765197686557967f, tol);
    CONTEND_DELTA(besselj_0(2.0f),  0.223890779141236f, tol);
    CONTEND_DELTA(besselj_0(2.5f), -0.048383776468199f, tol);
    CONTEND_DELTA(besselj_0(3.0f), -0.260051954901934f, tol);
    CONTEND_DELTA(besselj_0(3.5f), -0.380127739987263f, tol);
    CONTEND_DELTA(besselj_0(4.0f), -0.397149809863848f, tol);
    CONTEND_DELTA(besselj_0(4.5f), -0.320542508985121f, tol);
}

// 
// AUTOTEST: Modified Bessel function of the first kind
//
void autotest_besseli_0()
{
    float tol = 1e-3f;
    CONTEND_DELTA(besseli_0(0.0f), 1.0f, tol);
    CONTEND_DELTA(besseli_0(0.1f), 1.00250156293410f, tol);
    CONTEND_DELTA(besseli_0(0.2f), 1.01002502779515f, tol);
    CONTEND_DELTA(besseli_0(0.5f), 1.06348337074132f, tol);
    CONTEND_DELTA(besseli_0(1.0f), 1.26606587775201f, tol);
    CONTEND_DELTA(besseli_0(2.0f), 2.27958530233607f, tol);
    CONTEND_DELTA(besseli_0(3.0f), 4.88079258586503f, tol);
}


// 
// AUTOTEST: Q function
//
void autotest_Q()
{
    float tol = 1e-6f;
    CONTEND_DELTA(liquid_Qf(-4.0f), 0.999968329f, tol);
    CONTEND_DELTA(liquid_Qf(-3.0f), 0.998650102f, tol);
    CONTEND_DELTA(liquid_Qf(-2.0f), 0.977249868f, tol);
    CONTEND_DELTA(liquid_Qf(-1.0f), 0.841344746f, tol);
    CONTEND_DELTA(liquid_Qf( 0.0f), 0.5f,         tol);
    CONTEND_DELTA(liquid_Qf( 1.0f), 0.158655254f, tol);
    CONTEND_DELTA(liquid_Qf( 2.0f), 0.022750132f, tol);
    CONTEND_DELTA(liquid_Qf( 3.0f), 0.001349898f, tol);
    CONTEND_DELTA(liquid_Qf( 4.0f), 0.000031671f, tol);
}

// 
// AUTOTEST: sincf
//
void autotest_sincf()
{
    float tol = 1e-3f;
    CONTEND_DELTA(sincf(0.0f), 1.0f, tol);
}

// 
// AUTOTEST: nextpow2
//
void autotest_nextpow2()
{
    CONTEND_EQUALITY(liquid_nextpow2(1),    0);

    CONTEND_EQUALITY(liquid_nextpow2(2),    1);

    CONTEND_EQUALITY(liquid_nextpow2(3),    2);
    CONTEND_EQUALITY(liquid_nextpow2(4),    2);

    CONTEND_EQUALITY(liquid_nextpow2(5),    3);
    CONTEND_EQUALITY(liquid_nextpow2(6),    3);
    CONTEND_EQUALITY(liquid_nextpow2(7),    3);
    CONTEND_EQUALITY(liquid_nextpow2(8),    3);

    CONTEND_EQUALITY(liquid_nextpow2(9),    4);
    CONTEND_EQUALITY(liquid_nextpow2(10),   4);
    CONTEND_EQUALITY(liquid_nextpow2(11),   4);
    CONTEND_EQUALITY(liquid_nextpow2(12),   4);
    CONTEND_EQUALITY(liquid_nextpow2(13),   4);
    CONTEND_EQUALITY(liquid_nextpow2(14),   4);
    CONTEND_EQUALITY(liquid_nextpow2(15),   4);

    CONTEND_EQUALITY(liquid_nextpow2(67),   7);
    CONTEND_EQUALITY(liquid_nextpow2(179),  8);
    CONTEND_EQUALITY(liquid_nextpow2(888),  10);
}

#endif 

