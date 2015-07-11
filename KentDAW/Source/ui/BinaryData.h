/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_119175451_INCLUDED
#define BINARYDATA_H_119175451_INCLUDED

namespace BinaryData
{
    extern const char*   backwardbutton_png;
    const int            backwardbutton_pngSize = 6172;

    extern const char*   forwardbutton_png;
    const int            forwardbutton_pngSize = 6492;

    extern const char*   playbutton_png;
    const int            playbutton_pngSize = 6435;

    extern const char*   recordbutton_png;
    const int            recordbutton_pngSize = 6513;

    extern const char*   stopbutton_png;
    const int            stopbutton_pngSize = 5916;

    extern const char*   toEndbutton_png;
    const int            toEndbutton_pngSize = 6637;

    extern const char*   toStartbutton_png;
    const int            toStartbutton_pngSize = 6672;
    
    extern const char*   loopbutton_png;
    const int            loopbutton_pngSize = 6994;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 8;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
