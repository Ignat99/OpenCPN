#include "myframe1.h"

#include <mysqlcppapi/mysqlcppapi.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
#include "pluginmanager.h"
#include <stdint.h>
#include "qrcodegen.h"
#include "ImagePanel.hpp"
#include "bmp_output.hpp"
#include "labelprintout.h"
#include "Select.h"

extern PlugInManager    *g_pi_manager;
extern LabelPrintSelection    *pLabelPrintSelection;
extern wxString    g_default_wp_icon;
extern LabelList *pLabelList;
extern Select *pSelect;

#define BUTTON1 11000

wxBEGIN_EVENT_TABLE(MyFrame1, wxFrame)
    EVT_SIZE(MyFrame1::OnSize)
    EVT_BUTTON(BUTTON1, MyFrame1::OnButton1)
    EVT_MOVE(MyFrame1::OnMove)
    EVT_ACTIVATE(MyFrame1::OnActivate)
wxEND_EVENT_TABLE()

//    EVT_MAXIMIZE(MyFrame1::OnMaximize)
//    EVT_ERASE_BACKGROUND(MyFrame1::OnEraseBackground)

// Global print data, to remember settings during the session
extern wxPrintData*    g_printData;
// Global page setup data
extern wxPageSetupData*    g_pageSetupData;

MyFrame1::MyFrame1( wxFrame *frame, const wxString& title, const wxPoint& pos,
     const wxSize& size, long style ) :
     wxFrame( frame, -1, title, pos, size, style ) 
{

    wxDC *dc = new wxScreenDC();
    wxFont *qFont = GetOCPNScaledFont(_("Dialog"));
//    dc->SetFont( *qFont );

    idClient = " WHERE id = 596";
//    idCreator = " AND a.id = 1";
    idCreator = " WHERE a.id = 1";
    idProgress = " Progress 1%";

//    dbHost = "192.168.1.3";
//    dbUser = "djan_claroflex";
//    dbPassword = "7njc4m4mYwmPI4LG";
//    dbName = "claroflex_v0.2";

//    dbHost = "localhost";
//    dbUser = "root";
//    dbPassword = "Android123";
//    dbName = "drf_android";

    dbHost = "34.244.61.90";
    dbUser = "root";
    dbPassword = "dQ0;Cdm5HDM^3]w";
    dbName = "claroflex_v02";


    m_whatever = 1;
    m_pageDisplay = -1;
    int border_size = 4;
    int group_item_spacing = 2;
    int font_size_y, font_descent, font_lead;
    dc->GetTextExtent( _T("0"), NULL, &font_size_y, &font_descent, &font_lead );
//    m_small_button_size = wxSize( -1, (int) ( 1.4 * (font_size_y + font_descent + font_lead) ) );
    m_small_button_size = wxSize( -1, (int) ( 4.0 * (font_size_y + font_descent + font_lead) ) );

        wxScrolledWindow* ps57Ctl1 = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(1495, 990), wxHSCROLL | wxVSCROLL | wxTAB_TRAVERSAL);

        vectorPanel = new wxBoxSizer(wxHORIZONTAL);


        m_pNotebook = new wxNotebook (ps57Ctl1, wxID_ANY, wxDefaultPosition, wxSize(1490, 980), wxNB_TOP);

        wxPanel *pPanel = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxSize(1480, 950), wxNO_BORDER | wxTAB_TRAVERSAL, _("Bascula") );

        pPanel->SetFont( *qFont );

        m_pNotebook->AddPage(pPanel, _("Display") );



//        Centre();

    picturePanel = new wxBoxSizer(wxVERTICAL);


    wxFlexGridSizer* optionsColumn = new wxFlexGridSizer(1);
    optionsColumn->SetHGap(border_size);
//    optionsColumn->AddGrowableCol( 0, 2 );
//    optionsColumn->AddGrowableCol( 1, 3 );
    vectorPanel->Add( picturePanel);
//    vectorPanel->Add( optionsColumn, 3, wxALL | wxEXPAND, border_size );
    picturePanel->Add( optionsColumn, 3, wxALL, border_size );

    // spacer
    optionsColumn->Add( new wxStaticText(pPanel, wxID_ANY, _T("")) );
    optionsColumn->Add( new wxStaticText(pPanel, wxID_ANY, _T("")) );


    // dislay category
    optionsColumn->Add( new wxStaticText(pPanel, wxID_ANY, _("Data creation")), labelFlags );
    wxString pDispCatStrings[] = { _("1"), _("2"), _("3"), _("4"), _("5"), _("6"), _("7"), _("10"), _("12"), _("14"), _("21"), _("31"), _("62") };
//    pDispCat = new wxChoice( pPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 13, pDispCatStrings );
    pDispCat = new wxChoice( pPanel, wxID_ANY, wxDefaultPosition, wxSize(180, 60), 13, pDispCatStrings );
    pDispCat->SetSelection(0);
    optionsColumn->Add( pDispCat, 0, wxALL, 2 );

    pDispCat->Connect( wxEVT_COMMAND_CHOICE_SELECTED,  wxCommandEventHandler(MyFrame1::OnPrChoice), NULL, this );


    // spacer
    optionsColumn->Add( new wxStaticText(pPanel, wxID_ANY, _T("")) );
    optionsColumn->Add( new wxStaticText(pPanel, wxID_ANY, _T("")) );


    // spacer
    optionsColumn->Add( 0, border_size*4 );
    optionsColumn->Add( 0, border_size*4 );



    // graphics options
//    optionsColumn->Add( new wxStaticText(pPanel, wxID_ANY, _("Remarks")), labelFlags );
//    wxString pPointStyleStrings[] = { _("Paper Chart"), _("Simplified"), };
//    pPointStyle = new wxChoice( pPanel, ID_1RADARDISTUNIT, wxDefaultPosition, wxSize(180, 60), 2, pPointStyleStrings );
//    optionsColumn->Add( pPointStyle, inputFlags );

//    pPointStyle->Connect( wxEVT_COMMAND_CHOICE_SELECTED,  wxCommandEventHandler(MyFrame1::OnPrChoicePointStyle), NULL, this );


