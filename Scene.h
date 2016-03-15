#ifndef __SCENE
#define __SCENE

#include "libs/vector/GenVector.h"
#include "libs/png/simplePNG.h"
#include "libs/objLoad/objLoader.h"
#include "libs/ray/Ray.h"
#include "libs/ray/RayGenerator.h"
#include "Buffer.h"
#include "libs/primitive/Camera.h"
#include "libs/primitive/Sphere.h"
#include "libs/primitive/Triangle.h"
#include "libs/shading/Light.h"
#include "libs/shading/AmbientLight.h"
#include "Scene.h"

#include <math.h>

class Scene{
  public:
    Scene(int sphereNum, int triangleNum, int lightNum){
      this->sphereList = new Sphere[sphereNum];
      this->triangleList = new Triangle[triangleNum];
      this->lightPointerList = new Light*[lightNum];
      this->primPointerNum = sphereNum + triangleNum;
      this->primPointerList = new Primitive*[primPointerNum];
      this->sphereLoc = 0;
      this->triangleLoc = 0;
      this->primLoc = 0;
      this->lightLoc = 0;
    }

    void addSphere(Vector3 location, Vector3 up, Vector3 direction){
      this->sphereList[this->sphereLoc] = Sphere(location, up, direction);
      this->primPointerList[this->primLoc++] = &this->sphereList[sphereLoc++];
    }

    void addTriangle(Vector3 v1, Vector3 v2, Vector3 v3){
      this->triangleList[this->triangleLoc] = Triangle(v1, v2 ,v3);
      this->primPointerList[this->primLoc++] = &this->triangleList[triangleLoc++];
    }

    void addCamera(Vector3 location, Vector3 look, Vector3 up){
      this->camera = Camera(location, look, up);
    }

    void setAmbientLight(float intensity){
      this->ambientLight = AmbientLight(intensity);
      this->lightPointerList[lightLoc++] = &ambientLight;
    }

    Camera getCamera(){
      return this->camera;
    }

    HitPoint traceRay(Ray ray){
      HitPoint closestHP = HitPoint();
      float closestDis = -1;
      for (int i = 0; i < this->primPointerNum; i++){
        HitPoint HP = this->primPointerList[i]->getHitPoint(ray);
        if (HP.getT() > 0 && (HP.getT() < closestHP.getT() || closestHP.getT() < 0)){
          closestHP = HP;
        }
      }
      return closestHP;
    }

  private:
    int sphereLoc;
    int triangleLoc;
    int primLoc;
    int lightLoc;
    int primPointerNum;

    Camera camera;
    Triangle *triangleList;
    Sphere *sphereList;
    Primitive **primPointerList;
    AmbientLight ambientLight;
    Light **lightPointerList;

};

#endif
