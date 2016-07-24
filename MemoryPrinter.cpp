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

    #include "MemoryPrinter.h"


    /********************************************************************************
        EEPROMPrinter class
    ********************************************************************************/
#ifdef __AVR__
    size_t EEPROMPrinter::write( uint8_t u_Data )
        {
            if( eeprom_read_byte( start + len ) != u_Data )
                eeprom_write_byte( start + len, u_Data );
            ++len;
            return 0x01;
        }

    size_t EEPROMPrinter::printTo(Print& p) const
        {
            for( uint16_t counter = 0 ; counter < len ; ++counter ){
                p.write( ( uint8_t ) eeprom_read_byte( &start[counter] ) );
            }
            return len;
        }
#endif
    /********************************************************************************
        SRAMPrinter class
    ********************************************************************************/

    size_t SRAMPrinter::write( uint8_t data )
        {
            start[len++] = data;
            return 0x01;
        }

    /********************************************************************************
        PROGMEMPrinter class
    ********************************************************************************/
#ifdef __AVR__
    size_t PROGMEMPrinter::printTo(Print& p) const
        {
            size_t returnSize = 0;
            for( uint16_t counter = 0 ;; ++counter ){
                unsigned char current = pgm_read_byte( &start[counter] );
                if ( !current ) break;
                returnSize += p.write( current );
            }
            return returnSize;
        }
#endif
