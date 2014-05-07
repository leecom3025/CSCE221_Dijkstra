#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Vertex.h"
#include "Edge.h"
#include "PriorityQueue.h"

using namespace std;

class Edge;
class Vertex;

class Graph{

private:
	vector<Vertex*> vertList;
	vector<Edge*> edgeList;
	PriorityQueue<int> pq;
	Locator* loc;
	
public:
	Graph () {}
	Graph(string filename) {
		ifstream ifs(filename.c_str());
		int vertnum;
		ifs>>vertnum;
		for(int i=0;i<vertnum;i++) // push all vertices into the vertex vector before assigning the in and out list
		{
			Vertex *vert = new Vertex(i+1);
			vertList.push_back(vert);
		}
		int svert,evert,weit; 
		ifs>>svert; 
		
		while(svert!=-1)
		{	ifs>>evert; 
			while(evert!=-1)
			{	
				ifs>>weit; // one weight means one edge
                Edge *tempedge = new Edge(vertList[svert-1],vertList[evert-1],weit); // new edge
				edgeList.push_back(tempedge);				
				vertList[svert-1]->outList.push_back(tempedge);
				vertList[evert-1]->inList.push_back(tempedge);
				ifs>>evert; 
			}
			ifs>>svert; 
		}
		ifs.close();
	}
	
	~Graph() {
		for(int i = 0; i < vertList.size(); i++)
			delete vertList[i];
		for(int i = 0; i < edgeList.size(); i++)
			delete edgeList[i];
	}

	
	vector<Vertex*> getVertices() const {
		return vertList;
	}

	void PrintGraph() // print out all the edges and associated vertices in the entire graph
	{
		for(int i=0; i<vertList.size(); i++){
			cout << vertList[i]->getID() << "| ";
			for(int j=0; j<vertList[i]->outList.size(); j++){
				cout << vertList[i]->outList[j]->geteVertP()->getID() << " " << vertList[i]->outList[j]->getWeight() << " ";
			}
			cout << endl;
		}
	}
	
	vector<Vertex*> addVertex(int vtemp)  {
		Vertex *vert = new Vertex(vtemp);
		bool here = false;
			for(int i =0; i<vertList.size(); i++){
				try{
					if(vertList[i]->getID() == vtemp){ 
					throw vtemp;
					}
				}catch (int except){cout << "The vertex " << except << " is already in the graph\n"; here = true;}
			}
		if(!here)vertList.push_back(vert);
	}
	
	vector<Vertex*> addEdge(int svert, int evert,int weit){ 
		bool soc = false;
		bool des = false; 
		for(int i =0; i<vertList.size(); i++){
			if(vertList[i]->getID()==svert){ soc = true; break;}		
		}
		for(int j=0; j<vertList.size(); j++){
			if(vertList[j]->getID()==evert){ des = true; break;}
		}
		if(soc==false){cout << "source is not found\n";}
		if(des==false){cout << "destination is not found\n";}
		
		if(soc){if(dec){
			Edge *tedge = new Edge(vertList[svert-1], vertList[evert-1], weit);
			edgeList.push_back(tedge);
			vertList[svert-1]->outList.push_back(tedge);
			vertList[evert-1]->inList.push_back(tedge);
		}}
	}
	
	void findVertex(int vtemp){ //need to be improved
		int rv = vtemp;
		vtemp = vtemp -1;
		
		bool exist= false;
		if(vertList[vtemp]->getID() == rv){
			exist = true;
		}
		if(exist){
			cout << vertList[vtemp]->getID() << "| ";
			for(int j=0; j<vertList[vtemp]->outList.size(); j++){
				cout << vertList[vtemp]->outList[j]->geteVertP()->getID() << " "; 
				
			}
			cout << endl;
		}else{ cout << vtemp << " does not exist";}
	}
	
