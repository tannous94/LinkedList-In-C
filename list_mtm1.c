/*
 * list_mtm1.c
 *
 *  Created on: May 31, 2017
 *      Author: tannous
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list_mtm1.h"

typedef struct node_t {
	ListElement data;
	struct node_t* next;
} *Node;

struct list_t {
	int size;
	Node first;
	Node iter;
	CopyListElement copyElement;
	FreeListElement freeElement;
};

List listCreate(CopyListElement copyElement, FreeListElement freeElement) {
	if (!copyElement || !freeElement) {
		return NULL;
	}
	List list = malloc(sizeof(*list));
	if (!list) {
		return NULL;
	}
	list->copyElement = copyElement;
	list->freeElement = freeElement;
	list->size = 0;
	list->first = NULL;
	list->iter = NULL;
	return list;
}

void listDestroy(List list) {
	if (!list) {
		return;
	}
	listClear(list);
	free(list);
	return;
}

List listCopy(List list) {
	if (!list) {
		return NULL;
	}
	List copyList = listCreate(list->copyElement, list->freeElement);
	if (!copyList) {
		return NULL;
	}
	if (listGetSize(list) == 0) {
		return copyList;
	}
	Node save_iter = list->iter;
	list->iter = list->first;
	int place = 1;
	while (list->iter != save_iter) {
		list->iter = list->iter->next;
		place++;
	}
	list->iter = list->first;
	while (list->iter) {
		if (listInsertLast(copyList, list->iter->data) != LIST_SUCCESS) {
			listDestroy(copyList);
			return NULL;
		}
		list->iter = list->iter->next;
	}
	copyList->iter = copyList->first;
	while (--place) {
		copyList->iter = copyList->iter->next;
	}
	list->iter = save_iter;
	return copyList;
}

int listGetSize(List list) {
	if (!list) {
		return -1;
	}
	return list->size;
}

ListElement listGetFirst(List list) {
	if (!list || listGetSize(list) == 0) {
		return NULL;
	}
	list->iter = list->first;
	return list->iter->data;
}

ListElement listGetNext(List list) {
	if (!list || listGetSize(list) == 0 || list->iter->next == NULL) {
		return NULL;
	}
	list->iter = list->iter->next;
	return list->iter->data;
}

ListElement listGetCurrent(List list) {
	if (!list || list->iter == NULL) {
		return NULL;
	}
	return list->iter->data;
}

ListResult listInsertFirst(List list, ListElement element) {
	if (!list || !element) {
		return LIST_NULL_ARGUMENT;
	}
	Node newElement = malloc(sizeof(*newElement));
	if (!newElement) {
		return LIST_OUT_OF_MEMORY;
	}
	newElement->data = list->copyElement(element);
	if (listGetSize(list) > 0) {
		Node save_first = list->first;
		list->first = newElement;
		list->first->next = save_first;
	} else {
		list->first = newElement;
		list->first->next = NULL;
		list->iter = list->first;
	}
	list->size++;
	return LIST_SUCCESS;
}

ListResult listInsertLast(List list, ListElement element) {
	if (!list || !element) {
		return LIST_NULL_ARGUMENT;
	}
	Node newElement = malloc(sizeof(*newElement));
	if (!newElement) {
		return LIST_OUT_OF_MEMORY;
	}
	newElement->data = list->copyElement(element);
	if (listGetSize(list) > 0) {
		Node save_iter = list->iter; //
		list->iter = list->first;
		while (list->iter->next) {
			list->iter = list->iter->next;
		}
		list->iter->next = newElement;
		list->iter = list->iter->next;
		list->iter->next = NULL;
		list->iter = save_iter; //
	} else {
		list->first = newElement;
		list->first->next = NULL;
		list->iter = list->first;
	}
	list->size++;
	return LIST_SUCCESS;
}

ListResult listInsertBeforeCurrent(List list, ListElement element) {
	if (!list || !element) {
		return LIST_NULL_ARGUMENT;
	}
	if (list->iter == NULL) {
		return LIST_INVALID_CURRENT;
	}
	Node newElement = malloc(sizeof(*newElement));
	if (!newElement) {
		return LIST_OUT_OF_MEMORY;
	}
	Node save_iter = list->iter; //
	newElement->data = list->copyElement(element);
	if (list->iter == list->first) {
		Node save_current = list->iter;
		list->first = newElement;
		list->first->next = save_current;
	} else {
		Node save_current = list->iter;
		list->iter = list->first;
		while (list->iter->next != save_current) {
			list->iter = list->iter->next;
		}
		list->iter->next = newElement;
		list->iter = list->iter->next;
		list->iter->next = save_current;
	}
	list->iter = save_iter; //
	list->size++;
	return LIST_SUCCESS;
}

ListResult listInsertAfterCurrent(List list, ListElement element) {
	if (!list || !element) {
		return LIST_NULL_ARGUMENT;
	}
	if (list->iter == NULL) {
		return LIST_INVALID_CURRENT;
	}
	Node newElement = malloc(sizeof(*newElement));
	if (!newElement) {
		return LIST_OUT_OF_MEMORY;
	}
	newElement->data = list->copyElement(element);
	Node save_iter = list->iter; //
	if (list->iter->next == NULL) {
		list->iter->next = newElement;
		list->iter = list->iter->next;
		list->iter->next = NULL;
	} else {
		newElement->next = list->iter->next;
		list->iter->next = newElement;
	}
	list->iter = save_iter; //
	list->size++;
	return LIST_SUCCESS;
}

ListResult listRemoveCurrent(List list) {
	if (!list) {
		return LIST_NULL_ARGUMENT;
	}
	if (list->iter == NULL) {
		return LIST_INVALID_CURRENT;
	}
	if (listGetSize(list) == 1) {
		listClear(list);
		return LIST_SUCCESS;
	}
	Node to_delete = list->iter;
	if (list->iter == list->first) {
		list->first = list->iter->next;
		list->freeElement(to_delete->data);
		free(to_delete);
		//list->iter = list->first;
		list->iter = NULL;
	} else if (list->iter->next == NULL) {
		list->iter = list->first;
		while (list->iter->next != to_delete) {
			list->iter = list->iter->next;
		}
		list->iter->next = NULL;
		list->freeElement(to_delete->data);
		free(to_delete);
	} else {
		list->iter = list->first;
		while (list->iter->next != to_delete) {
			list->iter = list->iter->next;
		}
		Node save_current = list->iter;
		list->iter = list->iter->next;
		save_current->next = list->iter->next;
		list->freeElement(to_delete->data);
		free(to_delete);
		list->iter = NULL;
	}
	list->size--;
	return LIST_SUCCESS;
}

ListResult listClear(List list) {
	if (!list) {
		return LIST_NULL_ARGUMENT;
	}
	if (listGetSize(list) == 0) {
		return LIST_SUCCESS;
	}
	list->iter = list->first;
	while (list->iter) {
		Node to_delete = list->iter;
		list->iter = list->iter->next;
		list->freeElement(to_delete->data);
		free(to_delete);
	}
	list->first = NULL;
	list->iter = NULL;
	list->size = 0;
	return LIST_SUCCESS;
}

ListResult listSort(List list, CompareListElements compareElement) {
	if (!list || !compareElement) {
		return LIST_NULL_ARGUMENT;
	}
	if (listGetSize(list) < 2) {
		return LIST_SUCCESS;
	}
	Node save_iter = list->iter;
	ListElement temp;
	Node previous = list->first;
	while (previous) {
		Node current = previous;
		while (current) {
			if (compareElement(previous->data, current->data) > 0) {
				temp = previous->data;
				previous->data = current->data;
				current->data = temp;
			}
			current = current->next;
		}
		previous = previous->next;
	}
	list->iter = save_iter;
	return LIST_SUCCESS;
}

List listFilter(List list, FilterListElement filterElement, ListFilterKey key) {
	if (!list || !filterElement) {
		return NULL;
	}
	List filtered_list = listCreate(list->copyElement, list->freeElement);
	if (!filtered_list) {
		return NULL;
	}
	if (listGetSize(list) == 0) {
		return filtered_list;
	}
	list->iter = list->first;
	while (list->iter) {
		if (filterElement(list->iter->data, key) == true) {
			if (listInsertLast(filtered_list, list->iter->data) != LIST_SUCCESS) {
				listDestroy(filtered_list);
				return NULL;
			}
		}
		list->iter = list->iter->next;
	}
	return filtered_list;
}
