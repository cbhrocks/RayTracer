#ifndef __BVHTREE
#define __BVHTREE

#include "../vector/GenVector.h"
#include "../ray/HitPoint.h"
#include "BVHNode.h"
#include "Primitive.h"

class BVHTree{
  public:
    BVHTree(){
    }

    BVHTree(Primitive** primList, int primNum){
      this->root = new BVHNode(primList, primNum);
    }

    void buildTree(Primitive** primList, int primNum){
      printf("creating tree, primNum: %d\n", primNum);
      this->root = new BVHNode(primList, primNum);
    }

    HitPoint getHitPoint(Ray ray){
      return root->getHitPoint(ray);
    }

  private:
    BVHNode* root;
};

#endif
