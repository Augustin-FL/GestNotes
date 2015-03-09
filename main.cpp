#include <wx/wx.h>

// Classe application :
	class MyApp : public wxApp
	{
	public:
	   // Méthode virtuelle de démarrage de l'application :
	    virtual bool OnInit();
	};
	
	// Notre fenêtre minimale :
	class MyFrame : public wxFrame
	{
	public:
	    // Constructeur :
	    MyFrame(const wxString& title);
	
	    // 2 handler d'évènements
	    void OnQuit(wxCommandEvent& event);
	    void OnAbout(wxCommandEvent& event);
	
	private:
	    // la table des évènements
	    DECLARE_EVENT_TABLE()
	};
	
	IMPLEMENT_APP(MyApp)
	
	
	// Notre 'main' :
	bool MyApp::OnInit()
	{
	    if ( !wxApp::OnInit() )
	        return false;
	
	    MyFrame *frame = new MyFrame(_T("Test Compilation - Efrei - GCC 3.4.2"));
	    frame->Show(true);
	
	    return true;
	}
	
	// IDs pour nos menus et contrôles :
	enum
	{
	    Minimal_Quit = wxID_EXIT,
	    Minimal_About = wxID_ABOUT
	};
	
	// La table des évènements de notre fenêtre :
	BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
	    EVT_MENU(Minimal_About, MyFrame::OnAbout)
	END_EVENT_TABLE()
	
	
	// Le constructeur de notre classe de fenêtre :
	MyFrame::MyFrame(const wxString& title)
	       : wxFrame(NULL, wxID_ANY, title)
	{
	    // Ajoutons nos menus :
	    wxMenu *fileMenu = new wxMenu;
	    fileMenu->Append(Minimal_Quit, _T("&Quitter\tAlt-Q"), _T("Sortir du programme"));
	    wxMenu *helpMenu = new wxMenu;
	    helpMenu->Append(Minimal_About, _T("&A propos...\tF1"), _T("Affiche la boîte à propos"));
	    // dans une barre de menu :
	    wxMenuBar *menuBar = new wxMenuBar();
	    menuBar->Append(fileMenu, _T("&Fichier"));
	    menuBar->Append(helpMenu, _T("&Aide"));
	    SetMenuBar(menuBar);
	
	    // Une barre de statut :
	    CreateStatusBar(2);
	    SetStatusText(_T("Enfin !"));
	}
	
	
	// La gestion des évènements :
	
	void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
	{
	    Close(true);
	}
	
	void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
	{
	    wxMessageBox(wxString::Format(
	                    _T("Wallah même moi j'trouve que t'abuse"),
	                    wxVERSION_STRING,
	                    wxGetOsDescription().c_str()
	                 ),
	                 _T("A propos..."),
	                 wxOK | wxICON_INFORMATION,
	                 this);
	}
