#ifndef __IMAGE_PANEL_HPP__
#define __IMAGE_PANEL_HPP__

#include <wx/wx.h>

class ImagePanel : public wxPanel
{
  // a panel with just an image on it - use for displaying QR code
  public:
    ImagePanel(wxWindow *parent, wxString path, wxBitmapType format);
    void OnPaint(wxPaintEvent& event);
    void paintNow();
    void OnSize(wxSizeEvent& event);
    void render(wxDC& dc);

  private:
    wxImage img;
    wxBitmap bitmap;
    wxBitmapType cur_format;
    wxString cur_path;
    int width;
    int height;

};

#endif