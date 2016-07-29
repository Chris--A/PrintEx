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

#define PRINTEX_VERSION        10200

#include "lib/MemoryPrinter.h"
#include "lib/StreamExtension.h"

#include "tools/BufferedPrinter.h"
#include "tools/DualPrinter.h"
#include "tools/Base64Encoder/Base64Encoder.h"
#include "tools/URIEncoder/URIEncoder.h"
#include "tools/CRCStream/CRCStream.h"
#include "tools/RxTxCounter.h"
#include "tools/NullStream.h"
#include "tools/PrintAdapter.h"

#ifdef ISCPP11
    struct PrintExTemporary{
        PrintEx out;
        ios::OStreamParams params;

        template<typename T>
        PrintExTemporary operator <<( const T &data ){
            ios::OStream<PrintExtension> os( out, params );
            params = (os << data).params;
            return *this;
        }
    };

    template<
        typename D,
        typename T,
        typename = typename enable_if<is_base_of<Print,D>::value>::type,
        typename = typename enable_if<!is_base_of<PrintExtension,D>::value>::type,
        typename = typename enable_if<!is_base_of<StreamExtension,D>::value>::type
    >
        PrintExTemporary operator<< ( D &print, const T &data ){
            return PrintExTemporary{print, {}} << data;
    }

    template<
        typename D,
        typename T,
        typename = typename enable_if<is_base_of<Stream,D>::value>::type,
        typename = typename enable_if<!is_base_of<StreamExtension,D>::value>::type
    >
        D &operator>> ( D &stream, T &data ){
            StreamEx streamer = stream;
            return streamer >> data, stream;
    }
#endif
