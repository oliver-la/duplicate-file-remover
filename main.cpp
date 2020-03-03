#include <iostream>
#include <fstream>
#include <vector>
#include "crypto/md5.h"
#include "tinydir/tinydir.h"

using namespace std;

int main(int argc, char* argv[]) {
    bool error = false;
    bool testrun = false;
    char *folder = nullptr;

    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-test") == 0) {
            testrun = true;
        } else if(strcmp(argv[i], "--dir") == 0) {
            if(&argc >= &i) {
                folder = argv[i + 1];
                error = false;
            } else {
                error = true;
            }
        }
    }

    if(!error && argc > 1) {
        tinydir_dir dir;
        tinydir_open(&dir, folder);

        vector<string> storedMD5;

        while(dir.has_next) {
            tinydir_file file;
            tinydir_readfile(&dir, &file);

            if (!file.is_dir)
            {
                ifstream fin(file.path, ios::binary);
                if(!fin) {
                    cout << "Cannot open file: " << file.path << endl;
                } else {
                    fin.seekg(0, std::ios::end);
                    std::string data;
                    data.resize(fin.tellg());
                    fin.seekg(0, std::ios::beg);
                    fin.read(&data[0], data.size());

                    string hash = md5(data);


                    bool found = false;
                    for(unsigned long i = 0; i < storedMD5.size(); i++) {
                        if(storedMD5.at(i).compare(hash) == 0) {
                            cout << "Found duplicate! " << file.path << endl;
                            found = true;
                        }
                    }

                    if(!found) {
                        storedMD5.push_back(hash);
                    } else if (!testrun) {
                        remove(file.path);
                    }

                }
            }

            tinydir_next(&dir);
        }
    } else {
        cout << "Usage: [options] --dir <directory>" << endl;
        cout << endl;
        cout << "Available options are:" << endl;
        cout << "   -test       Don't delete anything." << endl;

        return -1;
    }

    return 0;
}