#ifndef SEG_H
#define SEG_H
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cstdint>
#include <vector>

class Pixel {
    private:
        uint32_t red, green, blue, alpha;

    public:
        Pixel(uint32_t red, uint32_t gree, uint32_t blue, uint32_t alpha);
        Pixel(Pixel *pxl);

        uint32_t gred(void) const;
        uint32_t ggreen(void) const;
        uint32_t gblue(void) const;
        uint32_t galpha(void) const;
        void set(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
};

class Photo {
    private:
        unsigned int x, y, d;
        std::vector<Pixel*> pixels;

    public:
        Photo(unsigned int x, unsigned int y, std::vector<Pixel*> pxls);
        
        std::vector<Pixel*> getPixels(void);
        Pixel* getPixel(unsigned int i);
        Pixel* getRandPos(void);
        void setPixel(Pixel *pixel, unsigned int x, unsigned int y);
        unsigned int size(void);

        ~Photo();
};

class PixelRegion {
    private:
        Photo *photo;
        Pixel *mid;
        std::vector<Pixel*> pixels;

    public:
        PixelRegion(Photo *photo);
        ~PixelRegion();
        
        double adjMid(void);
        double distTo(Pixel *pxl);
        double distTo(uint32_t r, uint32_t g, uint32_t b);
		int size(void);
		std::vector<Pixel*> getPixels();
        void addPix(Pixel *pixel);
        void clear(void);
        void change(void);
		void change(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
};
#endif
