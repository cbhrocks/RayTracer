#ifndef __RAYGENERATOR
#define __RAYGENERATOR

#include "../vector/GenVector.h"
#include "Ray.h"
#include "../primitive/Camera.h"

#include <math.h>

class RayGenerator{
  public:
    RayGenerator(Camera* camera){
      this->resX = 100;
      this->resY = 100;
      this->cam = camera;
      this->left = -this->resX/2;
      this->right = this->resX/2;
      this->bottom = -this->resY/2;
      this->top = this->resY/2;
      this->distance = this->top;
    }

    RayGenerator(Camera* camera, int resX, int resY, float FoV){
      this->resX = resX;
      this->resY = resY;
      this->cam = camera;
      this->distance = calculateDistance(FoV * M_PI/180);
      this->left = -this->resX/2;
      this->right = this->resX/2;
      this->bottom = -this->resY/2;
      this->top = this->resY/2;
    }

    Ray getRay(int i, int j){
      float scalarU = this->left + (this->right - this->left) * (i + 0.5)/this->resX;
      float scalarV = this->bottom + (this->top - this->bottom) * (j + 0.5)/this->resY;
      Vector3 s = this->cam->getLocation() + 
        scalarU * this->cam->getU() + 
        scalarV * this->cam->getV() - 
        this->distance*this->cam->getW();
      Vector3 rayDirection = (s - this->cam->getLocation()).normalize();
      Ray ray = Ray(this->cam->getLocation(), rayDirection);
      return ray;
    }

  private:
    int resX;
    int resY;
    float distance;
    float left;
    float right;
    float bottom;
    float top;
    float FoV;
    Camera *cam;

    float calculateDistance(float FoV){
      float d = (this->resX/2)/tan(FoV/2);
      return d;
    }
};

#endif
