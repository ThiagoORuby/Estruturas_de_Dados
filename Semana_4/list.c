#include <stdio.h>
#include <stdlib.h>

/*
DATA STRUCTURE: LISTs
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
        if(list[i++] == el) return 1;
    }
    return 0;
}

// return head
int head(int * list)
{
    return list[0];
}

// return tail
int tail(int * list)
{
    int i = 1, * aux = create_list();
    while(list[i] != '\e')
    {
        insert_end(aux, list[i++]);
    }
    return aux;
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

int * concatenate(int * list1, int * list2)
{
    int * aux = create_list();
    int i = 0, k = 0;

    while(list1[i] != '\e') insert_end(aux, list1[i++]);

    i = 0;
    while(list2[i] != '\e') insert_end(aux, list2[i++]);

    return aux;
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
void print_list(int * list)
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

// check a intersection of two lists
int * intersect(int * list1, int * list2)
{
    int * intersect = create_list();
    int i = 0;
    int * aux = concatenate(list1, list2);

    while(aux[i] != '\e')
    {
        if(isin(list1, aux[i]) && isin(list2, aux[i]))
        {
            if(! isin(intersect, aux[i])) insert_end(intersect, aux[i]);
        }
        i++;
    }

    free(aux);
    return intersect;
}


int main()
{
    int * list = create_list();
    int list2[6] = {3, 5, 2, 8, 9, '\e'};
    int aux;

    // set elements of list1
    while(scanf("%d", &aux) == 1){
        insert_end(list, aux);
    }

    // set elements of list2
    //while(scanf("%d", &aux) == 1){
    //    insert_end(list2, aux);
    //}

    printf("length of list1: %d\n", len(list));
    print_list(list);

    //printf("Removing all occurences of 23 from list1:\n");
    //remove_all(list, 23);
    //printarr(list);

    printf("Duplicates of list1:\n");
    has_duplicate(list);

    printf("Intersection of lists:\n");
    int * inter = intersect(list, list2);
    print_list(inter);

    free(list);
    free(inter);
    return 0;
}