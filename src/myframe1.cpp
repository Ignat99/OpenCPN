#include "myframe1.h"

#include <mysqlcppapi/mysqlcppapi.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include "pluginmanager.h"
#include <stdint.h>
#include "qrcodegen.h"
#include "ImagePanel.hpp"
#include "bmp_output.hpp"


extern PlugInManager    *g_pi_manager;

#define BUTTON1 11000

wxBEGIN_EVENT_TABLE(MyFrame1, wxFrame)
    EVT_SIZE(MyFrame1::OnSize)
    EVT_BUTTON(BUTTON1, MyFrame1::OnButton1)
    EVT_MOVE(MyFrame1::OnMove)
    EVT_ACTIVATE(MyFrame1::OnActivate)
wxEND_EVENT_TABLE()

//    EVT_MAXIMIZE(MyFrame1::OnMaximize)
//    EVT_ERASE_BACKGROUND(MyFrame1::OnEraseBackground)


MyFrame1::MyFrame1( wxFrame *frame, const wxString& title, const wxPoint& pos,
     const wxSize& size, long style ) :
     wxFrame( frame, -1, title, pos, size, style ) 
{

    wxDC *dc = new wxScreenDC();

    idClient = " WHERE id = 596";
//    idCreator = " AND a.id = 1";
    idCreator = " WHERE a.id = 1";
    idProgress = " Progress 1%";

    m_whatever = 1;
    m_pageDisplay = -1;
    int border_size = 4;
    int group_item_spacing = 2;
    int font_size_y, font_descent, font_lead;
    dc->GetTextExtent( _T("0"), NULL, &font_size_y, &font_descent, &font_lead );
    m_small_button_size = wxSize( -1, (int) ( 1.4 * (font_size_y + font_descent + font_lead) ) );

        wxScrolledWindow* ps57Ctl1 = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(900, 600), wxHSCROLL | wxVSCROLL | wxTAB_TRAVERSAL);

        vectorPanel = new wxBoxSizer(wxHORIZONTAL);


        m_pNotebook = new wxNotebook (ps57Ctl1, wxID_ANY, wxDefaultPosition, wxSize(895, 580), wxNB_TOP);

        wxPanel *pPanel = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxSize(890, 550), wxNO_BORDER | wxTAB_TRAVERSAL, _("Bascula") );

        m_pNotebook->AddPage(pPanel, _("Display") );


//        Centre();

    picturePanel = new wxBoxSizer(wxVERTICAL);


    wxFlexGridSizer* optionsColumn = new wxFlexGridSizer(2);
    optionsColumn->SetHGap(border_size);
    optionsColumn->AddGrowableCol( 0, 2 );
    optionsColumn->AddGrowableCol( 1, 3 );
    vectorPanel->Add( picturePanel);
//    vectorPanel->Add( optionsColumn, 3, wxALL | wxEXPAND, border_size );
    picturePanel->Add( optionsColumn, 3, wxALL | wxEXPAND, border_size );

    // spacer
    optionsColumn->Add( new wxStaticText(pPanel, wxID_ANY, _T("")) );
    optionsColumn->Add( new wxStaticText(pPanel, wxID_ANY, _T("")) );


    // dislay category
    optionsColumn->Add( new wxStaticText(pPanel, wxID_ANY, _("Data creation")), labelFlags );
    wxString pDispCatStrings[] = { _("1"), _("2"), _("3"), _("4"), _("5"), _("6"), _("7"), _("10"), _("12"), _("14"), _("21"), _("31"), _("62") };
    pDispCat = new wxChoice( pPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 13, pDispCatStrings );
    optionsColumn->Add( pDispCat, 0, wxALL, 2 );

    pDispCat->Connect( wxEVT_COMMAND_CHOICE_SELECTED,  wxCommandEventHandler(MyFrame1::OnPrChoice), NULL, this );


    // spacer
    optionsColumn->Add( new wxStaticText(pPanel, wxID_ANY, _T("")) );
    optionsColumn->Add( new wxStaticText(pPanel, wxID_ANY, _T("")) );


    // spacer
    optionsColumn->Add( 0, border_size*4 );
    optionsColumn->Add( 0, border_size*4 );



    // graphics options
    optionsColumn->Add( new wxStaticText(pPanel, wxID_ANY, _("Remarks")), labelFlags );
    wxString pPointStyleStrings[] = { _("Paper Chart"), _("Simplified"), };
    pPointStyle = new wxChoice( pPanel, ID_1RADARDISTUNIT, wxDefaultPosition, wxDefaultSize, 2, pPointStyleStrings );
    optionsColumn->Add( pPointStyle, inputFlags );

    pPointStyle->Connect( wxEVT_COMMAND_CHOICE_SELECTED,  wxCommandEventHandler(MyFrame1::OnPrChoicePointStyle), NULL, this );


    optionsColumn->Add( new wxStaticText(pPanel, wxID_ANY, _("Remarks special")), labelFlags );
    wxString pBoundStyleStrings[] = { _("Plain"), _("Symbolized"), };
    pBoundStyle = new wxChoice( pPanel, ID_1RADARDISTUNIT, wxDefaultPosition,
            wxDefaultSize, 2, pBoundStyleStrings );
    optionsColumn->Add( pBoundStyle, inputFlags );

    pBoundStyle->Connect( wxEVT_COMMAND_CHOICE_SELECTED,  wxCommandEventHandler(MyFrame1::OnBoundStyle), NULL, this );


    optionsColumn->Add( new wxStaticText(pPanel, wxID_ANY, _("Remarks internal")), labelFlags );
    wxString pColorNumStrings[] = { _("2 Color loooong"), _("4 Color loooong"), };
    p24Color = new wxChoice( pPanel, ID_1RADARDISTUNIT, wxDefaultPosition,
            wxDefaultSize, 2, pColorNumStrings );
    optionsColumn->Add( p24Color, inputFlags );

    p24Color->Connect( wxEVT_COMMAND_CHOICE_SELECTED,  wxCommandEventHandler(MyFrame1::On24Color), NULL, this );


    // spacer
    optionsColumn->Add( 0, border_size*4 );
    optionsColumn->Add( 0, border_size*4 );



    // depth options
    optionsColumn->Add( new wxStaticText( pPanel, ID_1RADARDISTUNIT, _("Product") ), labelFlags );
