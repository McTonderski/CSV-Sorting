#include<fstream>
#include<iostream>
#include<vector>
#include<string>
#include<ctype.h>
#include<sstream>
#include<stdlib.h>
#include<algorithm>
#include<functional>
using namespace std;

auto header(){
    cout<<"-------CSV manager-------"<<endl;
}

auto task_1(){
    cout<<"Choose column to sort after"<<endl;
}

void save(const vector<vector<string>>& data, const vector<string>& headers, string argv){
    system("CLS"); 
    fstream fin;
    fin.open(argv, ios::out);
    string head;
    for(string a : headers){
        head += a + ',';
    }
    head.pop_back();
    head += "\n";
    string data_to_save;
    for(vector<string> tmp : data){
        string tmp_data;
        for(string tmp_loop: tmp){
            tmp_data += tmp_loop + ",";
        }
        tmp_data.pop_back();
        tmp_data += "\n";
        data_to_save += tmp_data;
    }
    data_to_save.pop_back();
    string out = head + data_to_save;
    fin << out;
    fin.close();
    cout<<"File saved thank you for using program!";
}

void csv_sort(int sort_after, bool order,int col_count, const vector<string>& content, string argv){
    vector<vector<string>> data;
    vector<string> set;
    set = vector<string>(content.begin() + 1, content.end());
    ///dividing dataset to columns and rows for sorting purpouse
    for(auto v: set){
        stringstream s(v);
        vector<string> holder;
        while(s.good()){
            string substring;
            getline(s, substring, ',');
            if(substring != "\n")
                holder.push_back(substring);
        }
        data.push_back(holder);
        for(auto j: holder)
            holder.pop_back();
    }
    ///Sorting CSV files to user asking 
    sort(data.begin(), data.end(), bind([](vector<string>& a, vector<string>& b, int variabke, bool derek){
        return (derek) ? a[variabke - 1] < b[variabke - 1] :  a[variabke - 1] > b[variabke - 1];
    },std::placeholders::_1, std::placeholders::_2, sort_after, order));
    
    save(data, vector<string>(content.begin(), content.begin()+1), argv);
}

int menu(const vector<string>& col_names){
    system("CLS");
    header();
    task_1();
    int id = 1;
   
    for(auto i: col_names){
        cout<<id<<". "<<i<<endl;
        id++;
    }

    int a;
    try{
        scanf("%d", &a);
        if(a > id)
            throw a;
    }catch(int a){
        cout<<"Please choose one from the list!"<<endl;
        menu(col_names);
    }

    return a;
}

bool order_choice(){
    system("CLS");
    header();
    cout<<"Choose order you want to sort after:"<<endl;
    cout<<"1. Ascending"<<endl;
    cout<<"2. Descending"<<endl;
    int a {};

    try{
        scanf("%d", &a);
        if(a > 2)
            throw a;
    }catch(int a){
        cout<<"Please choose one from the list!"<<endl;
        order_choice();
    }

    return (a==2) ? false : true;
}

auto work_on_sheet(const vector<string>& content, string argv){
    vector<string>col_names;
    int col_count;
    if(!isdigit(content[0][0])){
        stringstream s(content[0]);
        
        while(s.good()){
            string substring;
            getline(s, substring, ',');
            col_names.push_back(substring);
        }
        // for(auto i: col_names){
        //     cout<<i<<endl;
        // }
        col_count = col_names.size();
    }else{
        stringstream s(content[0]);
        cout<<"File doesn't contain headers"<<endl;
        while(s.good()){
            string substring;
            getline(s, substring, ',');
            col_names.push_back(substring);
        }
        // for(auto i: col_names){
        //     cout<<i<<endl;
        // }
        col_count = col_names.size();
    }
    int sort_after = menu(col_names);
    bool order = order_choice();
    csv_sort(sort_after, order, col_count, content, argv);
}

//
//

int main(int argc, char* argv[]){
    fstream fout;
    string line, word;
    try{
        if(argc < 1){
            throw argc;
        }
        fout.open(argv[1], ios::in);
        vector<string> lines;
        while(!fout.eof()){
            string s;
            getline(fout, s);
            lines.push_back(s);
        }
        fout.close();
        work_on_sheet(lines, argv[1]);
    }catch(int x){
        cout <<"You didn't provided a file name!";
        return -1;
    }
    return 0;
}