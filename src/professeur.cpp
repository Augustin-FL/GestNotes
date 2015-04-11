#include "main.h"

Frame_prof::Frame_prof(Frame_login* parent,int& matricule,connexion_bdd*& bdd) : Frame_principale(parent,matricule,bdd)
{
	
	this->SetSize(wxDefaultCoord,wxDefaultCoord,770,625);
	
	wxPanel *fenetre = new wxPanel(this);

	wxBoxSizer *sizer_principal = new wxBoxSizer(wxVERTICAL);

	
	
	
	fenetre->SetSizer(sizer_principal);
	this->SetStatusText(_T("GestNotes - Accès Professeur"));
	this->Show();
	
	//liste déroulante en haut.->matière

			//saisir notes
			//changer groupe(?)
			//si accord de l'admin : changer les notes
			//ecrire des commentaires pour les buletins
}



