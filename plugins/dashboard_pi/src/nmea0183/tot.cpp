/***************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  NMEA0183 Support Classes
 * Author:   Samuel R. Blackburn, David S. Register
 *
 ***************************************************************************
 *   Copyright (C) 2010 by Samuel R. Blackburn, David S Register           *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.             *
 ***************************************************************************
 *
 *   S Blackburn's original source license:                                *
 *         "You can use it any way you like."                              *
 *   More recent (2010) license statement:                                 *
 *         "It is BSD license, do with it what you will"                   *
 */


#include "nmea0183.h"
#include "tot.hpp"

/*
** Author: Ignat
** CI$: 76300,326
** Internet: ignat@claroflex.com
**
** You can use it any way you like.
*/

TOT::TOT()
{
   Mnemonic = _T("Total:+");
   Empty();
}

TOT::~TOT()
{
   Mnemonic.Empty();
   Empty();
}

void TOT::Empty( void )
{
   TotalMileage = 0.0;
   TripMileage  = 0.0;
   IsDataValid = NTrue;
   TotalUnit = 100.0;
   }

bool TOT::Parse( const SENTENCE& sentence )
{
   /*
   TOT - Total quantity screen

        1   2 3   4 5
        |   | |   | |
 $--VLW,x.x,N,x.x,N*hh<CR><LF>

 Field Number:
  1) Total cumulative distance
  2) N = Nautical Miles
  3) Distance since Reset
  4) N = Nautical Miles
  5) Checksum

   */

   /*
   ** First we check the checksum...
   */

//   if ( sentence.IsChecksumBad( 5 ) == TRUE )
//   {
//      SetErrorMessage( _T("Invalid Checksum") );
//      return( FALSE );
//   }

//   TotalMileage = sentence.Double( 1 );
   TotalUnit = sentence.Double( 1 );
//   UnitWeighKg = 20.0;
//   TripMileage  = sentence.Double( 3 );

   return( TRUE );
}

bool TOT::Write( SENTENCE& sentence )
{
   /*
   ** Let the parent do its thing
   */

   RESPONSE::Write( sentence );

   sentence += TotalMileage;
   sentence += _T("N");
   sentence += TripMileage;
   sentence += _T("N");
   sentence += TotalUnit;
   sentence += _T("N");
   sentence.Finish();

   return( TRUE );
}



const TOT& TOT::operator = ( const TOT& source )
{
   TotalMileage = source.TotalMileage;
   TripMileage  = source.TripMileage;
   TotalUnit  = source.TotalUnit;
      return( *this );
}
