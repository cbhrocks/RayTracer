i#ifndef __SHADER
#define __SHADER

#include "../vector/GenVector.h"
#include "../ray/Ray.h"
#include "../primitive/Primitive.h"
#include "Material.h"
#include "Light.h"
#include <math.h>

class Shader{
  public:
    Shader(){
    }

    virtual Color getColor(
        Material *mat,
        Vector3 normal,
        Vector3 hitLoc,
        Vector3 vDirection,
        Light **lights,
        int lightNum
        ){
      Vector3 pixelColor = Vector3(0,0,0);
      Vector3 ambientColor;
      //printf("%s\n", mat->getName());
      for (int i = 0; i < lightNum; i++){
        float distance = (lights[i]->getLocation() - hitLoc).length();
        //Vector3 l = lights[i]->getDirection();
        Vector3 l = lights[i]->getDirection(hitLoc);
        Vector3 kd = mat->getDiffuseCoefficient()*255;
        Vector3 ks = mat->getSpecularCoefficient()*255;
        Vector3 ka = mat->getAmbientCoefficient()*255;
        Vector3 Id = lights[i]->getDiffuseIntensity(distance);
        Vector3 Is = lights[i]->getSpecularIntensity(distance);
        Vector3 Ia = lights[i]->getAmbientIntensity(distance);
        Vector3 h = (vDirection + l)/(vDirection + l).length();
        //Vector3 lr = 2*l.dot(normal)*normal - l;

        //printf("kd vector: %f, %f, %f\n", kd[0], kd[1], kd[2]);
        //printf("Ka vector: %f, %f, %f\n", ka[0], ka[1], ka[2]);
        //printf("n dot l: %f\n", l.dot(normal));

        int s = mat->getShine();

        Vector3 diffuse = kd*Id*max(0, l.dot(normal));
        Vector3 specular = ks * Is * pow(max(0, normal.dot(h)), s); 

        pixelColor += diffuse + specular;
        //printf("pixelColor: %f, %f, %f.", pixelColor[0], pixelColor[1], pixelColor[2]);
        if (Ia[0] > ambientColor[0]){
          ambientColor[0] = (ka)[0] * Ia[0];
        }
        if (Ia[1] > ambientColor[1]){
          ambientColor[1] = (ka)[1] * Ia[1];
        }
        if (Ia[2] > ambientColor[2]){
          ambientColor[2] = (ka)[2] * Ia[2];
        }
      }
      pixelColor += ambientColor;

      pixelColor = pixelColor/17.965782;

      //float maxPC = pixelColor.maxMagnitudeComponent();
      //pixelColor = pixelColor/maxPC * 255;

      //printf("ambientColor vector: %f, %f, %f\n", ambientColor[0], ambientColor[1], ambientColor[2]);
      Color color = Color(pixelColor[0], pixelColor[1], pixelColor[2]);
      return color;
    }

  protected:
    float max(float a, float b){
      if (a > b){
        return a;
      }
      else {
        return b;
      }
    }

    float min(float a, float b){
      if (a < b){
        return a;
      }
      else {
        return b;
      }
    }
};

#endif

