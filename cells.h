#ifndef CELLS_H_
#define CELLS_H_

#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;

int numCells(double, double, double);
void minHeapify(vector<double> &, unsigned int);
void buildMinHeap(vector<double> &);
double heapMin(vector<double> &);
double heapExtractMin(vector<double> &);
void minHeapInsert(vector<double> &, double);
double splitTime(double, double);

int numCells(double endTime, double minSplit, double maxSplit){

	vector<double> cells;
	double currentTime;

	//set cell 0 to zero, to simplify node calculations
	cells.push_back(0);

	//start with a single cell that divides at time 0
	cells.push_back(0);



	while(endTime >= heapMin(cells)){

		currentTime = heapExtractMin(cells);

		minHeapInsert(cells, currentTime+splitTime(minSplit, maxSplit));
		minHeapInsert(cells, currentTime+splitTime(minSplit, maxSplit));
	}


	return cells.size()-1;
}

double splitTime(double minSplit, double maxSplit){

	return minSplit + rand()*(maxSplit - minSplit)/RAND_MAX;

}

double heapExtractMin(vector<double> &heap){
	if(heap.size() <= 1)
		return -1;

	double min = heap[1];
	heap[1] = heap[heap.size()-1];
	heap.pop_back();
	minHeapify(heap, 1);
	return min;
}

void minHeapInsert(vector<double> &heap, double cell){

	heap.push_back(cell);

	unsigned int i = heap.size()-1;
	//this is faster than division
	unsigned int p = i >> 1;
	double temp;

	while(i > 1 && heap[p] > heap[i]){

		//could decrease assignments to just one, store a temp and switch the rest until the end
		temp = heap[i];
		heap[i] = heap[p];
		heap[p] = temp;

		i = p;
		p = i >> 1;
		//p = i/2;
	}

}

double heapMin(vector<double> &heap){
	return heap[1];
}

void minHeapify(vector<double> &heap, unsigned int i){
	//std::cout << "called MinHeapify with " << i << std::endl;
	double temp;
	unsigned int smallest;
	//this is faster than multiplication
	unsigned int l = i << 1;
	//this is faster than a bitwise or
	unsigned int r = l + 1;

	if(l < heap.size() && heap[l] < heap[i]){
		smallest = l;
		//std::cout << "Set smallest to l" << std::endl;
	}
	else{
		smallest = i;
		//std::cout << "Set smallest to i" << std::endl;
	}

	if(r < heap.size() && heap[r] < heap[smallest]){
		smallest = r;
		//std::cout << "Set smallest to r" << std::endl;
	}

	if(smallest != i){
		//std::cout << "Smallest != i" << std::endl;
		//can use only one assignment by storing a temp, shift the rest of the variables, until the end
		temp = heap[i];
		heap[i] = heap[smallest];
		heap[smallest] = temp;

		minHeapify(heap, smallest);
	}

}

void buildMinHeap(vector<double> &heap){

	for(int i = heap.size()/2; i > 0; i--){
		minHeapify(heap, i);
	}

}

#endif /* CELLS_H_ */

