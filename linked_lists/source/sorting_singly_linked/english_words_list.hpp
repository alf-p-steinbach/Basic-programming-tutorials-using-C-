#include "../data/english_words.hpp"
#include "List.hpp"

namespace oneway_sorting_examples {
    
    inline auto english_words_list()
        -> List
    {
        const string_view&  s       = data::english_words;
        const int           s_len   = s.length();

        List list;
        List::Appender appender( list );
        int i_wordstart = 0;
        while( i_wordstart < s_len ) {
            int i_wordend = i_wordstart + 1;
            while( i_wordend < s_len and s[i_wordend] != '\n' ) {
                ++i_wordend;
            }
            const auto word = string_view( &s[i_wordstart], i_wordend - i_wordstart );
            appender.append( new Node{ nullptr, word } );
            i_wordstart = i_wordend + 1;
        }
        return list;
    }

}  // namespace oneway_sorting_examples
