#include <iostream>
#include<cstdio>
#include <vector>
#include <string>
#include <stack>
#include<fstream>
using namespace std;

class TextEditor {
    private:
        vector<string> data;
        stack<vector<string>> undoStack;
        stack<vector<string>> redoStack;

    public:
        void createStorage(){
            data.clear();
        }
        void insertData(string line) {
            string word = "";
            //cout<<"....................";
            for (auto x : line)
            {
                if (x == ' ')
                {
                    data.push_back(word);
                    word = "";
                }
                else {
                    word = word + x;
                }
            }
            data.push_back(word);
            undoStack.push(data);
        }

        void updateData(int index, string line) {
            if (index >= 0 && index < data.size()) {
                data[index] = line;
            } else {
                cout << "Error: Index out of range" << endl;
            }
            undoStack.push(data);
        }

        void appendData(string line) {
            data.push_back(line);
            undoStack.push(data);
        }

        int searchData(string searchTerm) {
            int index = -1;
            for (int i = 0; i < data.size(); i++) {
                if (data[i]==searchTerm) {
                    return i;
                }
            }
            return index;
        }

        void deleteData(int index) {
            if (index >= 0 && index < data.size()) {
                data.erase(data.begin() + index);
            } else {
                cout << "Error: Index out of range" << endl;
            }
            undoStack.push(data);
        }

        void displayData() {
            int index = 0;
            for (string line : data) {
                cout << index << ": " << line << endl;
                index++;
            }
        }

        void undo() {
            if (!undoStack.empty()) {
                redoStack.push(data);
                data = undoStack.top();
                undoStack.pop();
            } else {
                cout << "Error: No undo available" << endl;
            }
        }

        void redo() {
            if (!redoStack.empty()) {
                undoStack.push(data);
                data = redoStack.top();
                redoStack.pop();
            } else {
                cout << "Error: No redo available" << endl;
            }
        }

        void saveData() {
            string store="";
            for(auto word:data){
                store+=word;
                store+=" ";
            }
            ofstream fout;
            cout<<"Enter name for your file:";
            string s;
            getline(cin,s);
            s+=".txt";
            fout.open(s);
            fout<<store;
            fout.close();

        }
};

int main() {
    TextEditor editor;
    int choice;
    while(true){
        cout << "Menu:" << endl;
        cout << "1:Create storage for your data" << endl;
        cout << "2:Insert data" << endl;
        cout << "3:Update data" << endl;
        cout << "4:Append data" << endl;
        cout << "5:Search data" << endl;
        cout << "6:Delete data" << endl;
        cout << "7:Display data on console" << endl;
        cout << "8:Undo operation" << endl;
        cout << "9:Redo operation" << endl;
        cout << "10:Save data in permanent storage" <<endl;
        cout<<"0:To Exit"<<endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        if(choice==1){
            editor.createStorage();
            system("cls");
            cout<<"created"<<endl;
        }
        else if(choice==2){
            cout<<"Insert data:";
            string line;
        
            getline(cin,line);
    
            editor.insertData(line);
            cout<<"Inserted"<<endl;
        }
        else if(choice==3){
            system("cls");
            editor.displayData();
            cout<<"Enter word:";
            string index;
            getline(cin,index);
            int temp = editor.searchData(index);
            if(temp==-1){
                cout<<"Not Found"<<endl;
                continue;
            }
            cout<<"Enter new word:";
            string line;
            getline(cin,line);
            editor.updateData(temp,line);
            cout<<"Updated"<<endl;
        }
        else if(choice==4){
            system("cls");
            cout<<"Enter data:";
            string line;
            getline(cin,line);
            editor.appendData(line);
            cout<<"Appended"<<endl;
        }
        else if(choice==5){
            system("cls");
            cout<<"Enter data:";
            string s;
            getline(cin,s);
            int temp = editor.searchData(s);
            if(temp==-1){
                cout<<"Not Found"<<endl;
            }
            else{
                cout<<"Data Found"<<endl;
            }
        }
        else if(choice==6){
            system("cls");
            cout<<"Enter data till:";
            string index;
            getline(cin,index);
            int temp = editor.searchData(index);
            if(temp==-1){
                cout<<"Not Found"<<endl;
                continue;
            }
            else{
                editor.deleteData(temp);
            }
            cout<<"Deleted"<<endl;
        }
        else if(choice==7){
            system("cls");
            editor.displayData();
        }
        else if(choice==8){
            system("cls");
            editor.undo();
            cout<<"Undo Succesful"<<endl;
        }
        else if(choice==9){
            system("cls");
            editor.redo();
            cout<<"Redo Succesful"<<endl;
        }
        else if(choice==10){
            system("cls");
            editor.saveData();
            cout<<"Data saved succesfully"<<endl;
        }
        else {
            
            break;
        }
    }
    return 0;
}