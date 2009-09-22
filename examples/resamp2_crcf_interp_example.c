//
// Halfband interpolator (complex)
//

#include <stdio.h>
#include <complex.h>
#include <math.h>

#include "liquid.h"

#define OUTPUT_FILENAME "resamp2_crcf_interp_example.m"

int main() {
    unsigned int m=5;           // filter semi-length
    unsigned int h_len = 4*m+1; // filter length
    float fc=0.17f;             // input tone frequency
    unsigned int N=128;         // number of input samples

    // create/print the half-band resampler
    resamp2_cccf f = resamp2_cccf_create(h_len,0.0f);
    resamp2_cccf_print(f);

    // open output file
    FILE*fid = fopen(OUTPUT_FILENAME,"w");
    fprintf(fid,"%% %s: auto-generated file\n",OUTPUT_FILENAME);
    fprintf(fid,"clear all;\nclose all;\n\n");
    fprintf(fid,"h_len=%u;\n", h_len);
    fprintf(fid,"N=%u;\n", N);

    unsigned int i;
    float theta=0.0f, dtheta=2*M_PI*fc;
    float complex x, y[2];
    for (i=0; i<N; i++) {
        // generate input : complex sinusoid
        x = cexpf(_Complex_I*theta);
        theta += dtheta;

        // run the interpolator
        resamp2_cccf_interp_execute(f, x, y);

        // save results to output file
        fprintf(fid,"x(%3u) = %8.4f + j*%8.4f;\n", i+1,   crealf(x),    cimagf(x));
        fprintf(fid,"y(%3u) = %8.4f + j*%8.4f;\n", 2*i+1, crealf(y[0]), cimagf(y[0]));
        fprintf(fid,"y(%3u) = %8.4f + j*%8.4f;\n", 2*i+2, crealf(y[1]), cimagf(y[1]));

        printf("y(%3u) = %8.4f + j*%8.4f;\n", 2*i+1, crealf(y[0]), cimagf(y[0]));
        printf("y(%3u) = %8.4f + j*%8.4f;\n", 2*i+2, crealf(y[1]), cimagf(y[1]));
    }

    fprintf(fid,"nfft=512;\n");
    fprintf(fid,"wx = hamming(length(x))'/N*1.8678;   %% normalized window (input)\n");
    fprintf(fid,"wy = hamming(length(y))'/N*1.8678/2; %% normalized window (output)\n");
    fprintf(fid,"X=20*log10(abs(fftshift(fft(x.*wx,nfft))));\n");
    fprintf(fid,"Y=20*log10(abs(fftshift(fft(y.*wy,nfft))));\n");
    fprintf(fid,"f=[0:(nfft-1)]/nfft-0.5;\n");
    fprintf(fid,"figure; plot(f/2,X,'Color',[0.5 0.5 0.5],f,Y,'LineWidth',2);\n");
    fprintf(fid,"grid on;\n");
    fprintf(fid,"xlabel('normalized frequency');\n");
    fprintf(fid,"ylabel('PSD [dB]');\n");
    fprintf(fid,"legend('original','interpolated',1);");
    fprintf(fid,"axis([-0.5 0.5 -100 10]);\n");

    fclose(fid);
    printf("results written to %s\n",OUTPUT_FILENAME);

    // clean up allocated objects
    resamp2_cccf_destroy(f);
    printf("done.\n");
    return 0;
}
