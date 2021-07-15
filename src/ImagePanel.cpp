#include <wx/wx.h>
#include "ImagePanel.hpp"

ImagePanel::ImagePanel(wxWindow *parent, wxString path, wxBitmapType format) : wxPanel(parent), img(path), bitmap(img)
{
  cur_path = path;
  cur_format = format;
  img.LoadFile(path, format);

  // get the image size
//  width = img.GetWidth();
//  height = img.GetHeight();

  width = 100;
  height = 100;


  // set the size of the panel accordingly
//  SetSize(width, height);

  Connect(wxEVT_PAINT, wxPaintEventHandler(ImagePanel::OnPaint));
  Connect(wxEVT_SIZE, wxSizeEventHandler(ImagePanel::OnSize));
}

void ImagePanel::OnPaint(wxPaintEvent& event)
{
  wxPaintDC dc(this);
  render(dc);
}

void ImagePanel::paintNow()
{
  wxClientDC dc(this);
  render(dc);
}

void ImagePanel::render(wxDC& dc)
{
  int neww, newh;
  dc.GetSize( &neww, &newh );
//  neww = 100;
//  newh = 100;

  if( neww != width || newh != height )
  {
    bitmap = wxBitmap( img.Scale( neww, newh) );
    width = neww;
    height = newh;
    dc.DrawBitmap(bitmap, 0, 0, true);
  } else {
    img.LoadFile(cur_path, cur_format);
    bitmap = wxBitmap( img.Scale( neww, newh) );
    dc.DrawBitmap(bitmap, 0, 0, true);
  }
}

void ImagePanel::OnSize(wxSizeEvent& event)
{
  Refresh();
  event.Skip();
}
