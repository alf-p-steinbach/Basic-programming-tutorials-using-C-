#pragma once
#include "List.hpp"
#include "../my_random.hpp"

#include <array>        // std::array

namespace oneway_sorting_examples {
    using std::array;
    using my_random::Choices, my_random::Seed, my_random::random_seed;
    
    inline void merge_shuffle( List& list, Choices& choices )
    {
        // Fine point: don't recurse infinitely on a list with 1 node. So check also that:
        if( list.head == nullptr or list.head->next == nullptr ) {
            return;
        }
        array<List, 2> parts;
        
        // Partition, where all that matters is to divide the nodes about equally:
        for( int i; list.head != nullptr; ) {
            unlinked( list.head )->link_in_before( parts[i%2].head );
            ++i;
        }
        
        // Recurse:
        for( int i = 0; i < 2; ++i ) {
            merge_shuffle( parts[i], choices );
        }
        
        // Merge the now random 2 parts randomly:
        List::Appender appender( list.head );
        for( ;; ) {
            const int n_non_empty =
                (parts[0].head != nullptr) + (parts[1].head != nullptr);
            if( n_non_empty == 0 ) {
                break;
            } else if( n_non_empty == 1 ) {
                const int i_rest = (parts[0].head != nullptr? 0 : 1);
                do {
                    appender.append( unlinked( parts[i_rest].head ) );
                } while( parts[i_rest].head != nullptr );
            } else { // n_non_empty == 2
                appender.append( unlinked( parts[choices.next()].head ) );
            }
        }
    }

    inline void merge_shuffle( List& list, const Seed seq_nr = random_seed() )
    {
        Choices choices( seq_nr );
        merge_shuffle( list, choices );
    }

}  // namespace oneway_sorting_examples
