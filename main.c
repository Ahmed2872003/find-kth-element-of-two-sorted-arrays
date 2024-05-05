#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>

void scanArr(int*, int);
void printArr(int*, int);

// Algorithm 1
void merge(int*, int, int*, int, int*);
int find_kth_elem_alg1(int*, int, int*,int, int);
// Algorithm 2
int find_kth_elem_alg2(int*, int, int*, int, int);
int find_kth_elem_alg2_src(int*, int, int*, int, int, int , int);



int main(){
    int s1 = 0, s2 = 0, k = 0;
    int result;
    char c = '\0';

    printf("Enter Array1 and Array2 size respectivly: ");
    scanf("%d%d", &s1, &s2);

    int arr1[s1], arr2[s2];

    if(s1 > 0){
        printf("Array1 With (%d) sorted Elements: ", s1);
        scanArr(arr1, s1);
    }
    if(s2 > 0){
        printf("Array2 With (%d) sorted Elements: ", s2);
        scanArr(arr2, s2);
    }
    
    printf("K = ");
    scanf("%d", &k);

    getchar();
    printf("1- find kth element using merge.\n");
    printf("2- find kth element using binary search.\n");

    printf("Choose an algorithm: ");
    scanf("%c", &c);

    switch (c)
    {
        default:
        case '1':
            result = find_kth_elem_alg1(arr1, s1, arr2, s2, k);
            break;
        case '2':
            result = find_kth_elem_alg2(arr1, s1, arr2, s2, k);
            break;

    } 

    printf("%d\n", result);

    return 0;
}



// Algorithm (1)
int find_kth_elem_alg1(int* arr1, int s1, int* arr2, int s2, int k){

    assert(k >= 1 && k <= s1 + s2);
    assert(s1 >= 0 && s2 >= 0);

    int result;
    int* mergedArr = (int*) malloc((s1 + s2) * sizeof(int));

    merge(arr1, s1, arr2, s2, mergedArr);

    result = mergedArr[k - 1];

    free(mergedArr);

    return result;
}
void merge(int* arr1, int s1, int* arr2, int s2, int* mergedArr){
    int ind1 = 0, ind2 = 0, i = 0;

    while(ind1 < s1 && ind2 < s2){
        if(arr1[ind1] <= arr2[ind2]){
            mergedArr[i] = arr1[ind1];
            ind1++;
        }else{
            mergedArr[i] = arr2[ind2];
            ind2++;
        }
        i++;
    }

    while(ind1 < s1){
        mergedArr[i] = arr1[ind1];
        ind1++;
        i++;
    }
    while(ind2 < s2){
        mergedArr[i] = arr2[ind2];
        ind2++;
        i++;
    }
}


// Algorithm (2)
int find_kth_elem_alg2(int* arr1, int s1, int* arr2, int s2, int k){
     
     assert(k >= 1 && k <= s1 + s2);
     assert(s1 >= 0 && s2 >= 0);


     if(s1 > s2) {
        return find_kth_elem_alg2(arr2, s2, arr1, s1, k); 
    }

    if(!s1 && s2) return arr2[k - 1];

    int low = fmax(0,k-s2-1), high = fmin(k,s1);

    return find_kth_elem_alg2_src(arr1, s1, arr2, s2, k, low, high);
}

int find_kth_elem_alg2_src(int* arr1, int s1, int* arr2, int s2, int k, int l, int h){

    if(l <= h){

        int cut1 = (l + h) / 2;
        int cut2 = k - cut1 - 2;
        int l1 = arr1[cut1];
        int l2 = cut2 >= 0 ? arr2[cut2] : INT_MIN;
        int r1 = cut1 + 1 < s1 ? arr1[cut1 + 1] : INT_MAX;
        int r2 = cut2 + 1 < s2 ? arr2[cut2 + 1] : INT_MAX;

        if(l1 <= r2 && l2 <= r1) {
            return fmax(l1, l2);
        }
        else if (l1 > r2) 
            return find_kth_elem_alg2_src(arr1, s1, arr2, s2, k, l, cut1 - 1);
        else 
            return find_kth_elem_alg2_src(arr1, s1, arr2, s2, k, cut1 + 1, h);

    }
    return arr2[k - 1];
}

void scanArr(int* arr, int size){

    for(int i = 0 ; i < size ; i++) scanf("%d", &arr[i]);
}

void printArr(int* arr, int size){


    printf("[");

    for(int i = 0 ; i < size ; i++){
        printf(" %d", arr[i]);

        if(i != size - 1) printf(",");
    }

    printf(" ]\n");
}

