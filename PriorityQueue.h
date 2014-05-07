#include "BinaryHeap.h"
#include "RuntimeException.h"
#include <vector>

template<typename ElemType>
class Item {
	private:
		int key;
		ElemType elem;
		Locator* loc;
	public:
		Item(const int k =0, const ElemType& e=ElemType())
			: key(k), elem(e){loc = new Locator();	}
		// Item(const int k=0, const ElemType& e=ElemType(), const int i=0)
		// : key(k), elem(e), index(i)  {loc = new Locator(this);}
		const int getKey() const { return key; }
		const ElemType& getElem() const { return elem; }
		Locator* getLoc(){ return loc;} 
		
		Locator* getElem(Locator* loc) { return loc->pos;}
		
		void setKey(const int k) { key = k; }
		void setElem(const ElemType& e) { elem = e; }
};

template<typename ElemType>
class Comp {
public:
	int operator()(const Item<ElemType>& e1,const Item<ElemType>& e2) {
		return e1.getKey() - e2.getKey();
	}
};

template<typename ElemType>
class PriorityQueue {
	class EmptyPriorityQueue : public RuntimeException {
	   public:
		 EmptyPriorityQueue() : RuntimeException("Empty PriorityQueue") {}
	  };
	protected: 
		typedef Item<ElemType> Item;
		typedef Comp<ElemType> Comp;
		
	private:
		vector<Item> v;                     //unsorted array 
		BinaryHeap<Item, Comp> T;
		static const int DEF_SIZE = 8;
	public: // class PriorityQueue cont.
		PriorityQueue(int size = DEF_SIZE) : T(size) { }
		int size(){return T.curSize;}
		
		bool isEmpty() const { return T.isEmpty(); }
		
		void insertItem(const int k, const ElemType& e){
			T.insert(Item(k,e));
		}
		
		const ElemType& minElement() throw(EmptyPriorityQueue) {
			if (T.isEmpty()) throw EmptyPriorityQueue();
			return T.findMin().getElem();
		}
		
		const int minKey() throw(EmptyPriorityQueue) {
			if (T.isEmpty()) throw EmptyPriorityQueue();
			return T.findMin().getKey();
		}
		
		void removeMin() throw(EmptyPriorityQueue) {
			if (T.isEmpty()) throw EmptyPriorityQueue();
			T.deleteMin();
		}
		//---------------------------------
			
		const int locGetKey(Locator* loc)throw(EmptyPriorityQueue){
			if(T.isEmpty()) throw EmptyPriorityQueue();
			return T.findVL(loc).getKey();
		}
		
		const ElemType& locGetElem(Locator* loc) throw(EmptyPriorityQueue){
			if(T.isEmpty()) throw EmptyPriorityQueue();
			return T.findVL(loc).getElem();
		}
		
		Locator* findV(int x)throw(EmptyPriorityQueue){
			if(T.isEmpty()) throw EmptyPriorityQueue();
			return T.findV(x).getLoc();
		}
		
		void locSetKey(Locator* loc, int k) throw (EmptyPriorityQueue){
			int hole = T.findVI(loc);
			T.findVL(loc).setKey(k);
			T.walkUp(hole);
		}
		Locator* min() throw(EmptyPriorityQueue){
			if(T.isEmpty()) throw EmptyPriorityQueue();	
			return T.findMin().getLoc();
		}
		
		void remove(Locator* loc) throw(EmptyPriorityQueue){  //walkdown 
			if(T.isEmpty()) throw EmptyPriorityQueue();
			T.remove(loc);

		}
		
		//---- To show the comparison
		void prR(){
			cout << "Number of Comparison to remove(walkdown): " << T.getR() << endl;
		}
		void resetR() {
			T.setR(0);
		}
		void prC(){
			cout << "Number of Comparison to find/update(walkup): "
			<< T.getC() << endl;
		}
		void resetC() {
			T.setC(0);
		}
		
		void decreaseKey(int loc, int k) throw(EmptyPriorityQueue){
			if(T.isEmpty()) throw EmptyPriorityQueue();
			
			T.decreaseKey(loc,k);
        }
		
		void createPriorityQueue(){
			 T.buildHeap();
		}	
		void printPQ(){
			// cout << "===ID=W===\n";
			T.print();
		}
		
// decreaseKey(loc, k) updates a minimum priority queue after the key k with locator loc was decreased
// createPriorityQueue() builds a minimum priority queue


};