	void dij(int sVert, int eVert){
		bool s = false;
		bool d = false;
		int source = sVert;
		int dest = eVert;
		PriorityQueue<int> pq2;
		pq.resetR();
		pq.resetC();
		
		for(int i = 0; i<vertList.size() && !s; i++){
			if(vertList[i]->getID() == source){ s=true;}
		}
		for(int i = 0; i<vertList.size() && !d; i++){
			if(vertList[i]->getID() == dest){ d=true;}
		}
		if(s != true || d !=true){ if(s!=true){ cout << "Source cannot be found\n";}
			if(d!=true){cout << "Destination cannot be found\n";}
			exit(0);
		}
		
		for(int i=0; i<vertList.size(); i++){
			Vertex* v = vertList[i];
			if(v->getID() == source){	
				pq.insertItem(0,v->getID());
			}else {
				pq.insertItem((10000),v->getID());
			}
		}
		vector<int> checked;	
		while(!pq.isEmpty()){
			Locator* loc = pq.min();
			Vertex* v = vertList[(pq.locGetElem(loc)-1)];
			for(int j =0; j<v->outList.size(); j++){   //relax
				bool there = false;
				for(int z =0; z<checked.size(); z++){ // relaxed don't go through
					if(checked[z] == v->outList[j]->geteVertP()->getID()){ there = true;}
				}
				if(!there){
					Locator* c = pq.findV(v->outList[j]->geteVertP()->getID());
					
					int sID = pq.locGetElem( loc );
					int eID = pq.locGetElem( c );
					int skey = pq.locGetKey(loc);
					int ekey = pq.locGetKey(c);
					int weight = v->outList[j]->getWeight();		
					if( ekey > skey + weight ){
						pq.locSetKey(c, ( skey + weight ));
						v->outList[j]->geteVertP()->setPID(v->getID());
					}
				}
			}
			checked.push_back(v->getID());
			pq2.insertItem(pq.locGetKey(loc),v->getID());// new queue
			pq.remove(loc);
			
		}
		Locator* print = pq2.findV(dest);
		int distance = pq2.locGetKey(print);
		pq.prR();
		pq.prC();
		
		vector<int> preW;
		vector<int> preI;
		//Okay now print out the weight b/w S and D
		for(int pk=0; pk<vertList.size(); pk++){
			if(dest==vertList[pk]->getID() && dest!=source){
				for(int p = 0; p<vertList[pk]->inList.size(); p++){
					if(vertList[pk]->getPID()==vertList[pk]->inList[p]->getsVertP()->getID()){
						preW.push_back(vertList[pk]->inList[p]->getWeight());       //weight put
						preI.push_back(vertList[pk]->inList[p]->getsVertP()->getID());  //vertices put
					}
				}
				if(dest != source){
					dest = vertList[pk]->getPID();
					pk = 0;
				}else if(dest == source){break;}
			}
		}
		
		for(int pw = preW.size()-1; pw>=0; pw--){   //weight print
			if(pw == preW.size()-1) cout << "\n    ";
			if(preW[pw]>=100){ cout << preW[pw] << "    ";}
			else if(preW[pw]>=10) {cout << preW[pw]<<"     ";}
			else{cout <<  preW[pw] << "       ";}
		}
		
		for(int i =0; i<=preW.size(); i++){     //ascii value print
			if(i==0){ cout << "\nS ----> ";}
			else if(i==preW.size()){ cout << "D";}
			else {cout << (char)(i+64) << " ----> ";}
		}
		
		// for(int pi = preI.size()-1; pi>=0; pi--){   //vertices print for test
			// if(pi == preI.size()-1) cout << "\n";
			// if(preI[pi]>=100){ cout << preI[pi] << "     ";}
			// else if(preI[pi]>=10) {cout << preI[pi]<<"      ";}
			// else{cout <<  preI[pi] << "       ";}
		// }
		cout << "\nTotal wight of the shortest path from S to D = " << distance << endl;
		
	}
};
#endif
