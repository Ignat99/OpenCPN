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

#if ! defined( MyWeigh_HEADER )

#define MyWeigh_HEADER

/*
** Author: Ignat
** CI$: 76300,326
** Internet: ignat@claroflex.com
**
** You can use it any way you like.
*/

//    Include wxWindows stuff
//#include "wx/wxprec.h"

//#ifndef  WX_PRECOMP
//  #include "wx/wx.h"
//#endif //precompiled headers
#include "wx/string.h"
#include "wx/list.h"
#include "wx/arrstr.h"

/*
** Turn off the warning about precompiled headers, it is rather annoying
*/

#ifdef __WXMSW__
#pragma warning( disable : 4699 )
#endif

#define CARRIAGE_RETURN 0x0D
#define LINE_FEED       0x0A


typedef enum _MyWeigh_BOOLEAN
{
   UnknownMyWeigh = 0,
   MTrue,
   MFalse
} MyWeigh_BOOLEAN;

int HexValue( const wxString& hex_string );

wxString& expand_talker_id( const wxString & );
wxString& Hex( int value );
wxString& talker_id( const wxString& sentence );

#include "myweigh.hpp"

#endif // MyWeigh_HEADER
