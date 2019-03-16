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
#include <memory.h>

#define MAXSIZE 20      //存储空间初始分配量
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef int ElemType;   //ElemType类型根据实际情况而定，这里假设为int

/**
 * 定义线性表
 */
typedef struct{
    ElemType data[MAXSIZE]; //数组存储数据元素，最大值为MAXSIZE
    int length;     //线性表当前长度
}SqList;

/**
 * 初始化操作，建立一个空的线性表L
 */
Status InitList(SqList *L){
    memset(L, 0, sizeof(SqList));
    return OK;
}

//若线性表为空，返回true，否则返回false。
Status ListEmpty(SqList L){
    return L.length == 0 ;
}

//清空线性表
Status ClearList(SqList *L){
    InitList(L);
}

Status GetElem(SqList L, int i, ElemType *e){
    if(L.length == 0 || i < 0 || i > L.length)
        return ERROR;
    *e = L.data[i -1];
    return OK;
}
//在线性表L中查找与给定值e相等的元素，如果查找成功，返回该元素在表中序号表示成功；
//否则，返回0表示失败。
int LocateElem(SqList L, ElemType e){
    int i = 0;
    for(;i < L.length; i++){
        if(L.data[i] == e)
            return i+1;
    }

    return 0;
}

//在线性表L中的第i个位置插入新元素e。
Status ListInsert(SqList *L, int i, ElemType e){
    int k;
    if(L->length == MAXSIZE)    //线性表已满
        return ERROR;
    //插入位置不合理，这里可以直接可以添加到表尾，所以+1
    if(i < 1 || i > L->length + 1)
        return ERROR;
    if(i <= L->length){  //插入位置在中间，需要移动元素,插入的最后位置是+1处
        for ( k = L->length -1; k >= i - 1; k--) {
            L->data[k + 1] = L->data[k];
        }
    }

    L->data[i - 1] = e;
    L->length++;
    return OK;
}

//删除线性表L中第i个位置元素，并用e返回其值。
Status ListDelete(SqList *L, int i, ElemType *e){
    int k;
    if(L->length == 0) //线性表已空
        return ERROR;
    if(i < 0 || i > L->length)
        return ERROR;

    *e = L->data[i-1];
    if(i < L->length){  //删除的不是最后一个，此处区别与插入，最后位置是列表长度处
        for(k = i; k < L->length; k++ ){
            L->data[k-1] = L->data[k];
        }
    }

    L->length--;
    return OK;
}

//返回线性表L中的元素个数
int ListLength(SqList L){
    return L.length;
}

void printList(SqList L){
    int i;
    for(i = 0; i < L.length; i++){
        printf("%d ", L.data[i]);
    }
    printf("\n");
}

int main(){
    SqList myList;
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
