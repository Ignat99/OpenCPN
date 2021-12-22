/*************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  OpenCPN Label printout
 * Author:   Pavel Saviankou
 *
 ***************************************************************************
 *   Copyright (C) 2012 by David S. Register                               *
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
using namespace std;

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers
#ifdef __WXMSW__
//#include "c:\\Program Files\\visual leak detector\\include\\vld.h"
#endif

#include "wx/print.h"
#include "wx/printdlg.h"
#include "wx/artprov.h"
#include "wx/stdpaths.h"
#include <wx/intl.h>
#include <wx/listctrl.h>
#include <wx/aui/aui.h>
#include <wx/dialog.h>
#include <wx/progdlg.h>
#include <wx/brush.h>
#include <wx/colour.h>


#if wxCHECK_VERSION( 2, 9, 0 )
#include <wx/dialog.h>
#else
//  #include "scrollingdialog.h"
#endif

#include "dychart.h"

#ifdef __WXMSW__
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <psapi.h>
#endif

#ifndef __WXMSW__
#include <signal.h>
#include <setjmp.h>
#endif

#include "labelprintout.h"
#include "printtable.h"

#define PRINT_WP_LOGO 0
#define PRINT_WP_REFERENCIA 1
#define PRINT_WP_COMPONENTE 2
//#define PRINT_WP_PESO 3
//#define PRINT_WP_STOCK 4
#define PRINT_WP_NAME 3
#define PRINT_WP_PACK 4
#define PRINT_WP_PCS 5
#define PRINT_WP_LAST 6
#define PRINT_WP_IMAGEN 7
#define PRINT_WP_CODIGOQR 8
#define PRINT_WP_ORDER 9
#define PRINT_WP_DATE 10

// Global print data, to remember settings during the session
extern wxPrintData*     g_printData;
// Global page setup data
extern wxPageSetupData* g_pageSetupData;

MyLabelPrintout::MyLabelPrintout( std::vector<bool> _toPrintOut,
                                  Label*            label,
                                  const wxChar*     title
                                  ) : MyPrintout( title ),
                                      myLabel( label ),
                                      toPrintOut( _toPrintOut )
{
    // Let's have at least some device units margin
    marginX = 5;
    marginY = 5;

    // Offset text from the edge of the cell (Needed on Linux)
//    textOffsetX = 5;
//    textOffsetY = 8;

    textOffsetX = 1;
    textOffsetY = 1;


    table.StartFillHeader();
    // setup widths for columns
    if ( toPrintOut[ PRINT_WP_LOGO ] ) {
        table << (const char *)wxString(_("Claro")).mb_str();
    }
    if ( toPrintOut[ PRINT_WP_REFERENCIA ] ) {
        table << (const char *)wxString(_("REF")).mb_str();
    }
    if ( toPrintOut[ PRINT_WP_COMPONENTE ] ) {
        table << (const char *)wxString(_("COM")).mb_str();
    }
    if ( toPrintOut[ PRINT_WP_NAME ] ) {
        table << (const char *)wxString(_("CN")).mb_str();
    }
    if ( toPrintOut[ PRINT_WP_PACK ] ) {
        table << (const char *)wxString(_("PACK")).mb_str();
    }
    if ( toPrintOut[ PRINT_WP_PCS ] ) {
        table << (const char *)wxString(_("PCS")).mb_str();
    }
    if ( toPrintOut[ PRINT_WP_LAST ] ) {
        table << (const char *)wxString(_("LAST")).mb_str();
    }
    if ( toPrintOut[ PRINT_WP_IMAGEN ] ) {
        table << (const char *)wxString(_("IMAG")).mb_str();
    }
    if ( toPrintOut[ PRINT_WP_CODIGOQR ] ) {
        table << (const char *)wxString(_("QR")).mb_str();
    }
    if ( toPrintOut[ PRINT_WP_ORDER ] ) {
        table << (const char *)wxString(_("ORDER")).mb_str();
    }
    if ( toPrintOut[ PRINT_WP_DATE ] ) {
        table << (const char *)wxString(_("DATE")).mb_str();
    }



    table.StartFillWidths();
    // setup widths for columns
    if ( toPrintOut[ PRINT_WP_LOGO ] ) {
        table << 500;
    }
    if ( toPrintOut[ PRINT_WP_REFERENCIA ] ) {
        table << 500;
    }
    if ( toPrintOut[ PRINT_WP_COMPONENTE ] ) {
        table << 500;
    }
    if ( toPrintOut[ PRINT_WP_NAME ] ) {
        table << 500;
    }
    if ( toPrintOut[ PRINT_WP_PACK ] ) {
        table << 500;
    }
    if ( toPrintOut[ PRINT_WP_PCS ] ) {
        table << 500;
    }
    if ( toPrintOut[ PRINT_WP_LAST ] ) {
        table << 500;
    }
    if ( toPrintOut[ PRINT_WP_IMAGEN ] ) {
        table << 500;
    }
    if ( toPrintOut[ PRINT_WP_CODIGOQR ] ) {
        table << 500;
    }
    if ( toPrintOut[ PRINT_WP_ORDER ] ) {
        table << 500;
    }
    if ( toPrintOut[ PRINT_WP_DATE ] ) {
        table << 500;
    }

    table.StartFillData();


    for ( int n = 1; n <= myLabel->GetnPoints(); n++ ) {
        LabelPoint* point = myLabel->GetPoint( n );
        if (point->m_bPtIsSelected) {
        if ( toPrintOut[ PRINT_WP_LOGO ] ) {
//            wxString point_name;
//            point_name.Printf( _T("==========") );
//            string   cell( point_name.mb_str() );
            string cell( point->GetCode().mb_str() );
            table << cell;
        }
        if ( toPrintOut[ PRINT_WP_REFERENCIA ] ) {
//            wxString point_position = toSDMM( 1, point->m_lat, point->m_bIsInTrack ) + _T( "\n" ) + toSDMM( 2, point->m_lon, point->m_bIsInTrack );
//            wxString point_position;
//            point_position.Printf( _T( "CAS002" ) );
//            string   cell( point_position.mb_str() );
            string cell( point->GetCode().mb_str() );
            table << "REF:  " + cell;
        }
        if ( toPrintOut[ PRINT_WP_COMPONENTE ] ) {
//            wxString point_course;
//            point_course.Printf( _T( "%03.0f Deg" ), point->GetCourse() );
//            point_course.Printf( _T( "CASQUILLO GUIA SUPERIOR" ) );
//            string   cell( point_course.mb_str() );
            string cell( point->GetName().mb_str() );
            table << "COM:  " + cell;
        }
        if ( toPrintOut[ PRINT_WP_NAME ] ) {
            string cell( point->GetCName().mb_str() );
            table << "NAME:  " + cell;
        }
        if ( toPrintOut[ PRINT_WP_PACK ] ) {
            string cell( point->GetPack().mb_str() );
            table << "PACK:  " + cell;

//// Setup the number of pages to print
//            numberOfPages = atoi(point->GetPack().mb_str());
//            if ( numberOfPages%2 == 0) {
//                numberOfPages = numberOfPages / 2;
//                  pageToPrint = numberOfPages;
//            } else {
//// Setup number of labels. TODO: Make function to print last labels
//                numberOfPages = ((numberOfPages - 1) / 2) + 1;
//                  pageToPrint = numberOfPages;
//            }
// Print number of page
//            string cell1( numberOfPages );

//            table << "PA_N:  " + numberOfPages ;

        }
        if ( toPrintOut[ PRINT_WP_PCS ] ) {
            string cell( point->GetPcs().mb_str() );
            table << "PCS:  " + cell;
        }
        if ( toPrintOut[ PRINT_WP_LAST ] ) {
            string cell( point->GetLast().mb_str() );
            table << "LAST:  " + cell;
        }
        if ( toPrintOut[ PRINT_WP_IMAGEN ] ) {
            string cell( point->GetImage().mb_str() );
            table <<  cell;
        }
        if ( toPrintOut[ PRINT_WP_CODIGOQR ] ) {
            string   cell( point->GetLast().mb_str() );
            table <<  "QR: " + cell;
        }
        if ( toPrintOut[ PRINT_WP_ORDER ] ) {
            string   cell( point->GetOrder().mb_str() );
            table <<  "ORDER: " + cell;
        }
        if ( toPrintOut[ PRINT_WP_DATE ] ) {
            string   cell( point->GetDate().mb_str() );
            table <<  "DATE: " + cell;
        }

        table << "\n";
        }
    }
}


void MyLabelPrintout::GetPageInfo( int* minPage, int* maxPage, int* selPageFrom, int* selPageTo )
{
    *minPage     = 1;
    *maxPage     = numberOfPages;
    *selPageFrom = 1;
    *selPageTo   = numberOfPages;
}


void MyLabelPrintout::OnPreparePrinting()
{
    pageToPrint = 1;
    wxDC*  dc = GetDC();
    wxFont labelPrintFont( 10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL );
    dc->SetFont( labelPrintFont );

    // Get the size of the DC in pixels
    int w, h;
    dc->GetSize( &w, &h );
//    w = 2000;
//    h = 1000;

    // We don't know before hand what size the Print DC will be, in pixels.  Varies by host.
    // So, if the dc size is greater than 1000 pixels, we scale accordinly.

    int maxX = wxMin(w, 1000);
    int maxY = wxMin(h, 1000);

    // Calculate a suitable scaling factor
    double scaleX = ( double )( w / maxX );
    double scaleY = ( double )( h / maxY );

    // Use x or y scaling factor, whichever fits on the DC
    double actualScale = wxMin( scaleX, scaleY );

    // Set the scale and origin
    dc->SetUserScale( actualScale, actualScale );
    dc->SetDeviceOrigin( ( long )marginX, ( long )marginY );

    table.AdjustCells( dc, marginX, marginY );
// Numer of pages we setup in pack amout
//    numberOfPages = table.GetNumberPages();
    numberOfPages = 1;
}


bool MyLabelPrintout::OnPrintPage( int page )
{
    wxDC* dc = GetDC();
    if( dc ) {
        if( page <= numberOfPages ){
            pageToPrint = page;
            DrawPage( dc );
            return true;
        }
        else
            return false;
    } else
        return false;

}

void MyLabelPrintout::DrawPage( wxDC* dc )
{

    wxString my_path = "/home/olimex/tmp/old/build/";
    wxImage m_bitmap(my_path + "logo_negro_200.png");
    wxString my_code;
    wxString my_image;
    wxRect cur_r;


    wxFont labelPrintFont_bold( 24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD );
    dc->SetFont( labelPrintFont_bold );
    wxBrush brush( wxColour(255,255,255),  wxTRANSPARENT );
    dc->SetBrush( brush );


    int header_textOffsetX = 80;
    int header_textOffsetY = 115;

    int currentX = marginX;
    int currentY = marginY;
//    vector< PrintCell >& header_content = table.GetHeader();
//    for ( size_t j = 0; j < header_content.size(); j++ ) {
//        PrintCell& cell = header_content[ j ];
//        dc->DrawRectangle( currentX, currentY, cell.GetWidth(), cell.GetHeight() );
//        dc->DrawText( cell.GetText(),  currentX +header_textOffsetX, currentY + header_textOffsetY );
//        currentX += cell.GetWidth();
//    }


// Print Right and Left Logo and Bold Lines
    dc->DrawBitmap(m_bitmap, 80, 30);
    dc->DrawBitmap(m_bitmap, 940, 30);

//    dc->DrawBitmap(m_bitmap, 80, 50);
//    dc->DrawBitmap(m_bitmap, 900, 50);


    dc->SetPen(*wxBLACK_PEN);
//    dc->SetBrush(*wxBLACK_BRUSH);

// Top Line
    dc->DrawLine( 20, 110, 1680, 110);
    dc->DrawLine( 20, 112, 1680, 112);

// Bottom Line
//    dc->DrawLine( 20, 1100, 1680, 1100);
//    dc->DrawLine( 20, 1102, 1680, 1102);



//    dc->DrawLine( 80, 110, 1030, 110);
//    dc->DrawLine( 80, 112, 1030, 112);
//    dc->DrawLine( 80, 1000, 1030, 1000);
//    dc->DrawLine( 80, 1002, 1030, 1002);

//    wxFont  labelPrintFont_normal( 24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL );
//    dc->SetFont( labelPrintFont_normal );

    vector< vector < PrintCell > > & cells = table.GetContent();
//    currentY = marginY + table.GetHeaderHeight() + header_textOffsetY;
    currentY = marginY + header_textOffsetY;
    int currentHeight = 0;
    for ( size_t i = 0; i < cells.size(); i = i + 1 ) {
        vector< PrintCell >& content_row = cells[ i ];
        currentX = marginX + header_textOffsetX;
        for ( size_t j = 0; j < content_row.size(); j++ ) {
            PrintCell& cell = content_row[ j ];
//            if ( cell.GetPage() == pageToPrint ) {
                wxRect r( currentX, currentY, cell.GetWidth(), cell.GetHeight() );
                r.Offset( textOffsetX, textOffsetY );
                if (j == 0) {
                   my_code = my_path;
                   my_code += "components/";
                   my_code += cell.GetText();
                   my_code += ".bmp";
// Print code for debug info
//                    dc->DrawLabel(my_code, r);

                    PrintCell& cell_img = content_row[ 7 ];

// Print first line of full name of image
//                    dc->DrawLabel(cell_img.GetText(), r);

                    my_image = my_path;
                    my_image += cell_img.GetText();
                    wxImage m_image(cell_img.GetText());
                    dc->DrawBitmap(m_image.Scale(200, 200, wxIMAGE_QUALITY_HIGH), 480, 400);
                    wxImage m_qrcode(my_code);
                    dc->DrawBitmap(m_qrcode.Scale(200, 200), 480, 650);
                }
                if (j == 1) dc->DrawLabel(cell.GetText(), r);
                if (j == 2) dc->DrawLabel(cell.GetText(), r);
                if (j == 3) dc->DrawLabel(cell.GetText(), r);
                if (j == 4) dc->DrawLabel(cell.GetText(), r);
                if (j == 5) dc->DrawLabel(cell.GetText(), r);
                if (j == 6) dc->DrawLabel(cell.GetText(), r);
//                if (j == 7) {
//                    my_image = my_path;
//                    my_image += cell.GetText();
//                    wxImage m_image(cell.GetText());
////                    dc->DrawLabel(cell.GetText(), r);
//                    dc->DrawBitmap(m_image.Scale(200, 200, wxIMAGE_QUALITY_HIGH), 480, 400);
//                }
//                if (j == 8) {
//                    r.Offset( 0, 200 );
//                    dc->DrawLabel("CODIGO QR:  ", r);
//                    wxImage m_qrcode(my_code);
//                    dc->DrawBitmap(m_qrcode.Scale(200, 200), 480, 650);
//                }
                if (j == 7) dc->DrawLabel(cell.GetText(), r);
                if (j == 8) dc->DrawLabel(cell.GetText(), r);
                if (j == 9) dc->DrawLabel(cell.GetText(), r);
                if (j == 10) dc->DrawLabel(cell.GetText(), r);
//                if (j == 11) dc->DrawLabel(cell.GetText(), r);

//                currentX     += cell.GetWidth();
                currentY     += cell.GetHeight() + 20;
                currentHeight = cell.GetHeight();
//            } // if cell.GetPage()
        }
//        content_row = cells[ i + 1 ];
        content_row = cells[ i ];
        currentX = marginX + header_textOffsetX;
//        currentY = marginY + table.GetHeaderHeight() + header_textOffsetY;
        currentY = marginY + header_textOffsetY;

//                    dc->DrawLabel("IMAGEN: ", r);
//                    dc->DrawLabel(cell.GetText(), r);
//                    dc->DrawBitmap(m_image.Scale(200, 200, wxIMAGE_QUALITY_HIGH), 480+940, 400);
//                    r.Offset( 0, 200 );
//                    dc->DrawLabel("CODIGO QR:  ", r);
//                    dc->DrawBitmap(m_qrcode.Scale(200, 200), 480+940, 650);
        pageToPrint = 2;
    }
}


// ---------- LabelPrintSelection dialof implementation

/*!
 * LabelPrintSelection type definition
 */

