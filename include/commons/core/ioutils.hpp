


#ifndef COMMONS_CORE_IOUTILS_HPP
#define COMMONS_CORE_IOUTILS_HPP

#include <stdio.h>
#include <commons/core/Exception.h>

using commons::core::Exception;

namespace commons {
namespace core {
namespace ioutils{

    void write(string& path, string& content){
        FILE* file = fopen(path.c_str(), "w");
        if(file == NULL){
            string msg = "Could not open file: '" + path +"'.";
            throw Exception(msg);
        }

        fprintf(file, "%s", content.c_str());
        fclose(file);
    };

    void write(string&& path, string& content){
        write(path, content);
    }
	

	
}/*namespace ioutils*/
}/*namespace core*/
}/*namespace commons*/

#endif