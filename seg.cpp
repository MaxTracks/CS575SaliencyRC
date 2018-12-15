#ifndef _K_MEANS_SEG_
#define _K_MEANS_SEG_

#include "seg.h"

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstdint>

Pixel::Pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a): red(r), green(g), blue(b), alpha(a) {}

Pixel::Pixel(Pixel *pxl): red(pxl->red), green(pxl->green), blue(pxl->blue) {}

uint32_t Pixel::gred(void) const {
    return red;
}

uint32_t Pixel::ggreen(void) const {
    return green;
}

uint32_t Pixel::gblue(void) const {
    return blue;
}

uint32_t Pixel::galpha(void) const {
    return alpha;
}

void Pixel::set(uint32_t r, uint32_t g, uint32_t b, uint32_t a) {
    red = r;
    green = g;
    blue = b;
	alpha = a;
}

Photo::Photo(unsigned int width, unsigned int height, std::vector<Pixel*> pxls) {
    x = width;
    y = height;

	std::cout << "X*Y + " << x*y << "; PixlList Size: " << pxls.size() << "\n";
    for(unsigned int i = 0; i < pxls.size(); i++) {
        pixels.push_back(pxls[i]);
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
    return pixels.size();
}

PixelRegion::PixelRegion(Photo *photo) : photo(photo), mid(new Pixel(photo->getRandPos())) {}

PixelRegion::~PixelRegion() {
    delete mid;
}

double PixelRegion::adjMid() {
    uint32_t r = 0, g = 0, b = 0, a = 0;
    
    for(unsigned int i = 0; i < pixels.size(); i++) {
        r += pixels[i]->gred();
        g += pixels[i]->ggreen();
        b += pixels[i]->gblue();
        a += pixels[i]->galpha();
    }
    
    int d = pixels.size();
    
    if(pixels.size() < 1) {
        d = 1;
    }

    r /= d;
    g /= d;
    b /= d;
    a /= d;

    double diff = this->distTo(r, g, b);
    mid->set(r, g, b, a);
    
    return diff;
}

double PixelRegion::distTo(Pixel *pxl) {
    uint32_t dr = pxl->gred() - mid->gred();
    uint32_t dg = pxl->ggreen() - mid->ggreen();
    uint32_t db = pxl->gblue() - mid->gblue();

    return std::sqrt(std::pow(dr, 2) + std::pow(dg, 2) + std::pow(db, 2));
}

double PixelRegion::distTo(uint32_t r, uint32_t g, uint32_t b) {
    uint32_t dr = r - mid->gred();
    uint32_t dg = g - mid->ggreen();
    uint32_t db = b - mid->gblue();

    return std::sqrt(std::pow(dr, 2) + std::pow(dg, 2) + std::pow(db, 2));
}

std::vector<Pixel*> PixelRegion::getPixels() {
	return pixels;
}

int PixelRegion::size() {
	return pixels.size();
}

void PixelRegion::addPix(Pixel *pxl) {
    pixels.push_back(pxl);
}

void PixelRegion::clear(void) {
    pixels = {};
}

void PixelRegion::change(void) {
    for(unsigned int i = 0; i < pixels.size(); i++) {
        pixels[i]->set(mid->gred(), mid->ggreen(), mid->gblue(), mid->galpha());
    }
}

void PixelRegion::change(uint32_t r, uint32_t g, uint32_t b, uint32_t a) {
    for(unsigned int i = 0; i < pixels.size(); i++) {
        pixels[i]->set(r, g, b, a);
    }
}

#endif 




