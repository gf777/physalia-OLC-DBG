/******************************************************************************

DBG demonstration
Giulio Formenti (giulio.formenti@gmail.com)

*******************************************************************************/


#include <iostream>
#include <list>
#include <vector>
#include <utility> //pair
#include <unordered_map>

using namespace std;

int main()
{
    //declare the problem
    string genome = "ATGCTGATCACAATATAGAT", Lkmer, Rkmer;
    int read_len = 7, k = 4, nodeUid = 0, n1 = 0, n2 = 0;
    vector<string> reads;
    unordered_map<string, int> nodesFW;
    unordered_map<int, string> nodesBW;
    vector<string> kmers;
    unordered_map<string, int> kmers_counts;
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
    
    //generate k-1 nodes from reads
    for(const auto& read : reads) {
        
        for (int i = 0; i<=read_len-k; i++) {
            
            cout<<"kmer: "<<read.substr(i, k)<<endl;
            kmers_counts[read.substr(i, k)]++;
            kmers.push_back(read.substr(i, k));
            
            Lkmer = read.substr(i, k-1);
            
            std::unordered_map<string,int>::const_iterator it = nodesFW.find(Lkmer);

            if (it != nodesFW.end()) {
                n1 = it->second;
            }else{
                nodesFW[Lkmer] = nodeUid;
                nodesBW[nodeUid] = Lkmer;
                n1 = nodeUid;
                nodeUid++;
                
                overlaps.resize(nodeUid+1);
            }
            
            cout<<"L k-1 mer: "<<Lkmer<<" (nodeUid: "<<n1<<")"<<endl;
            
            Rkmer = read.substr(i+1, k-1);
            
            it = nodesFW.find(Rkmer);

            if (it != nodesFW.end()) {
                n2 = it->second;
            }else{
                nodesFW[Rkmer] = nodeUid;
                nodesBW[nodeUid] = Rkmer;
                n2 = nodeUid;
                nodeUid++;
                
                overlaps.resize(nodeUid+1);
                
            }
            
            overlaps.at(n1).resize(nodeUid+1);
            
            cout<<"R k-1 mer: "<<Rkmer<<" (nodeUid: "<<n2<<")"<<endl;
            
            overlaps.at(n1).at(n2)++;
        
        }
        
    }
    
    //enumerate k-1 strings
    cout << "enumerate k-1 strings" << endl;
    for(const auto& node : nodesFW) {
        
        cout << "{" << node.first << ": " << node.second << "}\n";
    
    }
    
    //enumerate kmers
    cout << "enumerate kmers" << endl;
    for(const auto& kmer : kmers_counts) {
        
        cout << "{" << kmer.first << ": " << kmer.second << "}\n";
    
    }
    
    string path = nodesBW[0];
    
    //enumerate overlaps
    cout << "enumerate overlaps" << endl;
    for(int i = 0; i<overlaps.size(); i++) {
        
        for(int e = 0; e<overlaps[i].size(); e++) {
    
            cout << nodesBW[i] << "->" << nodesBW[e] << " (" << overlaps[i].at(e) <<")" << endl;
            
            if (overlaps[i].at(e) > 0) {
            
                //Euleran path
                path += nodesBW[e].back();
                
            }
            
        }
    }
    
    cout<<"The original genome is:\t\t\t"<<genome<<endl;
    //final path
    cout<<"The reconstructed genome is:\t"<<path<<endl;

    return 0;
}
