#include "list_copy_of_the_five_important_numbers.hpp"

#include <math.h>           // ::abs
#include <iostream>
#include <stdexcept>        // std::(runtime_error, exception)
using std::cout, std::endl, runtime_error;

void display( const Type_<const char*> explanation, const Type_<Node*> head )
{
    cout << explanation;
    for( Node* p = head; p != nullptr; p = p->next ) {
        cout << " " << p->value;
    }
    cout << "." << endl;
}

using C_str = const char*;

void fail( const C_str where, const string& message )
{
    throw runtime_error( string() + where + " - " + message );
}

template< class Func >
auto next_field_pointing_to_node( const Func& has_desired_property, Node*& head )
    -> Node*&           // Reference to next-field
{
    Node* trailing = nullptr;
    for(    Node* p = head;
            p != nullptr;
            p = p->next ) {
        if( has_desired_property( p->value ) ) {
            return (trailing == nullptr? head : trailing->next);
        }
        trailing = p;
    }
    fail( __func__, "failed to find specified node" );
}

auto main()
    -> int
{
    Node* head = list_copy_of_the_five_important_numbers();

    display( "Original values:", head );
#if defined( UB_PLEASE )
    // The pointer to next field function result makes it easy to do this inadvertently...
    const auto with_value_7 = [](double x) -> bool { return x == 7; };
    delete unlinked( next_field_pointing_to_node( with_value_7, head ) );
#elif defined( EFFICIENT_PLEASE )
    // Delete all nodes that are not 42, in a way that's O(n) efficient for a large list.
    try  {
        const auto not_42 = [](double x) -> bool { return x != 42; };
        Node** pp_sublist_head = &head;
        for( ;; ) {
            Node*& next = next_field_pointing_to_node( not_42, *pp_sublist_head );
            delete unlinked( next );
            pp_sublist_head = &next;    // Search only in the part of the list after this.
        }
    } catch( const runtime_error& ) {
        ;   // Ignore, it means the end of the list.
    }
#else
    // Delete all nodes that are not 42, in a simple but O(n^2) way.
    try  {
        const auto not_42 = [](double x) -> bool { return x != 42; };
        for( ;; ) {
            Node*& doomed = next_field_pointing_to_node( not_42, head );
            delete unlinked( doomed );
        }
    } catch( const runtime_error& ) {
        ;   // Ignore, it means the end of the list.
    }
#endif
    display( "After deleting the too math-ish numbers the list is", head );

    delete_list( head );
}
