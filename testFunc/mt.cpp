#include <iostream>

void swap(int* primList, int x, int y){
  int temp = primList[x];
  primList[x] = primList[y];
  primList[y] = temp;
}

void halfSort(int* primList, int left, int right, int dimension){
  for (int i = left; i < right; i++){
    for (int j = i+1; j <= right; j++){
      if (primList[j] < primList[i]){
        swap(primList, i, j);
      }
    }
  }
}

// selects the median of medians in an array
int getPivot(int *a, int s, int e, int k, int dimension){
  // if the partition length is less than or equal to 5
  // we can sort and find the kth element of it
  // this way we can find the median of n/5 partitions
  if(e-s < 5){
    halfSort(a, s, e, dimension);
    return s+k-1;
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

void split(int* primList, int primNum, int dimension){
  if (primNum <= 1){
    return;
  }
  int pivot = getPivot(primList, 0, primNum-1, primNum/2, dimension);
  int pivotVal = primList[pivot];
  std::cout << "pivot val: " << pivotVal << "\n";

  int i = 0;
  int j = primNum-1;

  swap(primList, pivot, (primNum-1)/2);

  while (i < j) {
    while (primList[i] <= pivotVal){
      i++;
    }
    while (primList[j] >= pivotVal){
      j--;
    }
    if (i < j){
      swap(primList, i, j);
    }
  }
}

int main(){
  int a[9] = {6,3,5,4,2,77,1,9,8};
  int n = 9;

  //int mom = getPivot(a, 0, n-1, n/2);
  //std::cout << "Median of Medians: " << a[mom] << "\n";
  for (int i = 0; i < n; i++)
    std::cout << a[i] << " ";
  std::cout << "\n";

  split(a, n, 0);

  for (int i = 0; i < n; i++)
    std::cout << a[i] << " ";
  std::cout << "\n";

  return 0;
}