//    wxBoxSizer* depShalRow = new wxBoxSizer( wxHORIZONTAL );
//    optionsColumn->Add( depShalRow );
  wxString pPointStyleStrings1[] = { _("Pivot"), _("Slide"), _("Double") };
    pPointStyle1 = new wxChoice( pPanel, ID_1RADARDISTUNIT, wxDefaultPosition,
            wxDefaultSize, 3, pPointStyleStrings1 );
    optionsColumn->Add( pPointStyle1, inputFlags );

    pPointStyle1->Connect( wxEVT_COMMAND_CHOICE_SELECTED,  wxCommandEventHandler(MyFrame1::OnPointStyle1), NULL, this );


    optionsColumn->Add( new wxStaticText( pPanel, wxID_ANY, _("Client") ), labelFlags );
    wxBoxSizer* depSafeRow = new wxBoxSizer( wxHORIZONTAL );
    optionsColumn->Add( depSafeRow );
    m_SafetyCtl = new wxTextCtrl( pPanel, ID_1TEXTCTRL, _T("596"), wxDefaultPosition, wxSize( 80, -1 ), wxTE_RIGHT );
    depSafeRow->Add( m_SafetyCtl, inputFlags );
    //m_depthUnitsSafe = new wxStaticText( pParent, wxID_ANY, _("metres") );
    //depSafeRow->Add( m_depthUnitsSafe, inputFlags );

    m_SafetyCtl->Connect( wxEVT_COMMAND_TEXT_UPDATED,  wxCommandEventHandler(MyFrame1::OnSafetyCtl), NULL, this );


    optionsColumn->Add( new wxStaticText( pPanel, wxID_ANY, _("Creator") ), labelFlags );
    wxBoxSizer* depDeepRow = new wxBoxSizer( wxHORIZONTAL );
    optionsColumn->Add( depDeepRow );
    m_DeepCtl = new wxTextCtrl( pPanel, ID_1TEXTCTRL, _T("596"), wxDefaultPosition, wxSize( 80, -1 ), wxTE_RIGHT );
    depDeepRow->Add( m_DeepCtl, inputFlags );
    //m_depthUnitsDeep = new wxStaticText( pParent, wxID_ANY, _("metres") );
    //depDeepRow->Add( m_depthUnitsDeep, inputFlags );

    m_DeepCtl->Connect( wxEVT_COMMAND_TEXT_UPDATED,  wxCommandEventHandler(MyFrame1::OnDeepCtl), NULL, this );




    // spacer
    optionsColumn->Add( 0, border_size*4 );
    optionsColumn->Add( 0, border_size*4 );


    // create Image panel
    wxBoxSizer* drawSizer = new wxBoxSizer(wxHORIZONTAL);
    drawPane = new ImagePanel(pPanel, wxT("/home/olimex/plan1.bmp"), wxBITMAP_TYPE_BMP);
    drawSizer->Add(drawPane, 1, wxEXPAND);

    wxStaticBox* drawStaticBox = new wxStaticBox( pPanel, wxID_ANY, _("Component") );
    wxStaticBoxSizer* drawStaticSizer = new wxStaticBoxSizer( drawStaticBox, wxVERTICAL );

    drawStaticSizer->Add( drawPane, 1, wxALL | wxEXPAND, group_item_spacing );

