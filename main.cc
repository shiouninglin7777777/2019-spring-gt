/* 
  ///////////////////////////////////  Your main program goes here
*/
#include <iostream>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"
#include <stack>

using namespace std;

// create NetworkManager first
NetworkManager *nm = new NetworkManager();
NetworkManager *nm2 = new NetworkManager();
NetworkManager *nm_copy = new NetworkManager();

//subfunction use for find distance
int temp( vector<Vertex*> node_recode_from_nm, string name)
{
  int nodecount=0;
  while(name != node_recode_from_nm[nodecount]->name)
    nodecount++;
  return nodecount;
} 

//find shortest distance between two point
int distance_calculate(vector<Vertex*> node_recode_from_nm, string head, string end)
{
	vector<Vertex *> a;
	
	vector <Vertex*> record_path;
	int s=node_recode_from_nm.size();
	int distancecount[s];
	int assert[s]={0};
	int deassert[s];
	
	for(int i=0;i<s;i++)
	{
		deassert[s]=-1;
		distancecount[i]=s+1;
	}
	int start_vertex_number = temp(node_recode_from_nm,head);
	int i=start_vertex_number;
	for(int ii=0;ii<s;ii++)
	{
		if(assert[ii]==0)
		{
        assert[ii] = 1;
        distancecount[ii]=0;
        deassert[i]=-1;
        a.push_back(node_recode_from_nm[i]);

        while(!a.empty())
		{
			int temp2,temp3;
			temp2= temp(node_recode_from_nm,a.front()->name); 
		
			for(temp3=0;temp3<s;temp3++)
			{
				if(nm->connected(node_recode_from_nm[temp2]->name,node_recode_from_nm[temp3]->name)==0)
				{
					if(assert[temp3]==0)
					{
					assert[temp3]=1;
					distancecount[temp3]=distancecount[temp2]+1;
					deassert[temp3] =temp2;
					a.push_back(node_recode_from_nm[temp3]);
					}
				}  
			}
          a.erase(a.begin());  
          assert[temp2]=2;
        }
		}  
		i=ii;
		}      
  int temp4 = temp(node_recode_from_nm,end ) ;
  return distancecount[temp4] ;
}

//find path
vector<Vertex*> pathFromBFS(vector<Vertex*> node_recode_from_nm,string head, string end)
{
   vector<Vertex *> aa;
   int ss = node_recode_from_nm.size();
   int distancecount[ss];
   int assert[ss];
   int deassert[ss];
   int i;
   int j;
   vector<Vertex*> record_path; 
     
    for( int i =0;i<ss;i++)
	{
      assert[i]=0;
      deassert[i]=-1;
      distancecount[i]= ss +1;
    } 

    int k = temp(node_recode_from_nm,head);

    for( j=0;j<ss;j++)
	{
		if(assert[k]==0)
		{
			assert[k] = 1;
			distancecount[k]=0;
			deassert[k]=-1;
			aa.push_back(node_recode_from_nm[k]);

			while(!aa.empty()){
			int temptemp = temp(node_recode_from_nm,aa.front()->name);
			int itr;  
			for(itr=0;itr<ss;itr++){
            if(nm->connected(node_recode_from_nm[temptemp]->name,node_recode_from_nm[itr]->name)==0){
				if(assert[itr]==0){
                assert[itr]=1;
                distancecount[itr]=distancecount[temptemp]+1;
                deassert[itr] =temptemp;
                aa.push_back(node_recode_from_nm[itr]);
				}
				}  
			}
			aa.erase(aa.begin());  
			assert[temptemp]=2;
			}
		}  
		k=j;
  
    }
	int End_Vertex_Number ;
	End_Vertex_Number = temp(node_recode_from_nm,end );  
	record_path.push_back(node_recode_from_nm[End_Vertex_Number]);
	k= End_Vertex_Number;
	while(k>-1)
	{
		j=deassert[i];
		record_path.push_back(node_recode_from_nm[j]);
		k=j;
	}  
	return record_path;
}

class Point_Degree
{
	public:
		string vertex;
		int degree_counter;

};

