#ifndef __SHADER
#define __SHADER

#include "../vector/GenVector.h"
#include "Material.h"
#include "../ray/HitPoint.h"
#include "../ray/Ray.h"
#include "../primitive/Primitive.h"
#include "Light.h"
#include "../../Scene.h"
#include <math.h>

class Scene;

class Shader{
  public:
    Shader(){
    }

    virtual Vector3 calculateColor(
        HitPoint* hp,
        Vector3 vDirection, 
        Light** lights, 
        Primitive** primList,
        int lightNum,
        int primNum,
        int iteration = 0
        ){
      if (iteration >10){
        return Vector3(0,0,0);
      }
      Vector3 rDirection = (vDirection - 2*(vDirection.dot(hp->getNormal()))*hp->getNormal()).normalize();
      Vector3 pixelColor = Vector3(0,0,0);
      Vector3 ambient;
      Vector3 kd = hp->getMaterial()->getDiffuseCoefficient()*255;
      Vector3 ks = hp->getMaterial()->getSpecularCoefficient()*255;
      Vector3 ka = hp->getMaterial()->getAmbientCoefficient()*255;
      for (int i = 0; i < lightNum; i++){
        float distance = (lights[i]->getLocation() - hp->getLocation()).length();

        Vector3 l = lights[i]->getDirection(hp->getLocation());
        Vector3 Id = lights[i]->getDiffuseIntensity(distance);
        Vector3 Is = lights[i]->getSpecularIntensity(distance);
        Vector3 Ia = lights[i]->getAmbientIntensity(distance);
        Vector3 lr = l - 2*l.dot(hp->getNormal())*hp->getNormal();

        int s = hp->getMaterial()->getShine();

        Vector3 diffuse = kd * Id * max(0, l.dot(hp->getNormal()));
        Vector3 specular = ks * Is * pow(max(0, vDirection.dot(lr)), s);

        if (!isShadow(primList, primNum, Ray(hp->getLocation(), l), distance)){
          pixelColor += diffuse + specular;
        }

        if (Ia.length() > ambient.length()){
          ambient = Ia * ka;
        }
      }

      pixelColor += ambient;

      //pixelColor = pixelColor/17.965782;            //Spheres
      //pixelColor = pixelColor/1.530942;             //Blue Sphere
      pixelColor = pixelColor/9.090648;             //Cornell Box

      pixelColor = pixelColor * (1.0 - hp->getMaterial()->getReflect());
      pixelColor += hp->getMaterial()->getReflect() * traceRay(
          Ray(hp->getLocation(), rDirection), 
          lights, 
          primList, 
          lightNum, 
          primNum, 
          pixelColor,
          iteration
          );

      //pixelColor = pixelColor * (1.0 - hp->getMaterial()->getTranslucent());
      //pixelColor += hp->getMaterial()->getTranslucent() * traceRay(
          //getTransRay(hp, vDirection),
          //lights,
          //primList,
          //lightNum,
          //primNum,
          //pixelColor,
          //iteration
          //);

      return pixelColor;
    }

    virtual Color getColor(
        Scene* scene,
        HitPoint* hp,
        Vector3 vDirection, 
        Light** lights, 
        Primitive** primList,
        int lightNum,
        int primNum
        ){
      Vector3 vColor = calculateColor(hp, vDirection, lights, primList, lightNum, primNum);
      Color color = Color(vColor[0], vColor[1], vColor[2]);
      return color;
    }

  protected:
    Ray getTransRay(HitPoint* hp, Vector3 vDirection){
      float cos1 = (-hp->getNormal()).dot(vDirection);
      float sin1 ;
    }

    bool isShadow(Primitive** primList, int primNum, Ray ray, float distance){
      for (int i = 0; i < primNum; i++){
        HitPoint HP = primList[i]->getHitPoint(ray);
        if (HP.getT() > 0 && HP.getT() < distance){
          return true;
        }
      }
      return false;
    }

    Vector3 traceRay(
        Ray ray,
        Light** lights, 
        Primitive** primList,
        int lightNum,
        int primNum,
        Vector3 curColor,
        int iteration
        ){
      HitPoint closestHP = HitPoint();
      Primitive* closestPrim = primList[0];
      float closestDis = -1;
      for (int i = 0; i < primNum; i++){
        HitPoint HP = primList[i]->getHitPoint(ray);
        if (HP.getT() > 0 && (HP.getT() < closestHP.getT() || closestHP.getT() <= 0)){
          closestHP = HP;
          closestPrim = primList[i];
        }
      }
      if (closestHP.getT() > -1){
        Vector3 retColor = closestPrim->getShader()->calculateColor(
            &closestHP,
            ray.getDirection(), 
            lights, 
            primList,
            lightNum,
            primNum,
            iteration + 1
            );
        return retColor;
      }
      else{
        return curColor;
      }
    }

    Color getReflectColor(
        HitPoint* hp,
        Vector3 vDirection, 
        Light** lights, 
        Primitive** primList,
        int lightNum,
        int primNum
        ){
    }

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
