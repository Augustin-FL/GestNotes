#include "main.h"
IMPLEMENT_APP(App_GestNote);



Frame_principale::Frame_principale(connexion_bdd*& bdd_arg) : wxFrame(NULL, wxID_ANY,_T("GestNote"),wxDefaultPosition,*(new wxSize(500,500)))
{
	bdd=bdd_arg;
	veto_autorise=true;
	SetIcon(wxICON(icone));
}

void Frame_principale::afficher_apres_login(int type_arg, int id_arg)
{
	type=type_arg;
	id=id_arg;
	
	if(type==ELEVE)
	{
		//consulter les notes (tableau) +imprimer buletin de notes
		//consulter son groupe
		//voir (modifier?) contacts
		
//		wxStaticBoxSizer*conteneur_notes	= new wxStaticBoxSizer(wxVERTICAL,fenetre,_T("Notes : "));
	//	contenu_fenetre_sans_marge->Add(conteneur_notes, 1, wxALIGN_CENTER_VERTICAL);
		
	}
	else if(type==PROF)
	{
		//liste déroulante en haut.->matière
		
		//saisir notes
		//changer groupe(?)
		//si accord de l'admin : changer les notes
	
	}
	else if(type==ADMIN) this->main_admin();
	else 
	{
			wxMessageBox(_T("Erreur ! Type de personne inconnu"), _T("GestNote"));
			veto_autorise=false;
			Close(); 
			return ;
	}
	
	
	this->Connect(wxEVT_CLOSE_WINDOW,wxCloseEventHandler(Frame_principale::onClose),NULL, this);
}


