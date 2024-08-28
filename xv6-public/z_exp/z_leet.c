#include "stdio.h"
#include "z_cmp.c"

void main(int argc, char** argv) {
    int arr[] = {1,2,3};
    int l = sizeof(arr) / sizeof (arr[0]);
    for (int i = 0; i < l - 1; i ++) {
        int tmp = compare(arr[i], arr[i + 1]);
        printf("%d \n", tmp );
        printf("%d ", arr[i]);
    }
}