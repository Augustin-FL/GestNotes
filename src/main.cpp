#include "main.h"

IMPLEMENT_APP(App_GestNotes);

bool App_GestNotes::OnInit()
{
	wxInitAllImageHandlers();
	 
	bdd=new connexion_bdd();
	Frame_principale *frame_principale=new Frame_principale(bdd);
	
	Frame_login *login=new Frame_login(frame_principale,bdd);
	login->Show();//pour éviter un warning "unused variable"
 
    return true;
}


int App_GestNotes::OnExit()
{
	bdd->close();
	return 0;
}






Frame_principale::Frame_principale(connexion_bdd*& bdd_arg) : wxFrame(NULL, wxID_ANY,_T("GestNotes"),wxDefaultPosition,*(new wxSize(500,500)))
{
	bdd=bdd_arg;
	veto_autorise=true;
	#ifdef __WXMSW__
		SetIcon(wxICON(icone)); // l'icone ne fonctionne que sous windows
	#endif
}

void Frame_principale::afficher_apres_login(int type_arg, int id_arg)
{
	wxMenuBar *barre_menu= new wxMenuBar();

	wxMenu *menu_fichier = new wxMenu();
	wxMenu *menu_aide	 = new wxMenu();

	menu_fichier->Append(wxID_EXIT,	 _T("Quitter"), _T("Quitter GestNotes"));
	menu_aide->Append(wxID_ABOUT, _T("A Propos"), _T("Quelques infos sur le créateur..."));
	this->SetMenuBar(barre_menu);
	
	barre_menu->Append(menu_fichier, _T("Fichier"));
	barre_menu->Append(menu_aide, _T("Aide"));

	this->CreateStatusBar(1);
	
	
	if(type_arg==ELEVE)
	{
		//consulter les notes (tableau) +imprimer buletin de notes
		//consulter son groupe
		//voir (modifier?) contacts
		
//		wxStaticBoxSizer*conteneur_notes	= new wxStaticBoxSizer(wxVERTICAL,fenetre,_T("Notes : "));
	//	contenu_fenetre_sans_marge->Add(conteneur_notes, 1, wxALIGN_CENTER_VERTICAL);
		wxMessageBox("aaa");
	}
	else if(type_arg==PROF)
	{
		//liste déroulante en haut.->matière
		
		//saisir notes
		//changer groupe(?)
		//si accord de l'admin : changer les notes
		wxMessageBox("prof");
	}
	else if(type_arg==ADMIN) new Frame_admin(this,bdd,id_arg);
	else 
	{
			wxMessageBox(_T("Erreur ! Type de personne inconnu"), _T("GestNotes"));
			veto_autorise=false;
			Close(); 
			return ;
	}
	
	this->Connect(wxEVT_CLOSE_WINDOW,wxCloseEventHandler(Frame_principale::onClose),NULL, this);
	this->Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Frame_principale::onQuit), NULL, this);
	this->Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(Frame_principale::onAbout), NULL, this);
}


void Frame_principale::onQuit(wxCommandEvent &evenement)
{
	this->Close();
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
	 this->Destroy();
}

void Frame_principale::onAbout(wxCommandEvent &evenement)
{
	wxDialog *frame_about= new wxDialog(this, wxID_ANY,_T("A propos..."));
	
	wxPanel *fenetre = new wxPanel(frame_about, -1);
	wxBoxSizer *sizer_droite = new wxBoxSizer(wxVERTICAL);
	wxStaticBitmap *image = new wxStaticBitmap( fenetre, wxID_ANY, wxBITMAP_PNG(logo_ressource));
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
	
	
	sizer_horisontal->Add(image,1, wxALIGN_CENTER_VERTICAL| wxALIGN_LEFT, 15 );
	sizer_horisontal->Add(sizer_droite, 1, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT, 15);
	fenetre->SetSizer(sizer_horisontal);
	
	frame_about->ShowModal();

}