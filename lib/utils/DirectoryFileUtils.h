//DirectoryFileUtils.h (Helper methods)

#include <iostream>
#include <dirent.h>
#include <vector>

using namespace std;

const char * extensions[] = {"txt", "doc","docx"};
vector<string> valid_extensions(extensions, end(extensions));

const char * badDirs[] = {"misc"};
vector<string> bad_directories(badDirs, end(badDirs));

/***************************************
 * Data structures to deal with
 * dirs/files
 **************************************/
typedef struct sfsFile {
    string name, fullpath;
} SfsFile;

/***************************************
 * Helper functions
 **************************************/

bool beginsWith(string name, string shorter) {
    string sub = name.substr(0, shorter.size());
    return sub == shorter;
}

bool hasValidExtension(string name) {
    string ext = name.substr(name.find_last_of(".")+1);
    for (int i = 0; i < valid_extensions.size(); i++) {
        if (ext == valid_extensions[i]) return true;
    }
    return false;

}

bool isInvalidDirectory(string dname) {
    for (int i = 0; i < bad_directories.size(); i++) {
	if (bad_directories[i] == dname) return true;
    }
    return false;
}

//Returns whether the given file is valid for indexing
bool shouldIndexFile(string fname) {
    return !beginsWith(fname, ".") && hasValidExtension(fname);
}

//Returns whether the given directory should be searched for indexing
bool shouldIndexDirectory(string dname) {
    return !beginsWith(dname, ".") && !isInvalidDirectory(dname);
}

//Returns a vector of strings of all directories in a given directory. Non recursive helper function
vector<string> getAllDirectories(string dir) {
    struct dirent *entry;
    DIR *dp = opendir(dir.c_str());
    vector<string> dirs;

    if (dp == NULL) {
	cout << "Path " << dir << " does not exist or could not be read" << endl;
        return vector<string>();
    }

    while ((entry = readdir(dp))) {
        if (entry->d_type == DT_DIR && shouldIndexDirectory(entry->d_name)) {
	    dirs.push_back(entry->d_name);
	}
    }

    closedir(dp);
    return dirs;
}

//Helper function to get all files in the current directory
void getFilesInDir(string dir, vector<SfsFile> &files) {
    struct dirent *entry;
    DIR *dp = opendir(dir.c_str());

    if (dp == NULL) {
	cout << "Path " << dir << " does not exist or could not be read" << endl;
        return;
    }

    while ((entry = readdir(dp))) {
        if (entry->d_type == DT_REG && shouldIndexFile(entry->d_name)) {
	    SfsFile curFile = (SfsFile){entry->d_name, dir+"/"+entry->d_name};
            files.push_back(curFile);
	}
    }

    closedir(dp);
    return;
}

//Helper function to get all files recursively in directory
void getAllFilesRecursive(string curDir, vector<SfsFile> &files) {
    getFilesInDir(curDir, files);
    vector<string> dirs = getAllDirectories(curDir);
    for (int i = 0; i < dirs.size(); i++) {
	getAllFilesRecursive(curDir+"/"+dirs[i], files);
    }
}

/***************************************
 * Main Functions
 **************************************/

//Returns a vector of strings of all files in a given directory recursively
//Example Call: getAllFiles(".")
vector<SfsFile> getAllFiles(string curDir) {
    vector<SfsFile> allFiles;
    getAllFilesRecursive(curDir, allFiles);
    return allFiles;
}
