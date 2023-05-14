#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXN 20
#define MAXM 20
#define GAPS 2

// Fila Estática
typedef struct queue{
    char * names[MAXN];
    int front;
    int rear;
    int gaps[MAXN];
} Queue;

Queue * create_queue()
{
    Queue * new = malloc(sizeof(Queue));

    // Inicializa index de inicio e fim
    new->front = -1;
    new->rear = -1;

    // tudo inicialmente é um gap
    memset(new->gaps, 1, sizeof(new->gaps));

    // Inicializa array de strings
    for(int i = 0; i < MAXN; i++)
    {
        new->names[i] = malloc(sizeof(char)*10);
        new->names[i][0] = '\0';
    }

    return new; 
}

int empty(Queue * queue)
{
    if(queue->rear == -1) return 1;
    return 0;
}

int full(Queue * queue)
{
    if(queue->rear == MAXN - 1) return 1;
    return 0;
}

int gaps_full(Queue * queue)
{
    int sum = 0;
    for(int i = 0; i <= queue->rear; i++)
        sum += queue->gaps[i];

    if(full(queue) && sum == 0) return 1;
    return 0;
}

// versão simples de enqueue
void enqueue(Queue * queue, char * name)
{
    if(full(queue)) return (void) printf("Fila cheia!\n");

    strcpy(queue->names[++(queue->rear)], name);
    queue->front = 0;
}

// versão simples de dequeue
char * dequeue(Queue * queue)
{
    char * name = malloc(sizeof(char)*MAXM);
    if(empty(queue))
    {
        printf("Fila vazia!\n");
        return "\0";
    }

    strcpy(name, queue->names[queue->front]);
    queue->front++;

    return name;
}

// book1 < book2 ?
int order_check(char * book1, char * book2, int i)
{
    if(i > strlen(book1)) return 1;
    if(i > strlen(book2)) return 0;
    if(tolower(book1[i]) < tolower(book2[i])) return 1;
    if(tolower(book1[i]) > tolower(book2[i])) return 0;
    if(tolower(book1[i]) == tolower(book2[i]))
        return order_check(book1, book2, i + 1); 
}

// pega o proximo indice da fila (nao vazio) de trás pra frente
int get_next_index(Queue * queue, int current)
{
    int index = current - 1;
    while(queue->gaps[index]) // enquanto for um buraco
    {
        index--;
        if(index < 0) return -1;
    }
    return index;
}

// empurra todos para frente se hover espaços
void push_all(Queue * queue, int index)
{
    int current = queue->rear;
    // primeiro com o rear
    while(current >= index)
    {
        if(current < MAXN - 1 && queue->gaps[current+1])
        {
            printf("Empurrando %s de %d para %d\n", queue->names[current], current, current + 1);
            strcpy(queue->names[current+1], queue->names[current]);
            if(current == queue->rear) queue->rear++;
            queue->gaps[current] = 1;
            queue->gaps[current+1] = 0;
        }

        current = get_next_index(queue, current);
    }
}

//try_add_begin(Queue * queue, char * name);

//try_add_end(Queue * queue, char * name);

// versão com gaps de enqueue
// enqueue ordenado por nomes
//TODO: quando a lista estiver full, analisar caso
void gaps_enqueue(Queue * queue, char * name)
{
    int index, len, gap_size, gap_index;

    // vê se o nome vem antes do primeiro da fila
    //try_add_begin(queue, name);
    // vê se o ultimo espaço está preenchido e o nome vem depois dele
    //try_add_end(queue, name);

    if(!gaps_full(queue)) // se nao tiver cheia
    {
        if(!empty(queue)) // se nao tiver vazia
        {
            printf("nao ta vazia\n");
            index = queue->rear;
            while(index >= 0)
            {
                if(order_check(queue->names[index], name, 0)) // se ultimo for menor que o novo
                {
                    printf("da pra adicionar no final!\n");
                    if(index == queue->rear) // se for adicionar no final
                    {
                        // calculando tamanho do gap
                        len = MAXN - queue->rear - 1;
                        gap_size = (len > GAPS) ? GAPS : len;

                        // adicionando novo nome
                        strcpy(queue->names[index + gap_size + 1], name);
                        queue->gaps[index + gap_size + 1] = 0; // nao é mais gap
                        queue->rear += gap_size + 1;

                        break;

                    }else // se nao, tenta achar um gap possível
                    {
                        printf("nao da pra adicionar no final!\n");
                        // checar se há gap vizinho a frente para adicionar
                        if(queue->gaps[index+1])
                        {
                            printf("achei um gap na frente!\n");
                            gap_index = index + 1;
                        }// checar se há gaps vizinhos atras para puxar
                        else if(index > 0 && queue->gaps[index-1])
                        {
                            printf("achei um gap atras\n");
                            // puxando para frente
                            strcpy(queue->names[index-1], queue->names[index]);
                            queue->gaps[index-1] = 0;
                            gap_index = index;
                        }// sair empurrando o resto da fila com base nos gaps 
                        else
                        {
                            printf("vou ter que empurrar!\n");
                            // empurra para ganhar uma espaço
                            while(!queue->gaps[index+1])
                                push_all(queue, index+1);
                            gap_index = index + 1;
                        }

                        // adiciona no gap encontrado
                        strcpy(queue->names[gap_index], name);
                        queue->gaps[gap_index] = 0; // informa que nao ha mais gap
                        break;
                    }
                }
                // tenta o proximo valor da fila de tras pra frente
                printf("pegando o proximo index!\n");
                index = get_next_index(queue, index);
            }
        }
        else // se tiver vazia
        {
            queue->gaps[0] = 0;
            return enqueue(queue, name);
        }
    }
}

// versão com gaps de dequeue
char * gaps_dequeue(Queue * queue)
{
    char * name = malloc(sizeof(char)*MAXM);
    if(empty(queue))
    {
        printf("Fila vazia!\n");
        return "\0";
    }

    queue->gaps[queue->front] = 1;
    strcpy(name, queue->names[queue->front]);
    queue->front++;
    queue->gaps[queue->front] = 0;

    return name;
}

void print_queue(Queue * queue)
{
    printf("( ");
    for(int i = queue->front; i <= queue->rear; i++)
    {
        if(queue->gaps[i]) printf("GAP, ");
        else printf("%s, ", queue->names[i]);
    }
    printf(")\n");
}

void print_queue_without_gaps(Queue * queue)
{
    printf("(");
    for(int i = queue->front; i <= queue->rear; i++)
    {
        if(!queue->gaps[i]) // se nao tiver gap na posição printa
        {
            printf("%s, ", queue->names[i]);
        }
    }
    printf(")\n");
}

int main(){
    int option;
    char nome[MAXM];
    Queue * queue = create_queue();

    printf("ESCOLHA UMA OPERACAO NA FILA:\n");
    
    printf("1. Adicionar\n2. Remover\n3. Parar\n");

    printf("Digite a opcao: ");
    
    while(scanf("%d", &option) == 1)
    {
        if(option == 3) break;
        switch(option)
        {
            case 1:
                printf("\nDigite o nome: ");
                scanf("%s", nome);
                gaps_enqueue(queue, nome);
                break;
            case 2:
                gaps_dequeue(queue);
                break;
        }

        print_queue(queue);

        printf("\n1. Adicionar\n2. Remover\n3. Parar\n");
        printf("Digite a opcao: ");
    }

    return 0;
}
