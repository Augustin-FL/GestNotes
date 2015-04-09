#include "main.h"

IMPLEMENT_APP(App_GestNotes);

bool App_GestNotes::OnInit()
{
	wxInitAllImageHandlers();


	bdd=new connexion_bdd();
	
	Frame_login* login=new Frame_login(bdd);
	login->Show();//pour éviter un warning "unused variable"

    return true;
}


int App_GestNotes::OnExit()
{
	bdd->close();
	return 0;
}






Frame_principale::Frame_principale(Frame_login *parent_arg,int& matricule,connexion_bdd*& bdd) : wxFrame(NULL, wxID_ANY,_T("GestNotes"),wxDefaultPosition,*(new wxSize(500,500)))
{
	SetIcon(wxICON(icone)); // l'icone ne fonctionne que sous windows
	parent=parent_arg;
	wxMenuBar *barre_menu= new wxMenuBar();

	wxMenu *menu_fichier = new wxMenu();
	wxMenu *menu_aide	 = new wxMenu();

	menu_fichier->Append(wxID_EXIT,	 _T("Quitter"), _T("Quitter GestNotes"));
	menu_aide->Append(wxID_ABOUT, _T("A Propos"), _T("Quelques infos sur le créateur..."));
	this->SetMenuBar(barre_menu);

	barre_menu->Append(menu_fichier, _T("Fichier"));
	barre_menu->Append(menu_aide, _T("Aide"));

	this->CreateStatusBar(1);

	this->Connect(wxEVT_CLOSE_WINDOW,wxCloseEventHandler(Frame_principale::onClose),(wxObject*)this, this);
	this->Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Frame_principale::onQuit), (wxObject*)this, this);
	this->Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(Frame_principale::onAbout), NULL, this);
}


void Frame_principale::onQuit(wxCommandEvent &evenement)
{
	parent->onClick_annuler(*(new wxCommandEvent()));
}


void Frame_principale::onClose(wxCloseEvent &evenement)
{
	if(evenement.CanVeto())
	{
		int reponse=wxMessageBox(_T("Voulez vous vraiment quitter?"), _T("Quitter"), wxYES_NO | wxCANCEL);
		if (reponse != wxYES )
		{
			evenement.Veto();
			return ;
		}
	}
	exit(0);
	
	//parent->onClose(*(new wxCloseEvent()));
}

void Frame_principale::onAbout(wxCommandEvent &evenement)
{
	wxDialog *frame_about= new wxDialog(this, wxID_ANY,_T("A propos..."));

	wxPanel *fenetre = new wxPanel(frame_about, -1);
	wxBoxSizer *sizer_droite = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *sizer_horisontal = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *sizer_twitter = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *sizer_email = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *sizer_github = new wxBoxSizer(wxHORIZONTAL);

  	wxStaticText *texte_haut = new wxStaticText(fenetre,wxID_ANY, _T(" Auteur : gusfl\n\n Sous licence Apache\n\n Contact :"));
	wxStaticText *texte_bas = new wxStaticText(fenetre,wxID_ANY, _T("\n Vous avez trouvé un bug?\n N'hésitez pas à m'en faire part sur"));
	wxStaticText *label_github = new wxStaticText(fenetre,wxID_ANY, _T(" "));
	wxStaticText *label_github_2 = new wxStaticText(fenetre,wxID_ANY, _T(" !"));
	wxStaticText *label_email=  new wxStaticText(fenetre,wxID_ANY, _T(" Email : "));
	wxStaticText *label_twitter=  new wxStaticText(fenetre,wxID_ANY, _T(" Twitter : "));
	wxHyperlinkCtrl* lien_twitter = new wxHyperlinkCtrl(fenetre,wxID_ANY, _T("@FLisMyName"), _T("https://twitter.com/FLisMyName"));


	wxHyperlinkCtrl* lien_email = new wxHyperlinkCtrl(fenetre,wxID_ANY, _T("gusfl@free.fr"), _T("mailto:gusfl@free.fr"));
	wxHyperlinkCtrl* lien_github = new wxHyperlinkCtrl(fenetre,wxID_ANY, _T("github"), _T("https://github.com/gusfl/GestNotes/issues"));

	sizer_twitter->Add(label_twitter);
	sizer_twitter->Add(lien_twitter);
	sizer_email->Add(label_email);
	sizer_email->Add(lien_email);
	sizer_github->Add(label_github);
	sizer_github->Add(lien_github);
	sizer_github->Add(label_github_2);

	sizer_droite->Add(texte_haut);
	sizer_droite->Add(sizer_twitter);
	sizer_droite->Add(sizer_email);
	sizer_droite->Add(texte_bas);
	sizer_droite->Add(sizer_github);


	wxStaticBitmap *image = new wxStaticBitmap( fenetre, wxID_ANY, wxBITMAP_PNG(logo_ressource));
	sizer_horisontal->Add(image,1, wxALIGN_CENTER_VERTICAL| wxALIGN_LEFT, 15 );

	sizer_horisontal->Add(sizer_droite, 1, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT, 15);
	fenetre->SetSizer(sizer_horisontal);

	frame_about->ShowModal();

}
