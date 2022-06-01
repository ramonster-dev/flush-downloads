#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <dirent.h>
#include <typeinfo>

template<typename T>
class FileHandler {
  private:
    DIR* dir;
    struct dirent* diread;
    std::vector<dirent*> files;
    std::string str_path;
    
  public:
    FileHandler(); //Initialise directories
    ~FileHandler();
    void init_dir(); //Creating directory path
    void init_files(); //Add files to vector for deletion
    void display_files();
    void confirm_deletion(); //User confirmation
};

template <typename T>
FileHandler<T>::FileHandler() {
  //Initialising directory path
  init_dir();
  init_files();
}

template <typename T>
FileHandler<T>::~FileHandler() {
}

template <typename T>
void FileHandler<T>::init_dir() {
  std::string user = getenv("USER");
  str_path = "/Users/" + user + "/Downloads/";
  char path_arr[str_path.length() + 1];
  strcpy(path_arr, str_path.c_str());

  dir = opendir(path_arr);
}

template <typename T>
void FileHandler<T>::init_files() {
  if (dir != nullptr) {
    while ((diread = readdir(dir)) != nullptr) {
      char first_char = diread->d_name[0];
      if (first_char != '.') { //Checking to make sure we only delete non-hidden files
        files.push_back(diread);
      }
    }
    closedir(dir);
  } else {
    perror("Either nothing is in your Downloads/ folder at the moment or the directory is incorrect.");
  }
}
  
template <typename T>
void FileHandler<T>::display_files() {
  std::cout << "There are " << files.size() << " files in your " << str_path << " folder." << std::endl; 
  for (auto file : files) {
    std::cout << file->d_name << std::endl;
  }
}

template <typename T>
void FileHandler<T>::confirm_deletion() {
}


