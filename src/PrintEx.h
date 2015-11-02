/********************************************************************************
    Copyright 2015 Christopher Andrews.
    https://github.com/Chris--A/PrintEx

    Released under MIT licence.
********************************************************************************/

#define PRINTEX_VERSION		10109

#include "lib/MemoryPrinter.h"
#include "lib/StreamExtension.h"

#include "tools/BufferedPrinter.h"
#include "tools/DualPrinter.h"
#include "tools/Base64Encoder/Base64Encoder.h"
#include "tools/URIEncoder/URIEncoder.h"
#include "tools/CRCStream/CRCStream.h"
#include "tools/RxTxCounter.h"
#include "tools/NullStream.h"

#ifdef ISCPP11
    template<
        typename D,
        typename T,
        typename = typename enable_if<is_base_of<Print,D>::value>::type,
        typename = typename enable_if<!is_base_of<PrintExtension,D>::value>::type,
        typename = typename enable_if<!is_base_of<StreamExtension,D>::value>::type
    >
        ios::OStream<PrintExtension> operator<< ( D &print, const T &data ){
            PrintEx printer = print;
            ios::OStream<PrintExtension> os( printer );
            return os << data;
    }

    template<
        typename D,
        typename T,
        typename = typename enable_if<is_base_of<Stream,D>::value>::type,
        typename = typename enable_if<!is_base_of<StreamExtension,D>::value>::type
    >
        ios::IStream<StreamExtension> operator>> ( D &stream, T &data ){
            StreamEx streamer = stream;
            ios::IStream<StreamExtension> os( streamer );
            return os >> data;
    }

#endif
