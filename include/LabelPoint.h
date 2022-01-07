/***************************************************************************
 *
 * Project:  OpenCPN
 *
 ***************************************************************************
 *   Copyright (C) 2013 by David S. Register                               *
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

#ifndef __LABELPOINT_H__
#define __LABELPOINT_H__

#include <wx/string.h>
#include <wx/datetime.h>
#include <wx/gdicmn.h>
#include <wx/gauge.h>
#include "Hyperlink.h"
#include "gpxdocument.h"

class ocpnDC;
class wxDC;

class LabelPoint
{
public:
      LabelPoint(const wxString& icon_ident, const wxString& no, const wxString& name, const wxString& cname, const wxString& pack, const wxString& pcs, const wxString& last, const wxString& code, const wxString& image, const wxString& order, const wxString& date, const wxString &pGUID = GPX_EMPTY_STRING, bool bAddToList = true);
      LabelPoint( LabelPoint* orig );
      LabelPoint();
      ~LabelPoint(void);
      void Draw(ocpnDC& dc, wxPoint *rpn = NULL);
      void ReLoadIcon(void);

      wxDateTime GetCreateTime(void);
      void SetCreateTime( wxDateTime dt );
      
      void SetPosition(double lat, double lon);
      void CalculateDCRect(wxDC& dc, wxRect *prect);

      bool IsSame(LabelPoint *pOtherRP);        // toh, 2009.02.11
      bool IsVisible() { return m_bIsVisible; }
      bool IsListed() { return m_bIsListed; }
      bool IsNameShown() { return m_bShowName; }
      void SetVisible(bool viz = true){ m_bIsVisible = viz; }
      void SetListed(bool viz = true){ m_bIsListed = viz; }
      void SetNameShown(bool viz = true) { m_bShowName = viz; }
      wxString GetNo(void){ return m_MarkNo; }
      wxString GetName(void){ return m_MarkName; }
      wxString GetCode(void){ return m_MarkCode; }
      wxString GetImage(void){ return m_MarkImage; }
      wxString GetDescription(void) { return m_MarkDescription; }
      wxString GetCName(void){ return m_MarkCName; }
      wxString GetPack(void){ return m_MarkPack; }
      wxString GetPcs(void){ return m_MarkPcs; }
      wxString GetLast(void){ return m_MarkLast; }
      wxString GetOrder(void){ return m_MarkOrder; }
      wxString GetDate(void){ return m_MarkDate; }
      
      wxString GetIconName(void){ return m_IconName; }
      wxBitmap *GetIconBitmap(){ return m_pbmIcon; }
      void SetIconName( wxString name ){ m_IconName = name; }
      
      void *GetSelectNode(void) { return m_SelectNode; }
      void SetSelectNode(void* node) { m_SelectNode = node; }

      void *GetManagerListNode(void) { return m_ManagerNode; }
      void SetManagerListNode(void* node) { m_ManagerNode = node; }
      
      void SetNo(const wxString & no);
      void SetName(const wxString & name);
      void SetCode(const wxString & code);
      void SetImage(const wxString & image);
      void SetCName(const wxString & cname);
      void SetPack(const wxString & pack);
      void SetPcs(const wxString & pcs);
      void SetLast(const wxString & last);
      void SetOrder(const wxString & code);
      void SetDate(const wxString & code);
      void CalculateNoExtents(void);
      void CalculateNameExtents(void);
      void CalculateCodeExtents(void);
      void CalculateImageExtents(void);
      void CalculateCNameExtents(void);
      void CalculatePackExtents(void);
      void CalculatePcsExtents(void);
      void CalculateLastExtents(void);
      void CalculateOrderExtents(void);
      void CalculateDateExtents(void);

      bool             m_bPtIsSelected;
      bool             m_bPtIsNotPrinted;  // For deleted item from lists in screen after print all label for every pockets of that item

      bool              m_bIsVisible;           // true if should be drawn, false if invisible
      bool              m_bIsListed;
      bool              m_bIsActive;
      wxString          m_MarkDescription;
      wxString          m_GUID;

      wxFont            *m_pMarkFont;
      wxColour          m_FontColor;

      wxSize            m_NoExtents;
      wxSize            m_NameExtents;
      wxSize            m_CodeExtents;
      wxSize            m_ImageExtents;
      wxSize            m_CNameExtents;
      wxSize            m_PackExtents;
      wxSize            m_PcsExtents;
      wxSize            m_LastExtents;
      wxSize            m_OrderExtents;
      wxSize            m_DateExtents;
      wxSize            m_PrintCounterExtents;  // Calculate have long the number of prints label


      bool              m_bDynamicName;
      bool              m_bShowName;
      wxRect            CurrentRect_in_DC;
      int               m_NameLocationOffsetX;
      int               m_NameLocationOffsetY;
      wxString          m_timestring;
      int               m_GPXTrkSegNo;
      bool              m_bIsInLayer;
      int               m_LayerID;
      int               m_PrintCounter;  // Haw many labels print for that item


      HyperlinkList     *m_HyperlinkList;
      bool              m_btemp;

#ifdef ocpnUSE_GL
      void DrawGL( ViewPort &vp, OCPNRegion &region );
      unsigned int m_iTextTexture;
      int m_iTextTextureWidth, m_iTextTextureHeight;

      LLBBox m_wpBBox;
      double m_wpBBox_chart_scale, m_wpBBox_rotation;

      static bool s_bUpdateWaypointsDisplayList;
#endif

      
private:
      wxString          m_MarkNo;
      wxString          m_MarkName;
      wxString          m_MarkCode;
      wxString          m_MarkImage;
      wxString          m_MarkCName;
      wxString          m_MarkPack;
      wxString          m_MarkPcs;
      wxString          m_MarkLast;
      wxString          m_MarkOrder;
      wxString          m_MarkDate;
      wxString          m_MarkPrintCounter;   // text view of print counter (have many time we push button print)
      wxDateTime        m_CreateTimeX;
      wxBitmap          *m_pbmIcon;
      wxString          m_IconName;
      
      void              *m_SelectNode;
      void              *m_ManagerNode;
      
};

WX_DECLARE_LIST(LabelPoint, LabelPointList);// establish class as list member

#endif