IMPLEMENT_DYNAMIC_CLASS( LabelPrintSelection, wxDialog )
/*!
 * LabelProp event table definition
 */

BEGIN_EVENT_TABLE( LabelPrintSelection, wxDialog )
EVT_BUTTON( ID_LABELPRINT_SELECTION_CANCEL, LabelPrintSelection::OnLabelpropCancelClick )
EVT_BUTTON( ID_LABELPRINT_SELECTION_OK, LabelPrintSelection::OnLabelpropOkClick )
END_EVENT_TABLE()

/*!
 * LabelProp constructors
 */

LabelPrintSelection::LabelPrintSelection()
{
}


LabelPrintSelection::LabelPrintSelection( wxWindow*       parent,
                                          Label*          _label,
                                          wxWindowID      id,
                                          const wxString& caption,
                                          const wxPoint&  pos,
                                          const wxSize&   size,
                                          long            style )
{
    label = _label;

    long wstyle = style;

    Create( parent, id, caption, pos, size, wstyle );
    Centre();
}


LabelPrintSelection::~LabelPrintSelection()
{
}


/*!
 * LabelProp creator
 */

bool LabelPrintSelection::Create( wxWindow* parent, wxWindowID id, const wxString& caption,
                             const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle( GetExtraStyle() | wxWS_EX_BLOCK_EVENTS );

#ifdef __WXOSX__
    style |= wxSTAY_ON_TOP;
#endif

    wxDialog::Create( parent, id, _("Print Label Selection"), pos, size, style );

    CreateControls();

    return TRUE;
}


