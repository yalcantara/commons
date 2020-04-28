/*
 * utils.cpp
 *
 *  Created on: Feb 05, 2020
 *      Author: Yaison Alcantara
 */

#ifndef COMMONS_CORE_UTILS_CPP_
#define COMMONS_CORE_UTILS_CPP_

#include <cctype>

namespace commons{
namespace core{
namespace utils{



    long currentTimeMillis(){
        //the type is: std::chrono::time_point<std::chrono::system_clock>
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        auto ans = millis.count();
        return ans;
    }

    // trim from start (in place)
    void ltrimi(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
        }));
    }

    // trim from end (in place)
    void rtrimi(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }



    // trim from both ends (copying)
    std::string trim(std::string s) {
        ltrimi(s);
        rtrimi(s);
        return s;
    }

    bool is_str_blank(const char* s){

        for(size_t i =0; ; i++){
            char c = s[i];
            if(c == '\0'){
                break;
            }

            if(isblank(c) == false){
                return false;
            }
        }

        return true;
    }

    bool is_str_blank(string_view& view){

        size_t len = view.length();

        for(size_t i =0; i < len; i++){
            char c = view.at(i);

            if(isblank(c) == false){
                return false;
            }
        }

        return true;
    }

    bool is_str_blank(string& s){
        return is_str_blank(s.c_str());
    }



}/*namespace utils*/
}/*namespace core*/
}/*namespace commons*/

#endif /* COMMONS_CORE_LANG_CPP_ */