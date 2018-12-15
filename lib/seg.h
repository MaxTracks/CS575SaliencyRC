
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>

class Pixel {
    private:
        int red, green, blue, alpha;

    public:
        Pixel(int red, int gree, int blue, int alpha);
        Pixel(Pixel *pxl);

        int gred(void);
        int ggreen(void);
        int gblue(void);
        int galpha(void);
        void set(int r, int g, int b);
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
        double distTo(int r, int g, int b);
        void addPix(Pixel *pixel);
        void clear(void);
        void change(void);
};
