#include "test_utilities.h"
#include "list_mtm1.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

static ListElement copyString(ListElement str){
	assert(str);
	char* copy = malloc(strlen(str)+1);
	return copy != NULL ? strcpy(copy, str) : NULL;
}

static void freeString(ListElement str){
	free(str);
}

static bool isLongerThan(ListElement element,ListFilterKey number) {
	char* string = element;
    return strlen(string) > *(int*)number;
}

static bool testListCreate() {
	ASSERT_TEST(listCreate(NULL,NULL) == NULL);
	ASSERT_TEST(listCreate(NULL,NULL) == NULL);
	ASSERT_TEST(listCreate(copyString,NULL) == NULL);
	ASSERT_TEST(listCreate(NULL,freeString) == NULL);

	return true;
}
static bool testListFilter() {
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	List list = listCreate(copyString,freeString);
	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
	int key = 5;
	List filtered = listFilter(list,isLongerThan, &key);
	ASSERT_TEST(listGetSize(filtered) == 1);
	ASSERT_TEST(strcmp(listGetFirst(filtered),a[3])==0);
	listDestroy(list);
	listDestroy(filtered);
	return true;
}
static bool testListCopy() {
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	List list = listCreate(copyString,freeString);
	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
	List copy = listCopy(list);
	ASSERT_TEST(copy != NULL);
	ASSERT_TEST(strcmp(listGetCurrent(list), "aaa") == 0);
	ASSERT_TEST(strcmp(listGetCurrent(copy), "aaa") == 0);
	ASSERT_TEST(strcmp(listGetFirst(copy), "I") == 0);
	ASSERT_TEST(strcmp(listGetNext(copy), "hello mister fish") == 0);
	ASSERT_TEST(listGetSize(copy) == 5);
	ASSERT_TEST(strcmp(listGetFirst(copy), listGetFirst(list)) == 0);
	ASSERT_TEST(strcmp(listGetCurrent(list), "I") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "hello mister fish") == 0);
	ASSERT_TEST(strcmp(listGetCurrent(list), "hello mister fish") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "NI") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "bbb") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "aaa") == 0);
	ASSERT_TEST(strcmp(listGetFirst(list), "I") == 0);
	listDestroy(list);
	listDestroy(copy);
	return true;
}

static bool testListGetSize() {
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	List list = listCreate(copyString,freeString);
	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
	ASSERT_TEST(listGetSize(list) == 5);
	listDestroy(list);
	return true;
}

static bool testListGetFirst() {
	List list = listCreate(copyString,freeString);
	ASSERT_TEST(listInsertFirst(list,"hi") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetCurrent(list), "hi") == 0);
	ASSERT_TEST(strcmp(listGetFirst(list), "hi") == 0);
	ASSERT_TEST(listGetSize(list) == 1);
	ASSERT_TEST(strcmp(listGetCurrent(list), "hi") == 0);
	ASSERT_TEST(listInsertFirst(list,"lora") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetCurrent(list), "hi") == 0);
	ASSERT_TEST(listInsertFirst(list,"tan") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetCurrent(list), "hi") == 0);
	ASSERT_TEST(listGetNext(list) == NULL);
	listDestroy(list);
	return true;
}

static bool testListInsertFirst() {
	List list = listCreate(copyString,freeString);
	ASSERT_TEST(listInsertFirst(list,"hi") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetCurrent(list), "hi") == 0);
	ASSERT_TEST(strcmp(listGetFirst(list), "hi") == 0);
	ASSERT_TEST(listGetSize(list) == 1);
	ASSERT_TEST(strcmp(listGetCurrent(list), "hi") == 0);
	ASSERT_TEST(listInsertFirst(list,"lora") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetCurrent(list), "hi") == 0);
	ASSERT_TEST(listInsertFirst(list,"tan") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetCurrent(list), "hi") == 0);
	ASSERT_TEST(listGetNext(list) == NULL);
	listDestroy(list);
	return true;
}

static bool testListInsertLast() {
	List list = listCreate(copyString,freeString);
	ASSERT_TEST(listInsertLast(list,"hi") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetCurrent(list), "hi") == 0);
	ASSERT_TEST(strcmp(listGetFirst(list), "hi") == 0);
	ASSERT_TEST(listGetSize(list) == 1);
	ASSERT_TEST(strcmp(listGetCurrent(list), "hi") == 0);
	ASSERT_TEST(listInsertLast(list,"lora") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetCurrent(list), "hi") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "lora") == 0);
	ASSERT_TEST(listInsertFirst(list,"tan") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetCurrent(list), "lora") == 0);
	ASSERT_TEST(strcmp(listGetFirst(list), "tan") == 0);
	listDestroy(list);
	return true;
}

static bool testListInsertBeforeCurrent() {
	List list = listCreate(copyString,freeString);
	ASSERT_TEST(listInsertLast(list,"hi") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetCurrent(list), "hi") == 0);
	ASSERT_TEST(strcmp(listGetFirst(list), "hi") == 0);
	ASSERT_TEST(listGetSize(list) == 1);
	ASSERT_TEST(strcmp(listGetCurrent(list), "hi") == 0);
	ASSERT_TEST(listInsertLast(list,"lora") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetCurrent(list), "hi") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "lora") == 0);
	ASSERT_TEST(listInsertFirst(list,"tan") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetCurrent(list), "lora") == 0);
	ASSERT_TEST(strcmp(listGetFirst(list), "tan") == 0);
	ASSERT_TEST(strcmp(listGetCurrent(list), "tan") == 0);
	ASSERT_TEST(listInsertBeforeCurrent(list, "fernas") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetFirst(list), "fernas") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "tan") == 0);
	ASSERT_TEST(listInsertBeforeCurrent(list, "israel") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetCurrent(list), "tan") == 0);
	ASSERT_TEST(strcmp(listGetFirst(list), "fernas") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "israel") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "tan") == 0);
	listDestroy(list);
	return true;
}

