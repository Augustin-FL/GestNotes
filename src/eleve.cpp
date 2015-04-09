#include "main.h"

Frame_eleve::Frame_eleve(Frame_login* parent,int& matricule,connexion_bdd*& bdd) : Frame_principale(parent,matricule,bdd)
{
	
	this->SetSize(wxDefaultCoord,wxDefaultCoord,770,625);
	
	wxPanel *fenetre = new wxPanel(this);

	wxBoxSizer *sizer_principal = new wxBoxSizer(wxVERTICAL);

	
	//consulter les notes (tableau) +imprimer buletin de notes
			//consulter son groupe
			//voir (modifier?) contacts

	
	fenetre->SetSizer(sizer_principal);
	this->SetStatusText(_T("GestNotes - Accès Élève"));
	this->Show();
}


