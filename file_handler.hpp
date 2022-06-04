#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include <filesystem>
#include <typeinfo>
#include <windows.h>
#include <lmcons.h>

namespace fs = std::filesystem;

class FileHandler {
  private:
    std::vector<std::string> files;
    std::string user;
    std::string str_dir;
    
  public:
    FileHandler(); //Initialise directories
    ~FileHandler();

  private:
    std::string get_user();
    std::string get_dir();
    void init_files();
    void delete_files();
    void display_files();
    char confirm_deletion();
};


FileHandler::FileHandler() {
  user = get_user();
  str_dir = get_dir();
  init_files();
  delete_files();
}


FileHandler::~FileHandler() {
}


void FileHandler::init_files() {
  for (const auto& entry : fs::directory_iterator(str_dir)) {
    files.push_back(entry.path().u8string());
  }
}

void FileHandler::delete_files() {
  display_files();
  
  char usr_in = confirm_deletion();
  if (usr_in == 'y' || usr_in == 'Y') {
    for (auto file : files) {
      char file_arr[file.length() + 1];
      strcpy(file_arr, file.c_str());
      remove(file_arr);
    }
    std::cout << "Flushed." << std::endl;
  } else {
    exit(1);
  }

}

char FileHandler::confirm_deletion() {
  char usr_in;
  std::cout << "Would you like to flush your Downloads/ directory? [y]/[n]";
  std::cin >> usr_in;

  return usr_in;
}
  

void FileHandler::display_files() {
  std::cout << "There are " << files.size() << " files in your " << str_dir << " folder." << std::endl; 
  for (auto file : files) {
    std::cout << file << std::endl;
  }
}

std::string FileHandler::get_user() {
  #ifdef _WIN64
    char user[UNLEN + 1]{};
    DWORD user_len = UNLEN + 1;
    ::GetUserNameA(user, &user_len);
    return user;
  #elif __APPLE__ || __MACH__
    return getenv("USER");
  #elif __linux__
    return getenv("USERNAME");
  #endif
}

std::string FileHandler::get_dir() {
  #ifdef _WIN64
    return "C:\\Users\\" + user + "\\Downloads\\";
  #elif __APPLE__ || __MACH__
    return "/Users/" + user + "/Downloads/";
  #elif __linux__
    return "/home/" + user + "/Downloads/";
  #endif
}


