#ifndef __SHADER
#define __SHADER

#include "../vector/GenVector.h"
#include "../ray/Ray.h"
#include "../primitive/Primitive.h"
#include "AmbientLight.h"
#include "Material.h"

class Shader{
  public:
    Shader(){
    }

    virtual Color getColor(HitPoint hp){
      Vector3 pixelColor = Vector3(0.0f, 0.0f, 0.0f);
      for (int i = 0; i < this->lightNum; i++){
        pixelColor += this->lights[i]->calculateShading(hp.getMaterial());
      }
      Color color = Color(pixelColor[0], pixelColor[1], pixelColor[2]);
      return color;
    }
};

#endif
