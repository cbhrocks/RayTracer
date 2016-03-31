#ifndef __BVHNODE
#define __BVHNODE

#include "AABB.h"
#include "../ray/Ray.h"
#include "../ray/HitPoint.h"
//#include "Splitter.h"
#include <math.h>

class BVHNode{
  public:
    BVHNode(){
      this->primitive = 0;
    }

    BVHNode(Primitive** primList, int primNum){
      this->primitive = 0;
      surround(primList, primNum);
      if (primNum == 1){
        this->primitive = primList[0];
      }
      else{
        int primHalf = primNum*0.5;
        this->leftNode = new BVHNode(primList, primHalf);
        if (primNum&1){
          this->rightNode = new BVHNode(&primList[primHalf], primHalf+1);
        }
        else{
          this->rightNode = new BVHNode(&primList[primHalf], primHalf);
        }
      }
    }

    HitPoint getHitPoint(Ray *ray){
      if (this->boundingBox.checkIntersect(ray)){
        if (this->primitive != 0){
          return this->primitive->getHitPoint(ray);
        }
        else{
          HitPoint lH = this->leftNode->getHitPoint(ray);
          HitPoint rH = this->rightNode->getHitPoint(ray);
          if (lH.getT() > 0 && (rH.getT() < 0 || lH.getT() < rH.getT())){
            return lH;
          }
          else{
            return rH;
          }
        }
      }
      else{
        return HitPoint();
      }
    }

    Vector3 getBoxNormal(Ray *ray, int depth){
      if (depth == 0 || this->primitive != 0){
        return this->boundingBox.checkIntersectNormal(ray);
      }
      else{
        Vector3 lN = this->leftNode->getBoxNormal(ray, depth-1);
        Vector3 rN = this->rightNode->getBoxNormal(ray, depth-1);
        if (rN.length() > 0){
          return rN;
        }
        else{
          return lN;
        }
      }
    }

  private:
    Primitive* primitive;
    BVHNode* leftNode;
    BVHNode* rightNode;
    AABB boundingBox;

    void surround(Primitive** primList, int primNum){
      Vector3 max = primList[0]->getMax();
      Vector3 min = primList[0]->getMin();
      for (int i = 1; i < primNum; i++){
        Vector3 primMax = primList[i]->getMax();
        Vector3 primMin = primList[i]->getMin();
        for (int j = 0; j < 3; j++){
          if (primMax[j] > max[j]){
            max[j] = primMax[j];
          }
          if (primMin[j] < min[j]){
            min[j] = primMin[j];
          }
        }
      }
      Vector3 dimens = Vector3(max[0] - min[0], max[1] - min[1], max[2] - min[2]);
      //printf("before sort");
      split(primList, 0, primNum-1, dimens.maxComponent());
      //printf("after sort");
      this->boundingBox = AABB(min, max);
    }

    void split(Primitive** primList, int min, int max, int dimension){
      int i = min;
      int j = max;
      Primitive* temp;
      float pivot = primList[(min + max) / 2]->getCenter()[dimension];

      while (i <= j) {
        while (primList[i]->getCenter()[dimension] < pivot){
          i++;
        }
        while (primList[j]->getCenter()[dimension] > pivot){
          j--;
        }
        if (i <= j){
          temp = primList[i];
          primList[i] = primList[j];
          primList[j] = temp;
          i++;
          j--;
        } 
      } 

      if (min < j){
        split(primList, min, j, dimension);
      } 
      if (i < max){
        split(primList, i, max, dimension);
      } 
    }
};

#endif
