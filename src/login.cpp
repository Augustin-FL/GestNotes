#include "main.h"

#ifndef __WXMSW__
	#include "ressources.xpm"//ressources linux
#endif


Frame_login::Frame_login( connexion_bdd*& arg_bdd): wxFrame(NULL, wxID_ANY,_T("GestNotes"),wxDefaultPosition,*(new wxSize(300,220)))
{
	SetIcon(wxICON(icone)); 
	frame_actuelle=this;
	wxPanel         *fenetre					= new wxPanel(this);
	wxBoxSizer      *contenu_fenetre_sans_marge	= new wxBoxSizer(wxVERTICAL);
	wxBoxSizer		*conteneur_horisontal_login	= new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer		*conteneur_horisontal_mdp 	= new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer 		*conteneur_boutons			= new wxBoxSizer(wxHORIZONTAL);
	
	wxStaticText	*texte_explicatif			= new wxStaticText(fenetre, -1, _T("\nVeuillez vous authentifier\npour accéder à votre espace GestNotes.\n"));
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
//	frame_parente=parent;
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
		int matricule=wxAtoi(input_login->GetValue());
		
		req->closeCursor();
		this->Hide();
		
		if(type==ELEVE)
		{
			//consulter les notes (tableau) +imprimer buletin de notes
			//consulter son groupe
			//voir (modifier?) contacts

		//	wxStaticBoxSizer*conteneur_notes	= new wxStaticBoxSizer(wxVERTICAL,fenetre,_T("Notes : "));
			//	contenu_fenetre_sans_marge->Add(conteneur_notes, 1, wxALIGN_CENTER_VERTICAL);
			wxMessageBox("aaa");
		}
		else if(type==PROF)
		{
			//liste déroulante en haut.->matière

			//saisir notes
			//changer groupe(?)
			//si accord de l'admin : changer les notes
			wxMessageBox("prof");
		}
		else if(type==ADMIN) frame_enfant=new Frame_admin(this,matricule,bdd);
		else
		{
			wxMessageBox(_T("Erreur ! Type de personne inconnu"), _T("GestNotes"));
			this->Close();
		}
	}
	else 
	{
		req->closeCursor();
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
}
