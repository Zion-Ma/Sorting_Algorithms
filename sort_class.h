#include <iostream>
#include <cstring>
#include<limits>
using namespace std;

 
class Sort{
	int opt, len; /*option code*/
	int * arr; /*array to be sorted*/
	public:
		void Option_Initialize_Sort(); /*this funciton is to receive input (option code) and execute the chosen algorithm*/
		void set_array(); /*setting the list (array)*/
		void print(); /*printing the list at any step*/
		void BubbleSort(); /*algorithm, supporting non-input-parameter method*/
		void QuickSort();
		void QuickSort(const int, const int); /*algorithm*/
		void Insert(const int, int i); /*auxiliary function in aid of InsertionSort*/
		void InsertionSort(); /*algorithm, supporting non-input-parameter method*/
		void Adjust(const int, const int); /*auxiliary function in aid of HeapSort*/
		void HeapSort(); /*algorithm*/
		void Merge(int arr_1[], int arr_2[], const int l, const int m, const int n); /*auxiliary function in aid of MergeSort*/
		void MergePass(int arr_1[], int arr_2[], const int n, const int s); /*auxiliary function in aid of MergeSort*/
		void MergeSort(int arr[], const int); /*algorithm, hereby being the prototype of NaturalMergeSort*/
		void NaturalMergeSort(); /*algorithm, supporting non-input-parameter method*/
};

void Sort::Option_Initialize_Sort(){ 

	cout<<"1. BubbleSort 2. QuickSort 3. Natural Merge Sort 4. HeapSort 5. InsertionSort"<<endl;
	cout<<"Please choose a sorting algorithm: ";
	cin>>opt;
	set_array();
	cout<<"You chose ";
	if(opt == 1){
		cout<<" BubbleSort."<<endl;
		BubbleSort();
	}
	else if(opt == 2){
		cout<<" QuickSort."<<endl;
		QuickSort(1, len);
	}
	else if(opt == 3){
		cout<<" Natural Merge Sort."<<endl;
		NaturalMergeSort();
	}
	else if(opt == 4){
		cout<<" HeapSort."<<endl;
		HeapSort();
	}
	else{
		cout<<" InsertionSort."<<endl;
		InsertionSort();
	}
	
	cout<<endl<<endl<<"result: ";
	this->print();
}

void Sort::set_array(){ 
	char a[100];
	char * t;
	int data[100];
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	cout<<"Type in the list to be sorted: ";
	cin.getline(a, 100);
	t = strtok(a, " ");
	len = 0;
	while(t != NULL)
    {
        data[len] = atoi(t);
        t = strtok(NULL," ");
        len++;
    }
	arr = new int[len+2];
	copy(data, data+len, arr + 1);
}

void Sort::print(){
	cout<<"[";
	for(int i = 1; i <= len; i++){
		if (i != len){
			cout<<arr[i]<<"\t";
		}
		else{
			cout<<arr[i]<<"]"<<endl;
		}
	}
}

void Sort::BubbleSort(){ /*sorting sequentially one by one*/
	for (int i = len; i > 0; i--){
		for(int j = 1; j < i; j++){
			if(arr[j] > arr[j + 1]){
				swap(arr[j], arr[j + 1]);
			}
		}
		this->print();
	}
}

void Sort::QuickSort(){
	QuickSort(1, len);
}

void Sort::QuickSort(const int left, const int right){ 
	/*sorting by the comparison with the pivots and the remianders*/
	if(left < right){
		int i = left, j = right + 1, pivot = arr[left];
		do{
			do i++; while (arr[i] < pivot);
			do j--; while (arr[j] > pivot);
			if(i < j) swap(arr[i], arr[j]);
		}while(i < j);
		swap(arr[left], arr[j]);
		print();
		
		QuickSort(left, j - 1);
		QuickSort(j + 1, right);
	}
}

void Sort::Insert(const int e, int i){ 
	/*inserting the smaller one to the previoulsy ordered sublist*/
	arr[0] = e;
	while(e < arr[i]){
		arr[i + 1] = arr[i];
		i--;
	}
	arr[i + 1] = e;

//	copy(arr + 1, a + 15, arr);
}

