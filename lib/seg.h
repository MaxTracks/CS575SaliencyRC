
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>

class Pixel {
    private:
        unsigned int red, green, blue;

    public:
        Pixel(unsigned int red, unsigned int gree, unsigned int blue);
        Pixel(Pixel *pxl);

        unsigned int gred(void);
        unsigned int ggreen(void);
        unsigned int gblue(void);
        void set(unsigned int r, unsigned int g, unsigned int b);
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
        double distTo(unsigned int r, unsigned int g, unsigned int b);
        void addPix(Pixel *pixel);
        void clear(void);
        void change(void);
};