//    dispSizer->Add( marinersSizer, 1, wxALL | wxEXPAND, border_size );
//    vectorPanel->Add( drawStaticSizer, 1, wxALL | wxEXPAND, border_size );
//    optionsColumn->Add( drawStaticSizer, 0, wxALL | wxEXPAND, 2  );
    picturePanel->Add( drawStaticSizer, 1, wxALL | wxEXPAND, 2  );


    wxBoxSizer* btnRow = new wxBoxSizer( wxHORIZONTAL );
    itemButtonSelectList = new wxButton( pPanel, ID_1SELECTLIST, _("Print label") );
    btnRow->Add( itemButtonSelectList, 1, wxALL | wxEXPAND, group_item_spacing );
//    itemButtonClearList = new wxButton( pPanel, ID_1CLEARLIST, _("Run Progress") );
//    btnRow->Add( itemButtonClearList, 1, wxALL | wxEXPAND, group_item_spacing );
    picturePanel->Add( btnRow );





    itemButtonSelectList->Connect( wxEVT_COMMAND_BUTTON_CLICKED,  wxCommandEventHandler(MyFrame1::OnBtnSelectClick), NULL, this );
//    itemButtonClearList->Connect( wxEVT_COMMAND_BUTTON_CLICKED,  wxCommandEventHandler(MyFrame1::OnBtnClearClick), NULL, this );


    // 2nd column, Display Category / Mariner's Standard options
    wxBoxSizer* dispSizer = new wxBoxSizer( wxVERTICAL );
    vectorPanel->Add( dispSizer, 2, wxALL | wxEXPAND, border_size );

    wxStaticBox* marinersBox = new wxStaticBox( pPanel, wxID_ANY, _("Projects") );
    wxStaticBoxSizer* marinersSizer = new wxStaticBoxSizer( marinersBox, wxVERTICAL );
    dispSizer->Add( marinersSizer, 1, wxALL | wxEXPAND, border_size );


// Products

    ps57CtlListCtrl = new wxListCtrl( pPanel, ID_1CHECKLISTBOX, wxDefaultPosition, wxSize( 600, 250 ),
           wxLC_REPORT | wxLC_SORT_ASCENDING | wxLC_HRULES | wxBORDER_SUNKEN  | wxLC_VRULES );

    ps57CtlListCtrl->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED,  wxListEventHandler(MyFrame1::OnPrSelected), NULL, this );

/*
    ps57CtlListCtrl->Connect(wxEVT_COMMAND_LIST_ITEM_DESELECTED,
           wxListEventHandler(PlugInManager::OnPrSelected), NULL, this );
    ps57CtlListCtrl->Connect(wxEVT_COMMAND_LIST_ITEM_ACTIVATED,
           wxListEventHandler(PlugInManager::OnPrDefaultAction), NULL, this );
    ps57CtlListCtrl->Connect(wxEVT_LEFT_DOWN,
           wxMouseEventHandler(PlugInManager::OnPrToggleVisibility), NULL, this );
    ps57CtlListCtrl->Connect(wxEVT_COMMAND_LIST_COL_CLICK,
           wxListEventHandler(PlugInManager::OnPrColumnClicked), NULL, this );
*/

    GetProjects(ps57CtlListCtrl);
    marinersSizer->Add( ps57CtlListCtrl, 1, wxALL | wxEXPAND, group_item_spacing );


// Components

    ps57ListCtrl1 = new wxListCtrl( pPanel, ID_1RADARDISTUNIT, wxDefaultPosition,
                                        wxSize( 600, 150 ), wxLC_REPORT );

    ps57ListCtrl1->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED,  wxListEventHandler(MyFrame1::OnCoSelected), NULL, this );


    GetComponents(ps57ListCtrl1);
    marinersSizer->Add( ps57ListCtrl1, 1, wxALL | wxEXPAND, group_item_spacing );


        pPanel->SetSizer(vectorPanel);
//        m_pNotebook->SetSizer(vectorPanel);
//        pPanel->SetSizer(topSizer);
//        pPanel->SetSizer(marinersSizer);


//        m_pNotebook->Show();
//        m_pNotebook->Layout();

}

MyFrame1::~MyFrame1()
{
}


