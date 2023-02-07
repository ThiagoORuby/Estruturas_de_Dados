#include <stdio.h>
#include <stdlib.h>

/*
DATA STRUCTURE: LIST
*/

#define MAXN 1000

// Create a list
int * create_list()
{
    int * list = malloc(MAXN * sizeof(int));
    list[0] = '\e';
    return list;
}

// Get list length
int len(int list[])
{
    int i = 0;
    while(list[i] != '\e') i++;
    return i;
}

// insert an element at the end of a list
int insert_end(int list[], int el)
{
    int pos = 0;
    while(list[pos] != '\e' && pos < 100) pos++;
    list[pos] = el;
    list[pos+1] = '\e';
    return 0;
}

// check is an element has in the list
int isin(int list[], int el){
    int i = 0;
    while(list[i] != '\e'){
        if(list[i] == el) return 1;
    }
    return 0;
}

// sort a list with bubblesort algorithm
void bubble_sort(int * list)
{
    int n = len(list), aux;

    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            if(list[i] > list[j]){
                aux = list[i];
                list[i] = list[j];
                list[j] = aux;
            }
        }
    }
}

// get a copy of a list
int * copy(int * list)
{
    int i = 0, * new = create_list(); 
    while(list[i] != '\e')
        insert_end(new, list[i++]);
    return new;
}

// check duplicates
int has_duplicate(int list[])
{
    int * new = copy(list), i = 0, end = 0, has = 0;
    bubble_sort(new);
    while(new[i] != '\e')
    {
        if(new[i] != new[end]){
            if(end - i > 1)
            {
                printf("The element %d has %d occurences\n", new[i], end - i);
                has = 1;
            }
            i = end;
            continue;
        }else{
            end++;
        }
    }
    if (!has){
        printf("This list has no duplicate elements\n");
        return 0;
    }
    free(new);
    return 1;
}

// print a list
void printarr(int * list)
{
    int i = 0;
    while(list[i] != '\e'){
        printf("%d ", list[i++]);
    }
    printf("\n");
    return;
}

// realloc array from a set position
void _reorder(int * list, int pos){
    while(list[pos] != '\e'){
        list[pos] = list[pos+1];
        pos++;
    }
    return;
}

// remove first occurence of an element
int remove_one(int * list, int ele)
{
    int i = 0, find = 0;
    while(list[i] != '\e')
    {
        if(list[i] == ele){
            find = 1;
            break;
        }
        i++;
    }
    if(find) _reorder(list, i);
    else printf("This element hasnt in the list\n");
    return find;
}

// remove all occurences of an element
int remove_all(int list[], int ele)
{
    int i = 0;
    while(list[i] != '\e'){
        if(list[i] == ele){
            _reorder(list, i);
        }
        i++;
    }
    return 1;
}


int main()
{
    int * list = create_list();
    int aux;

    while(scanf("%d", &aux) == 1){
        insert_end(list, aux);
    }

    printf("length: %d\n", len(list));
    printarr(list);

    printf("Removing all occurences of 23:\n");
    remove_all(list, 23);
    printarr(list);

    has_duplicate(list);
    printarr(list);

    free(list);
    return 0;
}