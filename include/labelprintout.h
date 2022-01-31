/***************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  OpenCP Route printout
 * Author:   Pavel Saviankou
 *
 ***************************************************************************
 *   Copyright (C) 2010 by David S. Register                               *
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
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
 **************************************************************************/

#include <iostream>
using namespace std; // FIXME: 'using namespace' must not be used in header files


#ifndef __LABELPRINTOUT_H__
#define __LABELPRINTOUT_H__

#include <wx/print.h>
#include <wx/datetime.h>
#include <wx/cmdline.h>

#ifdef __WXMSW__
#include <wx/msw/private.h>
#endif

#include "ocpn_types.h"
#include "navutil.h"
#include "printtable.h"


class MyLabelPrintout : public MyPrintout {
public:
#ifdef BASCULA
    MyLabelPrintout( std::vector<bool> _toPrintOut,
                     Label*            label,
                     const char*    title = "My Label printout" );
#else
    MyLabelPrintout( std::vector<bool> _toPrintOut,
                     Label*            label,
                     const wxChar*     title = _T( "My Label printout" ) );
#endif

    virtual
    bool
    OnPrintPage( int page );
    void
    DrawPage( wxDC* dc );
    virtual
    void
    OnPreparePrinting();

    virtual
    bool
    HasPage( int num )
    {
        return num > 0 || num <= 1;
    };

    virtual
    void
    GetPageInfo( int* minPage,
                 int* maxPage,
                 int* selPageFrom,
                 int* selPageTo );

protected:
    wxDC*             myDC;
    PrintTable        table;
    Label*            myLabel;
    std::vector<bool> toPrintOut; // list of fields of bool, if certain element should be print out.
//    static const int  pN = 5;     // number of fields sofar Ignat
    static const int  pN = 11;     // number of fields sofar
    int               pageToPrint;
    int               numberOfPages;
    int               marginX;
    int               marginY;
    int               textOffsetX;
    int               textOffsetY;
};


// label elements selection dialog
///@begin control identifiers
#define ID_LABELPRINTSELECTION 9000
#define SYMBOL_LABELPRINT_SELECTION_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX
#define SYMBOL_LABELPRINT_SELECTION_TITLE _( "Print Label Selection" )
#define SYMBOL_LABELPRINT_SELECTION_IDNAME ID_LABELPRINTSELECTION
#define SYMBOL_LABELPRINT_SELECTION_SIZE wxSize( 750, 300 )
#define SYMBOL_LABELPRINT_SELECTION_POSITION wxDefaultPosition

#define ID_LABELPRINT_SELECTION_OK 9001
#define ID_LABELPRINT_SELECTION_CANCEL 9002


class LabelPrintSelection : public wxDialog {
    DECLARE_DYNAMIC_CLASS( LabelPrintSelection )
    DECLARE_EVENT_TABLE()

public:
    // Constructors
    LabelPrintSelection();
    LabelPrintSelection( wxWindow*       parent,
                         Label*          label,
                         wxWindowID      id = SYMBOL_LABELPRINT_SELECTION_IDNAME,
                         const wxString& caption = SYMBOL_LABELPRINT_SELECTION_TITLE,
                         const wxPoint&  pos = SYMBOL_LABELPRINT_SELECTION_POSITION,
                         const wxSize&   size = SYMBOL_LABELPRINT_SELECTION_SIZE,
                         long            style = SYMBOL_LABELPRINT_SELECTION_STYLE );
    ~LabelPrintSelection();

    // Creation
    bool
    Create( wxWindow*       parent,
            wxWindowID      id = SYMBOL_LABELPRINT_SELECTION_IDNAME,
            const wxString& caption = SYMBOL_LABELPRINT_SELECTION_TITLE,
            const wxPoint&  pos = SYMBOL_LABELPRINT_SELECTION_POSITION,
            const wxSize&   size = SYMBOL_LABELPRINT_SELECTION_SIZE,
            long            style = SYMBOL_LABELPRINT_SELECTION_STYLE );

    void
    CreateControls();

    void
    SetColorScheme( ColorScheme cs );
    void
    SetDialogTitle(const wxString & title);
    void
    OnLabelpropCancelClick( wxCommandEvent& event );
    void
    OnLabelpropOkClick( wxCommandEvent& event );


    // Should we show tooltips?
    static bool
    ShowToolTips();



    wxButton*   m_CancelButton;
    wxButton*   m_OKButton;

    wxCheckBox* m_checkBoxWPName;
    wxCheckBox* m_checkBoxWPPosition;
    wxCheckBox* m_checkBoxWPCourse;
    wxCheckBox* m_checkBoxWPDistanceToNext;
    wxCheckBox* m_checkBoxWPDescription;
    wxCheckBox* m_checkBoxWPCName;
    wxCheckBox* m_checkBoxWPPack;
    wxCheckBox* m_checkBoxWPPcs;
    wxCheckBox* m_checkBoxWPLast;
    wxCheckBox* m_checkBoxWPOrder;
    wxCheckBox* m_checkBoxWPDate;

    Label*      label;
};

#endif
