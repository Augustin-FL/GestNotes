#include "main.h"

#ifndef __WXMSW__
	#include "ressources.xpm"//ressources linux
#endif




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



Frame_principale::Frame_principale(Frame_login *parent_arg,int& matricule,connexion_bdd*& bdd_arg) : wxFrame(NULL, wxID_ANY,_T("GestNotes"),wxDefaultPosition,wxSize(500,500))
{
	SetIcon(wxICON(icone)); // l'icone ne fonctionne que sous windows
	parent=parent_arg;
	bdd=bdd_arg;
	wxMenuBar *barre_menu= new wxMenuBar();

	wxMenu *menu_fichier = new wxMenu();
	wxMenu *menu_aide	 = new wxMenu();

	menu_fichier->Append(wxID_HIGHEST+1, _T("Modifier mon mot de passe"), _T("Modifier mon mot de passe"));
	menu_fichier->Append(wxID_EXIT,		 _T("Quitter"),					 _T("Quitter GestNotes"));
	menu_aide->Append(wxID_ABOUT,  		 _T("A Propos"),				 _T("Quelques infos sur le créateur..."));
	this->SetMenuBar(barre_menu);

	barre_menu->Append(menu_fichier,_T("Fichier"));
	barre_menu->Append(menu_aide, 	_T("Aide"));

	this->CreateStatusBar(1);

	this->Bind(wxEVT_CLOSE_WINDOW,			&Frame_principale::onClose,		this);
	this->Bind(wxEVT_COMMAND_MENU_SELECTED, &Frame_principale::onQuit, 		this, wxID_EXIT);
	this->Bind(wxEVT_COMMAND_MENU_SELECTED, &Frame_principale::onAbout,	 	this, wxID_ABOUT);
	this->Bind(wxEVT_COMMAND_MENU_SELECTED, &Frame_principale::onChangeMdp, this, wxID_HIGHEST+1);
	
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
	parent->Destroy();
}

void Frame_principale::onAbout(wxCommandEvent &evenement)
{
	wxDialog *frame_about	= new wxDialog(this, wxID_ANY,_T("A propos..."),wxDefaultPosition,wxSize(490,225));
	wxPanel  *fenetre 		= new wxPanel(frame_about, -1);
	
	wxBoxSizer *sizer_droite 		= new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *sizer_horisontal 	= new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *sizer_twitter 		= new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *sizer_email 		= new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *sizer_github 		= new wxBoxSizer(wxHORIZONTAL);

	wxStaticText *texte_version		= new wxStaticText(fenetre,wxID_ANY,_T("GestNotes ")+(std::string)VERSION);
  	wxStaticText *texte_haut 		= new wxStaticText(fenetre,wxID_ANY, _T("\nAuteurs : gusfl et krnruth\nProgramme sous licence Apache.\n\nContact :"));
	wxStaticText *texte_bas 		= new wxStaticText(fenetre,wxID_ANY, _T("\nVous avez trouvé un bug?"));
	wxStaticText *label_github 		= new wxStaticText(fenetre,wxID_ANY, _T("N'hésitez pas à nous en faire part sur "));
	wxStaticText *label_github_2 	= new wxStaticText(fenetre,wxID_ANY, _T(" !"));
	wxStaticText *label_virgule_1 	= new wxStaticText(fenetre,wxID_ANY, _T(", "));
	wxStaticText *label_virgule_2 	= new wxStaticText(fenetre,wxID_ANY, _T(", "));
	wxStaticText *label_email		= new wxStaticText(fenetre,wxID_ANY, _T("Email : "));
	wxStaticText *label_twitter		= new wxStaticText(fenetre,wxID_ANY, _T("Twitter : "));

	wxHyperlinkCtrl* lien_twitter_gusfl   	= new wxHyperlinkCtrl(fenetre,wxID_ANY, _T("@FLisMyName"), _T("https://twitter.com/FLisMyName"));
	wxHyperlinkCtrl* lien_twitter_krnruth 	= new wxHyperlinkCtrl(fenetre,wxID_ANY, _T("@krnruth"), _T("https://twitter.com/krnruth"));
	wxHyperlinkCtrl* lien_email_gusfl		= new wxHyperlinkCtrl(fenetre,wxID_ANY, _T("gusfl@free.fr"), _T("mailto:gusfl@free.fr"));
	wxHyperlinkCtrl* lien_email_krnruth 	= new wxHyperlinkCtrl(fenetre,wxID_ANY, _T("krnruth91@gmail.com"), _T("mailto:krnruth91@gmail.com"));
	wxHyperlinkCtrl* lien_github			= new wxHyperlinkCtrl(fenetre,wxID_ANY, _T("github"), _T("https://github.com/gusfl/GestNotes/issues"));

	
	wxStaticBitmap *image			= new wxStaticBitmap( fenetre, wxID_ANY, wxBITMAP_PNG(logo_ressource));//on récuère l'image depuis les ressources
	
	sizer_horisontal->Add(image,1, wxALIGN_CENTER_VERTICAL| wxALIGN_LEFT, 15 );
	sizer_horisontal->Add(sizer_droite, 1, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT, 15);
	
	sizer_droite->Add(texte_version);
	sizer_droite->Add(texte_haut);
	sizer_droite->Add(sizer_twitter);
	sizer_droite->Add(sizer_email);
	sizer_droite->Add(texte_bas);
	sizer_droite->Add(sizer_github);

	sizer_twitter->Add(label_twitter);
	sizer_twitter->Add(lien_twitter_gusfl);
	sizer_twitter->Add(label_virgule_1);
	sizer_twitter->Add(lien_twitter_krnruth);
	
	sizer_email->Add(label_email);
	sizer_email->Add(lien_email_gusfl);
	sizer_email->Add(label_virgule_2);
	sizer_email->Add(lien_email_krnruth);
	
	sizer_github->Add(label_github);
	sizer_github->Add(lien_github);
	sizer_github->Add(label_github_2);
	
	fenetre->SetSizer(sizer_horisontal);
	frame_about->ShowModal();
}

void Frame_principale::onChangeMdp(wxCommandEvent &evenement)
{
	wxMessageBox(_T("En construction ;p "));
	
	
}


wxTextRegexpValidator::wxTextRegexpValidator(wxString regexp, wxString* pointeur) : m_regEx(regexp)//constructeur : création d'un wxValidator
{
   m_stringValue = pointeur;
   m_reString = regexp;
}


wxObject* wxTextRegexpValidator::Clone() const // le constructeur de clonage
{
   return new wxTextRegexpValidator(m_reString, m_stringValue);
}

bool wxTextRegexpValidator::TransferToWindow()//la validation.
{
   if (m_stringValue == NULL)
      return true;

   if (m_regEx.Matches(*m_stringValue))
      return wxTextValidator::TransferToWindow();
   
   return false;
}

bool wxTextRegexpValidator::TransferFromWindow(void)// 
{
   wxTextCtrl *control = (wxTextCtrl *) m_validatorWindow;
   wxString tmp = control->GetValue();

   if (m_regEx.Matches(tmp))
      return wxTextRegexpValidator::TransferFromWindow();

    return false;
}