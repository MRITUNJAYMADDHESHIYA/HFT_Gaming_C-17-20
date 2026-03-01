//1.sparse matrix:- mostly zero elements
//2.CSR(Compressed Sparse Row) format:-store using three arrays
//values[], row_index[], col_index[]

//3.save memory and speed up computations

#include <iostream>
#include <vector>
using namespace std;

struct CSRMatrix{
    vector<double> values;
    vector<int>    col_index;
    vector<int>    row_ptr;
    int rows, cols;

    CSRMatrix(int r, int c): rows(r), cols(c){
        row_ptr.push_back(0);
    }

    void addRow(const vector<pair<int, double>> &row){
        for(auto [col, val]: row){
            values.push_back(val);
            col_index.push_back(col);
        }
        row_ptr.push_back(values.size());
    }

    void display(){
        cout<<"values: ";
        for(auto v: values) cout<< v <<" ";
        cout<<"\ncol_index: ";
        for(auto c: col_index) cout<< c << " ";
        cout<<"\nrow_ptr: ";
        for(auto r: row_ptr) cout<< r << " ";
        cout<<endl;
    }
};

int main(){
    CSRMatrix m(3, 4);
    m.addRow({{2,3}});
    m.addRow({{0, 33}});
    m.addRow({{0, 7}, {3, 5}});

    m.display();
}
