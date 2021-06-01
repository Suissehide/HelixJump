///////////////////////////////////////////////////////////////////////////////
//
//      TargaImage.h                            Author:     Stephen Chenney
//                                              Modified:   Eric McDaniel
//                                              Date:       Spring 2003
//
//      Class to manipulate targa images.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef TARGA_IMAGE_H_
#define TARGA_IMAGE_H_

#include <Fl/Fl.h>
#include <Fl/Fl_Widget.h>
#include <stdio.h>

class TargaImage1
{
    // methods
    public:
	    TargaImage1(void);
	    TargaImage1(int, int, unsigned char*);
	    ~TargaImage1(void);

        unsigned char*	To_RGB(void);	             // Convert the image to RGB format,
        bool Save_Image(char*);                     // save the image to a file
        static TargaImage1* Load_Image(char*);       // Load a file and return a pointer to a new TargaImage object.  Returns NULL on failure
	     TargaImage1* Reverse_Rows(void);             // reverse the rows of the image, some targas are stored bottom to top

    private:
        void RGBA_To_RGB(unsigned char *data, unsigned char *rgb);          // helper function for format conversion

    // members
    public:
        int		         width;	    // width of the image in pixels
        int		         height;	    // height of the image in pixels
        unsigned char	*data;	    // pixel data for the image, assumed to be in pre-multiplied RGBA format.

};


#endif


