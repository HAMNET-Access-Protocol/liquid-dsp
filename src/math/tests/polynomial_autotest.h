/*
 * Copyright (c) 2007, 2008, 2009, 2010, 2011 Joseph Gaeddert
 * Copyright (c) 2007, 2008, 2009, 2010, 2011 Virginia Polytechnic
 *                                      Institute & State University
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

#include <string.h>
#include <stdbool.h>

#include "autotest/autotest.h"
#include "liquid.h"

// 
// AUTOTEST: poly_fit 3rd order polynomial, critically sampled
//
void autotest_polyf_fit_q3n3()
{
    unsigned int Q=2;   // polynomial order
    unsigned int n=3;   // input vector size

    float x[3] = {-1.0f, 0.0f, 1.0f};
    float y[3] = { 1.0f, 0.0f, 1.0f};
    float p[3];
    float p_test[3] = {0.0f, 0.0f, 1.0f};
    float tol = 1e-3f;

    unsigned int k=Q+1;
    polyf_fit(x,y,n, p,k);

    if (liquid_autotest_verbose) {
        unsigned int i;
        for (i=0; i<3; i++)
            printf("%3u : %12.8f > %12.8f\n", i, x[i], y[i]);
        for (i=0; i<3; i++)
            printf("p[%3u] = %12.8f\n", i, p[i]);
    }
    
    CONTEND_DELTA(p[0], p_test[0], tol);
    CONTEND_DELTA(p[1], p_test[1], tol);
    CONTEND_DELTA(p[2], p_test[2], tol);
    //CONTEND_DELTA(p[3], p_test[3], tol);
}

// 
// AUTOTEST: poly_expandbinomial
//
void autotest_polyf_expandbinomial_4()
{
    float a[4] = { 3, 2, -5, 1 };
    float c[5];
    float c_test[5] = { 1, 1, -19, -49, -30 };
    float tol = 1e-3f;

    polyf_expandbinomial(a,4,c);

    if (liquid_autotest_verbose) {
        unsigned int i;
        printf("c[5] = ");
        for (i=0; i<5; i++)
            printf("%8.2f", c[i]);
        printf("\n");
    }
    
    CONTEND_DELTA(c[0], c_test[0], tol);
    CONTEND_DELTA(c[1], c_test[1], tol);
    CONTEND_DELTA(c[2], c_test[2], tol);
    CONTEND_DELTA(c[3], c_test[3], tol);
    CONTEND_DELTA(c[4], c_test[4], tol);
}


// 
// AUTOTEST: poly_expandroots
//
void autotest_polyf_expandroots_4()
{
    float roots[5] = { -2, -1, -4, 5, 3 };
    float c[6];
    float c_test[6] = { 120, 146, 1, -27, -1, 1 };
    float tol = 1e-3f;

    polyf_expandroots(roots,5,c);

    if (liquid_autotest_verbose) {
        unsigned int i;
        printf("c[6] = ");
        for (i=0; i<6; i++)
            printf("%8.2f", c[i]);
        printf("\n");
    }
    
    CONTEND_DELTA(c[0], c_test[0], tol);
    CONTEND_DELTA(c[1], c_test[1], tol);
    CONTEND_DELTA(c[2], c_test[2], tol);
    CONTEND_DELTA(c[3], c_test[3], tol);
    CONTEND_DELTA(c[4], c_test[4], tol);
    CONTEND_DELTA(c[5], c_test[5], tol);
}


// 
// AUTOTEST: poly_expandroots
//
void autotest_polyf_expandroots_11()
{
    float roots[11] = { -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11 };
    float c[12];
    float c_test[12] = {39916800,
                        120543840,
                        150917976,
                        105258076,
                        45995730,
                        13339535,
                        2637558,
                        357423,
                        32670,
                        1925,
                        66,
                        1};
    float tol = 1e-6f;

    polyf_expandroots(roots,11,c);

    unsigned int i;
    for (i=0; i<12; i++) {
        if (liquid_autotest_verbose)
            printf("  c[%3u] : %16.8e (expected %16.8e)\n", i, c[i], c_test[i]);

        CONTEND_DELTA(c[i], c_test[i], fabsf(tol*c_test[i]));
    }
}

// 
// AUTOTEST: polycf_expandroots
//
void autotest_polycf_expandroots_4()
{
    // expand complex roots on conjugate pair
    float theta = 1.7f;
    float complex a[2] = { -cexpf(_Complex_I*theta), -cexpf(-_Complex_I*theta) };
    float complex c[3];
    float complex c_test[3] = { 1, 2*cosf(theta), 1 };
    float tol = 1e-3f;

    polycf_expandroots(a,2,c);

    if (liquid_autotest_verbose) {
        unsigned int i;
        for (i=0; i<3; i++)
            printf("c[%3u] = %12.8f + j*%12.8f\n", i, crealf(c[i]), cimagf(c[i]));
    }
    
    CONTEND_DELTA(crealf(c[0]), crealf(c_test[0]), tol);
    CONTEND_DELTA(cimagf(c[0]), cimagf(c_test[0]), tol);

    CONTEND_DELTA(crealf(c[1]), crealf(c_test[1]), tol);
    CONTEND_DELTA(cimagf(c[1]), cimagf(c_test[1]), tol);

    CONTEND_DELTA(crealf(c[2]), crealf(c_test[2]), tol);
    CONTEND_DELTA(cimagf(c[2]), cimagf(c_test[2]), tol);

}

// 
// AUTOTEST: poly_expandroots2
//
// expand (2*x-5)*(3*x+2)*(-1*x+3)
//
void autotest_polyf_expandroots2_3()
{
    unsigned int n=3;
    float a[3] = {  2,  3, -1 };
    float b[3] = {  5, -2, -3 };
    float c[4];
    float c_test[4] = { -6, 29, -23, -30 };
    float tol = 1e-3f;

    polyf_expandroots2(a,b,n,c);

    if (liquid_autotest_verbose) {
        unsigned int i;
        printf("c[%u] = ", n+1);
        for (i=0; i<n+1; i++)
            printf("%8.2f", c[i]);
        printf("\n");
    }
    
    CONTEND_DELTA(c[0], c_test[0], tol);
    CONTEND_DELTA(c[1], c_test[1], tol);
    CONTEND_DELTA(c[2], c_test[2], tol);
    CONTEND_DELTA(c[3], c_test[3], tol);
}


// 
// AUTOTEST: polyf_mul
//
void autotest_polyf_mul_2_3()
{
    float a[3] = {  2, -4,  3 };
    float b[4] = { -9,  3, -2,  5};
    float c[6];
    float c_test[6] = { -18, 42, -43, 27, -26, 15 };
    float tol = 1e-3f;

    polyf_mul(a,2,b,3,c);

    if (liquid_autotest_verbose) {
        unsigned int i;
        printf("c[6] = ");
        for (i=0; i<6; i++)
            printf("%8.2f", c[i]);
        printf("\n");
    }
    
    CONTEND_DELTA(c[0], c_test[0], tol);
    CONTEND_DELTA(c[1], c_test[1], tol);
    CONTEND_DELTA(c[2], c_test[2], tol);
    CONTEND_DELTA(c[3], c_test[3], tol);
    CONTEND_DELTA(c[4], c_test[4], tol);
    CONTEND_DELTA(c[5], c_test[5], tol);
}

#if 0
// 
// AUTOTEST: poly_binomial_expand
//
void xautotest_poly_binomial_expand_n6()
{
    unsigned int n=6;
    int c[7];
    int c_test[7] = {1, 6, 15, 20, 15, 6, 1};

    poly_binomial_expand(n,c);

    if (liquid_autotest_verbose) {
        unsigned int i;
        printf("c[%u] = ", n+1);
        for (i=0; i<=n; i++)
            printf("%5d", c[i]);
        printf("\n");
    }
    
    CONTEND_SAME_DATA(c,c_test,sizeof(c));
}


// 
// AUTOTEST: poly_binomial_expand_pm
//
void xautotest_poly_binomial_expand_pm_n6_k1()
{
    unsigned int n=6;
    unsigned int k=1;
    int c[7];
    int c_test[7] = {1,  -4,   5,   0,  -5,   4,  -1};

    poly_binomial_expand_pm(n,k,c);

    if (liquid_autotest_verbose) {
        unsigned int i;
        printf("c[%u] = ", n+1);
        for (i=0; i<=n; i++)
            printf("%5d", c[i]);
        printf("\n");
    }
    
    CONTEND_SAME_DATA(c,c_test,sizeof(c));
}


// 
// AUTOTEST: poly_binomial_expand_pm
//
void xautotest_poly_binomial_expand_pm_n5_k2()
{
    unsigned int n=5;
    unsigned int k=2;
    int c[6];
    int c_test[6] = {1,  -1,  -2,   2,   1,  -1};

    poly_binomial_expand_pm(n,k,c);

    if (liquid_autotest_verbose) {
        unsigned int i;
        printf("c[%u] = ", n+1);
        for (i=0; i<=n; i++)
            printf("%5d", c[i]);
        printf("\n");
    }
    
    CONTEND_SAME_DATA(c,c_test,sizeof(c));
}
#endif

// 
// AUTOTEST: polyf_findroots
//
void autotest_polyf_findroots()
{
    float tol=1e-6f;

    float p[6] = {6,11,-33,-33,11,6};
    float complex roots[5];
    float complex rtest[5] = {-3,2,-1,0.5,-1./3.};

    polyf_findroots(p,6,roots);

    unsigned int i;
    if (liquid_autotest_verbose) {
        printf("poly:\n");
        for (i=0; i<6; i++)
            printf("  p[%3u] = %12.8f + j*%12.8f\n", i, crealf(p[i]), cimagf(p[i]));

        printf("roots:\n");
        for (i=0; i<5; i++)
            printf("  r[%3u] = %12.8f + j*%12.8f\n", i, crealf(roots[i]), cimagf(roots[i]));
    }

    bool rtest_used[5];
    memset(rtest_used, 0, sizeof(rtest_used));

    unsigned int j,k=0;
    for (i=0; i<5; i++) {
        for (j=0; j<5; j++) {
            // check to see if this root has been used already
            if (rtest_used[j]) continue;

            // check to see if roots match within relative tolerance
            if (cabsf(roots[i]-rtest[j]) < tol) {
                rtest_used[j] = true;
                CONTEND_DELTA(crealf(roots[i]), crealf(rtest[j]), tol);
                CONTEND_DELTA(cimagf(roots[i]), cimagf(rtest[j]), tol);
                k++;
                continue;
            }
        }
    }
    CONTEND_EQUALITY(k,5);
}


// 
// AUTOTEST: polycf_findroots (random roots)
//
void xautotest_polycf_findroots_rand()
{
    unsigned int n=5;
    float tol=1e-4f;

    float complex p[n];
    float complex roots[n-1];

    float complex p_hat[n];

    unsigned int i;
    for (i=0; i<n; i++)
        p[i] = i == n-1 ? 1 : 3.0f * randnf();

    polycf_findroots(p,n,roots);

    float complex roots_hat[n-1];
    // convert form...
    for (i=0; i<n-1; i++)
        roots_hat[i] = -roots[i];

    polycf_expandroots(roots_hat,n-1,p_hat);

    if (liquid_autotest_verbose) {
        printf("poly:\n");
        for (i=0; i<n; i++)
            printf("  p[%3u] = %12.8f + j*%12.8f\n", i, crealf(p[i]), cimagf(p[i]));

        printf("roots:\n");
        for (i=0; i<n-1; i++)
            printf("  r[%3u] = %12.8f + j*%12.8f\n", i, crealf(roots[i]), cimagf(roots[i]));

        printf("poly (expanded roots):\n");
        for (i=0; i<n; i++)
            printf("  p[%3u] = %12.8f + j*%12.8f\n", i, crealf(p_hat[i]), cimagf(p_hat[i]));
    }

    for (i=0; i<n; i++) {
        CONTEND_DELTA(crealf(p[i]), crealf(p_hat[i]), tol);
        CONTEND_DELTA(cimagf(p[i]), cimagf(p_hat[i]), tol);
    }
}

