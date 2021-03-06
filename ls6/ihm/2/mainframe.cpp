#include <stdio.h>
#include <stdlib.h>
#include <wx/wx.h>
#include <wx/accel.h>

#include "dialogs.h"
#include "mainframe.h"


BEGIN_EVENT_TABLE(CMainFrame, wxFrame)
	EVT_MENU(M_NOUVEAU_FICHIER, CMainFrame::OnNew)
	EVT_MENU(M_QUITTER, CMainFrame::OnQuit)
	EVT_MENU(M_OUVRIR, CMainFrame::OnOpen)
	EVT_MENU(M_SAUVEGARDER, CMainFrame::OnSave)
	EVT_MENU(M_EPAISSEUR_TRAIT, CMainFrame::OnEpaisseurTrait)
	EVT_MENU(M_COULEUR, CMainFrame::OnColor)
	EVT_MENU(M_GESTION_TRIANGLES, CMainFrame::OnGestionTriangles)
	EVT_MENU(M_TOOLBAR, CMainFrame::OnToolBar)
	EVT_MENU(M_VERSION, CMainFrame::OnVersion)
END_EVENT_TABLE()


CMainFrame::CMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame((wxFrame *)NULL, -1, title, pos, size) 
{
} //constructor

void CMainFrame::CreateMyToolBar()
{
	m_toolbar = CreateToolBar(wxNO_BORDER | wxTB_HORIZONTAL | wxTB_TEXT, TOOLBAR_TOOLS);
	wxBitmap toolBarBitmaps[4];

	toolBarBitmaps[0] = wxBitmap(wxT("img/new.bmp"),wxBITMAP_TYPE_BMP);
	toolBarBitmaps[1] = wxBitmap(wxT("img/open.bmp"),wxBITMAP_TYPE_BMP);
	toolBarBitmaps[2] = wxBitmap(wxT("img/save.bmp"),wxBITMAP_TYPE_BMP);
	toolBarBitmaps[3] = wxBitmap(wxT("img/draw.bmp"),wxBITMAP_TYPE_BMP);

	m_toolbar->SetToolBitmapSize(wxSize(toolBarBitmaps[0].GetWidth(), toolBarBitmaps[0].GetHeight()));
	m_toolbar->AddTool(M_NOUVEAU_FICHIER, wxT("Nouveau"), toolBarBitmaps[0]);
	m_toolbar->AddTool(M_OUVRIR, wxT("Ouvrir"), toolBarBitmaps[1]);
	m_toolbar->AddTool(M_SAUVEGARDER, wxT("Sauvegarder"), toolBarBitmaps[2]);
	m_toolbar->AddSeparator();
	m_toolbar->AddTool(M_GESTION_TRIANGLES, wxT("Gestion des triangles"), toolBarBitmaps[3], wxT("Gestion des triangles"));

	m_toolbar->Realize();

	SetToolBar(m_toolbar);
}
void CMainFrame::OnNew(wxCommandEvent& event)
{
}
void CMainFrame::OnQuit(wxCommandEvent& event)
{
	Close(TRUE);
}
void CMainFrame::OnOpen(wxCommandEvent& event)
{
}
void CMainFrame::OnSave(wxCommandEvent& event)
{
}
void CMainFrame::OnEpaisseurTrait(wxCommandEvent& event)
{
	EpaisseurDialog vdlg(this, -1, wxT("Epaisseur du trait"));
	vdlg.ShowModal();
}
void CMainFrame::OnColor(wxCommandEvent& event)
{
	ColorDialog vdlg(this, -1, wxT("Couleur"));
	vdlg.ShowModal();
}
void CMainFrame::OnGestionTriangles(wxCommandEvent& event)
{
	TriangleDialog vdlg(this, -1, wxT("Gestion des triangles"));
	vdlg.liste_triangles->Clear();
	vdlg.liste_triangles->Append(wxT("Triangle 1"));
	vdlg.liste_triangles->Append(wxT("Triangle 2"));
	vdlg.liste_triangles->SetSelection(1);
	vdlg.ShowModal();
}
void CMainFrame::OnToolBar(wxCommandEvent& event)
{
	// On masque / affiche la barre d'outils
	if(m_toolbar->IsShownOnScreen())
		m_toolbar->Hide();
	else
		m_toolbar->Show(true);
}
void CMainFrame::OnVersion(wxCommandEvent& event)
{
	VersionDialog vdlg(this, -1, wxT("Version"));
	vdlg.ShowModal();
}