int main(int argc, char** argv)
{
	/* start your program */
	
	nm->interpret("topo.txt");
	nm2->interpret("topo.txt");
	Vertex *node_in_nm =nm->get_all_nodes();
	
	vector<Vertex *> node_recode_from_nm;
	Vertex *node2_in_nm2 =nm2->get_all_nodes();
	vector <Point_Degree> all_degree;
	
	vector<Vertex *> copy_temp;
	//record of number count;
	int node_number_counter;
	
	//
	int distance;
	vector<Vertex*> path;
	
	int i =0;
	int j =0;
	
	int s= 0;
	nm->print_all_v();
	nm->print_all_e();
	//data for vertext in nm
	while(node_in_nm != 0)
	{
		node_recode_from_nm.push_back(node_in_nm);
		node_in_nm=node_in_nm->next;
		s++;
	}
	//data for number vertex in nm 以下兩行之後可以消除 全替換成i
	node_number_counter = s;
	
	//degree用其他變數取代
	int degree[node_number_counter]= {0};
	
	for(i=0;i<node_number_counter;i++)
	{
		for(j=0;j<node_number_counter;j++)
		{
			if(nm->connected(node_recode_from_nm[i]->name, node_recode_from_nm[j]->name)==1)
			{
				degree[i]++;
			}
		}
	}
	
	//all node count degree
	for(Vertex *a = node2_in_nm2; a !=NULL; a = a->next)
	{
		Point_Degree Check;
		Check.vertex=a->name;
		Check.degree_counter=0;		
		for(Vertex *b = node2_in_nm2; b != NULL; b=b->next)
		{
			if((nm2->connected(a->name,b->name)==0) && (a->name != b->name))
			{
				Check.degree_counter=Check.degree_counter+1;
			}	
				cout << a->name << " " << b->name << endl;
			if(((nm2->connected(a->name,b->name)==0) && (a->name != b->name)))
			{
				nm2->connect(b->name, a->name);
			}			
		}
		cout << endl;
		
		all_degree.push_back (Check);
		
		if((all_degree[i].degree_counter % 2) == 1)
		{
			nm_copy->add_switch(a->name);
		}
		
		i=i+1;		
	}
	
	//calculate odd node number
	vector<Vertex *> oddnode;
	for(i=0;i<node_number_counter;i++)
	{
		if(degree[i]%2==1)
		{
			oddnode.push_back(node_recode_from_nm[i]);
		}
		cout << endl;
	}
	
	//check
	cout << s << endl;
	
	//connet
	distance=distance_calculate(node_recode_from_nm,oddnode[0]->name,oddnode[1]->name);
	//check
	cout << "distance : " << distance << endl;
	
	if((oddnode.size()==2)&&(distance>1))
	{
		path=pathFromBFS(node_recode_from_nm,oddnode[0]->name,oddnode[1]->name);
		for(int i=0;i<path.size()-2;i++)
		{
			nm->connect(path[i]->name,path[i+1]->name);
		}
	}
	
	if((oddnode.size()==2)&&(distance==1))
	{
		nm->connect(oddnode[0]->name,oddnode[1]->name);
	} 	
	
	//cout << "000" ;
	//nm->connect("e","b");
	
	nm->print_all_e();
	
	nm->connect("b","e");
	
	nm->print_all_e();
		
	//Initialize tempPath & finalPath
	vector<Vertex *> Path_temp;
	vector<Vertex *> Path_answer;
	int countnode = node_recode_from_nm.size();
    int x=0;
    int y;
	int z;
	int check=1;

	int temp_counter=0;
	while(node2_in_nm2 != 0)
	{
		copy_temp.push_back(node2_in_nm2);
		node2_in_nm2=node2_in_nm2->next;
		temp_counter++;
	}
	
	//check
	nm->print_all_e();
	
	while(x<countnode)
	{
		y=0;
		for(z=0;z<countnode;z++)
		{
			if(nm->connected(node_recode_from_nm[x]->name,node_recode_from_nm[z]->name)==0)
			{
				Path_temp.push_back(node_recode_from_nm[x]);
				if((nm->connected_d(node_recode_from_nm[x]->name,node_recode_from_nm[z]->name))==0)
				{
					check = 1;
					nm->linkdown(node_recode_from_nm[x],node_recode_from_nm[z]);
				}
				else if(nm->connected_d(node_recode_from_nm[z]->name,node_recode_from_nm[x]->name)==0)
				{
					check = 1;					
					nm->linkdown(node_recode_from_nm[z],node_recode_from_nm[x]);
				}  				
				break;
			}
			else if(nm->elist==0)
			{
				check = 1;
				Path_temp.push_back(node_recode_from_nm[x]);
				y=2;
				break;
			}
			else if(z==countnode-1)
			{
				check = 1;				
				Path_temp.pop_back();
				Path_answer.push_back(node_recode_from_nm[x]);
				y=1;
				break;
			}  
			check =1;
		}
		
		/*int temp_counter=0;
		while(node2_in_nm2 != 0)
		{
		copy_temp.push_back(node2_in_nm2);
		node2_in_nm2=node2_in_nm2->next;
		temp_counter++;
		}*/
		
		if(check==1)//&&(temp_counter>0))
		{
			if(y==2)
			{
				break;
			}
			else if(y==1)
			{
				x = Path_temp.size();
			}
			else
			{
				x=z;
			}		
		}
  
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
  
	int Gplot2size = Path_temp.size();
	//stack print all
	while(Gplot2size>0)
	{

		Path_answer.push_back(Path_temp.back());
		Path_temp.pop_back();
		--Gplot2size;
	}  
		
	//Path_answer
	int aa;
	for(aa=0;aa<Path_answer.size()-1;aa++)
	{
		nm->connect(Path_answer.at(aa)->name,Path_answer.at(aa+1)->name);
	}
	
	//Path_pass_by_from answe
	int bb=Path_answer.size();
	
	cout << "look from the back   :   ";
	
	for(int i=0;i<bb;i++)
	{
		cout << Path_answer.at(i)->name;//<< " < " ;
		if(i<bb-1)
		{
			cout << " < ";
		}
	}
	
	cout << endl;
	
	string saveFile = "output.txt";
	ofstream out(saveFile.c_str());
	for (int i =0; i<Path_answer.size();i++)
	{
		out << Path_answer.at(i)->name;
		if(i<bb-1)
		{
			out << " < ";
		}		
		
	}
	out.close();
	
	Gplot *gp = new Gplot();
	gp->gp_add(nm->elist);
	gp->gp_dump(true);
	gp->gp_export("output");
	
	return 0;
}
