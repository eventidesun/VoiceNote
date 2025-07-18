#ifndef STORAGE_H
#define STORAGE_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

/**
 * @brief Interacts with the filesystem to provide basic I/O functionality.
 * 
 * @details
 * The storage class provides the application with basic I/O functionality, 
 * in particular, reading from and writing to files, deleting files, checking 
 * for the existence of files, and calculating the total storage used by the program.
 *
 * @author Geoffrey Kong
 */
class storage {
    public:
        /**
        * @brief Constructor creates a new storage object.
        * 
        * @return A newly created storage object.
        * 
        * @usage
        * storage myStorage; //Creates a new storage object.
        */
        storage();


        /**
        * @brief Saves a file to disk.
        * 
        * @param fileData Data to be written to the disk, broken up into an array of individual characters or binary digits.
        * 
        * @param fileName The name of the file that the data should be saved as.
        * 
        * @return True or False, depending on whether or not the operation to save data was successful or not.
        * 
        * @usage
        * myStorage.saveFile({'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!'}, "HelloWorld.txt");
        */
        bool saveFile(const vector<char>& fileData, const string& fileName);


        /**
         * @brief Loads a file from disk into memory.
         * 
         * @param fileName The name of the file to be loaded.
         * 
         * @return A vector of characters containing the file's contents. 
         *         Returns an empty vector if the file cannot be opened.
         * 
         * @usage
         * myStorage.loadFile("HelloWorld.txt");
         */
        vector<char> loadFile(const string& fileName);


        /**
         * @brief Deletes a file from disk.
         * 
         * @param fileName The name of the file to be deleted.
         * 
         * @return True if the file was successfully deleted, false otherwise.
         * 
         * @usage
         * myStorage.deleteFile("HelloWorld.txt");
         */
        bool deleteFile(const string& fileName);

        /**
         * @brief Retrieves a list of all stored files.
         * 
         * @return A vector of strings containing the names of all stored files.
         * 
         * @usage
         * myStorage.listFiles();
         */
        vector<string> listFiles();


        /**
         * @brief Checks if a file exists in storage.
         * 
         * @param fileName The name of the file to check for existence.
         * 
         * @return True if the file exists, false otherwise.
         * 
         * @usage
         * myStorage.fileExists("HelloWorld.txt");
         */
        bool fileExists(const string& fileName);


        /**
         * @brief Retrieves the total storage used.
         * 
         * @return The total storage used in bytes.
         * 
         * @usage
         * myStorage.getStorageUsage();
         */
        size_t getStorageUsage();

    private:
        // The directory where files are stored.
        string storagePath;

        // A mapping of stored file names to their respective sizes in bytes.
        map<string, size_t> fileIndex;

        // The total amount of storage used by all stored files.
        size_t totalStorageUsed;

        /**
         * @brief Calculates and updates the total storage used.
         * 
         * This function iterates through all stored files and sums their sizes 
         * to update the total storage usage.
         * 
         * @usage
         * myStorage.calculateStorageUsage();
         */
        void calculateStorageUsage();
};

#endif