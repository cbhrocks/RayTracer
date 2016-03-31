#ifndef __SPLITTER
#define __SPLITTER

#include "Primitive.h"

class Splitter{
  public:
    //uses quicksort to sort the list
    static void split(Primitive** primList, int min, int max, int dimension){
      int i = min;
      int j = max;
      Primitive* temp;
      Primitive* pivot = primList[(min + max) / 2];

      while (i <= j) {
        while (primList[i]->getCenter()[dimension] < pivot->getCenter()[dimension]){
          i++;
        }
        while (primList[j]->getCenter()[dimension] < pivot->getCenter()[dimension]){
          j--;
        }
        if (primList[i]->getCenter()[dimension] <= primList[j]->getCenter()[dimension]){
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
