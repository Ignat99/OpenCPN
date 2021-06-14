/***************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  MyWeigh Support Classes
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


#if ! defined( UW_CLASS_HEADER )
#define UW_CLASS_HEADER

/*
** Author: Ignat
** CI$: 76300,326
** Internet: ignat@claroflex.com
**
** You can use it any way you like.
*/

class UW : public RESPONSE
{

   public:

      UW();
     ~UW();

      /*
      ** Data
      */

      NMEA0183_BOOLEAN IsDataValid;
      double   UnitWeighKg;
      double   TotalMileage;
      double   TripMileage;
      
      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual bool Parse( const SENTENCE& sentence );
      virtual bool Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const UW& operator = ( const UW& source );
};

#endif // UW_CLASS_HEADER