//    optionsColumn->Add( new wxStaticText(pPanel, wxID_ANY, _("Remarks special")), labelFlags );
//    wxString pBoundStyleStrings[] = { _("Plain"), _("Symbolized"), };
//    pBoundStyle = new wxChoice( pPanel, ID_1RADARDISTUNIT, wxDefaultPosition, wxSize(180, 60), 2, pBoundStyleStrings );
//    optionsColumn->Add( pBoundStyle, inputFlags );

//    pBoundStyle->Connect( wxEVT_COMMAND_CHOICE_SELECTED,  wxCommandEventHandler(MyFrame1::OnBoundStyle), NULL, this );


//    optionsColumn->Add( new wxStaticText(pPanel, wxID_ANY, _("Remarks internal")), labelFlags );
//    wxString pColorNumStrings[] = { _("2 Color loooong"), _("4 Color loooong"), };
//    p24Color = new wxChoice( pPanel, ID_1RADARDISTUNIT, wxDefaultPosition, wxSize(180, 60), 2, pColorNumStrings );
//    optionsColumn->Add( p24Color, inputFlags );

//    p24Color->Connect( wxEVT_COMMAND_CHOICE_SELECTED,  wxCommandEventHandler(MyFrame1::On24Color), NULL, this );


    // spacer
    optionsColumn->Add( 0, border_size*4 );
    optionsColumn->Add( 0, border_size*4 );



    // depth options
    optionsColumn->Add( new wxStaticText( pPanel, ID_1RADARDISTUNIT, _("Packets") ), labelFlags );
//    wxBoxSizer* depShalRow = new wxBoxSizer( wxHORIZONTAL );
//    optionsColumn->Add( depShalRow );
    wxString pPointStyleStrings1[] = { _("1"), _("2"), _("3"), _("4"), _("5"), _("6"), _("7"), _("8"), _("9"), _("10"), _("11"), _("25 pcs"), _("30 pcs"), _("50 pcs"), _("100 pcs") };
    pPointStyle1 = new wxChoice( pPanel, ID_1RADARDISTUNIT, wxDefaultPosition,
            wxSize(180, 60), 15, pPointStyleStrings1 );
    pPointStyle1->SetSelection(0);
    optionsColumn->Add( pPointStyle1, inputFlags );

     pPointStyle1->Connect( wxEVT_COMMAND_CHOICE_SELECTED,  wxCommandEventHandler(MyFrame1::OnPointStyle1), NULL, this );


    optionsColumn->Add( new wxStaticText( pPanel, wxID_ANY, _("Client") ), labelFlags );
    wxBoxSizer* depSafeRow = new wxBoxSizer( wxHORIZONTAL );
    optionsColumn->Add( depSafeRow );
    m_SafetyCtl = new wxTextCtrl( pPanel, ID_1TEXTCTRL, _T("596"), wxDefaultPosition, wxSize( 180, 60 ), wxTE_RIGHT );
    depSafeRow->Add( m_SafetyCtl, inputFlags );
    //m_depthUnitsSafe = new wxStaticText( pParent, wxID_ANY, _("metres") );
    //depSafeRow->Add( m_depthUnitsSafe, inputFlags );

    m_SafetyCtl->Connect( wxEVT_COMMAND_TEXT_UPDATED,  wxCommandEventHandler(MyFrame1::OnSafetyCtl), NULL, this );


    optionsColumn->Add( new wxStaticText( pPanel, wxID_ANY, _("Creator") ), labelFlags );
    wxBoxSizer* depDeepRow = new wxBoxSizer( wxHORIZONTAL );
    optionsColumn->Add( depDeepRow );
    m_DeepCtl = new wxTextCtrl( pPanel, ID_1TEXTCTRL, _T("596"), wxDefaultPosition, wxSize( 180, 60 ), wxTE_RIGHT );
    depDeepRow->Add( m_DeepCtl, inputFlags );
    //m_depthUnitsDeep = new wxStaticText( pParent, wxID_ANY, _("metres") );
    //depDeepRow->Add( m_depthUnitsDeep, inputFlags );

    m_DeepCtl->Connect( wxEVT_COMMAND_TEXT_UPDATED,  wxCommandEventHandler(MyFrame1::OnDeepCtl), NULL, this );




    // spacer
//    optionsColumn->Add( 0, border_size*4 );
//    optionsColumn->Add( 0, border_size*4 );


    // create Image panel
    wxBoxSizer* drawSizer = new wxBoxSizer(wxHORIZONTAL);
    drawPane = new ImagePanel(pPanel, wxT("/home/olimex/plan1.bmp"), wxBITMAP_TYPE_BMP);
    drawSizer->Add(drawPane, 1, wxALL | wxEXPAND);

    wxStaticBox* drawStaticBox = new wxStaticBox( pPanel, wxID_ANY, _("Component") );
    wxStaticBoxSizer* drawStaticSizer = new wxStaticBoxSizer( drawStaticBox, wxVERTICAL );

    drawStaticSizer->Add( drawPane, 1, wxALL | wxEXPAND, 0 );

//    picturePanel->Add( drawStaticSizer, 1, wxALL | wxEXPAND, 2  ); 
//    Cube picture of QR code
    picturePanel->Add( drawStaticSizer, 1, wxALL | wxEXPAND, 2  );


    wxBoxSizer* btnRow = new wxBoxSizer( wxHORIZONTAL );
    itemButtonSelectList = new wxButton( pPanel, ID_1SELECTLIST, _("Print label"), wxPoint(0, 0), wxSize(180, 60) );
    btnRow->Add( itemButtonSelectList, 1, wxALL | wxEXPAND, group_item_spacing );
//    itemButtonClearList = new wxButton( pPanel, ID_1CLEARLIST, _("Run Progress") );
//    btnRow->Add( itemButtonClearList, 1, wxALL | wxEXPAND, group_item_spacing );
//    picturePanel->Add( btnRow, 1, wxALL  | wxEXPAND, 2 );
    optionsColumn->Add( btnRow, inputFlags );





