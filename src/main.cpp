#include "main.h"
IMPLEMENT_APP(App_GestNote);

Frame_login::Frame_login(Frame_principale*& parent, connexion_bdd*& arg_bdd): wxFrame(parent, wxID_ANY,_T("GestNote"),wxDefaultPosition,*(new wxSize(300,220)))
{
	wxPanel         *fenetre					= new wxPanel(this);
	wxBoxSizer      *contenu_fenetre_sans_marge	= new wxBoxSizer(wxVERTICAL);
	wxBoxSizer		*conteneur_horisontal_login	= new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer		*conteneur_horisontal_mdp 	= new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer 		*conteneur_boutons			= new wxBoxSizer(wxHORIZONTAL);
	
	wxStaticText	*texte_explicatif			= new wxStaticText(fenetre, -1, _T("\nVeuillez vous authentifier\npour accéder à votre espace GestNote.\n"));
	wxStaticBoxSizer*conteneur_authentification	= new wxStaticBoxSizer(wxVERTICAL,fenetre,_T("Authentification : "));
	
	wxStaticText	*label_login				= new wxStaticText(fenetre, -1, _T("Matricule : ")); 				
	wxStaticText	*label_mdp					= new wxStaticText(fenetre, -1, _T("Mot de passe : ")); 				
	
	bouton_valider	= new wxButton(    fenetre, -1, _T("Valider"));
	bouton_annuler 	= new wxButton(    fenetre, -1, _T("Quitter"));
	input_mdp		= new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,wxTE_PASSWORD);
	input_login		= new wxTextCtrl(  fenetre, -1, _T(""));
	
	fenetre->SetSizer(contenu_fenetre_sans_marge);
	
	contenu_fenetre_sans_marge->Add(texte_explicatif, 			1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL);//la fenetre contient : 
	contenu_fenetre_sans_marge->Add(conteneur_authentification, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL);//un texte explicatif, la zone de
	contenu_fenetre_sans_marge->Add(conteneur_boutons, 			1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxTOP, 10);//login, et les boutons
	
	conteneur_authentification->Add(conteneur_horisontal_login, 1, wxALIGN_LEFT|wxDOWN,5);//on dit que la zone d'authentification contient 
	conteneur_authentification->Add(conteneur_horisontal_mdp,   1, wxALIGN_LEFT);//un login et un mot de passe
	
	conteneur_horisontal_login->Add(label_login, 1);//la zone login contient un label pour le login, et un champ d'input.
	conteneur_horisontal_login->Add(input_login, 1);
	conteneur_horisontal_mdp->Add(label_mdp, 1);
	conteneur_horisontal_mdp->Add(input_mdp, 1);
	
	conteneur_boutons->Add(bouton_valider,1);//et il y a 2 boutons : valider et annuler
	conteneur_boutons->Add(bouton_annuler,1);

	bouton_valider->Disable();
	
	input_mdp->MoveAfterInTabOrder(input_login);//l'ordre des champs avec l'appui sur "tab"
	bouton_annuler->MoveAfterInTabOrder(input_mdp);
	
	bouton_valider->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frame_login::onClick_valider), NULL, this);
	bouton_annuler->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frame_login::onClick_annuler), NULL, this);
	input_login->Connect( 	wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Frame_login::onChange), NULL, this);
	input_mdp->Connect( 	wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Frame_login::onChange), NULL, this);
	this->Connect(			wxEVT_CLOSE_WINDOW,wxCloseEventHandler(Frame_login::onClose),NULL, this);
	this->Show();
	
	bdd=arg_bdd;
	frame_parente=parent;
	type=PAS_CONNECTE;
}


void Frame_login::onChange(wxCommandEvent &evenement)
{
	if(input_login->IsEmpty() ||input_mdp->IsEmpty()) bouton_valider->Disable();
	else 
	{
		bouton_valider->Enable();	
		bouton_valider->SetDefault();
	}
}

void Frame_login::onClick_valider(wxCommandEvent &evenement)
{
     
	requete_sql* req=bdd->prepare("SELECT count(*),type FROM login_centralise WHERE matricule=:matricule and mdp=:mdp");//WHERE matricule=:matricule AND mdp=:mdp
	
	req->bind(":matricule",string(input_login->GetValue().mb_str())); //si une erreur survient a ce niveau : 
	req->bind(":mdp",string(input_mdp->GetValue().mb_str()));//penser a utiliser le namespace std, ou a mettre std::string()

	if(req->fetch() && req->getColumn_int(0)==1)
	{
		type=req->getColumn_int(1);
		this->Hide();
		frame_parente->afficher_apres_login(type,req->getColumn_int(2));	
		this->Close();
	}
	else 
	{
		wxMessageBox(_T("Identifients incorrects !"),_T("erreur"));
		input_mdp->SetValue("");
	}
    
}

void Frame_login::onClick_annuler(wxCommandEvent &evenement)
{
	this->Close();
}


void Frame_login::onClose(wxCloseEvent &evenement)
{
		
	if(evenement.CanVeto() && type==PAS_CONNECTE)
	{
		int reponse=wxMessageBox(_T("Voulez vous vraiment quitter?"), _T("Quitter"), wxYES_NO | wxCANCEL);
		if (reponse == wxNO) 
		{
			evenement.Veto();	
			return ;
		}
	}
	
	this->Destroy();
	if(type==PAS_CONNECTE) frame_parente->Destroy();
}







Frame_principale::Frame_principale(connexion_bdd*& bdd_arg) : wxFrame(NULL, wxID_ANY,_T("GestNote"),wxDefaultPosition,*(new wxSize(500,500)))
{
	bdd=bdd_arg;
	veto_autorise=true;
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
	this->Show();
}


