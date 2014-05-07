#include "RuntimeException.h"
#include <iostream>

// template<typename ElemType>
class Locator
{
	public:
		int pos;
};
 
template<typename ElemType, typename Comp>
class BinaryHeap {
		class EmptyHeap : public RuntimeException {
		   public:
			 EmptyHeap() : RuntimeException("Empty Heap") {}
		   };
	private:
		Comp comp; // Comp is a comparator class
		// and comp(a,b) will compare arguments a and b
		int curSize; //number of elements in heap
		ElemType *array; //(dynamic) heap array
		int length; //the length of the array
		bool orderOK;
		static const int DEF_SIZE = 8;
		int numR, numC;
		
		void getNewArray(int newSize) {
			array = new ElemType[newSize];
			length = newSize;
		}
	
	public: // templated class BinaryHeap (cont)
		
		BinaryHeap(int size = DEF_SIZE) { //constructor
			curSize = 0;
			orderOK = true;
			getNewArray(size);
			numR =0;
			numC =0;
			}

		ElemType& findMin() throw(EmptyHeap) {
			if ( isEmpty() ) throw EmptyHeap();
			if (! orderOK) buildHeap();
			return array[0];
		}
		
		bool isEmpty( ) const {  return curSize == 0; }
		void incR() { ++numR;}
		void incC() { ++numC;}
		int getR(){return numR;}
		int getC(){return numC;}
		void setR(int x) { numR = x;}
		void setC(int x) { numC = x;}
		
		void buildHeap(){
			for (int i = (curSize-2)/2; i >= 0; i--) walkDown(i);
			orderOK = true;
		}
		
		void checkSize( ) {
			if (curSize == length) {
				ElemType *oldArray = array;
				getNewArray(2*curSize);
				for (int i = 0; i < curSize; i++)
				array[i] = oldArray[i];
				delete [] oldArray;
			}
		}
		
		void decreaseKey(int loc, int k){
			int i =0;
			while(loc != array[i].getLoc()){
				++i; //loc
			}
			
			array[i].setKey(array[i].getKey()-1);
			walkUp(i);
		}
		
		void insert(const ElemType& x){
			checkSize( );
			//walk up (establish heap order now)
			int hole = curSize++;
			for ( ; hole > 0 && comp(array[(hole-1)/2], x) > 0; hole = (hole-1)/2)
				array[hole] = array[(hole-1)/2];
			array[hole] = x;
		}
		
				
		void deleteMin() throw(EmptyHeap){			
			array[0] = array[ --curSize ]; //decrease size
			walkDown(0);
		}
		
		ElemType& findVL(Locator* loc) throw(EmptyHeap){
			int i = 0;
			while(loc != array[i].getLoc()){
				++i;
			}
			return array[i];
		}
		int findVI(Locator* loc) throw(EmptyHeap){
			int i = 0;
			while(loc != array[i].getLoc()){
				++i;
			}
			return i;
		}
		
		ElemType& findV(int x){
			int i =0;
			while(x != array[i].getElem()){
				i++;
				incC();
			}
			return array[i];
		}
			
		
		void remove(Locator* loc) throw(EmptyHeap){
			int i =0;
			while(loc != array[i].getLoc()){
				i++;
			}
			array[i] = array[--curSize];
			walkDown(i);
		}
		
		
		// void walkDown(int hole, int rcomp){
			// int child;
			// // int rcomp = 0;
			// ElemType key = array[hole];
			// for ( ; 2*hole+1 < curSize; hole = child) {
				// ++rcomp;
				// child = 2*hole+1;
				// if (child != curSize-1 && comp(array[child], array[child+1]) > 0){
					// ++rcomp;
					// child++; // right child = 2*hole+2
				// }
				// if (comp(key, array[child]) > 0) {
					// ++rcomp;
					// array[hole]=array[child];
				// }else break;
			// }
			// cout << "WALKDOWN: " << hole << endl;
			// array[hole] = key;
			// // cout << "***Remove Comparison: " << rcomp << endl;
		// }
		
		void walkDown(int hole){
			int child;
			ElemType key = array[hole];
			int k =0; 
			int r = getR();
			for ( ; 2*hole+1 < curSize; hole = child) {
				child = 2*hole+1;
				k++;
				if (++k&&child != curSize-1 && comp(array[child], array[child+1]) > 0){
					child++; // right child = 2*hole+2
				}
				if (k++&&comp(key, array[child]) > 0) {
					array[hole]=array[child];
				}else break;
				setR(r+k);
			}
			array[hole] = key;
		}
		
		
		void walkUp(int hole){
			ElemType x = array[hole];
			int k =0;
			int c = getC();
			for( ; ++k && hole>0 && comp(array[(hole-1)/2], x)>0; hole = (hole-1)/2){
				array[hole] = array[(hole-1)/2];
			}
			setC(c+k);
			array[hole] = x;
		}
		
		void print(){
			for(int i =0; i<curSize; i++){
				if(array[i].getKey()==0 && array[i].getLoc()==0){}else
				cout << "E" << i << ": " << array[i].getElem() << " " <<array[i].getKey() << endl;
			}
		}
};









