#include "EasyBMP.h"
#include "seg.h"


int main( int argc, char* argv[] ) {
    BMP test;
    //test.ReadFromFile("data/images/asdf.bmp");

    srand(time(NULL));

    unsigned int regionCount = 1728;
    double threshold = 5;
    std::vector<PixelRegion*> regions;

    test.ReadFromFile("data/images/EasyBMPtext.bmp");

    /*
    BMP Text;
    Text.ReadFromFile("data/images/EasyBMPtext.bmp");
      
    BMP Background;
    Background.ReadFromFile("data/images/EasyBMPbackground.bmp");

    BMP Output;
    //Output.SetSize( Background.TellWidth() , Background.TellHeight() );
    //Output.SetBitDepth(24);

    RangedPixelToPixelCopy( Background, 0, Output.TellWidth()-1,
                            Output.TellHeight()-1 , 0, 
                            Output, 0,0 );	
    
    RangedPixelToPixelCopyTransparent( Text, 0, 380, 
                                       43, 0,
                                    Output, 110,5, 
                                    *Text(0,0) );
    RangedPixelToPixelCopyTransparent( Text, 0, Text.TellWidth()-1, 
                                       Text.TellWidth()-1, 50,
                                    Output, 100,442, 
                                    *Text(0,49) );
    //Output.SetBitDepth( 32 );
    //Output.WriteToFile( "EasyBMPoutput32bpp.bmp" );

    // Write the result to a file
    Output.WriteToFile( "EasyBMPoutput24bpp_rescaled.bmp" );
    */
    int height = test.TellHeight();
    int width = test.TellWidth();
    std::vector<Pixel*> pixels;
    Photo *photo;
    double avgMidChange;

    std::cout << "Height: " << height << "\n";
    std::cout << "Width: " << width << "\n";
    
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            RGBApixel tmp1 = test.GetPixel(x, y);
            Pixel *tmp2 = new Pixel(tmp1.Red, tmp1.Green, tmp1.Blue);
            pixels.push_back(tmp2);
            break;
        }
    }

    photo = new Photo(width, height, pixels);

    for(unsigned int i = 0; i < regionCount; i++) {
        regions.push_back(new PixelRegion(photo));
    }

    do {
        for(unsigned int i = 0; i < regionCount; i++) {
            regions[i]->clear();
        }

        for(unsigned int i = 0; i < photo->size(); i++) {
            int closest = 0;
            double dist;

            for(unsigned int j = 0; j < regions.size(); j++) {
                dist = regions[j]->distTo(photo->getPixel(i));
                if(dist < regions[closest]->distTo(photo->getPixel(i))) {
                    closest = j;
                }
            }
        }

        avgMidChange = 0;
        for(unsigned int i = 0; i < regions.size(); i++) {
            avgMidChange += regions[i]->adjMid();
        }
        avgMidChange /= regions.size();
    }while(avgMidChange > threshold);

    for(unsigned int i = 0; i < regions.size(); i++) {
        regions[i]->change();
    }

    return 0;
}
