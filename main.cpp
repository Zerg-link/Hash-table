#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm> 
using namespace std;
struct bucket {
    long long value;
    int true_key;
};
//______________________________________________________________________________
int module = 100000;
int hash_func(int key) {
    return (key % module);
}
//______________________________________________________________________________
void get(int key, vector <vector <bucket> > &arr) {
    int hash_value = hash_func(key);
    bool F=true;
    if ( arr[hash_value].empty() ) 
        cout<<"None\n";
    else 
        {
            // Бегаем по второму вектору до тех пор, пока либо ничего не найдём (cout<<"None"), либо bucket.true_key == key   
            bucket b;
            bucket b_answer;
            for (const bucket& b : arr[hash_value]) {
                if (b.true_key == key) {
                    F=false;
                    b_answer.value=b.value;
                    b_answer.true_key=b.true_key;
                }
            }
            // Если мы дошли до начала второго вектора, то значит, что ничего и не было
            if (F) cout<<"None\n";
            else 
                cout<<b_answer.value<<"\n";
        }
}
//______________________________________________________________________________
void put(int key, long long value, vector <vector <bucket> > &arr) {
    int hash_value = hash_func(key);
    bucket b;
    b.true_key = key;
    b.value = value;
    arr[hash_value].push_back(b);
}
//______________________________________________________________________________
void Delete(int key, vector <vector <bucket> > &arr) {
    int hash_value = hash_func(key);
    if (arr[hash_value].empty()) 
        cout<<"None\n";
    else {  
            bool F=true;
            bucket b;
            bucket b_end;
            // Находим значения последнего элемента вторичного вектора
            for (const bucket& b : arr[hash_value]) {
                b_end.value=b.value;
                b_end.true_key=b.true_key;
            }
            for ( bucket& b : arr[hash_value]) {
                if (b.true_key == key) {
                    swap(b, b_end);
                    if (F) cout<<b.value<<"\n";
                    arr[hash_value].pop_back();
                    F=false;
                    
                }
            }
            // Если мы дошли до начала второго вектора, то значит, что ничего и не было
            if (F) cout<<"None\n";
    }
}
//______________________________________________________________________________
int main()
{
    vector <vector <bucket> > Hash_table;
    Hash_table.resize(100000);
    int count_of_command;
    cin>>count_of_command;
    string line;
    cin.ignore();
    // Какая операция нам требуется?
    bool F_put;
    bool F_get;
    bool F_delete;
    // Переменные для передачи в функцию
    int a;
    for (int i=1; i<=count_of_command; i++) {
        getline(cin, line);
        a=-1;
        F_put=false;
        F_get=false;
        F_delete=false;
        stringstream ss(line);
        for (string word; ss >> word;) {
            // Ловим слово-команду
            if (word == "put") 
                F_put=true;
            else
            if (word == "get") 
                F_get=true;
            else
            if (word == "delete") 
                F_delete=true;
            else {
            // put
                if (F_put && a==-1) 
                    a=stoi(word); 
                else 
                    if (F_put && a!=-1) 
                        put(a, stoi(word), Hash_table);
                    else
                    // get
                        if (F_get && a==-1) 
                            get(stoi(word), Hash_table);
                        else 
                            if (F_delete && a==-1) 
                               Delete(stoi(word), Hash_table);
            }
        }
    }
    return 0;
}