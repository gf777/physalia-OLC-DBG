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
    string genome = "ATGCTGATCT", Lkmer, Rkmer;
    int read_len = 7, k = 5;
    vector<string> reads;
    unordered_map<string, bool[4]> DBG;
    
    unordered_map<char,int> code = {
                            {'A',0},
                            {'C',1},
                            {'G',2},
                            {'T',3}
    };
    
    unordered_map<int,char> rev = {
                            {0,'A'},
                            {1,'C'},
                            {2,'G'},
                            {3,'T'}
    };
    
    //check variables
    cout << "The original genome is: " << genome << endl;
    cout << "Genome size: " << genome.size() << endl;
    cout << "Read length is: " << read_len << endl;
    cout << "Read number is: " << genome.size()-read_len+1 << endl;
    cout << "kmer length is: " << k << endl;

    //generate reads
    for (int i = 0; i <= genome.size()-read_len; i++)
        reads.push_back(genome.substr(i,read_len));
    
    //print reads
    for (int i = 0; i < reads.size(); i++)
        cout << reads[i] << " ("<< i << ")" << endl;
    
    //generate k-1 nodes from reads
    for(string read : reads) {
        
        for (int i = 0; i<=read_len-k; ++i) {
            
            string kmer = read.substr(i, k);
            
            cout<<"kmer: "<<kmer<<endl;
            
            Lkmer = read.substr(i, k-1);
            cout<<"L k-1 mer: "<<Lkmer<<endl;
            
            Rkmer = read.substr(i+1, k-1);
            cout<<"R k-1 mer: "<<Rkmer<<endl;
            
            DBG[Lkmer][code[kmer.back()]] = true;

        }
        
    }
    
    string path = genome.substr(0, k-1);
    
    Lkmer = path;
    
    //walk the graph
    for (int i = 0; i <= genome.size()-read_len; ++i) {
        
        for (int j = 0; j < 4; ++j) {
            
            if(DBG[Lkmer][j] == true) {
                
                path.push_back(rev[j]);
                Lkmer = path.substr(path.length() - k+1);
                
            }
            
        }
        
    }
    
    cout<<"The original genome is:\t\t\t"<<genome<<endl;
    //final path
    cout<<"The reconstructed genome is:\t"<<path<<endl;

    return 0;
}
