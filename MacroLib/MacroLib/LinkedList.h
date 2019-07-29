#pragma once

#include "Node.h"

struct LinkedList {
	Node *head;
	Node *tail;
	int count;
};
typedef struct LinkedList LinkedList;

// ��l�����
#define initLinkedList(list) \
    list.head = NULL;        \
    list.tail = NULL;        \
    list.count = 0;

// �إߨê�l�����
#define createLinkedList(name) \
    LinkedList name;           \
    initLinkedList(name)

// �P�_���O�_����
#define isLinkedListEmpty(list) \
    list.count == 0


// ���ʪ��Y��a�}
#define moveHandToNodeAddress(list, nodeAddress) \
    list.head = nodeAddress;

// �a�}���V���Y
#define nodeLinkToHandByNodeAddress(list, nodeAddress) \
     nodeAddress->next = list.head;

// �a�}�s�����Y
#define pushFrontByNodeAddress(list, nodeAddress)  \
    nodeLinkToHandByNodeAddress(list, nodeAddress) \
    moveHandToNodeAddress(list, nodeAddress)       \
    list.count++;


// ���ʪ����a�}
#define moveTailToNodeAddress(list, nodeAddress) \
    list.tail = nodeAddress;

// �a�}�s������
#define nodeLinkToTailByNodeAddress(list, nodeAddress) \
     nodeAddress->next = list.tail;

// ����s����a�}
#define pushBackByNodeAddress(list, nodeAddress)   \
    nodeLinkToTailByNodeAddress(list, nodeAddress) \
    moveTailToNodeAddress(list, nodeAddress)       \
    list.count++;


// 
#define pushFrontByNodeAddress_Safe(list, nodeAddress) \
    pushFrontByNodeAddress(list, nodeAddress)          \
    if (isLinkedListEmpty(list)) {                     \
        moveTailToNodeAddress(list, nodeAddress)       \
    }

// 
#define pushBackByNodeAddress_Safe(list, nodeAddress) \
    pushBackByNodeAddress(list, nodeAddress)          \
    if (isLinkedListEmpty(list)) {                    \
        moveHandToNodeAddress(list, nodeAddress)      \
    }

//
#define pushFrontByNewNodeByNode(list, newNodeName, node) \
    newNodeByNode(newNodeName, node);                     \
    pushFrontByNodeAddress_Safe(list, newNodeName);

//
#define pushFrontByNewNodeByValue(list, newNodeName, value) \
    newNodeByValue(newNodeName, value)                      \
    if(newNodeName){ pushFrontByNodeAddress_Safe(list, newNodeName); }

//
#define pushFrontByNode(list, node) \
    pushFrontByNodeAddress_Safe(list, &node);

//
#define pushFrontByValue(list, value) \
    pushFrontByNewNodeByValue(list, uniqueVarName(macroNodeTempVar), value)

//
#define travelLinkedList(list, currentNodeName, ...)      \
    loop(list.count){                                     \
        __VA_ARGS__                                       \
        moveToNextNodeByNodeAddress_Safe(currentNodeName) \
    }

//
#define freeLinkedList_template(list, tmp1, tmp2)     \
    Node *tmp1 = list.head;                           \
    Node *tmp2 = getNextNodeByNodeAddress(list.head); \
    travelLinkedList(list, tmp2,                      \
        free(tmp1);                                   \
        tmp1 = tmp2;                                  \
    )                                                 \
    initLinkedList(list);

//
#define freeLinkedList(list)                                 \
    if(list.head){                                           \
    freeLinkedList_template(list,                            \
                            uniqueVarName(macroNodeTempVar), \
							uniqueVarName(macroNodeTempVar)) \
    }

//
#define printLinkedList_template(list, tmp)        \
    Node *tmp = list.head;                         \
    travelLinkedList(list, tmp,                    \
	    printf("%d ", getValueByNodeAddress(tmp)); \
    )

//
#define printLinkedList(list) \
    if(list.head){ printLinkedList_template(list, uniqueVarName(macroNodeTempVar)) }



