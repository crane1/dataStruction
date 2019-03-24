/*****************************************************************************
     顺序栈实现
     栈的抽象数据类型
     ADT 栈（stack）
     Data
         同线性表。元素具有相同的类型，相邻元素具有前驱和后继关系。
     Operation
         InitStack(*S)： 初始化操作，建立一个空栈S。
         DestroyStack(*S): 若栈存在，则销毁它。
         ClearStack(*S)： 将栈清空。
         StackEmpty(S): 若栈为空，返回true，否则返回false。
         GetTop(S, *e): 若栈存在且非空，用e返回S的栈顶元素。
         Push(*S, e)： 若栈S存在，插入新元素e到栈S中并称为栈顶元素。
         Pop(*S, *e)： 删除栈S中栈顶元素，并用e返回其值。
         StackLength(S)： 返回栈S的元素个数。
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

/**
 * 定义顺序栈
 */
typedef int SElemType;  // SElemType类型根据实际情况而定，这里假设为int
typedef struct{
    SElemType data[MAXSIZE];
    int top;    //用于栈顶指针
}SqStack;

//初始化操作，建立一个空栈S
Status InitStack(SqStack *S){
    memset(S, 0, sizeof(SqStack));
    S->top = -1;
    return OK;
}

//若栈存在，则销毁它
Status DestroyStack(SqStack *S){
    S->top = -1;
    return OK;
}

//将栈清空
Status ClearStack(SqStack *S){
    return InitStack(S);
}

//若栈为空，返回true，否则返回false
int StackEmpty(SqStack S){
    return S.top == -1;
}

//若栈存在且非空，用e返回S的栈顶元素
Status GetTop(SqStack S, SElemType *e){
    if(S.top == -1){
        return ERROR;
    }
    *e = S.data[S.top];
    return OK;
}

//若栈S存在，插入新元素e到栈S中并称为栈顶元素
Status Push(SqStack *S, SElemType e){
    if(S->top == MAXSIZE - 1)//栈满
        return ERROR;
    S->top++;   //栈顶指针加1
    S->data[S->top] = e;    //将新元素插入给栈顶空间
    return OK;
}

//删除栈S中栈顶元素，并用e返回其值
Status Pop(SqStack *S, SElemType *e){
    if(S->top == -1)   //栈空
        return ERROR;
    *e = S->data[S->top];   //将要删除的栈顶元素赋值给e
    S->top--;   //将栈顶指针-1
    return OK;
}

//返回栈S的元素个数
int StackLength(SqStack S){
    return S.top + 1;
}

//自顶向下打印栈中元素
int printStack(SqStack S){
    if(S.top == -1){
        printf("栈已空！\n" );
    }
    int p = S.top;
    while(p != -1){
        printf("%d ", S.data[p]);
        p--;
    }
    printf("\n");
}

int printStackLength(SqStack S){
    printf("S length : %d\n", StackLength(S));
}


int main(){
    SqStack S;
    SElemType e;
    InitStack(&S);
    printStackLength(S);
    Push(&S, 1);
    Push(&S, 2);
    Push(&S, 3);
    printStackLength(S);
    printStack(S);
    Pop(&S, &e);
    printf("e: %d\n", e);
    printStack(S);
    Pop(&S, &e);
    printf("e: %d\n", e);
    printStack(S);
    Pop(&S, &e);
    printf("e: %d\n", e);
    printStack(S);
    Pop(&S, &e);
    printf("e: %d\n", e);
    printStack(S);
    Push(&S, 1);
    Push(&S, 2);
    Push(&S, 3);
    printStackLength(S);
    printStack(S);
    ClearStack(&S);
    printStackLength(S);
    printStack(S);
    return 0;
}