void MyFrame1::doBasicDemo(const wxString &wx_text)
{
	const char *text = wx_text.c_str();
//	enum qrcodegen_Ecc errCorLvl = qrcodegen_Ecc_LOW;
	enum qrcodegen_Ecc errCorLvl = qrcodegen_Ecc_MEDIUM;

	uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
	uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
	bool ok = qrcodegen_encodeText(text, tempBuffer, qrcode, errCorLvl,
		qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
	if (ok)
		printQr(qrcode);
		saveBitmap("/home/olimex/plan1.bmp", qrcode);
}

void MyFrame1::printQr(const uint8_t qrcode[]) {
	int x, y;
	int size = qrcodegen_getSize(qrcode);
	int border = 4;
	for (y = -border; y < size + border; y++) {
		for (x = -border; x < size + border; x++) {
			fputs((qrcodegen_getModule(qrcode, x, y) ? "##" : "  "), stdout);
		}
		fputs("\n", stdout);
	}
	fputs("\n", stdout);
}

std::string MyFrame1::toSvgString(const uint8_t qrcode[], int border) const {
	int x, y;
	int size = qrcodegen_getSize(qrcode);
        if (border < 0)
//                throw {std::cerr << "Domain error: " << "Border must be non-negative" <<  std::endl;}
                throw std::domain_error("Border must be non-negative");
        if (border > INT_MAX / 2 || border * 2 > INT_MAX - size)
//                std::cerr << "Overflow error: " << "Border too large" <<  std::endl;
                throw std::overflow_error("Border too large");
        
        std::ostringstream sb;
        sb << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        sb << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
        sb << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" viewBox=\"0 0 ";
        sb << (size + border * 2) << " " << (size + border * 2) << "\" stroke=\"none\">\n";
        sb << "\t<rect width=\"100%\" height=\"100%\" fill=\"#FFFFFF\"/>\n";
        sb << "\t<path d=\"";
        for (y = 0; y < size; y++) {
                for (x = 0; x < size; x++) {
                        if (qrcodegen_getModule(qrcode, x, y)) {
                                if (x != 0 || y != 0)
                                        sb << " ";
                                sb << "M" << (x + border) << "," << (y + border) << "h1v1h-1z";
                        }
                }
        }
        sb << "\" fill=\"#000000\"/>\n";
        sb << "</svg>\n";
        return sb.str();
}

/*Used to write QR code data into BMP image and generate BMP format picture*/
void MyFrame1::saveBitmap(const char *name, const uint8_t qrcode[])
{
	int x, y;
//        double x = 0, y = 0, x1 = 0, y1 = 0;  // Pixel coordinates, the image is scanned from left
//        to right, from top to bottom, mathematical two-bit coordinate system
	uint8_t qr_size = qrcodegen_getSize(qrcode);
//	int border = 4;
        printf("QR size %d\n", qr_size);
        const uint8_t w = 21; //Picture side length
        const uint32_t height = w;  // Image high
        const uint32_t width = w;  // width
//        const int rowSize = wxRound( (width * 3 + 3) / 4 * 4);
//        const int size = height * width * 3; // Total size of image data
        const int size = 1323 + 105; // Total size of image data
        int index = 0;  // Pixel position
        const double side = w % 4;
        char cur_c;
        uint8_t bufferBmp[] = {'B', 'M'};

// bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size
// Two reserved variables, set to 0
// bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
// Message header size
// Image high
// Image width
// Target device level, must be 1 - Planes 1, BitPerPixels 24 : 24 << 16 + 1 = 1572865
//        uint16_t bufferPlanes[] = {1, 24};
// The amount of compression
// Image data size
// biXPelsPerMeter = 1
// biYPelsPerMeter = 1
// ColorsUsed
// ColorsImportant
//        uint32_t bufferFileHeader[] = {19254, 0, 54, 40, 80, 80, 1572865, 0, 19200, 1, 1, 0, 0};
        uint32_t bufferFileHeader[] = {1510, 0, 54, 40, 21, 21, 1572865, 0, 1428, 1, 1, 0, 0};
//        uint32_t bufferBitmapHeader[] = {40, 80, 80, 1572865, 0, 19200, 0, 1, 1, 0, 0};

        uint8_t *bits = (uint8_t *)malloc(size);  // Open up memory to store image data

        memset(bits, 0xFF, size);  // Change the data in size bytes after the bits pointer to  0xFF
  // That is, the image data is initialized to white
        for (x = 0; x <= qr_size; x = x + 1)
//	for (y = -border; y < qr_size + border; y++)
        {
                for (y = 0; y <= qr_size; y += 1)
//		for (x = -border; x < qr_size + border; x++)
                {

//                        index = (uint8_t)((y + side) * w * 3 + (x + side) * 3);
                        index = ((y + side) * w * 3 + (x + side) * 3);
//                        index = int(y * w * 3 + x * 3);
                        if (qrcodegen_getModule(qrcode, x, y))
                        {
                                bits[index + 0] = 1;
                                bits[index + 1] = 1;
                                bits[index + 2] = 1;
                        }
                }
        }

   // Open the file for reading and writing, create it if you don't have it
        FILE *output = fopen(name, "wb");
        if (output == NULL)
        {
                printf("Cannot open file!\n");
        }
        else
        {
                fwrite(bufferBmp, sizeof(uint8_t), sizeof(bufferBmp), output);
                fwrite(bufferFileHeader, sizeof(uint32_t), sizeof(bufferFileHeader), output);
//                fwrite(bufferBitmapHeader, sizeof(uint32_t), sizeof(bufferBitmapHeader), output);
                fwrite(bits, size, 1, output);// Write image data
                fclose(output); // Close file
                printf("%s - QR code generated\n",name);
        }
}



void MyFrame1::OnCoSelected( wxListEvent &event )
{
    long clicked_index = event.m_itemIndex;

  //    Route  =  Item( ps57ListCtrl1->GetItemData( clicked_index ) )->GetData();
//     unsigned int item = ps57ListCtrl1->GetItemData( clicked_index );

    wxListItem info2;
    wxListItem info4;
    wxListItem info6;
    wxJSONValue v;

    info2.m_itemId = clicked_index;
    info2.m_col = 6;
    info2.m_mask = wxLIST_MASK_TEXT;

    if (ps57ListCtrl1->GetItem(info2))
    {
        printf(wxString::Format("On Components Selected ListCtr data from ID col:  %s\n", info2.m_text));
        wxLogMessage("On Components Selected ListCtr Weigh:  %s\n", info2.m_text);

    } else {
        printf("On Components Selected ListCtr GetItem() failed\n");
        wxFAIL_MSG("On Components Selected ListCtr GetItem() failed\n");
    }




    info6.m_itemId = clicked_index;
    info6.m_col = 3;
    info6.m_mask = wxLIST_MASK_TEXT;

    if (ps57ListCtrl1->GetItem(info6))
    {
        doBasicDemo(info6.m_text);
    } else {
        printf("On Components Selected ListCtr GetItem() failed\n");
        wxFAIL_MSG("On Components Selected ListCtr GetItem() failed\n");
    }



    info4.m_itemId = clicked_index;
    info4.m_col = 0;
    info4.m_mask = wxLIST_MASK_TEXT;

    if (ps57ListCtrl1->GetItem(info4))
    {
        printf(wxString::Format("On Components Selected ListCtr ID :  %s\n", info4.m_text));
        wxLogMessage("On Components Selected ListCtr ID:  %s\n", info4.m_text);
    } else {
        printf("On Components Selected ListCtr GetItem() failed\n");
        wxFAIL_MSG("On Components Selected ListCtr GetItem() failed\n");
    }


    std::string st3(" SELECT quantity FROM projects_projectcomponent WHERE component_id = ");
    st3 += info4.m_text.c_str();
    st3 += "";
// We are put different condition (creator_id) to the same variable idClient

    idProgress = st3;

  try {
    mysqlcppapi::Connection con;
    con.set_Host("localhost");
    con.set_User("root");
    con.set_Password("Android123");
    con.connect();
    con.select_database("drf_android");
    
    mysqlcppapi::Query query = con.create_Query();

//    std::string curSql2("select a.id, a.name, a.category, a.code, a.composition, a.description, a.image, a.measure_unit, a.position, a.price, a.price_insystem, a.product, a.weight, a.is_active, a.is_reportable, a.is_saleable  from components_component a ");
    std::string curSql2("");
    curSql2 += idProgress;
    query <<  curSql2;



    std::cout << "Query: " << query.preview() << std::endl;

    mysqlcppapi::Result_Store res = query.store();

    mysqlcppapi::Result_Store::iterator i = res.begin();
    mysqlcppapi::Row row = *i;
//      printf("On Components Selected Quantity :  %s\n", row[0]);
    printf(wxString::Format("On Components Selected Quantity :  %s\n", _(row[0])));
      v[_T("Decl")] = _(row[0]);
      wxString msg_id(_T("OCPN_DBP_DB_QUANTITY"));
      g_pi_manager->SendJSONMessageToAllPlugins(msg_id, v);

  }
  catch(mysqlcppapi::ex_BadQuery& er)
  {
   // handle any connection or query errors that may come up
      std::cerr << "Error: " << er.what() <<  std::endl;
  }
  catch(mysqlcppapi::ex_BadConversion& er)
  {
    // we still need to catch bad conversions in case something goes 
    // wrong when the data is converted into stock
      std::cerr << "Error: Tried to convert \"" << er.get_Data() << "\" to a \""
   << er.get_TypeName() << "\"." << std::endl;
  }

        v[_T("Decl")] = info2.m_text;
        wxString msg_id(_T("OCPN_DBP_DB_WEIGH"));
        g_pi_manager->SendJSONMessageToAllPlugins(msg_id, v);



}



void MyFrame1::OnPrSelected( wxListEvent &event )
{
    long clicked_index = event.m_itemIndex;
    long cur_item = -1;
    wxListItem info;

    info.m_itemId = clicked_index;
    info.m_col = 0;
    info.m_mask = wxLIST_MASK_TEXT;

    if (ps57CtlListCtrl->GetItem(info))
    {
//        printf(wxString::Format("On Project Selected ListCtr data from ID col:  %s\n", info.m_text));
        wxLogMessage("On Project Selected ListCtr %s\n", info.m_text);
    } else {
//        printf("On Project Selected ListCtr GetItem() failed\n");
        wxFAIL_MSG("On Project Selected ListCtr GetItem() failed\n");
    }
//    Route  =  Item( ps57CtlListCtrl->GetItemData( clicked_index ) )->GetData();
//    cur_item = ps57CtlListCtrl->GetItemData( clicked_index );
//    cur_item = ps57CtlListCtrl->GetNextItem(cur_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);


//    std::string st2(" AND a.id IN (SELECT component_id FROM projects_projectcomponent WHERE project_id = ");
    std::string st2(" WHERE a.id IN (SELECT component_id FROM projects_projectcomponent WHERE project_id = ");
    st2 += info.m_text.c_str();
    st2 += ")";
// We are put different condition (creator_id) to the same variable idClient
    idCreator = st2;


    ps57ListCtrl1->Hide();
    ps57ListCtrl1->ClearAll();
    GetComponents(ps57ListCtrl1);
    ps57ListCtrl1->Update();
    ps57ListCtrl1->Show();
    ps57ListCtrl1->Raise();


//    if( cc1 )
//        cc1->Refresh();

//    UpdatePrButtons();
}

void MyFrame1::OnPrChoice( wxCommandEvent& event )
{
    wxString myStr;
    myStr = wxEmptyString;
    int idChoice = pDispCat->GetSelection();

    printf("On Choice days Selected index %d ", idChoice);
    printf(wxString::Format("%s \n", event.GetString()));
//select id, name from projects_project where  unix_timestamp(date_creation) > UNIX_TIMESTAMP(DATE_ADD(CURDATE(),INTERVAL -40 DAY));

    std::string st3(" where  unix_timestamp(date_creation) > UNIX_TIMESTAMP(DATE_ADD(CURDATE(),INTERVAL -");
    st3 += event.GetString();
    st3 += " DAY))";
    idClient = st3;
    ps57CtlListCtrl->Hide();
    ps57CtlListCtrl->ClearAll();
    GetProjects(ps57CtlListCtrl);
    ps57CtlListCtrl->Update();
    ps57CtlListCtrl->Show();
    ps57CtlListCtrl->Raise();


}

void MyFrame1::OnPrChoicePointStyle( wxCommandEvent& event )
{
    wxString myStr;
    myStr = wxEmptyString;
    int idChoice = pPointStyle->GetSelection();

    printf("On Choice Points Selected index %d ", idChoice);
    printf(wxString::Format("%s \n", event.GetString()));

}

void MyFrame1::OnBoundStyle( wxCommandEvent& event )
{
    wxString myStr;
    myStr = wxEmptyString;
    int idChoice = pBoundStyle->GetSelection();

    printf("On Choice Bounds Selected index %d ", idChoice);
    printf(wxString::Format("%s \n", event.GetString()));

}

void MyFrame1::On24Color( wxCommandEvent& event )
{
    wxString myStr;
    myStr = wxEmptyString;
    int idChoice = p24Color->GetSelection();

    printf("On Choice Colors Selected index %d ", idChoice);
    printf(wxString::Format("%s \n", event.GetString()));

}

void MyFrame1::OnPointStyle1( wxCommandEvent& event )
{
    wxString myStr;
    myStr = wxEmptyString;
    int idChoice = pPointStyle1->GetSelection();

    printf("On Choice PointStyle Selected index %d ", idChoice);
    printf(wxString::Format("%s \n", event.GetString()));

}

void MyFrame1::OnSafetyCtl( wxCommandEvent& event )
{
//    wxString myStr;
//    myStr = wxEmptyString;
    wxString  m_textCtrlInfo = m_SafetyCtl->GetValue();
    std::string st1(" WHERE client_id = ");
    st1 += m_textCtrlInfo.c_str();
    idClient = st1;
    ps57CtlListCtrl->Hide();
    ps57CtlListCtrl->ClearAll();
    GetProjects(ps57CtlListCtrl);
    ps57CtlListCtrl->Update();
    ps57CtlListCtrl->Show();
    ps57CtlListCtrl->Raise();

    printf("On ID Client Selected %d, ", event.GetId());
    printf(wxString::Format("* %s, ", event.GetString()));
    printf(wxString::Format("* %s \n", m_textCtrlInfo));

}

void MyFrame1::OnDeepCtl( wxCommandEvent& event )
{
//    wxString myStr;
//    myStr = wxEmptyString;
    wxString  m_textCtrlInfo = m_DeepCtl->GetValue();
    std::string st1(" WHERE creator_id = ");
    st1 += m_textCtrlInfo.c_str();
// We are put different condition (creator_id) to the same variable idClient
    idClient = st1;
    ps57CtlListCtrl->Hide();
    ps57CtlListCtrl->ClearAll();
    GetProjects(ps57CtlListCtrl);
    ps57CtlListCtrl->Update();
    ps57CtlListCtrl->Show();
    ps57CtlListCtrl->Raise();

    printf("On ID Creator Selected %d, ", event.GetId());
    printf(wxString::Format("* %s, ", event.GetString()));
    printf(wxString::Format("* %s \n", m_textCtrlInfo));

}

void MyFrame1::GetComponents(wxListCtrl *ps57CtlListCtrl1) {

    long index=0;


  try {
    mysqlcppapi::Connection con;
    con.set_Host("localhost");
    con.set_User("root");
    con.set_Password("Android123");
    con.connect();
    con.select_database("drf_android");
    
    mysqlcppapi::Query query = con.create_Query();
    // This creates a query object that is bound to con.

//    query << "select id, name, category, code, composition, description, image, measure_unit, position, price, price_insystem, product, weight, is_active, is_reportable, is_saleable  from components_component ORDER BY id DESC LIMIT 10";
    // You can write to the query object like you would any other ostrem

//    std::string curSql("select id, name, date_creation, product, client_id, creator_id  from projects_project ");
//    std::string curSql2("select a.id, a.name, a.category, a.code, a.composition, a.description, a.image, a.measure_unit, a.position, a.price, a.price_insystem, a.product, a.weight, a.is_active, a.is_reportable, a.is_saleable, b.quantity  from components_component a, projects_projectcomponent b WHERE a.id = b.component_id ");
//    std::string curSql2("select a.id, a.name, a.category, a.code, a.composition, a.description, a.image, a.measure_unit, a.position, a.price, a.price_insystem, a.product, a.weight, a.is_active, a.is_reportable, a.is_saleable, b.quantity  from components_component a LEFT OUTER JOIN projects_projectcomponent b ON a.id = b.component_id ");
    std::string curSql2("select a.id, a.name, a.category, a.code, a.composition, a.description, a.image, a.measure_unit, a.position, a.price, a.price_insystem, a.product, a.weight, a.is_active, a.is_reportable, a.is_saleable  from components_component a ");
    curSql2 += idCreator;
    query <<  curSql2;



    std::cout << "Query: " << query.preview() << std::endl;

    mysqlcppapi::Result_Store res = query.store();
    // Query::store() executes the query and returns the results

    ps57CtlListCtrl1->InsertColumn(0, _("ID"));
    ps57CtlListCtrl1->InsertColumn(1, _("Name"));
    ps57CtlListCtrl1->InsertColumn(2, _("Category"));
    ps57CtlListCtrl1->InsertColumn(3, _("Code"));
//    ps57CtlListCtrl1->InsertColumn(4, _("Composition"));
//    ps57CtlListCtrl1->InsertColumn(5, _("Description"));
//    ps57CtlListCtrl1->InsertColumn(6, _("Image"));
    ps57CtlListCtrl1->InsertColumn(4, _("Measure unit"));
    ps57CtlListCtrl1->InsertColumn(5, _("Position"));
//    ps57CtlListCtrl1->InsertColumn(9, _("Price"));
//    ps57CtlListCtrl1->InsertColumn(10, _("Price insystem"));
//    ps57CtlListCtrl1->InsertColumn(11, _("Product"));
    ps57CtlListCtrl1->InsertColumn(6, _("Weight"));
//    ps57CtlListCtrl1->InsertColumn(13, _("Is Active"));
//    ps57CtlListCtrl1->InsertColumn(14, _("Is Reportable"));
//    ps57CtlListCtrl1->InsertColumn(15, _("Is Saleable"));


    wxListItem* item = new wxListItem();

    // The Result_Store class has a read-only Random Access Iterator
    for (mysqlcppapi::Result_Store::iterator i = res.begin(); i != res.end(); i++)
    {
      mysqlcppapi::Row row = *i;

      item->SetBackgroundColour(*wxRED);
      item->SetText(wxT("Programmer"));
      item->SetId(0);

      index = ps57CtlListCtrl1->InsertItem(0, *item);
      ps57CtlListCtrl1->SetItem(index, 0, _(row[0]), -1);
      ps57CtlListCtrl1->SetItem(index, 1, _(row[1]), -1);
      ps57CtlListCtrl1->SetItem(index, 2, _(row[2]), -1);
      ps57CtlListCtrl1->SetItem(index, 3, _(row[3]), -1);
//      ps57CtlListCtrl1->SetItem(index, 4, _(row[4]), -1);
//      ps57CtlListCtrl1->SetItem(index, 5, _(row[5]), -1);
//      ps57CtlListCtrl1->SetItem(index, 6, _(row[6]), -1);
      ps57CtlListCtrl1->SetItem(index, 4, _(row[7]), -1);
      ps57CtlListCtrl1->SetItem(index, 5, _(row[8]), -1);
//      ps57CtlListCtrl1->SetItem(index, 9, _(row[9]), -1);
//      ps57CtlListCtrl1->SetItem(index, 10, _(row[10]), -1);
//      ps57CtlListCtrl1->SetItem(index, 11, _(row[11]), -1);
      ps57CtlListCtrl1->SetItem(index, 6, _(row[12]), -1);
//      ps57CtlListCtrl1->SetItem(index, 13, _(row[13]), -1);
//      ps57CtlListCtrl1->SetItem(index, 14, _(row[14]), -1);
//      ps57CtlListCtrl1->SetItem(index, 15, _(row[15]), -1);

    }
  }
  catch(mysqlcppapi::ex_BadQuery& er)
  {
   // handle any connection or query errors that may come up
      std::cerr << "Error: " << er.what() <<  std::endl;
  }
  catch(mysqlcppapi::ex_BadConversion& er)
  {
    // we still need to catch bad conversions in case something goes 
    // wrong when the data is converted into stock
      std::cerr << "Error: Tried to convert \"" << er.get_Data() << "\" to a \""
   << er.get_TypeName() << "\"." << std::endl;
  }
}

void MyFrame1::GetProjects(wxListCtrl  *ps57CtlListCtrl) {

  long index=0;

  try {
    mysqlcppapi::Connection con;
    con.set_Host("localhost");
    con.set_User("root");
    con.set_Password("Android123");
    con.connect();
    con.select_database("drf_android");


    mysqlcppapi::Query query = con.create_Query();
    // This creates a query object that is bound to con.

    std::string curSql("select id, name, date_creation, product, client_id, creator_id  from projects_project ");
    curSql += idClient;
    query <<  curSql;
    // You can write to the query object like you would any other ostrem

//    std::cout << "Query: " << query.preview() << std::endl;


    mysqlcppapi::Result_Store res = query.store();
    // Query::store() executes the query and returns the results

    ps57CtlListCtrl->InsertColumn(0, _("ID"));
    ps57CtlListCtrl->InsertColumn(1, _("Name"));
    ps57CtlListCtrl->InsertColumn(2, _("Date creation"));
    ps57CtlListCtrl->InsertColumn(3, _("Product"));
    ps57CtlListCtrl->InsertColumn(4, _("Client ID"));
    ps57CtlListCtrl->InsertColumn(5, _("Creator ID"));

    wxListItem* item = new wxListItem();

    // The Result_Store class has a read-only Random Access Iterator
    for (mysqlcppapi::Result_Store::iterator i = res.begin(); i != res.end(); i++)
    {
      mysqlcppapi::Row row = *i;

      item->SetBackgroundColour(*wxRED);
      item->SetText(wxT("Programmer"));
      item->SetId(0);

      index = ps57CtlListCtrl->InsertItem(0, *item);
      ps57CtlListCtrl->SetItem(index, 0, _(row[0]), -1);
      ps57CtlListCtrl->SetItem(index, 1, _(row[1]), -1);
      ps57CtlListCtrl->SetItem(index, 2, _(row[2]), -1);
      ps57CtlListCtrl->SetItem(index, 3, _(row[3]), -1);
      ps57CtlListCtrl->SetItem(index, 4, _(row[4]), -1);
      ps57CtlListCtrl->SetItem(index, 5, _(row[5]), -1);

    }
  }
  catch(mysqlcppapi::ex_BadQuery& er)
  {
   // handle any connection or query errors that may come up
      std::cerr << "Error: " << er.what() <<  std::endl;
  }
  catch(mysqlcppapi::ex_BadConversion& er)
  {
    // we still need to catch bad conversions in case something goes 
    // wrong when the data is converted into stock
      std::cerr << "Error: Tried to convert \"" << er.get_Data() << "\" to a \""
   << er.get_TypeName() << "\"." << std::endl;
  }
}


void MyFrame1::OnButton1(wxCommandEvent& event)
{

   event.Skip();

}

void MyFrame1::OnBtnSelectClick(wxCommandEvent& event)
{
   event.Skip();
// RoutePrintSelection *pTrackPrintSelection = new RoutePrintSelection( this, m_pRoute );
// pTrackPrintSelection->ShowModal();
// delete pTrackPrintSelection;
}

void MyFrame1::OnBtnClearClick(wxCommandEvent& event)
{
   event.Skip();
}

void MyFrame1::OnSize(wxSizeEvent& event)
{
    wxSize size = event.GetSize();
}

void MyFrame1::OnMove(wxMoveEvent& event)
{

   event.Skip();

}

void MyFrame1::OnActivateApp( wxActivateEvent& event )
{
  if(!event.GetActive())
  {
    printf("App de-activate\n");
  } else {
    printf("App activate\n");
  }
}


void MyFrame1::OnMaximize(wxMaximizeEvent& event)
{

   event.Skip();

}

void MyFrame1::OnEraseBackgroun(wxEraseEvent& event)
{
   event.Skip();
}
