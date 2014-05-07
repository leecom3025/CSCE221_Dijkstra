#include <iostream>
#include <string>
#include "Graph.h"
using namespace std;

int main()
{       // you can use the following code to test your graph. 
        // you can also change your input file to do more testing
        // verify the results
	int wow;
	
	string again, right, left, move, move2, str;
	left = 'y'; 	right = 'Y'; 	again = 'Y'; move = 'm'; move2 = 'm';
	while(move.compare(move2)==0){
		cout << "1. Default(random_sparse.txt)\n"
		<< "2. User data\n" << "Choice: ";
		cin >> wow;
		if(wow == 1){ 
			move = 'a';
			str = "random_sparse.txt";			
		}
		else if(wow == 2){ 
			string filename;
			cout <<"Name of the file: ";
			cin >> filename;
			ifstream infile;
			const char* temp = filename.c_str();
			infile.open(temp);
			if(infile.good()){ 
				cout << "File opened\n";
				str = filename;
				move = 'a';
			} else{cout <<"File cannot be found\n"; move ='m'; }
		}else{cout << "Please type 1 or 2\n";}
	}
	
	Graph graph(str);
	
	while (again.compare(right) == 0 || again.compare(left) == 0)
	{
		char choi;
		cout << "1. Insert Edge\n"
		<<"2. Insert Vertex\n"
		<<"3. Print all the vertex\n"
		<<"4. Find adjacent vertex\n"
		<<"5. Find shortest path from source to end\n"
		<<"6. Exit\n"
		<<"Choice: ";
		cin >> choi;
		
		if(choi == '1'){
		//need to find source and end first;
			int svert, evert, weit;
			bool scheck,echeck = false;
			cout << "Source: ";
			cin >> svert;
			// graph.getVertices();
			// for(int i=0; i<vertList.size(); i++){
				// if(svert==vertList[i]->getID()) scheck = true;
				// else {cout << "Source does not exist\n"; return 0;}
			// }
			cout << "Destination: ";
			cin >> evert;
			
			// for(int i=0; i<vertList.size(); i++){
				// if(evert==Graph::getVertices().vertList[i]->getID()) echeck = true;
				// else {cout << "End does not exist\n"; return 0;}
			// }
			cout << "Weight: ";
			cin >> weit;
			if(weit<0){cout << "Weight should be bigger than 0\n"; return 0;}
			graph.addEdge(svert,evert,weit);
			
		} else if(choi == '2'){
			int vert;
			cout << "Insert vertex: ";
			cin >> vert;
			graph.addVertex(vert);
		
		
		} else if(choi == '3'){
			graph.PrintGraph();
			
		} else if(choi == '4'){
			int vert;
			cout << "Vertex: ";
			cin >> vert;
			graph.findVertex(vert);
		} else if(choi == '5'){
			int sVert, eVert;
			cout << "Source: ";
			cin >> sVert;
			cout << "Destination: ";
			cin >> eVert;
			graph.dij(sVert, eVert);
		} else if(choi == '6'){
			cout <<endl<< "Exit"<<endl;
			break;
		}
		else
			{cout << "INVALID NUMBER" <<endl; break;}
		cout <<endl;
	}
		
		return 0;
}