void Frame_principale::main_admin()
{
	//saisir prof
	//saisir éleve
	//ajouter/supprimer/modifier eleve & prof 
	
	requete_sql* req=bdd->exec("select nom, id_matiere from matieres");
	wxArrayString texte_select;
	while(req->fetch()) texte_select.Add(req->getColumn_text(0));
	texte_select.Add(_T("<Ajouter Une Matière>"));
	
	nombre_matiere=texte_select.GetCount()-1;
	
	// graphique
	
	this->SetSize(wxDefaultCoord,wxDefaultCoord,800,600);
	
	wxMenuBar *barre_menu= new wxMenuBar();
	wxMenu *menu_fichier = new wxMenu();
	wxMenu *menu_aide	 = new wxMenu();

	wxPanel          *fenetre					= new wxPanel(this);
	wxBoxSizer       *contenu_fenetre_sans_marge= new wxBoxSizer(wxVERTICAL);
	wxBoxSizer       *contenur_radio_ajout		= new wxBoxSizer(wxVERTICAL);
	wxStaticBoxSizer *texte_conteneur_ajout 	= new wxStaticBoxSizer(wxVERTICAL,fenetre,_T("Ajouter : "));
	wxBoxSizer		 *conteneur_ajout_horisontal= new wxBoxSizer(wxHORIZONTAL);
	wxFlexGridSizer  *conteneur_ajout_gauche= new wxFlexGridSizer(2,5,5);
	wxFlexGridSizer  *conteneur_ajout_droite= new wxFlexGridSizer(2,11,5);
	wxStaticLine     *separarion_horisontale 	= new wxStaticLine(fenetre, -1);
	wxStaticLine     *separarion_verticale	 	= new wxStaticLine(fenetre, -1,wxDefaultPosition, wxDefaultSize,wxLI_VERTICAL);
   
   
	wxStaticText* texte_ajouter_prof 		= new wxStaticText(fenetre, -1, _T("\nAjouter un professeur, ou un admin : \n"));
	wxStaticText* label_ajouter_prof_nom 	= new wxStaticText(fenetre, -1, _T("Nom : "));
	wxStaticText* label_ajouter_prof_prenom = new wxStaticText(fenetre, -1, _T("Prénom : "));
	wxStaticText* label_ajouter_prof_mdp 	= new wxStaticText(fenetre, -1, _T("Mot de Passe: "));
	wxStaticText* label_ajouter_prof_radio	= new wxStaticText(fenetre, -1, _T("Ajouter un : "));
	 
	label_ajouter_prof_matiere	= new wxStaticText(fenetre, -1, _T("Matière : "));
	input_ajout_nom				= new wxTextCtrl(  fenetre, -1, _T(""));
	input_ajout_prenom			= new wxTextCtrl(  fenetre, -1, _T(""));
	input_ajout_mdp				= new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,wxTE_PASSWORD);
	
	label_ajout_eleve__nom_responsable 	= new wxStaticText(fenetre, -1, _T("Nom du responsable : "));
	
	input_ajout_eleve__nom_responsable	= new wxTextCtrl(  fenetre, -1, _T(""));

	input_radio_prof  			= new wxRadioButton(fenetre, -1, _T("Professeur"));
	input_radio_admin 			= new wxRadioButton(fenetre, -1, _T("Administrateur"));
	input_radio_eleve 			= new wxRadioButton(fenetre, -1, _T("Élève"));
	input_select_matiere_ajout	= new wxComboBox(fenetre, -1,_T("<selectionner>"), wxDefaultPosition,wxDefaultSize,texte_select);
	bouton_valider_ajout_prof	= new wxButton(fenetre, -1, _T("Valider"));
     
	/*    
	
	input_ajout_eleve__prenom_responsable
	input_ajout_eleve__tel_responsable
	input_ajout_eleve__mail_responsable
	input_ajout_eleve__sexe
	input_ajout_eleve__nom_rue
	input_ajout_eleve__rue
	input_ajout_eleve__code_postal
	input_ajout_eleve__ville
	input_ajout_eleve__tel_mobile
	input_ajout_eleve__groupe
	*/
	
	// -- la liste des matières
	
	fenetre->SetSizer(contenu_fenetre_sans_marge);
	
	contenu_fenetre_sans_marge->Add(texte_conteneur_ajout,0,  wxALIGN_TOP|wxALIGN_LEFT, 10); 
	
	texte_conteneur_ajout->Add(texte_ajouter_prof,0,wxALIGN_CENTER);
	texte_conteneur_ajout->Add(conteneur_ajout_horisontal,0);
	
	conteneur_ajout_horisontal->Add(conteneur_ajout_gauche,0);
	conteneur_ajout_horisontal->Add(separarion_verticale,0, wxALL | wxEXPAND, 5);
	conteneur_ajout_horisontal->Add(conteneur_ajout_droite,0);
	

	conteneur_ajout_gauche->Add(label_ajouter_prof_nom,0);
	conteneur_ajout_gauche->Add(input_ajout_nom,0);
	conteneur_ajout_gauche->Add(label_ajouter_prof_prenom,0);
	conteneur_ajout_gauche->Add(input_ajout_prenom,0);
	conteneur_ajout_gauche->Add(label_ajouter_prof_mdp,0);
	conteneur_ajout_gauche->Add(input_ajout_mdp,0);
	conteneur_ajout_gauche->Add(label_ajouter_prof_radio,0);
	conteneur_ajout_gauche->Add(contenur_radio_ajout,0);
	conteneur_ajout_gauche->Add(label_ajouter_prof_matiere,0);
	conteneur_ajout_gauche->Add(input_select_matiere_ajout,0);
	
	texte_conteneur_ajout->Add(separarion_horisontale,0, wxALL | wxEXPAND, 5);
	texte_conteneur_ajout->Add(bouton_valider_ajout_prof,1, wxALIGN_CENTER_HORIZONTAL,5);
	
	// --les 2 radio
	contenur_radio_ajout->Add(input_radio_prof,1);
	contenur_radio_ajout->Add(input_radio_admin,1);
	contenur_radio_ajout->Add(input_radio_eleve,1);
	input_radio_prof->SetValue(true);
	
	//l'input select
	input_select_matiere_ajout->SetEditable(false);
	input_select_matiere_ajout->SetBackgroundColour(0xFFFFFF);
	
	
	
	input_radio_prof->MoveAfterInTabOrder(input_radio_admin);
	
	
	conteneur_ajout_droite->Add(label_ajout_eleve__nom_responsable,0);
	conteneur_ajout_droite->Add(input_ajout_eleve__nom_responsable,0);
	
	bouton_valider_ajout_prof->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frame_principale::onClick_ajouter_prof), NULL, this);
	input_select_matiere_ajout->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(Frame_principale::onChange_select_matiere), NULL, this);
	input_radio_prof->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED  ,wxCommandEventHandler(Frame_principale::onClick_radio_ajout_prof), NULL, this);
	input_radio_admin->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED ,wxCommandEventHandler(Frame_principale::onClick_radio_ajout_prof), NULL, this);
	
	this->Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Frame_principale::onQuit), NULL, this);
	this->Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(Frame_principale::onAbout), NULL, this);
	
	// --bare de menu : haut
	menu_fichier->Append(wxID_EXIT,	 _T("Quitter"), _T("Quitter GestNote"));
	menu_aide->Append(wxID_ABOUT, _T("A Propos"), _T("Quelques infos sur le créateur..."));
	this->SetMenuBar(barre_menu);
	
	barre_menu->Append(menu_fichier, _T("Fichier"));
	barre_menu->Append(menu_aide, _T("Aide"));
	
	// --barre de statut : bas
	this->CreateStatusBar(1);
	this->SetStatusText(_T("GestNote - Accès Admin"));
	
	this->Show();
}

