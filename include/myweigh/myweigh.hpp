/***************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  MyWeigh Support Classes
 * Author:   Ignat
 *
 ***************************************************************************
 *   Copyright (C) 2021 by Ignat           *
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


#if ! defined( MyWeigh_CLASS_HEADER )
#define MyWeigh_CLASS_HEADER

/*
** Author: Ignat
** CI$: 76300,326
** Internet: ignat@claroflex.com
**
** You can use it any way you like.
*/

/*
** General Purpose Classes
*/

#include "Sentence.hpp"
#include "Response1.hpp"
//#include "LatLong.hpp"
//#include "LoranTD.hpp"
//#include "Manufact.hpp"
//#include "MList.hpp"
//#include "OmegaPar.hpp"
//#include "DeccaLOP.hpp"
//#include "RatioPls.hpp"
//#include "RadarDat.hpp"
//#include "FreqMode.hpp"

/*
** Response Classes
*/

//#include "uw.hpp"

WX_DECLARE_LIST(RESPONSE1, MRL1);

class MyWeigh
{

   private:

      SENTENCE sentence;

      void initialize( void );

   protected:

      MRL1 response_table;

      void set_container_pointers( void );
      void sort_response_table( void );

   public:

      MyWeigh();
      virtual ~MyWeigh();

      /*
      ** NMEA 0183 Sentences we understand
      */

//      UW Uw;

      wxString ErrorMessage; // Filled when Parse returns FALSE
      wxString LastSentenceIDParsed; // ID of the lst sentence successfully parsed
      wxString LastSentenceIDReceived; // ID of the last sentence received, may not have parsed successfully

      wxString TalkerID;
      wxString ExpandedTalkerID;

//      MANUFACTURER_LIST Manufacturers;

      bool IsGood( void ) const;
      bool Parse( void );
      bool PreParse( void );

      MyWeigh& operator << ( wxString& source );
      MyWeigh& operator >> ( wxString& destination );
};

#endif // MyWeigh_CLASS_HEADER
