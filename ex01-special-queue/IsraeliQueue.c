#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "IsraeliQueue.h"



typedef struct node {
    void* value;
    int friendsEntered;
    int enemiesBlocked;
    struct node *next;
    struct node *previous;

} *Node;


struct IsraeliQueue_t{
    //friendship finction, comparesion. tresholds and head and tail
    FriendshipFunction *friendshipFunction;
    ComparisonFunction comparisonFunction;
    int friendship_th;
    int rivalry_th;
    Node head;
    Node tail;

};




IsraeliQueue IsraeliQueueCreate(FriendshipFunction* friendshipFunction, ComparisonFunction comparisonFunction, int friendship_th, int rivalry_th){

    if(friendshipFunction == NULL || comparisonFunction == NULL)
        return NULL;

    IsraeliQueue israeliQueue = malloc(sizeof(*israeliQueue));
    if (israeliQueue == NULL)
        return NULL;


    israeliQueue -> friendshipFunction = friendshipFunction;
    israeliQueue -> comparisonFunction = comparisonFunction;
    israeliQueue -> friendship_th = friendship_th;
    israeliQueue -> rivalry_th = rivalry_th;
    israeliQueue -> head = NULL;
    israeliQueue -> tail = NULL;

    printf("Created a new israeliQueue\n");
    return israeliQueue;

} //one


