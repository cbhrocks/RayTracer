#include <iostream>


void swap(int* primList, int x, int y){
  int temp = primList[x];
  primList[x] = primList[y];
  primList[y] = temp;
}

int medianOfFive(int* primList, int left, int right, int dimension){
  for (int i = left; i < (left + right)/2; i++){
    for (int j = i+1; j <= right; j++){
      if (primList[j] < primList[i]){
        swap(primList, i, j);
      }
    }
  }

  return (left+right)/2;
}

int getPivot(int* primList, int left, int right, int dimension){
  if (right  - left < 5){
    return medianOfFive(primList, left, right, dimension);
  }

  for (int i = left; i <= right; i += 5){
    int subRight = i+4;
    if (subRight > right){
      subRight = right;
    }

    int median5 = medianOfFive(primList, i, subRight, dimension);
    swap(primList, median5, left + (i-left)/5);
  }

  return getPivot(
      primList,
      left,
      left + (right - left)/5,
      dimension);
}

void split(int* primList, int primNum, int dimension){
  int pivot = getPivot(primList, 0, primNum-1, dimension);
  int pivotVal = primList[pivot];

  std::cout << pivotVal << "\n";

  int i = 0;
  int j = primNum-1;

  for (int i = 0; i < primNum; i++)
    std::cout << primList[i] << " ";
  std::cout << "\n";

  swap(primList, pivot, (primNum-1)/2);

  int iSteps = 0;
  int jSteps = 0;

  for (int i = 0; i < primNum; i++)
    std::cout << primList[i] << " ";
  std::cout << "\n";

  while (i < j) {
    while (primList[i] <= pivotVal){
      i++;
      iSteps++;
    }
    while (primList[j] >= pivotVal){
      j--;
      jSteps++;
    }
    if (i < j){
      swap(primList, i, j);
      //i++;
      //j--;
      iSteps++;
      jSteps++;
    }
  }
  //printf("primNum: %d,\n number of steps; i: %d, j: %d\n", primNum, iSteps, jSteps);
}

int main(){
  int a[] = {6,7,8,1,2,3,4,5,9,10};
  int n = 10;

  int m5loc = medianOfFive(a, 0, 4, 0);
  std::cout << "medianOfFive: " << a[m5loc] << "\n";

  split(a, 10, 1);
  for (int i = 0; i < n; i++) 
    std::cout << a[i] << " ";
  std::cout << "\n";
  //printf("median of medians: %d", mom);
  return 0;
}