/*!
 * Control creation for LabelProp
 */

void LabelPrintSelection::CreateControls()
{
    LabelPrintSelection* itemDialog1 = this;

    wxStaticBox*         itemStaticBoxSizer3Static = new wxStaticBox( itemDialog1, wxID_ANY,
                                                                      _( "Elements to print..." ) );

    wxStaticBoxSizer* itemBoxSizer1 = new wxStaticBoxSizer( itemStaticBoxSizer3Static,  wxVERTICAL );
    itemDialog1->SetSizer( itemBoxSizer1 );

    wxFlexGridSizer* fgSizer2;
    fgSizer2 = new wxFlexGridSizer( 5, 2, 0, 0 );

    m_checkBoxWPName = new wxCheckBox( itemDialog1, wxID_ANY, _( "Logo" ),
                                       wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT );
    m_checkBoxWPName->SetValue( true );
    fgSizer2->Add( m_checkBoxWPName, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );

    wxStaticText* label1 = new  wxStaticText( itemDialog1, wxID_ANY, _( "Show Claroflex logo." ), wxDefaultPosition, wxDefaultSize );
    fgSizer2->Add( label1, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5 );

    m_checkBoxWPPosition = new wxCheckBox( itemDialog1, wxID_ANY, _( "Referencia" ),
                                           wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT );
    m_checkBoxWPPosition->SetValue( true );
    fgSizer2->Add( m_checkBoxWPPosition, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );
    wxStaticText* label2 = new  wxStaticText( itemDialog1, wxID_ANY, _( "Show Referencia." ), wxDefaultPosition, wxDefaultSize );
    fgSizer2->Add( label2, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5 );

    m_checkBoxWPCourse = new wxCheckBox( itemDialog1, wxID_ANY, _( "Componente" ),
                                         wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT );
    m_checkBoxWPCourse->SetValue( true );
    fgSizer2->Add( m_checkBoxWPCourse, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );
    wxStaticText* label3 = new  wxStaticText( itemDialog1, wxID_ANY, _( "Show Componente. " ), wxDefaultPosition, wxDefaultSize );
    fgSizer2->Add( label3, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5 );



    m_checkBoxWPCName = new wxCheckBox( itemDialog1, wxID_ANY, _( "Client Name" ),
                                              wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT );
    m_checkBoxWPCName->SetValue( true );
    fgSizer2->Add( m_checkBoxWPCName, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );
    wxStaticText* label4 = new  wxStaticText( itemDialog1, wxID_ANY, _( "Show Client Name." ), wxDefaultPosition, wxDefaultSize );
    fgSizer2->Add( label4, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5 );


    m_checkBoxWPPack = new wxCheckBox( itemDialog1, wxID_ANY, _( "Pack" ),
                                              wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT );
    m_checkBoxWPPack->SetValue( true );
    fgSizer2->Add( m_checkBoxWPPack, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );
    wxStaticText* label5 = new  wxStaticText( itemDialog1, wxID_ANY, _( "Show pack" ), wxDefaultPosition, wxDefaultSize );
    fgSizer2->Add( label5, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5 );

    m_checkBoxWPPcs = new wxCheckBox( itemDialog1, wxID_ANY, _( "Pcs" ),
                                              wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT );
    m_checkBoxWPPcs->SetValue( true );
    fgSizer2->Add( m_checkBoxWPPcs, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );
    wxStaticText* label6 = new  wxStaticText( itemDialog1, wxID_ANY, _( "Show pcs." ), wxDefaultPosition, wxDefaultSize );
    fgSizer2->Add( label6, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5 );


    m_checkBoxWPLast = new wxCheckBox( itemDialog1, wxID_ANY, _( "Last pack" ),
                                              wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT );
    m_checkBoxWPLast->SetValue( true );
    fgSizer2->Add( m_checkBoxWPLast, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );
    wxStaticText* label7 = new  wxStaticText( itemDialog1, wxID_ANY, _( "Show pcs in last pack." ), wxDefaultPosition, wxDefaultSize );
    fgSizer2->Add( label7, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5 );


    m_checkBoxWPDistanceToNext = new wxCheckBox( itemDialog1, wxID_ANY, _( "Imagen" ),
                                                 wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT );
    m_checkBoxWPDistanceToNext->SetValue( true );
    fgSizer2->Add( m_checkBoxWPDistanceToNext, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );
    wxStaticText* label8 = new  wxStaticText( itemDialog1, wxID_ANY, _( "Show Imagen componente." ), wxDefaultPosition, wxDefaultSize );
    fgSizer2->Add( label8, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5 );

    m_checkBoxWPDescription = new wxCheckBox( itemDialog1, wxID_ANY, _( "Codigo QR" ),
                                              wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT );
    m_checkBoxWPDescription->SetValue( true );
    fgSizer2->Add( m_checkBoxWPDescription, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );
    wxStaticText* label9 = new  wxStaticText( itemDialog1, wxID_ANY, _( "Show codigo QR." ), wxDefaultPosition, wxDefaultSize );
    fgSizer2->Add( label9, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5 );

// ------------- Order, Date ----------------------------
    m_checkBoxWPOrder = new wxCheckBox( itemDialog1, wxID_ANY, _( "Order" ),
                                              wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT );
    m_checkBoxWPOrder->SetValue( true );
    fgSizer2->Add( m_checkBoxWPOrder, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );
    wxStaticText* label10 = new  wxStaticText( itemDialog1, wxID_ANY, _( "Show codigo Order." ), wxDefaultPosition, wxDefaultSize );
    fgSizer2->Add( label10, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5 );


    m_checkBoxWPDate = new wxCheckBox( itemDialog1, wxID_ANY, _( "Date" ),
                                              wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT );
    m_checkBoxWPDate->SetValue( true );
    fgSizer2->Add( m_checkBoxWPDate, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );
    wxStaticText* label11 = new  wxStaticText( itemDialog1, wxID_ANY, _( "Print date." ), wxDefaultPosition, wxDefaultSize );
    fgSizer2->Add( label11, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5 );

// ===========================

    itemBoxSizer1->Add( fgSizer2, 5, wxEXPAND, 5 );

    wxBoxSizer* itemBoxSizer16 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer1->Add( itemBoxSizer16, 0, wxALIGN_RIGHT | wxALL, 5 );

    m_CancelButton = new wxButton( itemDialog1, ID_LABELPRINT_SELECTION_CANCEL, _( "Cancel" ), wxDefaultPosition,
                                   wxDefaultSize, 0 );
    itemBoxSizer16->Add( m_CancelButton, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_OKButton = new wxButton( itemDialog1, ID_LABELPRINT_SELECTION_OK, _( "OK" ), wxDefaultPosition,
                               wxDefaultSize, 0 );
    itemBoxSizer16->Add( m_OKButton, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    m_OKButton->SetDefault();

    SetColorScheme( ( ColorScheme )0 );
}


void LabelPrintSelection::SetColorScheme( ColorScheme cs )
{
    DimeControl( this );
}


/*
 * Should we show tooltips?
 */

bool LabelPrintSelection::ShowToolTips()
{
    return TRUE;
}


void LabelPrintSelection::SetDialogTitle(const wxString & title)
{
    SetTitle( title );
}


void LabelPrintSelection::OnLabelpropCancelClick( wxCommandEvent& event )
{
    Hide();
    event.Skip();
}


void LabelPrintSelection::OnLabelpropOkClick( wxCommandEvent& event )
{
    std::vector<bool> toPrintOut;
    toPrintOut.push_back( m_checkBoxWPName->GetValue() );
    toPrintOut.push_back( m_checkBoxWPPosition->GetValue() );
    toPrintOut.push_back( m_checkBoxWPCourse->GetValue() );
    toPrintOut.push_back( m_checkBoxWPCName->GetValue() );
    toPrintOut.push_back( m_checkBoxWPPack->GetValue() );
    toPrintOut.push_back( m_checkBoxWPPcs->GetValue() );
    toPrintOut.push_back( m_checkBoxWPLast->GetValue() );
    toPrintOut.push_back( m_checkBoxWPDistanceToNext->GetValue() );
    toPrintOut.push_back( m_checkBoxWPDescription->GetValue() );
    toPrintOut.push_back( m_checkBoxWPOrder->GetValue() );
    toPrintOut.push_back( m_checkBoxWPDate->GetValue() );

    if ( NULL == g_printData ) {
        g_printData = new wxPrintData;
//        g_printData->SetOrientation( wxLANDSCAPE );
        g_printData->SetOrientation( wxPORTRAIT );
//        g_printData->SetPaperId( wxPAPER_PENV_1);
        g_printData->SetPaperId( wxPAPER_P32K);
//        g_printData->SetPaperId( wxPAPER_A6_ROTATED);
//        g_printData->SetPaperId( wxPAPER_A6);
        g_pageSetupData = new wxPageSetupDialogData(*g_printData);
        g_pageSetupData->SetMarginTopLeft(wxPoint(0,0));
        g_pageSetupData->SetMarginBottomRight(wxPoint(0,0));

//        wxPageSetupDialog dialog( NULL, g_pageSetupData );
//        dialog.ShowModal();
    }

//    g_printData->SetPaperId( wxPAPER_A6);
//    g_pageSetupData = new wxPageSetupDialogData(*g_printData);



    MyLabelPrintout*  mylabelprintout1 = new MyLabelPrintout( toPrintOut, label,  _( "Label Print" ) );

    wxPrintDialogData printDialogData( *g_printData );
    printDialogData.EnablePageNumbers( true );
    printDialogData.EnableSelection( true );

    wxPrinter printer( &printDialogData );

    if ( !printer.Print( this, mylabelprintout1, true ) ) {
        if ( wxPrinter::GetLastError() == wxPRINTER_ERROR ) {
            OCPNMessageBox(
                NULL,
                _( "There was a problem printing.\nPerhaps your current printer is not set correctly?" ),
                _T( "OpenCPN" ), wxOK );
        }
    } else {
        ( *g_printData ) = printer.GetPrintDialogData().GetPrintData();
    }

//    Hide();
    event.Skip();
}
