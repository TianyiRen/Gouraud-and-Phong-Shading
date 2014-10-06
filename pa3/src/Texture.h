#if defined(__APPLE__) || defined(MACOSX)
#   	include <GLUT/glut.h>

#else
#   	include <GL/glut.h>
#	include <iostream>


#endif

class Texture
{
    unsigned int textureID;
public:
    Texture(void* data, int w, int h, int format);
    unsigned int getTextureID();
    static Texture* loadBMP(const char* filename);
    
};

