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
        if (lN.length() > 0){
          return lN;
        }
        else{
          return rN;
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
      //split(primList, primNum, dimens.maxComponent());
      splitSort(primList, 0, primNum-1, dimens.maxComponent());
      //printf("after sort");
      this->boundingBox = AABB(min, max);
    }

    void splitSort(Primitive** primList, int min, int max, int dimension){
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
        splitSort(primList, min, j, dimension);
      } 
      if (i < max){
        splitSort(primList, i, max, dimension);
      } 
    }

    void split(Primitive** primList, int primNum, int dimension){
      if (primNum <=1){
        return;
      }
      printf("getting pivot\n");
      int pivot = getPivot(primList, 0, primNum-1, primNum/2, dimension);
      printf("got pivot\n");
      int pivotVal = primList[pivot]->getCenter()[dimension];

      int i = 0;
      int j = primNum-1;

      swap(primList, pivot, (primNum-1)/2);

      while (i < j) {
        while (primList[i]->getCenter()[dimension] <= pivotVal){
          i++;
        }
        while (primList[j]->getCenter()[dimension] >= pivotVal){
          j--;
        }
        if (i < j){
          swap(primList, i, j);
        }
      }
    }

    int getPivot(Primitive** a, int s, int e, int k, int dimension){
      // if the partition length is less than or equal to 5
      // we can sort and find the kth element of it
      // this way we can find the median of n/5 partitions
      if(e-s+1 <= 5){
        halfSort(a, s, e, dimension);
        return s+k;
      }

      // if array is bigger 
      // we partition the array in subarrays of size 5
      // no. of partitions = n/5 = (e+1)/5
      // iterate through each partition
      // and recursively calculate the median of all of them
      // and keep putting the medians in the starting of the array
      for(int i=0; i<(e+1)/5; i++){
        int left = 5*i;
        int right = left + 4;
        if(right > e) right = e;
        int median = getPivot(a, 5*i, 5*i+4, 3, dimension);
        swap(a, median, i);
      }

      // now we have array 
      // a[0] = median of 1st 5 sized partition
      // a[1] = median of 2nd 5 sized partition
      // and so on till n/5
      // to find out the median of these n/5 medians
      // we need to select the n/10th element of this set (i.e. middle of it)
      return getPivot(a, 0, (e+1)/5, (e+1)/10, dimension);
    }

    int halfSort(Primitive** primList, int left, int right, int dimension){
      for (int i = left; i < right; i++){
        for (int j = i+1; j <= right; j++){
          if (primList[j]->getCenter()[dimension] < primList[i]->getCenter()[dimension]){
            swap(primList, i, j);
          }
        }
      }

      return (left+right)/2;
    }

    void swap(Primitive** primList, int x, int y){
      Primitive* temp = primList[x];
      primList[x] = primList[y];
      primList[y] = temp;
    }

};

#endif
