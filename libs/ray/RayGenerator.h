#ifndef __RAYGENERATOR
#define __RAYGENERATOR

#include "../vector/GenVector.h"
#include "Ray.h"
#include "../camera/Camera.h"

#include <math.h>

class RayGenerator{
  public:
    RayGenerator(){
      this->resX = 100;
      this->resY = 100;
      this->cam = Camera();
      this->left = this->cam.getLocation()[0] - this->resX/2;
      this->right = this->cam.getLocation()[0] + this->resX/2;
      this->bottom = this->cam.getLocation()[1] - this->resY/2;
      this->top = this->cam.getLocation()[1] + this->resY/2;
      this->distance = this->top;
    }

    RayGenerator(Camera camera, int resX, int resY, float FoV){
      this->resX = resX;
      this->resY = resY;
      this->left = this->cam.getDirection()[0] - this->resX/2;
      this->right = this->cam.getDirection()[0] + this->resX/2;
      this->bottom = this->cam.getDirection()[1] - this->resY/2;
      this->top = this->cam.getDirection()[1] + this->resY/2;
      this->distance = calculateDistance(FoV);
      //this->distance = 50;
      this->cam = camera;
    }

    Ray getRay(int i, int j){
      //double wLoc = this->cam.getLocation()[2] - this->distance;
      //double uLoc = this->cam.getLocation()[0] + this->left + (this->right - this->left) * (i + 0.5)/this->resX;
      //double vLoc = this->cam.getLocation()[1] + this->bottom + (this->top - this->bottom) * (j + 0.5)/this->resY;
      float scalarU = this->left + (this->right - this->left) * (i + 0.5)/this->resX;
      float scalarV = this->bottom + (this->top - this->bottom) * (j + 0.5)/this->resY;
      Vector3 s = this->cam.getLocation() + 
        scalarU * this->cam.getU() + 
        scalarV * this->cam.getV() - 
        this->distance*this->cam.getW();
      Vector3 rayDirection = s - this->cam.getLocation();
      Ray ray = Ray(this->cam.getLocation(), rayDirection.normalize());
      return ray;
    }

  private:
    int resX;
    int resY;
    float distance;
    int left;
    int right;
    int bottom;
    int top;
    float FoV;
    Camera cam;

    float calculateDistance(float FoV){
      float d = (this->resX/2)/tan(FoV/2);
      return d;
    }
};

#endif