void Frame_principale::main_admin()
{
	//saisir prof
	//saisir éleve
	//ajouter/supprimer/modifier eleve & prof 
	
	wxMenuBar *barre_menu= new wxMenuBar();
    wxMenu *menu_fichier = new wxMenu();
	wxMenu *menu_aide = new wxMenu();

	this->SetSize(wxDefaultCoord,wxDefaultCoord,300,500);
	
	wxPanel         *fenetre					= new wxPanel(this);
	wxBoxSizer      *contenu_fenetre_sans_marge	= new wxBoxSizer(wxVERTICAL);
	wxBoxSizer      *contenur_radio_ajout		= new wxBoxSizer(wxVERTICAL);
	
	wxStaticText* texte_ajouter_prof 		= new wxStaticText(fenetre, -1, _T("\nAjouter un professeur, ou un admin : \n"));
	wxStaticText* label_ajouter_prof_nom 	= new wxStaticText(fenetre, -1, _T("Nom : "));
	wxStaticText* label_ajouter_prof_prenom = new wxStaticText(fenetre, -1, _T("Prénom : "));
	wxStaticText* label_ajouter_prof_mdp 	= new wxStaticText(fenetre, -1, _T("Mot de Passe: "));
	wxStaticText* label_ajouter_prof_radio	= new wxStaticText(fenetre, -1, _T("Ajouter un : "));
	label_ajouter_prof_matiere= new wxStaticText(fenetre, -1, _T("Matière : "));
	
	
	input_ajout_nom		= new wxTextCtrl(  fenetre, -1, _T(""));
	input_ajout_prenom	= new wxTextCtrl(  fenetre, -1, _T(""));
	input_ajout_mdp		= new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,wxTE_PASSWORD);
	input_ajout_matiere	= new wxTextCtrl(  fenetre, -1, _T(""));
	
	wxStaticBoxSizer* texte_conteneur_ajout = new wxStaticBoxSizer(wxVERTICAL,fenetre,_T("Ajouter : "));
	wxFlexGridSizer*  conteneur_formulaire_ajout = new wxFlexGridSizer(2,5,5);
	
	
	fenetre->SetSizer(contenu_fenetre_sans_marge);
	
	
	contenu_fenetre_sans_marge->Add(texte_conteneur_ajout,0,  wxALIGN_TOP, 10); 
	texte_conteneur_ajout->Add(texte_ajouter_prof,0);
	
	texte_conteneur_ajout->Add(conteneur_formulaire_ajout,0);
	conteneur_formulaire_ajout->Add(label_ajouter_prof_nom,0);
	conteneur_formulaire_ajout->Add(input_ajout_nom,0);
	conteneur_formulaire_ajout->Add(label_ajouter_prof_prenom,0);
	conteneur_formulaire_ajout->Add(input_ajout_prenom,0);
	conteneur_formulaire_ajout->Add(label_ajouter_prof_mdp,0);
	conteneur_formulaire_ajout->Add(input_ajout_mdp,0);
	conteneur_formulaire_ajout->Add(label_ajouter_prof_radio,0);
	conteneur_formulaire_ajout->Add(contenur_radio_ajout,0);
	
	
	conteneur_formulaire_ajout->Add(label_ajouter_prof_matiere,0);
	
//	vector<string> liste_matieres=this->lister_matieres();
	/*
	requete_sql* req=bdd->exec("select nom, id_matiere from matieres");
	
	while(req->fetch())
	{
		int id_matiere req->getColumn_int(0);
	//	 texte=new wxString(""); 
		
		
	}*/
	
	conteneur_formulaire_ajout->Add(input_ajout_matiere,0);
	
	
	
	input_radio_prof  = new wxRadioButton(fenetre,wxID_ANY, _T("Professeur"));
	input_radio_admin = new wxRadioButton(fenetre, wxID_ANY, _T("Administrateur"));
	
	contenur_radio_ajout->Add(input_radio_prof,1);
	contenur_radio_ajout->Add(input_radio_admin,1);
	
	input_radio_prof->SetValue(true);
	input_radio_prof->MoveAfterInTabOrder(input_radio_admin);
	
	input_radio_prof->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED  ,wxCommandEventHandler(Frame_principale::onClick_radio_ajout_prof), NULL, this);
	input_radio_admin->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED ,wxCommandEventHandler(Frame_principale::onClick_radio_ajout_prof), NULL, this);
	

	
	menu_fichier->Append(wxID_EXIT,	 _T("Quitter"));
	menu_aide->Append(wxID_ABOUT, _T("A Propos"));
	barre_menu->Append(menu_fichier, _T("Fichier"));
	barre_menu->Append(menu_aide, _T("Aide"));
	this->SetMenuBar(barre_menu);
	
	this->CreateStatusBar(1);
	this->SetStatusText(_T("GestNote - Accès Admin"));
	
	this->Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Frame_principale::onQuit), NULL, this);
	
	//ajout d'une matière 
	
	
	}

void Frame_principale::onClick_radio_ajout_prof(wxCommandEvent &evenement)
{
		if(input_radio_prof->GetValue())
		{
			input_ajout_matiere->Enable();
			label_ajouter_prof_matiere->Enable();
		}
		else if(input_radio_admin->GetValue())
		{
			input_ajout_matiere->Disable();
			label_ajouter_prof_matiere->Disable();
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
		if (reponse == wxNO)
		{
			evenement.Veto();
			return ;
		}
	}
	 this->Destroy();
}

bool App_GestNote::OnInit()
{
	
	bdd=new connexion_bdd();
	Frame_principale *frame_principale=new Frame_principale(bdd);
	
	Frame_login *login=new Frame_login(frame_principale,bdd);
	login->Show();//pour éviter un warning "unused variable"
 
    return true;
}