static bool testListInsertAfterCurrent() {
	List list = listCreate(copyString,freeString);
	ASSERT_TEST(listInsertLast(list,"hi") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetCurrent(list), "hi") == 0);
	ASSERT_TEST(strcmp(listGetFirst(list), "hi") == 0);
	ASSERT_TEST(listGetSize(list) == 1);
	ASSERT_TEST(strcmp(listGetCurrent(list), "hi") == 0);
	ASSERT_TEST(listInsertLast(list,"lora") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetCurrent(list), "hi") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "lora") == 0);
	ASSERT_TEST(listInsertFirst(list,"tan") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetCurrent(list), "lora") == 0);
	ASSERT_TEST(strcmp(listGetFirst(list), "tan") == 0);
	ASSERT_TEST(strcmp(listGetCurrent(list), "tan") == 0);
	ASSERT_TEST(listInsertAfterCurrent(list, "fernas") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetFirst(list), "tan") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "fernas") == 0);
	ASSERT_TEST(listInsertAfterCurrent(list, "israel") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetCurrent(list), "fernas") == 0);
	ASSERT_TEST(strcmp(listGetFirst(list), "tan") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "fernas") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "israel") == 0);
	listDestroy(list);
	return true;
}

static bool testListRemoveCurrent() {
	List list = listCreate(copyString,freeString);
	ASSERT_TEST(listInsertLast(list,"hi") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetCurrent(list), "hi") == 0);
	ASSERT_TEST(strcmp(listGetFirst(list), "hi") == 0);
	ASSERT_TEST(listGetSize(list) == 1);
	ASSERT_TEST(strcmp(listGetCurrent(list), "hi") == 0);
	ASSERT_TEST(listInsertLast(list,"lora") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetCurrent(list), "hi") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "lora") == 0);
	ASSERT_TEST(listInsertFirst(list,"tan") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetCurrent(list), "lora") == 0);
	ASSERT_TEST(strcmp(listGetFirst(list), "tan") == 0);
	ASSERT_TEST(strcmp(listGetCurrent(list), "tan") == 0);
	ASSERT_TEST(listInsertAfterCurrent(list, "fernas") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetFirst(list), "tan") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "fernas") == 0);
	ASSERT_TEST(listInsertAfterCurrent(list, "israel") == LIST_SUCCESS);
	ASSERT_TEST(strcmp(listGetCurrent(list), "fernas") == 0);
	ASSERT_TEST(strcmp(listGetFirst(list), "tan") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "fernas") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "israel") == 0);
	ASSERT_TEST(listGetSize(list) == 5);
	ASSERT_TEST(strcmp(listGetNext(list), "hi") == 0);
	ASSERT_TEST(listRemoveCurrent(list) == LIST_SUCCESS);
	ASSERT_TEST(listGetSize(list) == 4);
	ASSERT_TEST(strcmp(listGetFirst(list), "tan") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "fernas") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "israel") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "lora") == 0);
	ASSERT_TEST(listRemoveCurrent(list) == LIST_SUCCESS);
	ASSERT_TEST(listGetSize(list) == 3);
	ASSERT_TEST(strcmp(listGetFirst(list), "tan") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "fernas") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "israel") == 0);
	ASSERT_TEST(strcmp(listGetCurrent(list), "israel") == 0);
	ASSERT_TEST(listGetNext(list) == NULL);
	ASSERT_TEST(strcmp(listGetFirst(list), "tan") == 0);
	ASSERT_TEST(listRemoveCurrent(list) == LIST_SUCCESS);
	ASSERT_TEST(listGetSize(list) == 2);
	ASSERT_TEST(strcmp(listGetFirst(list), "fernas") == 0);
	ASSERT_TEST(strcmp(listGetNext(list), "israel") == 0);
	ASSERT_TEST(listClear(list) == LIST_SUCCESS);
	ASSERT_TEST(listGetSize(list) == 0);
	ASSERT_TEST(listGetCurrent(list) == NULL);
	ASSERT_TEST(listGetNext(list) == NULL);
	ASSERT_TEST(listGetFirst(list) == NULL);
	listDestroy(list);
	return true;
}

static bool testListSort() {
	return true;
}

int main (int argv, char** arc){
	RUN_TEST(testListCreate);
	RUN_TEST(testListFilter);
	RUN_TEST(testListCopy);
	RUN_TEST(testListGetSize);
	RUN_TEST(testListGetFirst);
	RUN_TEST(testListInsertFirst);
	RUN_TEST(testListInsertLast);
	RUN_TEST(testListInsertBeforeCurrent);
	RUN_TEST(testListInsertAfterCurrent);
	RUN_TEST(testListRemoveCurrent);
	RUN_TEST(testListSort);
	return 0;
}

