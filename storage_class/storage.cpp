#include "storage.h"
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;


storage::storage() {
    //Files are saved in the directory in which the code is run from.
    storagePath = "storage-notes/";
    //The total storage used is initialized to 0.
    totalStorageUsed = 0;
    //C++'s built in I/O functionality is used to create the path if it does not already exist.
    fs::create_directories(storagePath);

    // Load existing files from disk
    for (const auto& entry : fs::directory_iterator(storagePath)) {
        if (entry.is_regular_file()) {
            std::string fileName = entry.path().filename().string();
            size_t fileSize = fs::file_size(entry.path());
            fileIndex[fileName] = fileSize;
        }
    }

    //The initial storage used by the program is calculated.
    calculateStorageUsage();
}


bool storage::saveFile(const vector<char>& fileData, const string& fileName) {
    // The full path of the file is determined by appending the file name to the storage path.
    string filePath = storagePath + fileName;
    
    // The file is opened in binary mode for writing.
    ofstream outFile(filePath, ios::binary);

    // If the file could not be opened, an error message is displayed, and the function returns false.
    if (!outFile) {
        cerr << "Error: Could not open file for writing: " << filePath << endl;
        return false;
    }

    // The file data is written to the file.
    outFile.write(fileData.data(), fileData.size());
    
    // The file stream is closed to ensure data is properly saved.
    outFile.close();

    // The size of the newly saved file is determined.
    size_t fileSize = fs::file_size(filePath);
    
    // The file index is updated with the new file's size.
    fileIndex[fileName] = fileSize;
    
    // The total storage usage is recalculated after saving the file.
    calculateStorageUsage();

    // The function returns true to indicate the file was saved successfully.
    return true;
}


vector<char> storage::loadFile(const string& fileName) {
    // The full path of the file is determined by appending the file name to the storage path.
    string filePath = storagePath + fileName;
    
    // The file is opened in binary mode for reading.
    ifstream inFile(filePath, ios::binary);

    // If the file could not be opened, an error message is displayed, and an empty vector is returned.
    if (!inFile) {
        cerr << "Error: Could not open file for reading: " << filePath << endl;
        return {};
    }

    // The file contents are read into a vector using stream iterators.
    vector<char> fileContents((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());

    // The file stream is closed after reading.
    inFile.close();

    // The file's contents are returned as a vector of characters.
    return fileContents;
}


bool storage::deleteFile(const string& fileName) {
    // The full path of the file is determined by appending the file name to the storage path.
    string filePath = storagePath + fileName;
    
    // The file is removed from the filesystem. If successful, additional cleanup is performed.
    if (fs::remove(filePath)) {
        // The file entry is removed from the file index.
        fileIndex.erase(fileName);
        
        // The total storage usage is recalculated after deletion.
        calculateStorageUsage();
        
        // The function returns true to indicate the file was deleted successfully.
        return true;
    }

    // The function returns false if the file could not be deleted.
    return false;
}


vector<string> storage::listFiles() {
    // A vector is created to store the file names.
    vector<string> files;

    // Iterates through the file index and adds each file name to the vector.
    for (const auto& entry : fs::directory_iterator(storagePath)) {
        if (entry.is_regular_file()) {
            string fileName = entry.path().filename().string();

            // Optional: skip hidden files like .gitkeep
            if (fileName[0] == '.') continue;

            files.push_back(fileName);
        }
    }

    // Returns the list of stored file names.
    return files;
}


bool storage::fileExists(const string& fileName) {
    // Checks if the file name exists in the file index and returns the result.
    return fileIndex.find(fileName) != fileIndex.end();
}


size_t storage::getStorageUsage() {
    // Returns the total storage used.
    return totalStorageUsed;
}


void storage::calculateStorageUsage() {
    // Resets the total storage used to zero before recalculating.
    totalStorageUsed = 0;

    // Iterates through the file index and adds up the sizes of all stored files.
    for (const auto &[_, fileSize] : fileIndex) {
        totalStorageUsed += fileSize;
    }
}