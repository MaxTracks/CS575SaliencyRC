#include "EasyBMP.h"
using namespace std;

int main( int argc, char* argv[] ) {
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
    
    /*                     
    RangedPixelToPixelCopyTransparent( Text, 0, 380, 
                                       43, 0,
                                    Output, 110,5, 
                                    *Text(0,0) );
    RangedPixelToPixelCopyTransparent( Text, 0, Text.TellWidth()-1, 
                                       Text.TellWidth()-1, 50,
                                    Output, 100,442, 
                                    *Text(0,49) );
    */                
    //Output.SetBitDepth( 32 );
    //Output.WriteToFile( "EasyBMPoutput32bpp.bmp" );

    // Write the result to a file
    Output.WriteToFile( "EasyBMPoutput24bpp_rescaled.bmp" );

    return 0;
}