//    itemButtonSelectList->Connect( wxEVT_COMMAND_BUTTON_CLICKED,  wxCommandEventHandler(MyFrame1::DoLabel), NULL, this );
//    itemButtonSelectList->Connect( wxEVT_COMMAND_BUTTON_CLICKED,  wxCommandEventHandler(MyFrame1::OnLabelpropOkClick), NULL, this );
    itemButtonSelectList->Connect( wxEVT_COMMAND_BUTTON_CLICKED,  wxCommandEventHandler(MyFrame1::OnBtnPrintClick), NULL, this );
//    itemButtonClearList->Connect( wxEVT_COMMAND_BUTTON_CLICKED,  wxCommandEventHandler(MyFrame1::OnBtnClearClick), NULL, this );


    // 2nd column, Display Category / Mariner's Standard options
    wxBoxSizer* dispSizer = new wxBoxSizer( wxVERTICAL );
    vectorPanel->Add( dispSizer, 2, wxALL | wxEXPAND, border_size );

    wxStaticBox* marinersBox = new wxStaticBox( pPanel, wxID_ANY, _("Projects") );
    wxStaticBoxSizer* marinersSizer = new wxStaticBoxSizer( marinersBox, wxVERTICAL );
    dispSizer->Add( marinersSizer, 1, wxALL | wxEXPAND, border_size );


// Products

    ps57CtlListCtrl = new wxListCtrl( pPanel, ID_1CHECKLISTBOX, wxDefaultPosition, wxSize( 1000, 250 ),
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
                                        wxSize( 1000, 300 ), wxLC_REPORT );

    ps57ListCtrl1->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED,  wxListEventHandler(MyFrame1::OnCoSelected), NULL, this );


// Make memory list of selected component
    m_pLabel = new Label();
    pLabelList->Append( m_pLabel );
    InitializeList(ps57ListCtrl1);


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
        wxString my_path = "/home/olimex/tmp/old/build/components/";
        wxString file = "/home/olimex/plan1.bmp";