IsraeliQueueError IsraeliQueueEnqueue(IsraeliQueue israeliQueue, void * item){
    printf("Entered enq \n");
    if(israeliQueue==NULL || item==NULL){
        return ISRAELIQUEUE_BAD_PARAM;
    }

    Node newItem = malloc(sizeof *newItem);
    if (newItem == NULL){
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    newItem->value = item;
    newItem->friendsEntered = 0;
    newItem->enemiesBlocked = 0;


    if(israeliQueue -> head == NULL){
        israeliQueue->head = newItem;
        israeliQueue -> tail = israeliQueue -> head;
        printf("Enqueue SUCCESS First \n");
        return ISRAELIQUEUE_SUCCESS;
    }


    Node temp = israeliQueue -> head;
    while(temp != NULL ) {
        printf("Test 1 \n");
        if ((temp->friendsEntered < 5) && CheckStatus(israeliQueue, temp->value, item) == 1){
            printf("Test 2 \n");
            bool canPass = true;
            Node temp2 = temp;
            while (temp2 != NULL) {
                printf("Test 3 \n");
                if(temp2->enemiesBlocked < 3 && (CheckStatus(israeliQueue, temp2->value, item) == 2)){
                    printf("Test 4 \n");
                    temp2 -> enemiesBlocked++;
                    temp = temp2->next;
                    canPass = false;
                    break;
                }
                printf("Test 5 \n");
                temp2 = temp2->next;
            }

            if (canPass) {
                printf("Test 6 \n");
                temp->friendsEntered++;
                newItem->next = temp->next;
                newItem->previous = temp;
                temp->next = newItem;
                temp->next->previous = newItem;
                printf("Enqueue SUCCESS Passed \n");
                return ISRAELIQUEUE_SUCCESS;
            }

        }
        temp = temp->next;
        printf("Test 7 \n");

    }

    newItem->previous = israeliQueue -> tail;
    israeliQueue->tail->next=newItem;
    israeliQueue->tail = newItem;
    printf("Enqueue SUCCESS Last \n");
    return ISRAELIQUEUE_SUCCESS;
} //Two

IsraeliQueueError IsraeliQueueAddFriendshipMeasure(IsraeliQueue q, FriendshipFunction friendships_function){
    int friendshipFunctionLength = 0;
    FriendshipFunction *temp = q->friendshipFunction;
    while (temp != NULL){
        friendshipFunctionLength++;
        temp++;
    }

    FriendshipFunction *newFriendshipFunction=malloc(sizeof(*newFriendshipFunction)*(friendshipFunctionLength+2));
    if(newFriendshipFunction == NULL){
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    FriendshipFunction *temp2 = newFriendshipFunction;
    FriendshipFunction *temp1 = q->friendshipFunction;

    for (int i = 0; i < friendshipFunctionLength; i++){
        *temp2 = *temp1;
        temp2++;
        temp1++;
    }

    *temp2 = friendships_function;
    *(temp2+1) = NULL;
    
    q->friendshipFunction = newFriendshipFunction;
    return ISRAELIQUEUE_SUCCESS;
} //three

IsraeliQueueError IsraeliQueueUpdateFriendshipThreshold(IsraeliQueue israeliQueue, int newFriendshipTh)
{
    if( israeliQueue == NULL )
    {
        return ISRAELIQUEUE_BAD_PARAM;
    }

    israeliQueue->friendship_th = newFriendshipTh;
    return ISRAELIQUEUE_SUCCESS;
}// four


IsraeliQueueError IsraeliQueueUpdateRivalryThreshold(IsraeliQueue israeliQueue, int newRivalryTh)
{
    if( israeliQueue == NULL )
    {
        return ISRAELIQUEUE_BAD_PARAM;
    }


    israeliQueue->rivalry_th= newRivalryTh;
    return ISRAELIQUEUE_SUCCESS;
} //five

int IsraeliQueueSize(IsraeliQueue israeliQueue)
{
    if( israeliQueue == NULL )
    {
        return 0;
    }

    int size = 0;
    Node ptr = israeliQueue -> head;

    while(ptr != NULL)
    {
        size++;
        ptr = ptr -> next;
    }

    return size;
} //six

void* IsraeliQueueDequeue(IsraeliQueue israeliQueue)
{
    void* removedHead = israeliQueue -> head -> value;
    israeliQueue -> head = israeliQueue -> head -> next;
    return removedHead;
} //seven

bool IsraeliQueueContains(IsraeliQueue israeliQueue , void* item)
{
    if( israeliQueue == NULL || item == NULL )
    {
        return false;
    }

    Node ptr = israeliQueue -> head;

    while(ptr != NULL)
    {
        if (israeliQueue -> comparisonFunction(ptr->value , item))
        {
            return true;
        }
        ptr = ptr -> next;
    }
    return false;
} //eight

IsraeliQueueError IsraeliQueueImprovePositions(IsraeliQueue israeliQueue){

    if (israeliQueue == NULL)
        return ISRAELIQUEUE_BAD_PARAM;
    int lenOfFriends=0;
    FriendshipFunction  *tempFriendshipFunction = israeliQueue->friendshipFunction;
    while (tempFriendshipFunction!=NULL) {
        lenOfFriends++;
        tempFriendshipFunction++;
    }
    Node item = israeliQueue -> tail;
    while (item != NULL){
        Node temporary = item->previous;
        Node temp = israeliQueue->head;
        bool key = true;
        while(temp != item && key){
            for (int i = 0; i < lenOfFriends; i++) {
                if(temp->friendsEntered<5&&(israeliQueue->friendshipFunction[i](item->value,temp->value)) >
                                           israeliQueue->friendship_th){
                    bool canPass = true;
                    Node temp2 = temp->next;
                    while(temp2 != NULL){
                        int sum = 0, j=0;
                        while(j<lenOfFriends){
                            if (israeliQueue->friendshipFunction[j](item->value, temp2->value) > israeliQueue->friendship_th){
                                sum = israeliQueue ->friendship_th * j;
                                break;
                            }
                            sum += israeliQueue -> friendshipFunction[j](item, temp2->value);
                            j++;
                        }
                        if (sum / j < israeliQueue -> rivalry_th && temp2->enemiesBlocked< 3 ){
                            temp2 -> enemiesBlocked++;
                            temp = temp2->next;
                            canPass = false;
                            break;
                        }
                        temp2 = temp2->next;
                    }
                    if (canPass) {
                        temp->friendsEntered++;
                        item->next = temp->next;
                        item->previous = temp;
                        temp->next = item;
                        temp->next->previous = item;
                        key = false;
                        break;
                    }
                }
            }
            temp = temp->next;
        }
        item = temporary;
    }
    return ISRAELIQUEUE_SUCCESS;
} //Nine

IsraeliQueue IsraeliQueueMerge(IsraeliQueue* qarr,ComparisonFunction comparisonFunction){
    if(qarr == NULL || comparisonFunction == NULL)
        return NULL;
    IsraeliQueue* temp = qarr;
    int length = 0, friendshipSum = 0,rivalry = 1,friendshipsLength = 0;
    while(temp != NULL){
        friendshipSum += (*temp)->friendship_th;
        rivalry *= (*temp)->rivalry_th;
        length ++;
        temp++;
        FriendshipFunction *temp2 = (*temp)->friendshipFunction;
        while(temp2!= NULL){
            friendshipsLength++;
            temp2++;
        }
    }
    FriendshipFunction *friendshipFunction = malloc(sizeof(*friendshipFunction)*(friendshipsLength + 1));
    FriendshipFunction *temp2 = friendshipFunction;
    for (int j = 0; j < friendshipsLength; ++j){
        FriendshipFunction *temp1 = (*(qarr+j))-> friendshipFunction;
        while (temp1 != NULL){
            *temp2 = *temp1;
            temp2++;
            temp1++;
        }
    }
    temp2 = NULL;
    int friendship_th = ceil(friendshipSum/length);
    int rivalry_th = ceil(pow(rivalry,1/length));
    IsraeliQueue israeliQueue = IsraeliQueueCreate(friendshipFunction,comparisonFunction,friendship_th,rivalry_th);

    bool key = true;
    Node queuePtr = israeliQueue->head;
    queuePtr->previous = NULL;
    while(key){
        int remaining = length;

        for(int i = 0; i < length; i++){
            if (*(qarr+i) == NULL) {
                remaining--;
                continue;
            }

            queuePtr -> friendsEntered = (*(qarr+i))->head->friendsEntered;
            queuePtr -> enemiesBlocked = (*(qarr+i))->head->enemiesBlocked;
            queuePtr-> value= IsraeliQueueDequeue((*(qarr+i)));
            Node temp4 = queuePtr;
            queuePtr = queuePtr->next;
            queuePtr -> previous = temp4;
        }
        if (remaining == 0)
            key = false;
    }
    queuePtr->next = NULL;
    israeliQueue->tail = queuePtr;

    return israeliQueue;
} //Ten

IsraeliQueue IsraeliQueueClone(IsraeliQueue israeliQueue){
    if(israeliQueue == NULL){
        return NULL;
    }

    FriendshipFunction *friendshipFunction = israeliQueue->friendshipFunction;
    ComparisonFunction comparisonFunction = israeliQueue->comparisonFunction;
    int rivalry_th = israeliQueue->rivalry_th;
    int friendship_th = israeliQueue->friendship_th;
    IsraeliQueue newIsraeliQueue = IsraeliQueueCreate(friendshipFunction,comparisonFunction,friendship_th,rivalry_th);
    if(newIsraeliQueue == NULL)
        return NULL;

    Node temp1 = israeliQueue->head;
    Node temp2 = newIsraeliQueue->head;

    temp2->value= temp1->value;
    temp2->enemiesBlocked = temp1->enemiesBlocked;
    temp2->friendsEntered = temp1->friendsEntered;
    Node temp3 = temp2;
    temp2 = temp2->next;
    temp1 = temp1->next;
    temp2->previous = temp3;


    while (temp1 != NULL){
        temp2 -> value= temp1 -> value;
        temp2 -> enemiesBlocked = temp1 -> enemiesBlocked;
        temp2 -> friendsEntered = temp1 -> friendsEntered;
        temp2 = temp2 -> next;
        temp3 = temp3 -> next;
        temp2 -> previous= temp3;
        temp1 = temp1 -> next;
    }


    return newIsraeliQueue;
}// Eleven

void IsraeliQueueDestroy(IsraeliQueue israeliQueue)
{
    while(israeliQueue->head != NULL)
    {
        Node toDelete = israeliQueue -> head;
        israeliQueue -> head = israeliQueue -> head -> next;
        free(toDelete);
    }
    free(israeliQueue);
} //twelve

int CheckStatus(IsraeliQueue israeliQueue,void* item1,void*item2){
    printf("Test A1 \n");
    int lenOfFriends=0;
    FriendshipFunction *tempFriendshipFunction = israeliQueue->friendshipFunction[0];
    while (israeliQueue->friendshipFunction[lenOfFriends]!=NULL){
        printf("Test A2 \n");
        lenOfFriends++;
        printf("flen - %d \n",lenOfFriends);
    }

    int sum = 0, j=0;
    printf("Test A3 \n");
    for(int i = 0; i < lenOfFriends; i++){
        printf("Test A4 \n");
        if(israeliQueue->friendshipFunction[i](item1,item2) > israeliQueue->friendship_th) {
            printf("Friends \n");
            return 1;
        }
        sum += israeliQueue->friendshipFunction[i](item1,item2);
        j++;
        printf("Test A5 \n");
    }

    if(sum / j < israeliQueue->rivalry_th) {
        printf("Rivals \n");
        return 2;
    }

    return 0;
} //Helper Function that returns 1 if friends, 2 if rivals, and 0 if neutral

int comparison_function_mock(void *obj1, void *obj2) {
    int id1 = *(int *)obj1;
    int id2 = *(int *)obj2;

    return id1 - id2;
}

int mockfriendshipfunction(void* firstObject, void* secondObject){
    int temp = (*(int*)firstObject)+(*(int*)firstObject)+5;
    return temp;
}



int main(){
    int arr[]={1,2,3,4};
    FriendshipFunction functions[]={mockfriendshipfunction, NULL};
    IsraeliQueue queue=IsraeliQueueCreate(functions, comparison_function_mock, 100, 0);
    for (int i=0; i<4; i++){
        IsraeliQueueEnqueue(queue, &arr[i]);

    }
    IsraeliQueueAddFriendshipMeasure(queue, mockfriendshipfunction);
    IsraeliQueue p=IsraeliQueueClone(queue);
    IsraeliQueue j=IsraeliQueueClone(queue);
    IsraeliQueue m=IsraeliQueueClone(queue);
    IsraeliQueue s=IsraeliQueueClone(queue);
    IsraeliQueueDequeue(p);
    IsraeliQueueDequeue(p);
    IsraeliQueueDequeue(j);
    IsraeliQueueDequeue(j);
    IsraeliQueueDequeue(j);
    IsraeliQueueDequeue(m);

    IsraeliQueueImprovePositions(queue);

    IsraeliQueue f[]={queue, p, j, m, s , NULL};
    IsraeliQueue g=IsraeliQueueMerge(f, comparison_function_mock);
    IsraeliQueueDestroy(queue);


    return 0;
}

/* Check your IsraeliQueue g. It's supposed to be: start->4->3->4->2->1->3->4->3->2->2->4->3->1->4->end
*/