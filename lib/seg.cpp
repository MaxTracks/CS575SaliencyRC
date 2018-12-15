#ifndef _K_MEANS_SEG_
#define _K_MEANS_SEG_

#include "seg.h"

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>

Pixel::Pixel(unsigned int r, unsigned int g, unsigned int b): red(r), green(g), blue(b) {}

Pixel::Pixel(Pixel *pxl): red(pxl->red), green(pxl->green), blue(pxl->blue) {}

unsigned int Pixel::gred(void) {
    return red;
}

unsigned int Pixel::ggreen(void) {
    return green;
}

unsigned int Pixel::gblue(void) {
    return blue;
}

void Pixel::set(unsigned int r, unsigned int g, unsigned int b) {
    red = r;
    green = g;
    blue = b;
}

Photo::Photo(unsigned int width, unsigned int height, std::vector<Pixel*> pxls) {
    x = width;
    y = height;
    for(unsigned int i = 0; i < x*y; i++) {
        pixels.push_back(new Pixel(0, 0, 0));
    }
}

Photo::~Photo() {
    for(unsigned int i = 0; i < pixels.size(); i++) {
        delete pixels[i];
    }
}

std::vector<Pixel*> Photo::getPixels(void) {
    return pixels;
}

Pixel* Photo::getPixel(unsigned int i) {
    return pixels[i];
}

Pixel* Photo::getRandPos(void) {
    return pixels[rand() % x*y];
}

unsigned int Photo::size(void) {
    return x*y;
}

PixelRegion::PixelRegion(Photo *photo) : photo(photo), mid(new Pixel(photo->getRandPos())) {}

PixelRegion::~PixelRegion() {
    delete mid;
}

double PixelRegion::adjMid() {
    unsigned int r = 0, g = 0, b = 0;
    
    for(unsigned int i = 0; i < pixels.size(); i++) {
        r += pixels[i]->gred();
        g += pixels[i]->ggreen();
        b += pixels[i]->gblue();
    }
    
    int d = pixels.size();
    
    if(pixels.size() < 1) {
        d = 1;
    }

    r /= d;
    g /= d;
    b /= d;

    double diff = this->distTo(r, g, b);
    mid->set(r, g, b);
    
    return diff;
}

double PixelRegion::distTo(Pixel *pxl) {
    int dr = pxl->gred() - mid->gred();
    int dg = pxl->ggreen() - mid->ggreen();
    int db = pxl->gblue() - mid->gblue();

    return std::sqrt(std::pow(dr, 2) + std::pow(dg, 2) + std::pow(db, 2));
}

double PixelRegion::distTo(unsigned int r, unsigned int g, unsigned int b) {
    int dr = r - mid->gred();
    int dg = g - mid->ggreen();
    int db = b - mid->gblue();

    return std::sqrt(std::pow(dr, 2) + std::pow(dg, 2) + std::pow(db, 2));
}

void PixelRegion::addPix(Pixel *pxl) {
    pixels.push_back(pxl);
}

void PixelRegion::clear(void) {
    pixels = {};
}

void PixelRegion::change(void) {
    for(unsigned int i = 0; i < pixels.size(); i++) {
        pixels[i]->set(mid->gred(), mid->ggreen(), mid->gblue());
    }
}

#endif 




