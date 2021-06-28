#include "myframe1.h"

#include <mysqlcppapi/mysqlcppapi.h>
#include <iostream>
#include <iomanip>


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


    m_whatever = 1;
    m_pageDisplay = -1;
    int border_size = 4;
    int group_item_spacing = 2;
    int font_size_y, font_descent, font_lead;
    dc->GetTextExtent( _T("0"), NULL, &font_size_y, &font_descent, &font_lead );
    m_small_button_size = wxSize( -1, (int) ( 1.4 * (font_size_y + font_descent + font_lead) ) );

        wxScrolledWindow* ps57Ctl1 = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(1000, 600), wxHSCROLL | wxVSCROLL | wxTAB_TRAVERSAL);

//        wxWindow* ps57Ctl = this;





//        wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
        vectorPanel = new wxBoxSizer(wxHORIZONTAL);
//        vectorPanel = new wxBoxSizer(wxVERTICAL);

//        ps57Ctl1->SetSizer(vectorPanel);

        m_pNotebook = new wxNotebook (ps57Ctl1, wxID_ANY, wxDefaultPosition, wxSize(880, 580), wxNB_TOP);

        wxPanel *pPanel = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxSize(850, 550), wxNO_BORDER | wxTAB_TRAVERSAL, _("Bascula") );

//        wxScrolledWindow* ps57Ctl1 = 
        m_pNotebook->AddPage(pPanel, _("Display") );


//        vectorPanel->Add( m_pNotebook, 1, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL | wxEXPAND, 5 );
//        vectorPanel->Add( pPanel, 0, wxEXPAND | wxALL, 0 );


//        topSizer->Add(vectorPanel , 1, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL | wxEXPAND, 5 );



//        topSizer->Add( m_pNotebook, 1, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL | wxEXPAND, 5 );

//        m_pNotebook->SetSizer(vectorPanel);

//        Centre();



    wxFlexGridSizer* optionsColumn = new wxFlexGridSizer(2);
    optionsColumn->SetHGap(border_size);
    optionsColumn->AddGrowableCol( 0, 2 );
    optionsColumn->AddGrowableCol( 1, 3 );
    vectorPanel->Add( optionsColumn, 3, wxALL | wxEXPAND, border_size );
//    topSizer->Add( optionsColumn, 3, wxALL | wxEXPAND, border_size );

    // spacer
    optionsColumn->Add( new wxStaticText(pPanel, wxID_ANY, _T("A")) );
    optionsColumn->Add( new wxStaticText(pPanel, wxID_ANY, _T("B")) );


    // dislay category
    optionsColumn->Add( new wxStaticText(pPanel, wxID_ANY, _("Data creation")), labelFlags );
    wxString pDispCatStrings[] = { _("1 day"), _("2 day"), _("3 day"), _("Week") };
    pDispCat = new wxChoice( pPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 4, pDispCatStrings );
    optionsColumn->Add( pDispCat, 0, wxALL, 2 );

    pDispCat->Connect( wxEVT_COMMAND_CHOICE_SELECTED,  wxCommandEventHandler(MyFrame1::OnPrChoice), NULL, this );


    // spacer
    optionsColumn->Add( new wxStaticText(pPanel, wxID_ANY, _T("C")) );
    optionsColumn->Add( new wxStaticText(pPanel, wxID_ANY, _T("D")) );


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




    // 2nd column, Display Category / Mariner's Standard options
    wxBoxSizer* dispSizer = new wxBoxSizer( wxVERTICAL );
    vectorPanel->Add( dispSizer, 2, wxALL | wxEXPAND, border_size );

    wxStaticBox* marinersBox = new wxStaticBox( pPanel, wxID_ANY, _("Projects") );
    wxStaticBoxSizer* marinersSizer = new wxStaticBoxSizer( marinersBox, wxVERTICAL );
    dispSizer->Add( marinersSizer, 1, wxALL | wxEXPAND, border_size );


