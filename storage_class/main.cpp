// #include "storage.h"
// #include <fstream>
// #include <vector>
//
// int main() {
//      storage myStorage;
//
//      // Text file test
//      cout << "--- Text File Test ---" << endl;
//      const vector<char> textData = {'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
//      myStorage.saveFile(textData, "test_text.txt");
//      vector<char> loadedTextData = myStorage.loadFile("test_text.txt");
//      cout << "Loaded text: " << string(loadedTextData.begin(), loadedTextData.end()) << endl;
//
//      // Binary file test
//      cout << "\n--- Binary File Test (MP3 Simulation) ---" << endl;
//      vector<char> mp3Data = myStorage.loadFile("sample.mp3");
//      if (!mp3Data.empty()) {
//          cout << "Read MP3 file successfully! Size: " << mp3Data.size() << " bytes" << endl;
//          myStorage.saveFile(mp3Data, "copy.mp3");
//          vector<char> loadedMp3Data = myStorage.loadFile("copy.mp3");
//          cout << "Loaded MP3 data size: " << loadedMp3Data.size() << " bytes" << endl;
//      } else {
//          cout << "Failed to read sample.mp3. Please ensure the file exists." << endl;
//      }
//
//      // Lyrics file test
//      cout << "\n--- Lyrics File Test ---" << endl;
//      vector<char> lyricsData = myStorage.loadFile("lyrics.txt");
//      if (!lyricsData.empty()) {
//          cout << "Loaded lyrics from lyrics.txt:" << endl;
//          cout << string(lyricsData.begin(), lyricsData.end()) << endl;
//      } else {
//          cout << "Failed to read lyrics.txt. Please ensure the file exists." << endl;
//      }
//
//      // File existence check
//      cout << "\n--- File Existence Check ---" << endl;
//      cout << "File test_text.txt exists: " << myStorage.fileExists("test_text.txt") << endl;
//      cout << "File copy.mp3 exists: " << myStorage.fileExists("copy.mp3") << endl;
//
//      // File deletion test
//      cout << "\n--- File Deletion Test ---" << endl;
//      if (myStorage.deleteFile("test_text.txt")) cout << "Deleted test_text.txt" << endl;
//      if (myStorage.deleteFile("copy.mp3")) cout << "Deleted copy.mp3" << endl;
//
//      // Final storage usage
//      cout << "\nFinal storage usage: " << myStorage.getStorageUsage() << " bytes" << endl;
//
//      return 0;
//  }
