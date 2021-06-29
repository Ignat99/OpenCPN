#include <wx/wx.h>
#include <wx/listbook.h>
#include <wx/listctrl.h>
#include <iostream>
#include <iomanip>
#include <string>


enum {
ID_1RADARDISTUNIT = 50000,
ID_1TEXTCTRL = 50001,
ID_1CHECKLISTBOX = 50002,
ID_1SELECTLIST = 50003,
ID_1CLEARLIST = 50004,
xID_1OK = 50003
};

class MyFrame1 : public wxFrame
{
public:
    MyFrame1( wxFrame *frame, const wxString& title, const wxPoint& pos, const wxSize& size, long style );
    ~MyFrame1();

protected:
      int m_whatever;

public:
      wxListCtrl    *ps57CtlListCtrl;
      wxListCtrl    *ps57ListCtrl1;
      size_t        m_pageDisplay;
      wxSize        m_small_button_size;
      wxNotebook    *m_pNotebook;
      wxBoxSizer    *vectorPanel;
      wxScrolledWindow    *ps57Ctl1;
//      wxWindow    *ps57Ctl1;
      wxSizerFlags inputFlags;
      wxSizerFlags labelFlags;
      wxChoice    *pDispCat;
      wxChoice    *pPointStyle;
      wxChoice    *pPointStyle1;
      wxChoice    *pBoundStyle;
      wxChoice    *p24Color;
      wxTextCtrl    *m_SafetyCtl;
      wxTextCtrl    *m_DeepCtl;
      wxButton      *itemButtonSelectList;
      wxButton      *itemButtonClearList;
      std::string        idClient;
      std::string      idCreator;

      void GetProjects(wxListCtrl *ps57CtlListBoxStrings);
      void GetComponents(wxListCtrl *ps57CtlListBoxStrings);

private:
    void OnButton1(wxCommandEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnMove(wxMoveEvent& event);
    void OnActivateApp( wxActivateEvent& event );
    void OnMaximize(wxMaximizeEvent& event);
    void OnEraseBackgroun(wxEraseEvent& event);
    void OnCoSelected( wxListEvent &event );
    void OnPrSelected( wxListEvent &event );
    void OnPrChoice( wxCommandEvent &event );
    void OnPrChoicePointStyle( wxCommandEvent &event );
    void OnBoundStyle( wxCommandEvent &event );
    void On24Color( wxCommandEvent &event );
    void OnPointStyle1( wxCommandEvent &event );
    void OnSafetyCtl( wxCommandEvent &event );
    void OnDeepCtl( wxCommandEvent &event );


    DECLARE_EVENT_TABLE()
};