//	enum qrcodegen_Ecc errCorLvl = qrcodegen_Ecc_LOW;
	enum qrcodegen_Ecc errCorLvl = qrcodegen_Ecc_MEDIUM;

	uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
	uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
	bool ok = qrcodegen_encodeText(text, tempBuffer, qrcode, errCorLvl,
		qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
	if (ok)
		printQr(qrcode);
		saveBitmap(file, qrcode);
                my_path += wx_text;
                my_path += wxT(".bmp");
		saveBitmap( my_path, qrcode);
//                wxImage m_image(file);
//                m_image.Scale(200,200, wxIMAGE_QUALITY_NORMAL).SaveFile(file, wxBITMAP_TYPE_BMP);
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
	int qr_size = qrcodegen_getSize(qrcode); //Picture side length
//        add extra bytes for size by 4 bytes block
        const int side = (int) (qr_size % 4);
	int const top_border = 0; // Must be divide by 4 without remainder
	int const border = (4 - side);
        const int w = qr_size + border;
        const int height = w + top_border;  // Image high
        const int width = w + top_border;  // width
        const int image_size = height * width * 3;
//        look to bfOffBits
//        const int image_size = height * width * 3 + (height + width + top_border) * top_border;
        const int size = 54 + image_size; // Total size of image data
        int index = 0;  // Pixel position
        char cur_c;
        uint8_t bufferBmp[] = {'B', 'M'};

// bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size
// Two reserved variables, set to 0
// bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) = 14 + 40 = 54
// Message header size
// Image high
// Image width
// Target device level, must be 1 - Planes 1, BitPerPixels 24 : 24 << 16 + 1 = 1572865
//        uint16_t bufferPlanes[] = {1, 24};
// The amount of compression
// Image data size if it not compressed must be 0
// biXPelsPerMeter = 3780
// biYPelsPerMeter = 3780
// ColorsUsed - size of color table if BitPerPixels > 16 (In our case BpP=24 and ColUsed = 0)
// ColorsImportant = 0
        uint32_t bufferFileHeader[] = { (uint32_t) size, 0, 54, 40, (uint32_t) w, (uint32_t) w,
             1572865, 0, 0, 3780, 3780, 0, 0};

        uint8_t *bits = (uint8_t *)malloc(image_size);  // Open up memory to store image data
        memset(bits, 0xFF, image_size);  // Change the data in size bytes after the bits pointer to  0xFF
  // That is, the image data is initialized to white
        for (x = 0; x < height; x++ )
        {
                for (y = 0; y < width; y++)
                {
//                        index = (int)((y + side) * w * 3 + (x + side) * 3);
                        index = (int) (image_size - y * (width) * 3 - (height - x) * 3);
                        if (qrcodegen_getModule(qrcode, x, y))
                        {
                                bits[index + 0] = (uint8_t) 1;
                                bits[index + 1] = (uint8_t) 1;
                                bits[index + 2] = (uint8_t) 1;
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
//      Write two letters BM
                fwrite(bufferBmp, sizeof(uint8_t), sizeof(bufferBmp), output);
//      13 elements in buffer
                fwrite(bufferFileHeader, sizeof(uint32_t), 13, output);
                fwrite(bits, image_size, 1, output);// Write image data
                fclose(output); // Close file
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
    wxJSONValue pack_txt;

    OnLabelListClick(event);

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

    con.set_Host(dbHost);
    con.set_User(dbUser);
    con.set_Password(dbPassword);
    con.connect();
    con.select_database(dbName);

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
      db_quantity = row[0];
      v[_T("Decl")] = _(row[0]);
      wxString msg_id(_T("OCPN_DBP_DB_QUANTITY"));
      g_pi_manager->SendJSONMessageToAllPlugins(msg_id, v);

// Calculate bolsa
// We will put 4 just for test print more then 1 label without bascula
    pack = 1;
    pack_pcs = 30;
    pcs_last = 0;
    std::string packets_full_txt("");
    std::string packet_pcs_txt("");

    if (int(row[0]) > 330) {
        std::cout << "Quantity: " << row[0] << std::endl;

        if (int(row[0]) % 100  == 0 ) {
            pcs_last = 0;
            pack = int(row[0]) / 100;
            pack_pcs = 100;
            std::cout << "Quantity: " << row[0] << " Packets: " <<  pack  << std::endl;
            pPointStyle1->SetSelection(14);
        } else {

        if (int(row[0]) % 50  == 0 ) {
            pcs_last = 0;
            pack = int(row[0]) / 50;
            pack_pcs = 50;
            std::cout << "Quantity: " << row[0] << " Packets: " <<  pack << std::endl;
            pPointStyle1->SetSelection(13);
        } else {

        if (int(row[0]) % 30  == 0 ) {
            pcs_last = 0;
            pack = int(row[0]) / 30;
            pack_pcs = 30;
            std::cout << "Quantity: " << row[0] << " Packets: " <<  pack  << std::endl;
            pPointStyle1->SetSelection(12);
        } else {

        if (int(row[0]) % 25  == 0 ) {
            pcs_last = 0;
            pack = int(row[0]) / 25;
            pack_pcs = 25;
            std::cout << "Quantity: " << row[0] << " Packets: " <<  pack  << std::endl;
            pPointStyle1->SetSelection(11);
        } else {
            pcs_last = int(row[0]) % 30;
            pack = int((int(row[0]) - pcs_last)/ 30);
            pack_pcs = 30;
//            packets_full_txt += pack;
//            packet_pcs_txt += pack_pcs;
            std::cout << "Quantit " << row[0] << " Packets_full: " << pack  << " Per pocket : " << pack_pcs << " Pcs in fin_pocket: " <<  pcs_last << std::endl;
            pPointStyle1->SetSelection(12);
        }
    }}}}




    if (int(row[0]) < 31 ) {
        pack = 1;
        pack_pcs = row[0];
        std::cout << "Quantity: " << row[0] << " Packets: " <<  "1" << std::endl;
        pPointStyle1->SetSelection(0);
    } else {

    if (int(row[0]) < 61 ) {
        if (int(row[0]) % 2 == 0 ) {
            pack = 2;
            pack_pcs = int(int(row[0]) / 2);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "2" << std::endl;
            pPointStyle1->SetSelection(1);
        } else {
            pack = 2;
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "2" << std::endl;
            pPointStyle1->SetSelection(1);
        }
    if (int(row[0]) < 91 ) {
        if (int(row[0]) % 3 == 0 ) {
            pack = 3;
            pack_pcs = int(int(row[0]) / 3);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "3" << std::endl;
            pPointStyle1->SetSelection(2);
        } else {
            pack = 2;
            pcs_last = int(int(row[0]) % 2 );
            pack_pcs = int((int(row[0]) - pcs_last )/2);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "2" << std::endl;
            pPointStyle1->SetSelection(1);
        }

    } else {

    if (int(row[0]) < 121 ) {
        if (int(row[0]) % 4 == 0 ) {
            pack = 4;
            pack_pcs = int(int(row[0]) / 4);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "4" << std::endl;
            pPointStyle1->SetSelection(3);
        } else {
            if (int(row[0]) % 3 == 0 ) {
                pack = 3;
                pack_pcs = int(int(row[0]) / 3);
                std::cout << "Quantity: " << row[0] << " Packets: " <<  "3" << std::endl;
                pPointStyle1->SetSelection(2);
            } else {
                pack = 2;
                pcs_last = int(int(row[0]) % 2 );
                pack_pcs = int((int(row[0]) - pcs_last)/2);
                std::cout << "Quantity: " << row[0] << " Packets: " <<  "2" << std::endl;
                pPointStyle1->SetSelection(1);
            }

        }

    } else {

    if (int(row[0]) < 151 ) {
        if (int(row[0]) % 5 == 0 ) {
            pack = 5;
            pack_pcs = int(int(row[0]) / 5);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "5" << std::endl;
            pPointStyle1->SetSelection(4);
        } else {
        if (int(row[0]) % 4 == 0 ) {
            pack = 4;
            pack_pcs = int(int(row[0]) / 4);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "4" << std::endl;
            pPointStyle1->SetSelection(3);
        } else {
            if (int(row[0]) % 3 == 0 ) {
                pack = 3;
                pack_pcs = int(int(row[0]) / 3);
                std::cout << "Quantity: " << row[0] << " Packets: " <<  "3" << std::endl;
                pPointStyle1->SetSelection(2);
            } else {
                pack = 2;
                pcs_last = int(int(row[0]) % 2 );
                pack_pcs = int((int(row[0]) - pcs_last)/2);
                std::cout << "Quantity: " << row[0] << " Packets: " <<  "2" << std::endl;
                pPointStyle1->SetSelection(1);
            }

        }

        }
    } else {

    if (int(row[0]) < 181 ) {
        if (int(row[0]) % 6 == 0 ) {
            pack = 6;
            pack_pcs = int(int(row[0]) / 6);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "6" << std::endl;
            pPointStyle1->SetSelection(5);
        } else {
        if (int(row[0]) % 5 == 0 ) {
            pack = 5;
            pack_pcs = int(int(row[0]) / 5);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "5" << std::endl;
            pPointStyle1->SetSelection(4);
        } else {
        if (int(row[0]) % 4 == 0 ) {
            pack = 4;
            pack_pcs = int(int(row[0]) / 4);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "4" << std::endl;
            pPointStyle1->SetSelection(3);
        } else {
            if (int(row[0]) % 3 == 0 ) {
                pack = 3;
                pack_pcs = int(int(row[0]) / 3);
                std::cout << "Quantity: " << row[0] << " Packets: " <<  "3" << std::endl;
                pPointStyle1->SetSelection(2);
            } else {
                pack = 2;
                pcs_last = int(int(row[0]) % 2 );
                pack_pcs = int((int(row[0]) - pcs_last)/2);
                std::cout << "Quantity: " << row[0] << " Packets: " <<  "2" << std::endl;
                pPointStyle1->SetSelection(1);
            }

        }

        }
    }} else {

    if (int(row[0]) < 211 ) {
        if (int(row[0]) % 7 == 0 ) {
            pack = 7;
            pack_pcs = int(int(row[0]) / 7);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "7" << std::endl;
            pPointStyle1->SetSelection(6);
        } else {
        if (int(row[0]) % 6 == 0 ) {
            pack = 6;
            pack_pcs = int(int(row[0]) / 6);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "6" << std::endl;
            pPointStyle1->SetSelection(5);
        } else {
        if (int(row[0]) % 5 == 0 ) {
            pack = 5;
            pack_pcs = int(int(row[0]) / 5);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "5" << std::endl;
            pPointStyle1->SetSelection(4);
        } else {
        if (int(row[0]) % 4 == 0 ) {
            pack = 4;
            pack_pcs = int(int(row[0]) / 4);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "4" << std::endl;
            pPointStyle1->SetSelection(3);
        } else {
            if (int(row[0]) % 3 == 0 ) {
                pack = 3;
                pack_pcs = int(int(row[0]) / 3);
                std::cout << "Quantity: " << row[0] << " Packets: " <<  "3" << std::endl;
                pPointStyle1->SetSelection(2);
            } else {
                pack = 2;
                pcs_last = int(int(row[0]) % 2 );
                pack_pcs = int((int(row[0]) - pcs_last)/2);
                std::cout << "Quantity: " << row[0] << " Packets: " <<  "2" << std::endl;
                pPointStyle1->SetSelection(1);
            }

        }

        }
    }}} else {


    if (int(row[0]) < 241 ) {
        if (int(row[0]) % 8 == 0 ) {
            pack = 8;
            pack_pcs = int(int(row[0]) / 8);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "8" << std::endl;
            pPointStyle1->SetSelection(7);
        } else {
        if (int(row[0]) % 7 == 0 ) {
            pack = 7;
            pack_pcs = int(int(row[0]) / 7);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "7" << std::endl;
            pPointStyle1->SetSelection(6);
        } else {
        if (int(row[0]) % 6 == 0 ) {
            pack = 6;
            pack_pcs = int(int(row[0]) / 6);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "6" << std::endl;
            pPointStyle1->SetSelection(5);
        } else {
        if (int(row[0]) % 5 == 0 ) {
            pack = 5;
            pack_pcs = int(int(row[0]) / 5);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "5" << std::endl;
            pPointStyle1->SetSelection(4);
        } else {
        if (int(row[0]) % 4 == 0 ) {
            pack = 4;
            pack_pcs = int(int(row[0]) / 4);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "4" << std::endl;
            pPointStyle1->SetSelection(3);
        } else {
            if (int(row[0]) % 3 == 0 ) {
                pack = 3;
                pack_pcs = int(int(row[0]) / 3);
                std::cout << "Quantity: " << row[0] << " Packets: " <<  "3" << std::endl;
                pPointStyle1->SetSelection(2);
            } else {
                pack = 2;
                pcs_last = int(int(row[0]) % 2 );
                pack_pcs = int((int(row[0]) - pcs_last)/2);
                std::cout << "Quantity: " << row[0] << " Packets: " <<  "2" << std::endl;
                pPointStyle1->SetSelection(1);
            }

        }

        }
    }}}} else {

    if (int(row[0]) < 271 ) {
        if (int(row[0]) % 9 == 0 ) {
            pack = 9;
            pack_pcs = int(int(row[0]) / 9);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "9" << std::endl;
            pPointStyle1->SetSelection(8);
        } else {
        if (int(row[0]) % 8 == 0 ) {
            pack = 8;
            pack_pcs = int(int(row[0]) / 8);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "8" << std::endl;
            pPointStyle1->SetSelection(7);
        } else {
        if (int(row[0]) % 7 == 0 ) {
            pack = 7;
            pack_pcs = int(int(row[0]) / 7);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "7" << std::endl;
            pPointStyle1->SetSelection(6);
        } else {
        if (int(row[0]) % 6 == 0 ) {
            pack = 6;
            pack_pcs = int(int(row[0]) / 6);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "6" << std::endl;
            pPointStyle1->SetSelection(5);
        } else {
        if (int(row[0]) % 5 == 0 ) {
            pack = 5;
            pack_pcs = int(int(row[0]) / 5);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "5" << std::endl;
            pPointStyle1->SetSelection(4);
        } else {
        if (int(row[0]) % 4 == 0 ) {
            pack = 4;
            pack_pcs = int(int(row[0]) / 4);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "4" << std::endl;
            pPointStyle1->SetSelection(3);
        } else {
            if (int(row[0]) % 3 == 0 ) {
                pack = 3;
                pack_pcs = int(int(row[0]) / 3);
                std::cout << "Quantity: " << row[0] << " Packets: " <<  "3" << std::endl;
                pPointStyle1->SetSelection(2);
            } else {
                pack = 2;
                pcs_last = int(int(row[0]) % 2 );
                pack_pcs = int((int(row[0]) - pcs_last)/2);
                std::cout << "Quantity: " << row[0] << " Packets: " <<  "2" << std::endl;
                pPointStyle1->SetSelection(1);
            }

        }

        }
    }}}}} else {


    if (int(row[0]) < 301 ) {
        if (int(row[0]) % 10 == 0 ) {
            pack = 10;
            pack_pcs = int(int(row[0]) / 10);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "10" << std::endl;
            pPointStyle1->SetSelection(9);
        } else {
        if (int(row[0]) % 9 == 0 ) {
            pack = 9;
            pack_pcs = int(int(row[0]) / 9);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "9" << std::endl;
            pPointStyle1->SetSelection(8);
        } else {
        if (int(row[0]) % 8 == 0 ) {
            pack = 8;
            pack_pcs = int(int(row[0]) / 8);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "8" << std::endl;
            pPointStyle1->SetSelection(7);
        } else {
        if (int(row[0]) % 7 == 0 ) {
            pack = 7;
            pack_pcs = int(int(row[0]) / 7);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "7" << std::endl;
            pPointStyle1->SetSelection(6);
        } else {
        if (int(row[0]) % 6 == 0 ) {
            pack = 6;
            pack_pcs = int(int(row[0]) / 6);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "6" << std::endl;
            pPointStyle1->SetSelection(5);
        } else {
        if (int(row[0]) % 5 == 0 ) {
            pack = 5;
            pack_pcs = int(int(row[0]) / 5);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "5" << std::endl;
            pPointStyle1->SetSelection(4);
        } else {
        if (int(row[0]) % 4 == 0 ) {
            pack = 4;
            pack_pcs = int(int(row[0]) / 4);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "4" << std::endl;
            pPointStyle1->SetSelection(3);
        } else {
            if (int(row[0]) % 3 == 0 ) {
                pack = 3;
                pack_pcs = int(int(row[0]) / 3);
                std::cout << "Quantity: " << row[0] << " Packets: " <<  "3" << std::endl;
                pPointStyle1->SetSelection(2);
            } else {
                pack = 2;
                pcs_last = int(int(row[0]) % 2 );
                pack_pcs = int((int(row[0]) - pcs_last)/2);
                std::cout << "Quantity: " << row[0] << " Packets: " <<  "2" << std::endl;
                pPointStyle1->SetSelection(1);
            }

        }

        }
    }}}}}} else {

    if (int(row[0]) < 331 ) {
        if (int(row[0]) % 11 == 0 ) {
            pack = 11;
            pack_pcs = int(int(row[0]) / 11);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "11" << std::endl;
            pPointStyle1->SetSelection(10);
        } else {
        if (int(row[0]) % 10 == 0 ) {
            pack = 10;
            pack_pcs = int(int(row[0]) / 10);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "10" << std::endl;
            pPointStyle1->SetSelection(9);
        } else {
        if (int(row[0]) % 9 == 0 ) {
            pack = 9;
            pack_pcs = int(int(row[0]) / 9);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "9" << std::endl;
            pPointStyle1->SetSelection(8);
        } else {
        if (int(row[0]) % 8 == 0 ) {
            pack = 8;
            pack_pcs = int(int(row[0]) / 8);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "8" << std::endl;
            pPointStyle1->SetSelection(7);
        } else {
        if (int(row[0]) % 7 == 0 ) {
            pack = 7;
            pack_pcs = int(int(row[0]) / 7);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "7" << std::endl;
            pPointStyle1->SetSelection(6);
        } else {
        if (int(row[0]) % 6 == 0 ) {
            pack = 6;
            pack_pcs = int(int(row[0]) / 6);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "6" << std::endl;
            pPointStyle1->SetSelection(5);
        } else {
        if (int(row[0]) % 5 == 0 ) {
            pack = 5;
            pack_pcs = int(int(row[0]) / 5);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "5" << std::endl;
            pPointStyle1->SetSelection(4);
        } else {
        if (int(row[0]) % 4 == 0 ) {
            pack = 4;
            pack_pcs = int(int(row[0]) / 4);
            std::cout << "Quantity: " << row[0] << " Packets: " <<  "4" << std::endl;
            pPointStyle1->SetSelection(3);
        } else {
            if (int(row[0]) % 3 == 0 ) {
                pack = 3;
                pack_pcs = int(int(row[0]) / 3);
                std::cout << "Quantity: " << row[0] << " Packets: " <<  "3" << std::endl;
                pPointStyle1->SetSelection(2);
            } else {
                pack = 2;
                pcs_last = int(int(row[0]) % 2 );
                pack_pcs = int((int(row[0]) - pcs_last)/2);
                std::cout << "Quantity: " << row[0] << " Packets: " <<  "2" << std::endl;
                pPointStyle1->SetSelection(1);
            }

        }

        }
    }}}}}}} else {
            pcs_last = int(int(row[0]) % 30 );
            pack = int((int(row[0]) - pcs_last )/ 30) + 1;
            pack_pcs = 30;
            std::cout << "Quantity: " << row[0] << " Packets_full: " << pack  << " Per pocket : " << pack_pcs << " Pcs in fin_pocket: " <<  pcs_last << std::endl;
            pPointStyle1->SetSelection(12);



    } } } }}}}}}}}




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

        db_weigh = atof(info2.m_text);
        v[_T("Decl")] = info2.m_text;
        wxString msg_id(_T("OCPN_DBP_DB_WEIGH"));
        g_pi_manager->SendJSONMessageToAllPlugins(msg_id, v);


// Every time when select put first curent pack 
    pack_cur = 1;

    std::ostringstream packets_full_ss("");
    std::ostringstream packet_pcs_ss("");
    std::ostringstream packet_cur_ss("");
    std::ostringstream pcs_last_ss("");

      packets_full_ss << pack;
      packet_pcs_ss << pack_pcs;
      pcs_last_ss << pcs_last;
      packet_cur_ss << pack_cur;

      pack_txt[_T("Decl")] = _(packets_full_ss.str());
      wxString pack_msg_id(_T("OCPN_DBP_PACK"));
      g_pi_manager->SendJSONMessageToAllPlugins(pack_msg_id, pack_txt);

      pack_txt[_T("Decl")] = _(packet_cur_ss.str());
      wxString pack_cur_msg_id(_T("OCPN_DBP_PACK_CUR"));
      g_pi_manager->SendJSONMessageToAllPlugins(pack_cur_msg_id, pack_txt);


      pack_txt[_T("Decl")] = _(packet_pcs_ss.str());
      wxString pack_psc_msg_id(_T("OCPN_DBP_PACK_PCS"));
      g_pi_manager->SendJSONMessageToAllPlugins(pack_psc_msg_id, pack_txt);

      pack_txt[_T("Decl")] = _(pcs_last_ss.str());
      wxString pcs_last_msg_id(_T("OCPN_DBP_PCS_LAST"));
      g_pi_manager->SendJSONMessageToAllPlugins(pcs_last_msg_id, pack_txt);


      std::cout << "Instrunent Weigh: " << info2.m_text << " Packets_full: " << packets_full_ss.str()  << " Per pocket : " << packet_pcs_ss.str() << " Pcs last : " << pcs_last_ss.str() << std::endl;

// Update information in LabelPoint list

//      for ( int n = 1; n <= pLabelList->pLabelPointList->GetnPoints(); n++ ) {
//          LabelPoint *pLP_upd = pLabelList->pLabelPointList->GetPoint(n);
//          if (pLP_upd->m_bPtIsSelected) {
//              string cur_label(pLP_upd->GetCode().mb_str());
//              std::cout << "Point List: " << cur_label << std::endl;
//          }
//      }


// Correct right list
    wxLabelPointListNode *node = m_pLabel->pLabelPointList->GetFirst();

    while( node ) {
//        node = node->GetNext();


//    wxLabelListNode *node = pLabelList->GetFirst();
//    while(node) {
//        Label *cur_label = node->GetData();


        if ( node ) {
            LabelPoint *pLP_upd = node->GetData();

//        for ( int n = 1; n <= cur_label->GetnPoints(); n++ ) {
//            LabelPoint *pLP_upd = cur_label->GetPoint(n);


            if (pLP_upd->m_bPtIsSelected) {
                string cur_label_str(pLP_upd->GetCode().mb_str());
                std::cout << "Point List: " << cur_label_str << " Packets_full: " << packets_full_ss.str()  << " Per pocket : " << packet_pcs_ss.str() << " Pcs last : " << pcs_last_ss.str() << std::endl;
                pLP_upd->SetPack(packets_full_ss.str());
                pLP_upd->SetPcs(packet_pcs_ss.str());
                pLP_upd->SetLast(pcs_last_ss.str());

            }

//            if (cur_label == m_pLabel) {
//                std::cout << "m_pLabel: " << cur_label << " Packets_full: " << packets_full_ss.str()  << " Per pocket : " << packet_pcs_ss.str() << "Pcs last : " << pcs_last_ss.str() << std::endl;
//            }
//        }
       }

        node = node->GetNext();
    }

  drawPane->paintNow();

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
    wxJSONValue pack_txt;
    myStr = wxEmptyString;
    int idChoice = pPointStyle1->GetSelection();

    pack = 1;

    if (idChoice < 11) {
        pack = idChoice + 1;
        pcs_last = int(db_quantity % pack);
        pack_pcs = int((db_quantity - pcs_last)/pack);
    } else {
        if (idChoice == 11) {
            pcs_last = int(db_quantity % 25);
            pack = int((db_quantity - pcs_last)/25);
            pack_pcs = 25;
        }
        if (idChoice == 12) {
            pcs_last = int(db_quantity % 30);
            pack = int((db_quantity - pcs_last)/30);
            pack_pcs = 30;
        }
        if (idChoice == 13) {
            pcs_last = int(db_quantity % 50);
            pack = int((db_quantity - pcs_last)/50);
            pack_pcs = 50;
        }
        if (idChoice == 14) {
            pcs_last = int(db_quantity % 100);
            pack = int((db_quantity - pcs_last)/100);
            pack_pcs = 100;
        }

    }

    printf("On Choice PointStyle Selected index %d ", idChoice);
    printf(wxString::Format("%s \n", event.GetString()));

    std::ostringstream packets_full_ss("");
    std::ostringstream packet_pcs_ss("");
    std::ostringstream packet_cur_ss("");
    std::ostringstream pcs_last_ss("");


//Every time when select component we put numer current pack to 1
      pack_cur = 1;

      packets_full_ss << pack;
      packet_pcs_ss << pack_pcs;
      pcs_last_ss << pcs_last;
      packet_cur_ss << pack_cur;

      pack_txt[_T("Decl")] = _(packets_full_ss.str());
      wxString pack_msg_id(_T("OCPN_DBP_PACK"));
      g_pi_manager->SendJSONMessageToAllPlugins(pack_msg_id, pack_txt);


      pack_txt[_T("Decl")] = _(packet_pcs_ss.str());
      wxString pack_psc_msg_id(_T("OCPN_DBP_PACK_PCS"));
      g_pi_manager->SendJSONMessageToAllPlugins(pack_psc_msg_id, pack_txt);

      pack_txt[_T("Decl")] = _(packet_cur_ss.str());
      wxString pack_cur_msg_id(_T("OCPN_DBP_PACK_CUR"));
      g_pi_manager->SendJSONMessageToAllPlugins(pack_cur_msg_id, pack_txt);

      pack_txt[_T("Decl")] = _(pcs_last_ss.str());
      wxString pcs_last_msg_id(_T("OCPN_DBP_PCS_LAST"));
      g_pi_manager->SendJSONMessageToAllPlugins(pcs_last_msg_id, pack_txt);

      std::cout << "Packet select: " << packets_full_ss.str()  << " Per pocket : " << packet_pcs_ss.str() << " Pcs last : " << pcs_last_ss.str() << std::endl;


// Correct right list
    wxLabelPointListNode *node = m_pLabel->pLabelPointList->GetFirst();

    while( node ) {

        if ( node ) {
            LabelPoint *pLP_upd = node->GetData();


            if (pLP_upd->m_bPtIsSelected) {
                string cur_label_str(pLP_upd->GetCode().mb_str());
                std::cout << "Point List: " << cur_label_str << " Packets_full: " << packets_full_ss.str()  << " Per pocket : " << packet_pcs_ss.str() << " Pcs last : " << pcs_last_ss.str() << std::endl;
                pLP_upd->SetPack(packets_full_ss.str());
                pLP_upd->SetPcs(packet_pcs_ss.str());
                pLP_upd->SetLast(pcs_last_ss.str());

            }

       }

        node = node->GetNext();
    }


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
    long item1 = -1;


//  Aria of visualibylity not continue to try area
//    std::ostringstream packets_full_ss("");
//    std::ostringstream packet_pcs_ss("");
//    std::ostringstream pcs_last_ss("");

//    packets_full_ss << pack;
//    packet_pcs_ss << pack_pcs;
//    pcs_last_ss << pcs_last;



  try {
    mysqlcppapi::Connection con;

    con.set_Host(dbHost);
    con.set_User(dbUser);
    con.set_Password(dbPassword);
    con.connect();
    con.select_database(dbName);


    
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

    ps57CtlListCtrl1->InsertColumn(0, _("ID"), wxLIST_FORMAT_LEFT, 100);
    ps57CtlListCtrl1->InsertColumn(1, _("Name"), wxLIST_FORMAT_LEFT, 450);
    ps57CtlListCtrl1->InsertColumn(2, _("Category"), wxLIST_FORMAT_LEFT, 100);
    ps57CtlListCtrl1->InsertColumn(3, _("Code"), wxLIST_FORMAT_LEFT, 190);
//    ps57CtlListCtrl1->InsertColumn(4, _("Composition"));
//    ps57CtlListCtrl1->InsertColumn(5, _("Description"));
//    ps57CtlListCtrl1->InsertColumn(6, _("Image"));
    ps57CtlListCtrl1->InsertColumn(4, _("Measure unit"), wxLIST_FORMAT_LEFT, 150);
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

    std::ostringstream packets_full_ss("");
    std::ostringstream packet_pcs_ss("");
    std::ostringstream pcs_last_ss("");


      packets_full_ss << pack;
      packet_pcs_ss << pack_pcs;
      pcs_last_ss << pcs_last;

      
    std::cout << "Check Pack: " << packets_full_ss.str() << " pcs: " << packet_pcs_ss.str() << " last: " << pcs_last_ss.str() << std::endl;


      LabelPoint *pLP_src = new LabelPoint( g_default_wp_icon, _(row[0]) ,_(row[1]), dbClientName, _(packets_full_ss.str()), _(packet_pcs_ss.str()), _(pcs_last_ss.str()), _(row[3]), _(row[6]), GPX_EMPTY_STRING );
//      pSelect->AddSelectableLabelPoint( pLP_src );
      m_pLabel->AddPoint(pLP_src);

//      item1 = ps57CtlListCtrl1->GetNextItem(item1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
//      if( item1 != -1 ) {
////          LabelPoint *lp = m_pLabel->pLabelPointList->Item(ps57CtlListCtrl1->GetItemData(index))->GetData();
//          LabelPoint *lp = (LabelPoint *) ps57CtlListCtrl1->GetItemData(item1);
//          if ( !lp ) {
//              std::cerr << "Error : index of LabelPoint" <<  std::endl;
//          } else {
//             pSelect->AddSelectableLabelPoint( lp );

////      Label *temp_label = new Label();
//  //    pLabelList->Append( temp_label );
////      temp_label->AddPoint( pLP_src );
////      temp_label->AddPoint( lp );
//             m_pLabel->AddPoint( lp );
//          }
//      }
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

    con.set_Host(dbHost);
    con.set_User(dbUser);
    con.set_Password(dbPassword);
    con.connect();
    con.select_database(dbName);

    mysqlcppapi::Query query = con.create_Query();
    // This creates a query object that is bound to con.

    std::string curSql("select id, name, date_creation, product, client_id, creator_id  from projects_project ");
    curSql += idClient;
    query <<  curSql;
    // You can write to the query object like you would any other ostrem

//    std::cout << "Query: " << query.preview() << std::endl;


    mysqlcppapi::Result_Store res = query.store();
    // Query::store() executes the query and returns the results

    ps57CtlListCtrl->InsertColumn(0, _("ID"), wxLIST_FORMAT_LEFT, 100);
    ps57CtlListCtrl->InsertColumn(1, _("Name"), wxLIST_FORMAT_LEFT, 450);
    ps57CtlListCtrl->InsertColumn(2, _("Date creation"), wxLIST_FORMAT_LEFT, 220);
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
      dbClientName = _(row[1]);
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

void MyFrame1::DoLabel( wxCommandEvent& event )
{
    if( NULL == g_printData ) {
        g_printData = new wxPrintData;
        g_printData->SetOrientation( wxLANDSCAPE );
        g_pageSetupData = new wxPageSetupDialogData;
    }

    wxPrintDialogData printDialogData( *g_printData );
    printDialogData.EnablePageNumbers( false );

    wxPrinter printer( &printDialogData );

    MyPrintout printout( _("Label Print") );

    if( !printer.Print( this, &printout, true ) ) {
        if( wxPrinter::GetLastError() == wxPRINTER_ERROR ) OCPNMessageBox(NULL,
            _("There was a problem printing. \nPerhaps your current printer is not set correctly?"),
            _T("OpenCPN"), wxOK );
    } else {
        ( *g_printData ) = printer.GetPrintDialogData().GetPrintData();
    }

    Hide();
    event.Skip();

}

void MyFrame1::OnBtnPrintClick(wxCommandEvent& event)
{
    if (pLabelPrintSelection == NULL)
        pLabelPrintSelection = new LabelPrintSelection( this, m_pLabel );



//    if( !pLabelPrintSelection->IsShown() ) pLabelPrintSelection->ShowModal();
//    if( !pLabelPrintSelection->IsShown() )


// Stop show dialog. We are select all. Not need mass click
//    pLabelPrintSelection->Show();

//We push button automatical
    pLabelPrintSelection->OnLabelpropOkClick(event);



//        delete pLabelPrintSelection;

//    pLabelPrintSelection = NULL;

//    Hide();


//    event.Skip();
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

void MyFrame1::OnLabelListClick( wxListEvent& event )
{
    long itemno = 0;
    long curno = 0;
    m_nSelected = 0;
    int selected_no;
    long sel_no;
    const wxListItem &i = event.GetItem();
    i.GetText().ToLong( &itemno );
    sel_no = itemno;
    selected_no = itemno;

    m_pLabel->ClearHighlights();
    wxLabelPointListNode *node = m_pLabel->pLabelPointList->GetFirst();
    while( node && itemno-- ) {
        node = node->GetNext();
        printf("Node %d\n", itemno);
//    }
        if ( node ) {
            LabelPoint *plp = node->GetData();
            if ( plp ) {
                plp->GetNo().ToLong( &curno );
                if (curno == sel_no) {
                    printf("Itemno %d\n", curno);
                    plp->m_bPtIsSelected = true;
                    printf("bPtIsSelected %d\n", sel_no);
                    if( !( m_pLabel->m_bIsInLayer ) && !( m_pLabel->m_bRtIsActive ) ) {
                        m_nSelected = selected_no + 1;
                    }
                }
            }
        }
    }
}

void MyFrame1::InitializeList(wxListCtrl *ps57CtlListCtrl1)
{
    if( NULL == m_pLabel ) return;

    if( !m_pLabel->m_bIsTrack ) {
        wxLabelPointListNode *pnode = m_pLabel->pLabelPointList->GetFirst();
        int in = 0;
        while( pnode ) {
            ps57CtlListCtrl1->InsertItem( in, _T(""), 0 );
            ps57CtlListCtrl1->SetItemPtrData( in, (wxUIntPtr)pnode->GetData() );
            in++;

            pnode = pnode->GetNext();
        }
    }

}
