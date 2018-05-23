#ifndef __SHADER
#define __SHADER

#include "../vector/GenVector.h"
#include "Material.h"
#include "../ray/HitPoint.h"
#include "../ray/Ray.h"
#include "../primitive/Primitive.h"
#include "../primitive/BVHNode.h"
#include "Light.h"
#include <math.h>

class Shader{
  public:
    Shader(){
    }

    virtual Vector3 calculateColor(
        HitPoint* hp,
        Light** lights, 
        BVHNode* tree,
        int lightNum,
        int primNum,
        int iteration = 0
        ){

      if (iteration >10){
        return Vector3(0,0,0);
      }

      Vector3 normal = hp->getNormal();
      Vector3 vDirection = -(hp->getRay()->getDirection());
      Vector3 rDirection = 2*(vDirection.dot(normal))*normal - vDirection;
      Vector3 pixelColor = Vector3(0,0,0);
      Vector3 kd = hp->getMaterial()->getDiffuseCoefficient();
      Vector3 ks = hp->getMaterial()->getSpecularCoefficient();
      Vector3 ka = hp->getMaterial()->getAmbientCoefficient();
      int s = hp->getMaterial()->getShine();

      for (int i = 0; i < lightNum; i++){
        Vector3 l = -lights[i]->getDirection(hp->getLocation());
        float distance = lights[i]->getLocation().distance(hp->getLocation());

        Vector3 Ia = lights[i]->getAmbientIntensity(distance);
        Vector3 ambient = Ia * ka;
        pixelColor += ambient;

        Ray shadowRay = Ray(hp->getLocation() + (normal * .001), l);
        if (!isShadow(tree, primNum, &shadowRay, distance)){

          Vector3 Id = lights[i]->getDiffuseIntensity(distance);
          Vector3 Is = lights[i]->getSpecularIntensity(distance);
          Vector3 lr = 2*(l.dot(normal))*normal - l;

          Vector3 diffuse = Id * kd * max(l.dot(normal), 0);
          Vector3 specular = Is * ks * pow(max(vDirection.dot(lr), 0), s);

          pixelColor += diffuse + specular;
        }
      }

      if (hp->getMaterial()->getReflect() > 0){
        pixelColor = pixelColor * (1 - hp->getMaterial()->getReflect());
        Ray refRay = Ray(hp->getLocation() + (normal * .001), rDirection);
        HitPoint refHP = tree->getHitPoint(&refRay);
        if (refHP.getT() > 0){
          pixelColor += hp->getMaterial()->getReflect() * refHP.getShader()->calculateColor(
              &refHP,
              lights, 
              tree,
              lightNum,
              primNum,
              iteration + 1
              );
        }
        else{
          pixelColor += Vector3(0,0,0);
        }
      }

      if (hp->getMaterial()->getTranslucent() < 1){
        pixelColor = pixelColor * hp->getMaterial()->getTranslucent();
        Ray transRay = getTransRay(hp);
        HitPoint transHP = tree->getHitPoint(&transRay);
        if (transHP.getT() > 0){
          pixelColor += (1 - hp->getMaterial()->getTranslucent()) * transHP.getShader()->calculateColor(
              &transHP,
              lights, 
              tree,
              lightNum,
              primNum,
              iteration + 1
              );
        }
        else{
          pixelColor += Vector3(0,0,0);
        }
      }

      return pixelColor;
    }

  protected:
    Ray getTransRay(HitPoint* hp){
      Vector3 vDirection = hp->getRay()->getDirection();
      float refractIn = hp->getRay()->getRefract();
      float refractOut = hp->getMaterial()->getRefract();

      if (refractIn == refractOut){
        refractOut = 1;
      }

      Vector3 rDirection = vDirection - 2*(vDirection.dot(hp->getNormal()))*hp->getNormal();
      float cos = (hp->getNormal()).dot(vDirection);
      float root = 1 - pow(refractIn, 2) * (1 - pow(cos, 2))/pow(refractOut, 2);

      if (root < 0){
        return Ray(
            hp->getLocation() + hp->getNormal() * (0.001), 
            vDirection - 2*(vDirection.dot(hp->getNormal()))*hp->getNormal(), 
            refractIn);
      }
      else{
        Vector3 first = (refractIn * (vDirection - hp->getNormal() * cos))/refractOut;
        return Ray(
            hp->getLocation() + hp->getNormal() * (-0.001), 
            (first - hp->getNormal() * sqrt(root)).normalize(), 
            refractOut
            );
      }
    }

    bool isShadow(BVHNode *tree, int primNum, Ray* ray, float distance){
      HitPoint hp = tree->getHitPoint(ray);
      if (hp.getT() > 0 && hp.getT() < distance){
        return true;
      }
      return false;
    }

    //Vector3 shadowColor(Primitive** primList, int primNum, Ray ray, float distance, Vector3 pixelColor){
      //Vector3 curColor = pixelColor;
      //if (primNum <= 0){
        //return Vector3(0,0,0);
      //}
      //HitPoint HP = primList[0]->getHitPoint(ray);
      //int i;
      //float t;
      ////printf("distance: %f\n", distance);
      //for (i = 1, t = HP.getT(); i < primNum && pixelColor.length() > 0; i++){
        //if (t < distance && t > 0 && HP.getMaterial()->getTranslucent() <= 1){
          ////printf("T: %f\n", t);
          //if (HP.getMaterial()->getTranslucent() > 1){
            //printf("T: %f\n", t);
            ////printf("mat name: %s\n", HP.getMaterial()->getName());
          //}
          ////printf("trans: %f\n", HP.getMaterial()->getTranslucent());
          ////curColor = curColor * (1 - HP.getMaterial()->getTranslucent());
        //}
        //HP = primList[i]->getHitPoint(ray);
      //}
      //return curColor;
    //}

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
