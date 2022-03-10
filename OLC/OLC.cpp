/******************************************************************************

OLC demonstration
Giulio Formenti (giulio.formenti@gmail.com)

*******************************************************************************/

#include <iostream>
#include <list>
#include <vector>
#include <utility> //pair
#include <unordered_map>

using namespace std;

//DFS to walk the graph
void DFS(string* path, int v1, vector<string> reads, vector<vector<int>> overlaps, unordered_map<int, bool>* visited) {
    
    if (!(*visited)[v1]) {
    
        path->insert(path->size(),reads[v1].substr(4,1));
        
        cout<<"current path is: "<<*path<<endl;
        
        if(overlaps.at(v1).size() > 0) {
            
            int v2 = overlaps.at(v1).at(0);
            
            (*visited)[v1] = true;
        
            DFS(path, v2, reads, overlaps, visited);
            
        }
        
    }
    
};

int main()
{
    //declare the problem
    string genome = "ATGCTGATCA";
    int read_len = 5, overlap_len = 1;
    vector<string> reads;
    vector<vector<int>> overlaps;
    
    //check variables
    cout<<"The original genome is: "<<genome<<endl;
    cout<<"Genome size: "<<genome.size()<<endl;

    //generate reads
    for (int i = 0; i <= genome.size()-read_len; i++)
        reads.push_back(genome.substr(i,read_len));
    
    //check reads
    for(const auto& read : reads)
      std::cout << read << std::endl;
    
    auto isOverlap = [read_len, reads, overlap_len](int a, int b) {
        
        return reads[a].substr(1, read_len-overlap_len) == reads[b].substr(0, read_len-overlap_len) ? true : false;
        
    };
    
    //resize adjaciency list to accomodate nodes
    overlaps.resize(reads.size());
    
    //generate and print overlaps
    for(int i = 0; i <= reads.size();) {
        
        for(int e = i+1; e < reads.size(); e++) {
            
            if(isOverlap(i, e)) {
        
                std::cout << "read " << reads[i] << " (" << i << ") overlaps with read " << reads[e] << " (" << e << ")" << std::endl;
                
                //build graph
                overlaps.at(i).push_back(e);
                
            }
        
        }
        
        i++;
        
    }
    
    int start_node = 0;
    
    string path = reads[start_node].substr(0,read_len-overlap_len);
    unordered_map<int, bool> visited;
    
    //walk the graph (DFS)
    DFS(&path, start_node, reads, overlaps, &visited);
    
    //output consensus
    cout<<"final path is: "<<path<<endl;

    return 0;
}
