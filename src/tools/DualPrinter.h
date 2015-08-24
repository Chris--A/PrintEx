/********************************************************************************
    Copyright 2015 Christopher Andrews.
    https://github.com/Chris--A/PrintEx

    Released under MIT licence.
********************************************************************************/

#ifndef HEADER_DUALPRINTER
    #define HEADER_DUALPRINTER

	class DualPrinter : public PrintExtension{
	  public:
		DualPrinter( Print *OutputA = 0x00, Print *OutputB = 0x00 ) : OutputA( OutputA ), OutputB( OutputB ){}

		size_t write( uint8_t u_Data )
		  {
			if( OutputA ) OutputA->write( u_Data );
			if( OutputB ) OutputB->write( u_Data );
			return 0x01;
		  }
		
		void SetA( Print *OutputA = 0x00 ){ this->OutputA = OutputA; }
		void SetB( Print *OutputB = 0x00 ){ this->OutputB = OutputB; }

	  protected:
		Print *OutputA;
		Print *OutputB;
	};

#endif
