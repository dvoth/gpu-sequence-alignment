#pragma once

#ifndef __MER_LIST_CUH__
#define __MER_LIST_CUH__

#include "encodedData.cuh"
#include <stdlib.h>  

//data structure 
typedef struct dataList {
	//vars
	int id;
	dataList *next;
	encodedData *value;

	//will dynamically add a new item in the list
	__host__ __device__ void addNewVal(encodedData *val) {
		dataList *temp = this;

		//check if it is an empty root (head)
		if ((*temp).next == NULL && (*temp).value == NULL) {
			(*temp).value = new encodedData();
			(*temp).value = val;
			(*temp).id = 1;
		}
		//iterate list and insert
		else {
			
			while ((*temp).next != NULL)
				temp = (*temp).next;
			//new data list object to insert
			dataList *newT = new dataList();
			(*newT).value = new encodedData();
			(*newT).id = (*temp).id + 1;		//increase ID value
			(*temp).next = newT;				//set the temp (iterated dataList) to point at new dataList as next
			(*newT).value = val;				//set the new data list object's value
		}
	}

	//this will destory the list when called upon
	__host__ __device__ void destroyList() {
		dataList *temp = this;
		
		while ((*temp).next != NULL) {
			dataList *pointerHold = temp;
			(*temp).value = new encodedData();
			delete (*temp).value;
			temp = (*temp).next;
			pointerHold = new dataList();
			delete pointerHold;
		}
		//delete last object
		(*temp).value = new encodedData();
		delete (*temp).value;
		temp = new dataList();
		delete temp;
	}
	//will return the dataList object at a specified depth
	__host__ __device__ void getDataListAtDepth(int depth, dataList **val) {
		dataList *temp = this;
		for (int i = 0; i < depth; i++)
			temp = (*temp).next;
		(*val) = temp;
	}
	//will return the last dataList object in the list
	__host__ __device__ void getListItem(encodedData **temp) {
		dataList *it = this;
		while ((*it).next != NULL) {
			it = (*it).next;
		}
		(*temp) = (*it).value;
	}

} dataList;
#endif