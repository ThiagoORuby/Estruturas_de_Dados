#include <stdio.h>


// check if the element is in the set
int isin(int el, int n, int set1[]){
    for(int i = 0; i < n; i++){
        if(set1[i] == el) return 1;
    }
    return 0;
}

// check max
int max(int n, int m){
    return n > m ? n : m;
}

// prin array
void printArr(int n, int arr[]){
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}


int uniao(int set1[], int n, int set2[], int m, int u[]){
    // initiliaze parameters
    int k = 0;
    int mx = max(n, m);
    // loop
    for(int i = 0; i < mx; i++){
        // i and j are equals
        if (set1[i % n] == set2[i % m]){
            if (!isin(set1[i % n], n, u)){
                u[k] = set1[i % n];
                k++;
            }
        }
        // i and j are differents
        if(set1[i % n] != set2[i % m]){
            if(!isin(set1[i % n], n, u)){
                u[k] = set1[i % n];
                k++;
            }
            if(!isin(set2[i % m], m, u)){
                u[k] = set2[i % m];
                k++;
            }
        }
    }
    return k;
}

int intersecao(int set1[], int n, int set2[], int m, int it[]){
    // initiliaze parameters
    int k = 0;
    // loop
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            // compare two values in the sets
            if(set1[i] == set2[j]){
                if (!isin(set1[i], n, it)){
                    it[k] = set1[i];
                    k++;
                }
            }
        }
    }

    return k;
}

int complemento(int set1[], int n, int set2[], int m, int cp[]){
    // check if has intersection
    int k = 0;
    int it[10000];
    if (!intersecao(set1, n, set2, m, it)) return -1;
    // loop
    for(int i = 0; i < n; i++){
        // compare two values in the sets
        if (!isin(set1[i], n, set2)){
            cp[k] = set1[i];
            k++;
        }
    }
    return k;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);

    int set1[n], set2[m];
    int u[10000], it[10000], cp[10000];
    
    // scan set1
    for(int i = 0; i < n; i++){
        scanf("%d", &set1[i]);
    }
    // scan set2
    for(int i = 0; i < m; i++){
        scanf("%d", &set2[i]);
    }
    
    int len1 = uniao(set1, n, set2, m, u);
    int len2 = intersecao(set1, n, set2, m, it);
    int len3 = complemento(set1, n, set2, m, cp);

    printf("\n");
    printArr(len1, u);
    printArr(len2, it);
    if (len3 != -1) printArr(len3, cp);
    else printf("Não tem complemento\n");
    printf("\n");
    return 0;
}