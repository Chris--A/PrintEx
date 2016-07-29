/********************************************************************************
        Copyright 2016 Christopher Andrews.
        https://github.com/Chris--A/PrintEx

        Released using: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007

        You should have received a copy of the licence with the software
        package. You can also view a copy of the full licence here:
        https://github.com/Chris--A/PrintEx/blob/master/LICENSE

        The only exception to the licence applies when a piece of software
        used within PrintEx, and uses a less restrictive licence or is
        public domain. However, these items will be marked accordingly
        with a link or reference of its origins.

        The exception mentioned in the above paragraph only applies to the
        particular lines of code that may be licensed differently, and does
        not remove the GNU GPLv3 restrictions from the remainder of the
        source which contains these items, or other source files used in
        conjunction with them.

********************************************************************************/

#ifndef HEADER_STREAMITERATE
    #define HEADER_STREAMITERATE

    /***
        StreamIterator object.
        Implements an iterate-able object.
        This object will keep iterating until there is no more data in the Stream.
    ***/

    struct StreamIterator{
        StreamIterator( Stream &o, bool endOfStream = false ) : owner(o), current(endOfStream ? -1 : o.read()) {}
        bool operator !=( const StreamIterator &b ){ return b.current != current; }
        StreamIterator &operator ++(){ return this->current = owner.read(), *this; }
        char operator *(){ return (char) this->current; }
        Stream &owner;
        int current;
    };

    /***
        StreamIterate object.
        This is a temporary which provides an interface defining the iteration range.
    ***/

    struct StreamIterate{
        StreamIterate( Stream &o ) : owner(o) {}
        StreamIterator begin() { return StreamIterator(owner); }
        StreamIterator end() { return StreamIterator(owner, true); }
        Stream &owner;
    };

    /***
        StreamIteration interface.
        This object attaches the iteration functionality to the derived object.
    ***/

    template< typename derived >
    struct StreamIteration{

        StreamIterate each(){ return StreamIterate(CRTPO); }

        derived &waitForData(){
            while( !CRTPO.available() );
            return CRTPO;
        }
    };

#endif
