


#ifndef COMMONS_CORE_IOUTILS_HPP
#define COMMONS_CORE_IOUTILS_HPP

#include <stdio.h>
#include <sys/stat.h>
#include <stdio.h>
#include <commons/core/Exception.h>

using commons::core::Exception;

namespace commons {
namespace core {
namespace ioutils{

    bool ends_with(string& txt, const char c){
        if(txt.length() == 0 && c == '\0'){
            return true;
        }

        if(txt.length() == 0){
            return false;
        }

        var idx = txt.length() -1;
        return txt.at(idx) == c;
    }

    void write(string& path, string& content){
        FILE* file = fopen(path.c_str(), "w");
        if(file == NULL){
            string msg = "Could not open file: '" + path +"'.";
            throw Exception(msg);
        }

        fprintf(file, "%s", content.c_str());
        fflush(file);
        fclose(file);
    };

    void writeln(const char* dir, const char* fileName, const char* mode, const char* content){

        string full;

        string sdir{dir};
        string sfileName{fileName};
        if(ends_with(sdir, '/')){
            full = sdir + fileName;
        }else{
            full = sdir + "/" + fileName;
        }

        struct stat sb;
        if(stat(dir, &sb) != 0 || S_ISDIR(sb.st_mode) == false){
            string msg = "The directory '" + sdir +"' does not exist.";
            throw Exception(msg);
        }

        FILE* file = fopen(full.c_str(), mode);
        if(file == NULL){
            string msg = "Could not open file: '" + full +"'.";
            throw Exception(msg);
        }

        fprintf(file, "%s", content);
        fputc('\n', file);
        fflush(file);
        fclose(file);
    }

    void writeln(string& dir, string& fileName, const char* mode, string& content){
        writeln(dir.c_str(), fileName.c_str(), mode, content.c_str());
    }

    void write(string&& path, string& content){
        write(path, content);
    }
	

	
}/*namespace ioutils*/
}/*namespace core*/
}/*namespace commons*/

#endif