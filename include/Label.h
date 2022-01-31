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

#ifndef __LABEL_H__
#define __LABEL_H__

#include <wx/object.h>
#include <wx/list.h>

#include "ocpn_types.h"
#include "LabelPoint.h"

#define STYLE_UNDEFINED -1

#define LABEL_DEFAULT_SPEED 5.0
#define RTE_TIME_DISP_UTC _T("UTC")
#define RTE_TIME_DISP_PC _T("PC")
#define RTE_TIME_DISP_LOCAL _T("LOCAL")
#define RTE_UNDEF_DEPARTURE wxInvalidDateTime

class ocpnDC;

class Label : public wxObject
{
public:
      Label(void);
      ~Label(void);

      void AddPoint(LabelPoint *pNewPoint,
                    bool b_rename_in_sequence = true,
                    bool b_deferBoxCalc = false,
                    bool b_isLoading = false);

      void AddTentativePoint(const wxString& GUID);
      LabelPoint *GetPoint(int nPoint);
      LabelPoint *GetPoint ( const wxString &guid );
      int GetIndexOf(LabelPoint *prp);
      LabelPoint *InsertPointBefore(LabelPoint *pRP, double rlat, double rlon, bool bRenamePoints = false);
      void DrawPointWhich(ocpnDC& dc, int iPoint, wxPoint *rpn);
//      void DrawSegment(ocpnDC& dc, wxPoint *rp1, wxPoint *rp2, ViewPort &VP, bool bdraw_arrow);
      virtual void Draw(ocpnDC& dc, ViewPort &pVP);
      virtual void DrawGL( ViewPort &VP, OCPNRegion &region );
      LabelPoint *GetLastPoint();
      void DeletePoint(LabelPoint *rp, bool bRenamePoints = false);
      void RemovePoint(LabelPoint *rp, bool bRenamePoints = false);
      void DeSelectLabel();
      void FinalizeForRendering();
      void UpdateSegmentDistances(double planspeed = -1.0);
      void CalculateDCRect(wxDC& dc_label, wxRect *prect, ViewPort &VP);
      int GetnPoints(void){ return m_nPoints; }
      wxBoundingBox GetBBox();
      void SetnPoints(void){ m_nPoints = pLabelPointList->GetCount(); }
      void SetHiLite( int width ) {m_hiliteWidth = width; }
      void Reverse(bool bRenamePoints = false);
      void RebuildGUIDList(void);
      void RenameLabelPoints();
      void ReloadLabelPointIcons();
      wxString GetNewMarkSequenced(void);
      void AssembleLabel();
      bool IsEqualTo(Label *ptargetlabel);
      void CloneLabel(Label *psourcelabel, int start_nPoint, int end_nPoint, const wxString & suffix);
      void CloneTrack(Label *psourcelabel, int start_nPoint, int end_nPoint, const wxString & suffix);
      void CloneAddedTrackPoint(LabelPoint *ptargetpoint, LabelPoint *psourcepoint);
      void CloneAddedLabelPoint(LabelPoint *ptargetpoint, LabelPoint *psourcepoint);
      void ClearHighlights(void);
      void RenderSegment(ocpnDC& dc, int xa, int ya, int xb, int yb, ViewPort &VP, bool bdraw_arrow, int hilite_width = 0);
      void RenderSegmentArrowsGL( int xa, int ya, int xb, int yb, ViewPort &VP);

      bool CrossesIDL(){ return m_bcrosses_idl; }
      void SetVisible(bool visible = true, bool includeWpts = true);
      void SetListed(bool visible = true);
      bool IsVisible() { return m_bVisible; }
      bool IsListed() { return m_bListed; }
      bool IsActive() { return m_bRtIsActive; }
      bool IsSelected() { return m_bRtIsSelected; }
      bool IsTrack(){ return m_bIsTrack; }

//      double GetLabelArrivalRadius(void){ return m_ArrivalRadius;}
//      void SetLabelArrivalRadius(double radius){m_ArrivalRadius = radius;}

      int         m_ConfigLabelNum;
      bool        m_bRtIsSelected;
      bool        m_bRtIsActive;
      LabelPoint  *m_pLabelActivePoint;
      bool        m_bIsBeingCreated;
      bool        m_bIsBeingEdited;
      double      m_label_length;
      double      m_label_time;
      wxString    m_LabelNameString;
      wxString    m_LabelStartString;
      wxString    m_LabelEndString;
      wxString    m_LabelDescription;
      bool        m_bIsTrack;             //TODO should use class type instead
      LabelPoint  *m_pLastAddedPoint;
      bool        m_bDeleteOnArrival;
      wxString    m_GUID;
      bool        m_bIsInLayer;
      int         m_LayerID;
      int         m_width;
      int         m_style;
      int         m_lastMousePointIndex;
      bool        m_NextLegGreatCircle;
      double      m_PlannedSpeed;
      wxDateTime  m_PlannedDeparture;
      wxString    m_TimeDisplayFormat;
      HyperlinkList     *m_HyperlinkList;

      wxArrayString      LabelPointGUIDList;
      LabelPointList     *pLabelPointList;

      wxRect      active_pt_rect;
      wxString    m_Colour;
      bool        m_btemp;
      int         m_hiliteWidth;

private:
      bool m_bNeedsUpdateBBox;
      wxBoundingBox     RBBox;

      bool        CalculateCrossesIDL();
      int         m_nPoints;
      int         m_nm_sequence;
      bool        m_bVisible; // should this label be drawn?
      bool        m_bListed;
      double      m_ArrivalRadius;
      bool        m_bcrosses_idl;
};

WX_DECLARE_LIST(Label, LabelList); // establish class Label as list member

#endif
