/**
 * @file imageop.cpp
 * @brief Fichero con definiciones para el resto de métodos de la clase Image
 */

#include <iostream>
#include <cmath>
#include <image.h>

#include <cassert>

// Métodos de la clase Image más complejos

Image Image::Crop(int nrow, int ncol, int height, int width) const {

    Image nueva(height, width);
    for (int i = 0; i < height && nrow+i < get_rows(); i++) {
        for (int j = 0; j < width && ncol+j < get_cols(); j++)
            nueva.set_pixel(i, j, get_pixel(nrow+i, ncol+j));

    }
    return nueva;
}

Image Image::Zoom2X() const {

    int dim;
    if (get_rows()!=get_cols())
        dim = (get_cols()<get_rows()) ? get_cols() : get_rows();
    else dim = get_rows();
    dim=(dim*2)-1;
    Image zoomed(dim, dim);

    for (int i=0; i<dim; i++) {
        for (int j=0; j<dim; j++) {
            if (i%2==0 && j%2==0) zoomed.set_pixel(i, j, get_pixel(i / 2, j / 2));
            else if (i%2==0 && j%2!=0) {
                int pixel= round(Mean(i/2,j/2,1,2));
                zoomed.set_pixel(i, j, pixel);
            }
            else if (i%2!=0 && j%2==0) {
                int pixel = round(Mean(i/2,j/2,2,1));
                zoomed.set_pixel(i, j, pixel);
            }
            else {
                int pixel = round(Mean(i/2,j/2,2,2));
                zoomed.set_pixel(i, j, pixel);
            }
        }
    }
    return zoomed;
}

double Image::Mean(int i, int j, int height, int width) const {

    double media = 0;
    int contador = 0;
    for (int k = 0;k<height;k++) {
        for (int l = 0; l<width;l++) {
            if (i + k < get_rows() && j + l < get_cols()){
                media += get_pixel(i + k, j + l);
                contador++;
            }
        }
    }
    media/=contador;
    return media;

}

Image Image::Subsample(int factor) const {
    int h = get_rows()/factor;
    int w = get_cols()/factor;
    Image icon(h,w);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++)
            icon.set_pixel(i,j, round(Mean(i*factor,j*factor,factor,factor)));
    }

    return icon;

}

void Image::AdjustContrast(byte in1, byte in2, byte out1, byte out2) {

    double prop=(out2-out1)/(in2-in1);

    for (int i=0;i<get_rows()*get_cols();i++) {
        double valor = out1 + (prop * (get_pixel(i) - in1));
        set_pixel(i, round(valor));
    }

}

void Image::Invert() {
    int pixeles=get_rows()*get_cols();
    for (int i = 0; i < pixeles; i++)
        set_pixel(i,255-get_pixel(i));
}

// Modificada para una mayor eficacia
void Image::ShuffleRows() {
    const int p = 9973;
    Image temp(rows,cols);
    int newr;
    for (int r=0; r<rows; r++){
        newr = r*p % rows;
        /*for (int c=0; c<cols;c++)
            temp.set_pixel(r,c,get_pixel(newr,c));*/

        temp.img[r]=img[newr];
    }
    Copy(temp);
}

