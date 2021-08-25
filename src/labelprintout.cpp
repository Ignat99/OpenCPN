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
#define PRINT_WP_IMAGEN 3
#define PRINT_WP_CODIGOQR 4
#define PRINT_WP_PESO 5
#define PRINT_WP_STOCK 6

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
//    marginX = 5;
//    marginY = 5;


    marginX = 20;
    marginY = 5;

    // Offset text from the edge of the cell (Needed on Linux)
    textOffsetX = 5;
    textOffsetY = 8;

//    textOffsetX = 50;
//    textOffsetY = 80;

/*
    table.StartFillHeader();
    // setup widths for columns
    if ( toPrintOut[ PRINT_WP_LOGO ] ) {
        table << (const char *)wxString(_("Claroflex")).mb_str();
    }
    if ( toPrintOut[ PRINT_WP_REFERENCIA ] ) {
        table << (const char *)wxString(_("REFERENCIA")).mb_str();
    }
    if ( toPrintOut[ PRINT_WP_COMPONENTE ] ) {
        table << (const char *)wxString(_("COMPONENTE")).mb_str();
    }
    if ( toPrintOut[ PRINT_WP_IMAGEN ] ) {
        table << (const char *)wxString(_("IMAGEN")).mb_str();
    }
    if ( toPrintOut[ PRINT_WP_CODIGOQR ] ) {
        table << (const char *)wxString(_("CODIGO QR")).mb_str();
    }
*/
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
    if ( toPrintOut[ PRINT_WP_IMAGEN ] ) {
        table << 500;
    }
    if ( toPrintOut[ PRINT_WP_CODIGOQR ] ) {
        table << 500;
    } 

    table.StartFillData();


    for ( int n = 1; n <= myLabel->GetnPoints(); n++ ) {
        LabelPoint* point = myLabel->GetPoint( n );

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
            table << "REFERENCIA:  " + cell;
        }
        if ( toPrintOut[ PRINT_WP_COMPONENTE ] ) {
//            wxString point_course;
//            point_course.Printf( _T( "%03.0f Deg" ), point->GetCourse() );
//            point_course.Printf( _T( "CASQUILLO GUIA SUPERIOR" ) );
//            string   cell( point_course.mb_str() );
            string cell( point->GetName().mb_str() );
            table << "COMPONENTE:  " + cell;
        }
        if ( toPrintOut[ PRINT_WP_IMAGEN ] ) {
//            wxString point_distance;
//            point_distance.Printf( _T( "%6.2f" + getUsrDistanceUnit() ), toUsrDistance( point->GetDistance() ) );
//            point_distance.Printf( _T( "%6.2f" + getUsrDistanceUnit() ) );
//            string   cell( point_distance.mb_str() );
            string cell( point->GetImage().mb_str() );
            table << cell;
        }
        if ( toPrintOut[ PRINT_WP_CODIGOQR ] ) {
//            wxString point_description;
//            point_description.Printf( _T( "gr" ) );
//            string cell( point->GetDescription().mb_str() );
//            string   cell( point_description.mb_str() );
            table << "CODIGO QR:  ";
        }
        table << "\n";
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
    numberOfPages = table.GetNumberPages();
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


    wxFont labelPrintFont_bold( 24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD );
    dc->SetFont( labelPrintFont_bold );
    wxBrush brush( wxColour(255,255,255),  wxTRANSPARENT );
    dc->SetBrush( brush );

    int header_textOffsetX = 25;
    int header_textOffsetY = 115;

//    int header_textOffsetX = 80;
//    int header_textOffsetY = 115;

    int currentX = marginX;
    int currentY = marginY;
//    vector< PrintCell >& header_content = table.GetHeader();
//    for ( size_t j = 0; j < header_content.size(); j++ ) {
//        PrintCell& cell = header_content[ j ];
//        dc->DrawRectangle( currentX, currentY, cell.GetWidth(), cell.GetHeight() );
//        dc->DrawText( cell.GetText(),  currentX +header_textOffsetX, currentY + header_textOffsetY );
//        currentX += cell.GetWidth();
//    }

    dc->DrawBitmap(m_bitmap, 80, 30);
    dc->DrawBitmap(m_bitmap, 940, 30);

//    dc->DrawBitmap(m_bitmap, 80, 50);
//    dc->DrawBitmap(m_bitmap, 900, 50);


    dc->SetPen(*wxBLACK_PEN);
//    dc->SetBrush(*wxBLACK_BRUSH);

    dc->DrawLine( 20, 110, 1680, 110);
    dc->DrawLine( 20, 112, 1680, 112);
    dc->DrawLine( 20, 1100, 1680, 1100);
    dc->DrawLine( 20, 1102, 1680, 1102);

//    dc->DrawLine( 80, 110, 1030, 110);
//    dc->DrawLine( 80, 112, 1030, 112);
//    dc->DrawLine( 80, 1000, 1030, 1000);
//    dc->DrawLine( 80, 1002, 1030, 1002);