// Products

    ps57CtlListCtrl = new wxListCtrl( pPanel, ID_1CHECKLISTBOX, wxDefaultPosition, wxSize( 350, 250 ),
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


    wxBoxSizer* btnRow = new wxBoxSizer( wxHORIZONTAL );
    itemButtonSelectList = new wxButton( pPanel, ID_1SELECTLIST, _("Select All") );
    btnRow->Add( itemButtonSelectList, 1, wxALL | wxEXPAND, group_item_spacing );
    itemButtonClearList = new wxButton( pPanel, ID_1CLEARLIST, _("Clear All") );
    btnRow->Add( itemButtonClearList, 1, wxALL | wxEXPAND, group_item_spacing );
    marinersSizer->Add( btnRow );
//    vectorPanel->Add( btnRow );


// Components

    ps57ListCtrl1 = new wxListCtrl( pPanel, ID_1RADARDISTUNIT, wxDefaultPosition,
                                        wxSize( 350, 150 ), wxLC_REPORT );
    GetComponents(ps57ListCtrl1);
    marinersSizer->Add( ps57ListCtrl1, 1, wxALL | wxEXPAND, group_item_spacing );
//    vectorPanel->Add( ps57ListCtrl1, 1, wxALL | wxEXPAND, group_item_spacing );


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

void MyFrame1::OnPrSelected( wxListEvent &event )
{
    long clicked_index = event.m_itemIndex;

    printf("On Project Selected\n");
//    Route  =  Item( ps57CtlListCtrl->GetItemData( clicked_index ) )->GetData();
     unsigned int item = ps57CtlListCtrl->GetItemData( clicked_index );

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

    printf("On ID user Selected %d, ", event.GetId());
    printf(wxString::Format("* %s, ", event.GetString()));
    printf(wxString::Format("* %s \n", m_textCtrlInfo));

}

void MyFrame1::OnDeepCtl( wxCommandEvent& event )
{
//    wxString myStr;
//    myStr = wxEmptyString;
    wxString  m_textCtrlInfo = m_DeepCtl->GetValue();

    printf("On ID user Selected %d, ", event.GetId());
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

    query << "select id, name, category, code, composition, description, image, measure_unit, position, price, price_insystem, product, weight, is_active, is_reportable, is_saleable  from components_component ORDER BY id DESC LIMIT 10";
    // You can write to the query object like you would any other ostrem

    mysqlcppapi::Result_Store res = query.store();
    // Query::store() executes the query and returns the results

    ps57CtlListCtrl1->InsertColumn(0, _("ID"));
    ps57CtlListCtrl1->InsertColumn(1, _("Name"));
    ps57CtlListCtrl1->InsertColumn(2, _("Category"));
    ps57CtlListCtrl1->InsertColumn(3, _("Code"));
    ps57CtlListCtrl1->InsertColumn(4, _("Composition"));
    ps57CtlListCtrl1->InsertColumn(5, _("Description"));
    ps57CtlListCtrl1->InsertColumn(6, _("Image"));
    ps57CtlListCtrl1->InsertColumn(7, _("Measure unit"));
    ps57CtlListCtrl1->InsertColumn(8, _("Position"));
    ps57CtlListCtrl1->InsertColumn(9, _("Price"));
    ps57CtlListCtrl1->InsertColumn(10, _("Price insystem"));
    ps57CtlListCtrl1->InsertColumn(11, _("Product"));
    ps57CtlListCtrl1->InsertColumn(12, _("Weight"));
    ps57CtlListCtrl1->InsertColumn(13, _("Is Active"));
    ps57CtlListCtrl1->InsertColumn(14, _("Is Reportable"));
    ps57CtlListCtrl1->InsertColumn(15, _("Is Saleable"));


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
      ps57CtlListCtrl1->SetItem(index, 4, _(row[4]), -1);
      ps57CtlListCtrl1->SetItem(index, 5, _(row[5]), -1);
      ps57CtlListCtrl1->SetItem(index, 6, _(row[6]), -1);
      ps57CtlListCtrl1->SetItem(index, 7, _(row[7]), -1);
      ps57CtlListCtrl1->SetItem(index, 8, _(row[8]), -1);
      ps57CtlListCtrl1->SetItem(index, 9, _(row[9]), -1);
      ps57CtlListCtrl1->SetItem(index, 10, _(row[10]), -1);
      ps57CtlListCtrl1->SetItem(index, 11, _(row[11]), -1);
      ps57CtlListCtrl1->SetItem(index, 12, _(row[12]), -1);
      ps57CtlListCtrl1->SetItem(index, 13, _(row[13]), -1);
      ps57CtlListCtrl1->SetItem(index, 14, _(row[14]), -1);
      ps57CtlListCtrl1->SetItem(index, 15, _(row[15]), -1);

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

    query << "select id, name, date_creation, product, client_id, creator_id  from projects_project ORDER BY date_creation DESC LIMIT 10";
    // You can write to the query object like you would any other ostrem

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
