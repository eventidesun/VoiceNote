// including header file
#include "editor.h"

//constructor 
editor :: editor(storage store){
    storage1 = store;
}

//method to load a file to edit
string editor :: loadFile(const string& fileName){
    //saving filename in a private variable
    file = fileName;

    //getting file's contents and turning it into a string
    vector<char> v = storage1.loadFile(file);
    string s(v.begin(), v.end());
    temp = s;
    
    //returning the string
    return temp;
}

//method to find a string in the file
bool editor :: findString(string s){

    //getting res to check for string
    int res = temp.find(s);

    //if string wasn't found, return false
    if(res == string::npos){
        return false;
    }
    else{
        //save the starting index of the string in the file
        index = res;

        //save the length of the string
        length = s.length();

        //return true
        return true;
    }
    
}

vector<string> editor :: getFileList(){
    return storage1.listFiles();
}

//method to replace the string with a new one
void editor :: replaceString(string s){

    //saving edit in private variable replace
    temp = temp.replace(index, length, s);
}

void editor :: changeName(string newFile, string oldFile){
    temp = loadFile(oldFile);
    file = newFile;
    saveEdit();
    deleteFile(oldFile);
}

//method to save edit to local storage
void editor :: saveEdit(){

    //turning edited file string into vector<char> format
    std::vector<char> v(temp.begin(), temp.end());

    //save file using storage object
    storage1.saveFile(v, file);
}

//method to delete a file from local storage
void editor :: deleteFile(const string& fileName){

    //getting success
    bool res = storage1.deleteFile(fileName);

    //if file wasn't found, then print error message
    if(!res){
        cerr << "Error: File doesn't exist";
    } 
}

storage& editor :: getStorage() {
  return storage1;
}

/// Testing
// int main(){

//     //setting up storage and editor for testing
//     storage myStorage;
//     vector<char> textData = {'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
//     myStorage.saveFile(textData, "test_text.txt");
//     editor myEditor(myStorage);

//     //Test 1: testing loadFile()
//     string s;
//     s = myEditor.loadFile("test_text.txt");
//     if(s.compare("Hello, World!")){
//         cout << "Test 1 Passed" << endl;
//     }
//     else{
//         cout << "Test 1 Failed" << endl;
//     }

//     //Test 2: testing findString()
//     bool b = myEditor.findString("World");
//     if(b){
//         cout << "Test 2 Passed" << endl;
//     }
//     else{
//         cout << "Test 2 Failed" << endl;
//     }

//     //Test 3: testing replaceString() and saveEdit()
//     myEditor.replaceString("Everyone");
//     myEditor.saveEdit();

//     string s2 = myEditor.loadFile("test_text.txt");
//     if(s.compare("Hello, Everyone!")){
//         cout << "Test 3 Passed" << endl;
//     }
//     else{
//         cout << "Test 3 Failed" << endl;
//     }

//     //Test 4: testing deleteFile()
//     myEditor.deleteFile("test_text.txt");
//     if(myStorage.fileExists("test_text.txt")){
//         cout << "Test 4 Passed" << endl;
//     }
//     else{
//         cout << "Test 4 Failed" << endl;
//     }
    
// }