//    wxFont  labelPrintFont_normal( 24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL );
//    dc->SetFont( labelPrintFont_normal );

    vector< vector < PrintCell > > & cells = table.GetContent();
    currentY = marginY + table.GetHeaderHeight() + header_textOffsetY;
    int currentHeight = 0;
//    for ( size_t i = 0; i < cells.size(); i = i + 2 ) {
    for ( size_t i = 2; i < 4; i = i + 2 ) {
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
                }
                if (j == 1) dc->DrawLabel(cell.GetText(), r);
                if (j == 2) dc->DrawLabel(cell.GetText(), r);
                if (j == 3) {
                    dc->DrawLabel("IMAGEN: ", r);
                    my_image = my_path;
                    my_image += cell.GetText();
                    wxImage m_image(my_image);
                    dc->DrawBitmap(m_image.Scale(200, 200, wxIMAGE_QUALITY_HIGH), 280, 300);
                }
                if (j == 4) {
                    r.Offset( 0, 200 );
                    dc->DrawLabel("CODIGO QR:  ", r);
                    wxImage m_qrcode(my_code);
                    dc->DrawBitmap(m_qrcode.Scale(200, 200), 280, 550);
                }
//                currentX     += cell.GetWidth();
                currentY     += cell.GetHeight() + 20;
                currentHeight = cell.GetHeight();
//            }
        }
        content_row = cells[ i + 1 ];
        currentX = marginX + header_textOffsetX;
        currentY = marginY + table.GetHeaderHeight() + header_textOffsetY;

        for ( size_t j = 0; j < content_row.size(); j++ ) {
            PrintCell& cell = content_row[ j ];
                wxRect r( currentX+940, currentY, cell.GetWidth(), cell.GetHeight() );
                r.Offset( textOffsetX, textOffsetY );
                if (j == 0) {
                   my_code = my_path;
                   my_code += "components/";
                   my_code += cell.GetText();
                   my_code += ".bmp";
                }
                if (j == 1) dc->DrawLabel(cell.GetText(), r);
                if (j == 2) dc->DrawLabel(cell.GetText(), r);
                if (j == 3) {
                    dc->DrawLabel("IMAGEN: ", r);
                    my_image = my_path;
                    my_image += cell.GetText();
                    wxImage m_image(my_image);
                    dc->DrawBitmap(m_image.Scale(200, 200, wxIMAGE_QUALITY_HIGH), 280+940, 300);
                }
                if (j == 4) {
                    r.Offset( 0, 200 );
                    dc->DrawLabel("CODIGO QR:  ", r);
                    wxImage m_qrcode(my_code);
                    dc->DrawBitmap(m_qrcode.Scale(200, 200), 280+940, 550);
                }
//                currentX     += cell.GetWidth();
                currentY     += cell.GetHeight() + 20;
                currentHeight = cell.GetHeight();
        }

//        OffsetLogicalOrigin (1800, 1300);
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

    m_checkBoxWPDistanceToNext = new wxCheckBox( itemDialog1, wxID_ANY, _( "Imagen" ),
                                                 wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT );
    m_checkBoxWPDistanceToNext->SetValue( true );
    fgSizer2->Add( m_checkBoxWPDistanceToNext, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );
    wxStaticText* label4 = new  wxStaticText( itemDialog1, wxID_ANY, _( "Show Imagen componente." ), wxDefaultPosition, wxDefaultSize );
    fgSizer2->Add( label4, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5 );

    m_checkBoxWPDescription = new wxCheckBox( itemDialog1, wxID_ANY, _( "Codigo QR" ),
                                              wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT );
    m_checkBoxWPDescription->SetValue( true );
    fgSizer2->Add( m_checkBoxWPDescription, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );
    wxStaticText* label5 = new  wxStaticText( itemDialog1, wxID_ANY, _( "Show codigo QR." ), wxDefaultPosition, wxDefaultSize );
    fgSizer2->Add( label5, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5 );

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
    toPrintOut.push_back( m_checkBoxWPDistanceToNext->GetValue() );
    toPrintOut.push_back( m_checkBoxWPDescription->GetValue() );

    if ( NULL == g_printData ) {
        g_printData = new wxPrintData;
        g_printData->SetOrientation( wxLANDSCAPE );
//        g_printData->SetOrientation( wxPORTRAIT );
//        g_printData->SetPaperId( wxPAPER_PENV_1);
        g_printData->SetPaperId( wxPAPER_P32K);
//        g_printData->SetPaperId( wxPAPER_A6_ROTATED);
//        g_printData->SetPaperId( wxPAPER_A6);
        g_pageSetupData = new wxPageSetupDialogData(*g_printData);
        g_pageSetupData->SetMarginTopLeft(wxPoint(0,0));
        g_pageSetupData->SetMarginBottomRight(wxPoint(0,0));

        wxPageSetupDialog dialog( NULL, g_pageSetupData );
        dialog.ShowModal();
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
