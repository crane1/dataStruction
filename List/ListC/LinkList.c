/*****************************************************************************
     顺序线性表实现
     线性表的抽象数据类型
     ADT 线性表（List）
     Data
         线性表的数据对象集合为{a1,a2,...,an}，每个元素的类型均为DataType。其中，除第一个元素a1外，每一个元素有且只有一个直接前驱元素，除了最后一个元素an外，每一个元素有且只有一个直接后继元素。数据元素之间的关系时一对一的关系。
     Operation
         InitList(*L)： 初始化操作，建立一个空的线性表L。
         ListEmpty(L):  若线性表为空，返回true，否则返回false。
         ClearList(*L): 将线性表清空。
         GetElem(L, i, *e)： 将线性表L中的第i个位置元素值返回给e。
         LocateElem(L, e): 在线性表L中查找与给定值e相等的元素，如果查找成功，返回该元素在表中序号表示成功； 否则，返回0表示失败。
         ListInsert(*L, i, e): 在线性表L中的第i个位置插入新元素e。
         ListDelete(*L, i, *e): 删除线性表L中第i个位置元素，并用e返回其值。
         ListLength(L): 返回线性表L中的元素个数
     endADT
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef int ElemType;   //ElemType类型根据实际情况而定，这里假设为int

/**
 * 定义结点
 */
typedef struct Node{
    ElemType data;  //数据域
    struct Node *next;  //后继元素
}Node;

typedef struct Node *LinkList;  //定义线性链表

/**
 * 初始化操作，建立一个空的线性表L
 */
Status InitList(LinkList *L){
    *L = (LinkList)malloc(sizeof(Node)); //生成一个新结点
    if(*L == NULL){
        printf("InitList malloc faild!");
        return ERROR;
    }
    (*L)->next = NULL;
    return OK;
}

//若线性表为空，返回true，否则返回false。
Status ListEmpty(LinkList L){
    return L->next == NULL ? OK : ERROR ;
}

//清空线性表
Status ClearList(LinkList *L){
    LinkList p, q;
    if(L == NULL){
        printf("ClearList NULL point!");
        return ERROR;
    }
    p = (*L)->next; //p作为移动指针
    while(p){   //没到表尾
        q = p->next;
        free(p);
        p = q;
    }
    (*L)->next = NULL;  //头结点指针域为空
    return OK;
}

//获取第i个元素
Status GetElem(LinkList L, int i, ElemType *e){
    LinkList p;
    int j;
    if(L == NULL || L->next == NULL){
        printf("GetElem NULL point!");
        return ERROR;
    }

    j = 1;
    p = L->next;

    //没到第i个指针后移
    while(p && j < i){
        p = p->next;
        ++j;
    }

    if(!p || j > i){    //当i<1时 j>i条件成立
        return ERROR;
    }
    *e = p->data;   //取第i个结点的数据
    return OK;
}
//在线性表L中查找与给定值e相等的元素，如果查找成功，返回该元素在表中序号表示成功；
//否则，返回0表示失败。
int LocateElem(LinkList L, ElemType e){
    LinkList p;
    int j;
    if(L == NULL || L->next == NULL){
        printf("LocateElem NULL point!");
        return 0;
    }

    j = 1;
    p = L->next;

    //没找到到元素e指针后移
    while(p){
        if(p->data == e){
            return j;
        }
        p = p->next;
        ++j;
    }
    return 0;
}

//在线性表L中的第i个位置插入新元素e。
Status ListInsert(LinkList *L, int i, ElemType e){
    LinkList p, q;
    int j;
    if(L == NULL){
        printf("ListInsert NULL point!");
        return ERROR;
    }

    j = 1;
    p = *L;

    //没到第i个指针后移
    while(p && j < i){
        p = p->next;
        ++j;
    }
    if(!p || j > i){    //当i<1时 j>i条件成立
        return ERROR;
    }

    q = (LinkList)malloc(sizeof(Node)); //生成新结点
    q->data = e;
    q->next = p->next;  //把p的后继给新生成元素的后继
    p->next = p;    //把新生成元素作为p的后继
    printf("ListInsert %d!", e);
    return OK;
}

//删除线性表L中第i个位置元素，并用e返回其值。
Status ListDelete(LinkList *L, int i, ElemType *e){
    LinkList p, q;
    int j;
    if(L == NULL){
        printf("ListDelete NULL point!");
        return ERROR;
    }

    j = 1;
    p = *L;

    //没到第i个指针后移
    while(p->next && j < i){
        p = p->next;
        ++j;
    }
    if(!(p->next) || j > i){    //当i<1时 j>i条件成立
        return ERROR;
    }

    q = p->next;    //把要删除的元素保存起来
    p->next = q->next;  //链表跳过要删除的元素链接下一个
    *e = q->data;    //取出要删除元素的数据域
    free(q);    //释放要删除的元素
    return OK;
}

//返回线性表L中的元素个数
int ListLength(LinkList L){
    LinkList p;
    int j;
    if(L == NULL){
        printf("ListLength NULL point!");
        return 0;
    }

    j = 0;
    p = L;

    //没到第i个指针后移
    while(p->next){
        p = p->next;
        ++j;
    }
    return j;
}

void printList(LinkList L){
    LinkList p;
    int j;
    if(L == NULL){
        printf("ListLength NULL point!");
        return ;
    }

    p = L->next;

    while(p){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main(){
    LinkList myList;
    Status res = OK;
    ElemType e;

    res = InitList(&myList);
    printf("InitList is %d\n", res);
    res = ListEmpty(myList);
    printf("myList is empty: %d\n", res);
    res = ListLength(myList);
    printf("ListLength is %d\n", res);
    ListInsert(&myList, 1, 1);
    printList(myList);
    ListInsert(&myList, 1, 2);
    printList(myList);
    ListInsert(&myList, 1, 3);
    printList(myList);
    ListInsert(&myList, 1, 4);
    printList(myList);
    ListDelete(&myList, 1, &e);
    printList(myList);
    LocateElem(myList, 4);
    GetElem(myList, 2, &e);
    printf("GetElem e:%d\n", e);
    ClearList(&myList);
    printList(myList);
}