void Frame_principale::onClick_ajouter_prof(wxCommandEvent &evenement)
{
	
	
}

void Frame_principale::onAbout(wxCommandEvent &evenement)
{
	wxDialog *frame_about= new wxDialog(this, wxID_ANY,_T("A propos..."));
	
	wxPanel *fenetre = new wxPanel(frame_about, -1);
	wxBoxSizer *sizer_horisontal = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *sizer_droite = new wxBoxSizer(wxVERTICAL);
	wxStaticBitmap *image = new wxStaticBitmap( fenetre, wxID_ANY, wxBITMAP_PNG(logo_ressource));
	wxBoxSizer *sizer_twitter = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *sizer_email = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *sizer_github = new wxBoxSizer(wxHORIZONTAL);
	
  	wxStaticText *texte_haut = new wxStaticText(fenetre,wxID_ANY, _T("Programme créé par Gusfl\nSous licence Apache\n\nContact :"));
	wxStaticText *texte_bas = new wxStaticText(fenetre,wxID_ANY, _T("\nVous avez trouvé un bug?\nN'hésitez pas à m'en faire part sur"));
	
	wxStaticText *texte_bas_2 = new wxStaticText(fenetre,wxID_ANY, _T(" !"));
	
	
	wxStaticText *label_twitter=  new wxStaticText(fenetre,wxID_ANY, _T("Twitter : "));
	wxHyperlinkCtrl* lien_twitter = new wxHyperlinkCtrl(fenetre,wxID_ANY, _T("@FLisMyName"), _T("https://twitter.com/FLisMyName"));
	
	wxStaticText *label_email=  new wxStaticText(fenetre,wxID_ANY, _T("Email : "));
	wxHyperlinkCtrl* lien_email = new wxHyperlinkCtrl(fenetre,wxID_ANY, _T("gusfl@free.fr"), _T("mailto:gusfl@free.fr"));
	wxHyperlinkCtrl* lien_github = new wxHyperlinkCtrl(fenetre,wxID_ANY, _T("github"), _T("https://github.com/gusfl/GestNote/issues"));
	
	sizer_twitter->Add(label_twitter);
	sizer_twitter->Add(lien_twitter);
	sizer_email->Add(label_email);
	sizer_email->Add(lien_email);
	sizer_github->Add(lien_github);
	sizer_github->Add(texte_bas_2);
	
	sizer_droite->Add(texte_haut);
	sizer_droite->Add(sizer_twitter);
	sizer_droite->Add(sizer_email);
	sizer_droite->Add(texte_bas);
	sizer_droite->Add(sizer_github);
	
	
	sizer_horisontal->Add(image,1, wxALIGN_CENTER_VERTICAL);
	sizer_horisontal->Add(sizer_droite, 1, wxALIGN_CENTER|wxALIGN_RIGHT, 15);
	fenetre->SetSizer(sizer_horisontal);
	
	frame_about->ShowModal();

}

void Frame_principale::onChange_select_matiere(wxCommandEvent &evenement)
{
	if(input_select_matiere_ajout->GetSelection()==nombre_matiere)
	{
		input_select_matiere_ajout->SetEditable(true);
		input_select_matiere_ajout->SetValue("");
	}
	else
	{
		input_select_matiere_ajout->SetEditable(false);
		input_select_matiere_ajout->SetBackgroundColour(0xFFFFFF);
	}
	
}
void Frame_principale::onClick_radio_ajout_prof(wxCommandEvent &evenement)
{
	if(input_radio_eleve->GetValue())
	{
		label_ajout_eleve__nom_responsable->Enable();
		input_ajout_eleve__nom_responsable->Enable();
		
		input_select_matiere_ajout->Disable();
		label_ajouter_prof_matiere->Disable();
	}
	else
	{
		if(input_radio_prof->GetValue())
		{
			input_select_matiere_ajout->Enable();
			label_ajouter_prof_matiere->Enable();
		}
		else if(input_radio_admin->GetValue())
		{
			input_select_matiere_ajout->Disable();
			label_ajouter_prof_matiere->Disable();
		}
		
		label_ajout_eleve__nom_responsable->Disable();
		input_ajout_eleve__nom_responsable->Disable();
	}
		
	
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

bool App_GestNote::OnInit()
{
	wxInitAllImageHandlers();
	 
	bdd=new connexion_bdd();
	Frame_principale *frame_principale=new Frame_principale(bdd);
	
	Frame_login *login=new Frame_login(frame_principale,bdd);
	login->Show();//pour éviter un warning "unused variable"
 
    return true;
}
