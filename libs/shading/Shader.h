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

class Shader{
  public:
    Shader(){
    }

    virtual Vector3 calculateColor(
        HitPoint* hp,
        Light** lights, 
        Primitive** primList,
        int lightNum,
        int primNum,
        int iteration = 0
        ){
      if (iteration >10){
        return Vector3(0,0,0);
      }
      Vector3 vDirection = hp->getRay()->getDirection();
      Vector3 rDirection = (vDirection - 2*(vDirection.dot(hp->getNormal()))*hp->getNormal()).normalize();
      Vector3 pixelColor = Vector3(0,0,0);
      Vector3 ambient;
      Vector3 kd = hp->getMaterial()->getDiffuseCoefficient();
      Vector3 ks = hp->getMaterial()->getSpecularCoefficient();
      Vector3 ka = hp->getMaterial()->getAmbientCoefficient();
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

        pixelColor += diffuse + specular;

        //pixelColor = shadowColor(
            //primList, 
            //primNum, 
            //Ray(hp->getLocation() + (hp->getNormal() * .001), l), 
            //distance,
            //pixelColor
            //);
        
        if (!isShadow(primList, primNum, Ray(hp->getLocation() + (hp->getNormal() * .001), l), distance)){
          pixelColor += diffuse + specular;
        }

        if (Ia.length() > ambient.length()){
          ambient = Ia * ka;
        }
      }

      pixelColor += ambient;

      if (hp->getMaterial()->getReflect() > 0){
        pixelColor = pixelColor * (1 - hp->getMaterial()->getReflect());
        pixelColor += hp->getMaterial()->getReflect() * traceRay(
            Ray(hp->getLocation(), rDirection), 
            lights, 
            primList, 
            lightNum, 
            primNum, 
            pixelColor,
            iteration
            );
      }

      if (hp->getMaterial()->getTranslucent() < 1){
      pixelColor = pixelColor * hp->getMaterial()->getTranslucent();
      pixelColor += (1 - hp->getMaterial()->getTranslucent()) * traceRay(
          getTransRay(hp, vDirection),
          lights,
          primList,
          lightNum,
          primNum,
          pixelColor,
          iteration
          );
      }

      return pixelColor;
    }

    virtual Vector3 getColor(
        HitPoint* hp,
        Light** lights, 
        Primitive** primList,
        int lightNum,
        int primNum
        ){
      Vector3 vColor = calculateColor(hp, lights, primList, lightNum, primNum);
      Color color = Color(vColor[0], vColor[1], vColor[2]);
      return vColor;
    }

  protected:
    Ray getTransRay(HitPoint* hp, Vector3 vDirection){
      float refractIn = hp->getRay()->getRefract();
      float refractOut = hp->getMaterial()->getRefract();
      if (refractIn == refractOut){
        refractOut = 1;
        //printf("SET OUT TO !\n");
      }

      Vector3 rDirection = (vDirection - 2*(vDirection.dot(hp->getNormal()))*hp->getNormal()).normalize();
      float cos = -(hp->getNormal()).dot(vDirection);
      float root = 1 - pow(refractIn, 2) * (1 - pow(cos, 2))/pow(refractOut, 2);

      if (root < 0){
        //printf("return reflect\n");
        return Ray(hp->getLocation() + hp->getNormal() * (-0.001), rDirection, refractIn);
        //return Ray(hp->getLocation() + vDirection * (0.001), rDirection, refractIn);
      }
      else{
        Vector3 first = (refractIn * (vDirection + hp->getNormal() * cos))/refractOut;
        //return Ray(hp->getLocation() + hp->getNormal()*(-0.001), first - hp->getNormal() * sqrt(root), refractOut); 
        return Ray(hp->getLocation() + vDirection*(0.001), first - hp->getNormal() * sqrt(root), refractOut); 
      }
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

    Vector3 shadowColor(Primitive** primList, int primNum, Ray ray, float distance, Vector3 pixelColor){
      Vector3 curColor = pixelColor;
      if (primNum <= 0){
        return Vector3(0,0,0);
      }
      HitPoint HP = primList[0]->getHitPoint(ray);
      int i;
      float t;
      //printf("distance: %f\n", distance);
      for (i = 1, t = HP.getT(); i < primNum && pixelColor.length() > 0; i++){
        if (t < distance && t > 0 && HP.getMaterial()->getTranslucent() <= 1){
        //printf("T: %f\n", t);
          if (HP.getMaterial()->getTranslucent() > 1){
        printf("T: %f\n", t);
            //printf("mat name: %s\n", HP.getMaterial()->getName());
          }
        //printf("trans: %f\n", HP.getMaterial()->getTranslucent());
          //curColor = curColor * (1 - HP.getMaterial()->getTranslucent());
        }
        HP = primList[i]->getHitPoint(ray);
      }
      return curColor;
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
