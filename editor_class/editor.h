#ifndef EDITOR_H
#define EDITOR_H

// Importing c++ libraies and storage class 
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "../storage_class/storage.h"

using namespace std;

/** @class editor
 * 
 * @brief A class to edit files. 
 * 
 * @details 
 * This class allows other classes to edit and delete files from storage. 
 *
 * @author Jasmine Vu
 */
class editor{

    public:
    
    /**
     * @brief Contructor of the editor class.
     * 
     * @details
     * This function creates an editor object with a storage object.
     *
     * @param store The storage object in which files will be loaded and stored.
     *
     * @usage
     * editor myEditor(storage myStorage);
     *
     */
    editor(storage store);

    /**
     * @brief Loads a file from storage.
     * 
     * @details
     * This function loads a spcified file from local hard drive using a storage object.
     * Then the file is stored as a string.
     *
     * @param fileName The file's name.
     *
     * @return The file's contents as a string.
     *
     * @usage
     * string file = myEditor.loadFile("123.txt");
     *
     */
    string loadFile(const string& fileName);

    /**
     * @brief Finds a string in the file
     * 
     * @details
     * This function searches the file for a specified string. 
     * Then, the index and the length of the string is saved.
     *
     * @param s The string being found.
     *
     * @return False if string was not found and true if it was found
     *
     * @usage
     * bool found = myEditor.findString("test");
     *
     */
    bool findString(string s);

    /**
     * @brief Gets list of file names from storage
     *
     * @details 
     * Using storage object, this method retrieves the list of file names and returns it
     *
     * @return A list of all the file names
     *
     * @usage
     * vector<string> list = myEditor.getFileList();
     *
     */
    vector<string> getFileList();

    /**
     * @brief Changes the name of the file
     * 
     * @details
     * This function changes the name of the file by saving a file with the new name with the same contents.
     * Then, the old file is deleted.
     *
     * @param newFile The name of the new file
     * @param oldFile The name of the old file
     *
     * @usage
     * myEditor.changeName("newfilename.txt", "test.txt")
     *
     */
    void changeName(string newFile, string oldFile);

    /**
     * @brief Replaces the found string in the file
     * 
     * @details
     * This function replaces the string found with findString() function with a specified string.
     * Saves the edit in a private variable called replace.
     *
     * @param s The string that's replacing the other string
     *
     * @usage
     * myEditor.replaceString("Hello!");
     *
     */
    void replaceString(string s);

    /**
     * @brief Saves the edit to local drive
     * 
     * @details
     * This function saves the most recently opened file to local storage using storage object
     *
     * @usage
     * myEditor.saveEdit();
     *
     */
    void saveEdit();

    /**
     * @brief Deletes file
     * 
     * @details
     * This function deletes a specified file from local storage
     * An error message is printed if the file doesn't exist
     *
     * @usage
     * myEditor.saveEdit();
     *
     */
    void deleteFile(const string& fileName);

    storage& getStorage();

    private:

    //variables

    /**
     * A storage variable for storage object.
     * Used to load and save files to local drive
     */
    storage storage1;

    /**
     * A temporary string to hold file's contents
     */
    string temp;

    /**
     * The file name
     */
    string file;

    /**
     * A vairable to hold the index in a file
     */
    int index;

    /**
     * A variable to hold the length of a string 
     */
    int length;

};


#endif