void Sort::InsertionSort(){ /*sorting sequentially one by one*/
	for(int i = 1; i <= len; i++){
		int temp = arr[i];
		Insert(temp, i - 1);
		this->print();
	}
}

void Sort::Adjust(const int root, const int n){ 
	/*adjust root node by maximum heap method*/
	int e = arr[root];
	int j;
	for(j = 2 * root; j <= n; j *= 2){
		if(j < n && arr[j] < arr[j + 1]) j++;
		if(e >= arr[j]) break;
		arr[j/2] = arr[j];
	}
	arr[j/2] = e;
	print();
}

void Sort::HeapSort(){
	/*sorting according the to the heap's order*/
	for(int i = len / 2; i >= 0; i--){
		Adjust(i, len);
	}
	for(int i = len - 1; i >= 0; i--){
		swap(arr[1], arr[i + 1]);
		Adjust(1, i);
	}
}

void Sort::Merge(int initList[], int mergedList[], const int l, const int m, const int n){
	/*merging two ordered sublists into one ordered list*/
	int i1, i2, iResult;
	for (i1 = l, iResult = l, i2 = m + 1; i1 <= m && i2 <= n; 
		iResult++){
		if(initList[i1] <= initList[i2]){
			mergedList[iResult] = initList[i1];
			i1++;
		}
		else{
			mergedList[iResult] = initList[i2];
			i2++;
		}
	}
	copy(initList + i1, initList + m + 1, mergedList + iResult);
    copy(initList + i2, initList + n + 1, mergedList + iResult);
}

void Sort::MergePass(int initList[], int resultList[], const int n, const int s){
	/*merging multiple sublists according to the segmentation result*/
	int i;
	for(i = 1; i <= n - 2 * s + 1; i += 2 * s)
		Merge(initList, resultList, i, i + s - 1, i + 2 * s - 1);
		
	if((i + s - 1) < n) Merge(initList, resultList, i, i + s - 1, n);
	else copy(initList + i, initList + n + 1, resultList + i);
}

void Sort::MergeSort(int arr_shift[], const int n){
	/*sorting by bottom-up merging method*/
	int * temp_list = new int[n + 1];
	for(int l = 1; l < n; l *= 2){
		MergePass(arr_shift, temp_list, n, l);
		cout<<"[";
		for (int j = 1; j < 15; j++){
			if(j != 14){
				cout<<arr_shift[j]<<"\t";
			}
			else{
				cout<<arr_shift[j]<<"]"<<endl;
			}
		} 
		l *= 2;
		MergePass(temp_list, arr_shift, n, l);
		cout<<"[";
		for (int j = 1; j < 15; j++){
			if(j != 14){
				cout<<arr_shift[j]<<"\t";
			}
			else{
				cout<<arr_shift[j]<<"]"<<endl;
			}
		}
	}

	delete []temp_list;	
}

void Sort::NaturalMergeSort(){ /*this one is really interesting and also time-costly*/
	
	int sum = 0, k, order[len] = {0}; /*list that stores the prevailing ordered list*/
	/*e.g. 89 34 23 78 67 100 66 29 79 55 78 88 92 936 
		=> (89), (34), (23 78), (67 100), (66), (29 79), (55 78 88 92 936)
	 	=> order[0] = 1, order[1] = 1, order[2] = 2, order[3] = 2, order[4] = 1, order[5] = 2, order[6] = 5
	*/
	int *result_list = new int[len + 2]; /*list used to store current result*/
	for(int i = 0; sum < len; i++){ /*referring to order[i]*/
		int j = sum; /*by summing order[i]'s value, we can find where the next ordered sublist at*/
		do{ /*this loop is to find order[i]'s value*/
			order[i]++;
			if(arr[j] > arr[j + 1]) break; 
			j++; 
		}while(j < len);
		sum += order[i];
		if(i > 0){ /*merging */
			Merge(arr, result_list, 1, sum - order[i] - 1, sum); /*merging two ordered 2 ordered sublists*/
			Merge(result_list, arr, 1, sum - order[i] - 1, sum); /*return the current result back to the object's array*/
		}
		print();
	}
	
}


