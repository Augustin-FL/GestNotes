#include "main.h"

/*
TODO : 
>Editer l'appréciation Générale de chaque élève

*/

Frame_admin::Frame_admin(Frame_login* parent,int& matricule,connexion_bdd*& bdd) : Frame_principale(parent,matricule,bdd)
{
	this->SetSize(wxDefaultCoord,wxDefaultCoord,770,625);
	wxPanel *fenetre = new wxPanel(this);

	wxBoxSizer *sizer_principal 		 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *sizer_principal_haut	 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *sizer_gauche			 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *sizer_centre			 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *sizer_droite			 = new wxBoxSizer(wxVERTICAL);
	
	liste_appreciations=new wxDataViewListCtrl(fenetre,-1, wxDefaultPosition, wxDefaultSize);
	
	
	wxStaticBoxSizer *texte_conteneur_ajout 	= new wxStaticBoxSizer(wxVERTICAL,  fenetre, _T("Utilisateurs : "));
	wxStaticBoxSizer *texte_conteneur_arrondi 	= new wxStaticBoxSizer(wxVERTICAL,  fenetre, _T("Arrondi des moyennes : "));
	wxStaticBoxSizer *sizer_principal_bas		= new wxStaticBoxSizer(wxHORIZONTAL,fenetre, _T("Appréciations Générales : "));
	
	wxStaticText *texte					 = new wxStaticText(fenetre, -1, _T("Gestion des utilisateurs\nde GestNotes :\n\n"));
	wxStaticText *label_arrondir_moyenne = new wxStaticText(fenetre, -1, _T("Arrondir les moyennes sur les buletins\n(n'affecte pas les calculs)\n\n"));
	
	wxButton *button_ajouter			 = new wxButton(	fenetre, -1, _T("Ajouter"));
	wxButton *button_modifier			 = new wxButton(	fenetre, -1, _T("Modifier"));
	wxButton *button_supprimer			 = new wxButton(	fenetre, -1, _T("Supprimer"));

	input_checkbox__notes_hors_bareme	 =new wxCheckBox(	fenetre, -1, _T("Autoriser les notes hors barème\n(au dessus de 20)\n\n"));
	input_checkbox__afficher_buletins	 =new wxCheckBox(	fenetre, -1, _T("Autoriser l'affichage/impression des buletins"));
	input_checkbox__autoriser_modif_notes=new wxCheckBox(	fenetre, -1, _T("Autoriser l'éditions des notes par les professeurs"));
	
	//Arrondi des moyennes (n'affecte pas les calculs)
	input_radio__arrondi_cent			 =new wxRadioButton(fenetre, -1, _T("Arrondi au 1/100° de point"));
	input_radio__arrondi_dix			 =new wxRadioButton(fenetre, -1, _T("Arrondi au 1/10° de point"));
	input_radio__arrondi_demi			 =new wxRadioButton(fenetre, -1, _T("Arrondi au demi point"));
	input_radio__arrondi_un				 =new wxRadioButton(fenetre, -1, _T("Arrondi au point"));

	sizer_principal->Add(sizer_principal_haut,1,wxEXPAND);
	sizer_principal->Add(sizer_principal_bas,1,wxEXPAND|wxALL,15);

	sizer_principal_haut->Add(sizer_gauche,1,wxALIGN_CENTER_VERTICAL,1);
	sizer_principal_haut->Add(sizer_centre,1,wxALIGN_CENTER,1);
	sizer_principal_haut->Add(sizer_droite,1,wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT,1);

	sizer_centre->Add(texte_conteneur_arrondi);

	sizer_gauche->Add(texte_conteneur_ajout,0,wxLEFT,15);
	texte_conteneur_ajout->Add(texte,0, wxALIGN_CENTER_HORIZONTAL,5);
	texte_conteneur_ajout->Add(button_ajouter,0,wxALIGN_LEFT|wxALIGN_CENTER_HORIZONTAL,5);
	texte_conteneur_ajout->Add(button_modifier,0,wxALIGN_LEFT|wxALIGN_CENTER_HORIZONTAL,5);
	texte_conteneur_ajout->Add(button_supprimer,0,wxALIGN_LEFT|wxALIGN_CENTER_HORIZONTAL,5);

	texte_conteneur_arrondi->Add(label_arrondir_moyenne);
	texte_conteneur_arrondi->Add(input_radio__arrondi_cent);
	texte_conteneur_arrondi->Add(input_radio__arrondi_dix);
	texte_conteneur_arrondi->Add(input_radio__arrondi_demi);
	texte_conteneur_arrondi->Add(input_radio__arrondi_un);

	sizer_droite->Add(input_checkbox__notes_hors_bareme,1);
	sizer_droite->Add(input_checkbox__afficher_buletins,1);
	sizer_droite->Add(input_checkbox__autoriser_modif_notes,1);
	
	sizer_principal_bas->Add(liste_appreciations,1,wxEXPAND);
	
	liste_appreciations->AppendTextColumn(_T("Classe"),  	  wxDATAVIEW_CELL_INERT	,wxCOL_WIDTH_AUTOSIZE);
	liste_appreciations->AppendTextColumn(_T("Appréciation"), wxDATAVIEW_CELL_EDITABLE);// 
	
	
	menu_fichier->Insert(1,wxID_HIGHEST+2, _T("Liste Des Utilisateurs"),	 _T("Afficher la liste des membres de GestNotes"));
	
	fenetre->SetSizer(sizer_principal);

	button_ajouter->Bind(					wxEVT_BUTTON,		&Frame_admin::onAjouter,	 	  this);
	input_checkbox__afficher_buletins->Bind(wxEVT_CHECKBOX, 	&Frame_admin::onCheck_Buletins,	  this);
	button_modifier->Bind(					wxEVT_BUTTON,		&Frame_admin::onModifier,		  this);
	button_supprimer->Bind(					wxEVT_BUTTON,		&Frame_admin::onSupprimer,		  this);
	input_radio__arrondi_cent->Bind(		wxEVT_RADIOBUTTON,	&Frame_admin::onChange_arrondi,	  this);
	input_radio__arrondi_dix->Bind(			wxEVT_RADIOBUTTON,	&Frame_admin::onChange_arrondi,	  this);
	input_radio__arrondi_demi->Bind(		wxEVT_RADIOBUTTON,	&Frame_admin::onChange_arrondi,	  this);
	input_radio__arrondi_un->Bind(			wxEVT_RADIOBUTTON,	&Frame_admin::onChange_arrondi,	  this);
	input_checkbox__notes_hors_bareme->Bind(wxEVT_CHECKBOX,		&Frame_admin::onClick_hors_bareme,this);
	input_checkbox__autoriser_modif_notes->Bind(wxEVT_CHECKBOX,		&Frame_admin::onCheck_Modif_notes,this);
	this->Bind(wxEVT_COMMAND_MENU_SELECTED, &Frame_admin::onAfficherMembres, this, wxID_HIGHEST+2);
	
	bdd->exec("SELECT * FROM reglages");
	
	if(bdd->getColumn_int(2)==1)//affichage buletins
	{
		input_checkbox__afficher_buletins->SetValue(true);
		input_checkbox__afficher_buletins->Disable();
		input_checkbox__autoriser_modif_notes->Disable();
	}
	
	if(bdd->getColumn_int(0)==1) input_checkbox__notes_hors_bareme->SetValue(true);//notes_hors_bareme
	
	if(bdd->getColumn_int(1)==100)	 	input_radio__arrondi_cent->SetValue(true);//précision
	else if(bdd->getColumn_int(1)==10)	input_radio__arrondi_dix-> SetValue(true);
	else if(bdd->getColumn_int(1)==2)	input_radio__arrondi_demi->SetValue(true);
	else if(bdd->getColumn_int(1)==1)	input_radio__arrondi_un->  SetValue(true);
	
	if(bdd->getColumn_int(3)==1) input_checkbox__autoriser_modif_notes->SetValue(true);//notes_hors_bareme
	
	this->SetStatusText(_T("GestNotes - Accès Admin"));
	this->Show();

}


void Frame_admin::onAjouter(wxCommandEvent &evenement)
{
	Frame_ajout_modification_membre(this,bdd);
}

void Frame_admin::onCheck_Buletins(wxCommandEvent &evenement)
{
	int reponse=wxMessageBox(_T("Voulez vous vraiment autoriser l'impression des buletins?\nVous ne pourrez pas annuler cette décision, et cela entrainera l'interdiction de la modification des notes"), _T("Confirmer"), wxYES_NO);
    
	if (reponse == wxNO)
	{
		input_checkbox__afficher_buletins->SetValue(false);
		evenement.Skip(false);
		return ;
	}
		
	bdd->exec("UPDATE reglages SET affichage_buletins=1");
	bdd->exec("UPDATE reglages SET edition_notes=0");
	
	input_checkbox__afficher_buletins->SetValue(true);
	input_checkbox__autoriser_modif_notes->SetValue(false);
	input_checkbox__autoriser_modif_notes->Disable();
	input_checkbox__afficher_buletins->Disable();
}

void Frame_admin::onCheck_Modif_notes(wxCommandEvent &evenement)
{
	if(input_checkbox__autoriser_modif_notes->IsChecked()) bdd->exec("UPDATE reglages SET edition_notes=1");
	else bdd->exec("UPDATE reglages SET edition_notes=0");
}


void Frame_admin::onAfficherMembres(wxCommandEvent &evenement)
{
	liste_membres=new Afficher_liste_membres(this,bdd,0);
}

void Frame_admin::onSupprimer(wxCommandEvent &evenement)
{
	liste_membres=new Afficher_liste_membres(this,bdd,2);	
}

void Frame_admin::onModifier(wxCommandEvent &evenement)
{
	liste_membres=new Afficher_liste_membres(this,bdd,1);
}

void Frame_admin::onModifier_id_selectionne(wxListEvent &evenement)
{
	if(evenement.GetIndex()!=wxNOT_FOUND)
	{
		if(liste_membres->ongletProfs_selected())
		{
			int matiere_tmp,classe_tmp; 
			wxString matiere_string=liste_membres->getListCtrl()->GetItemText(evenement.GetIndex(),2);//on récupère le texte dans la cellule (séléction,2)
			wxString classe_string=liste_membres->getListCtrl()->GetItemText(evenement.GetIndex(),3);
			
			requete_sql*req=bdd->prepare("SELECT profs.matiere, profs.classe FROM profs			\
											JOIN classes  ON classes.id=profs.classe			\
											JOIN matieres ON matieres.id_matiere=profs.matiere  \
											WHERE profs.id=:matricule 							\
												AND matieres.nom=:matiere_string				\
												AND classes.nom=:classe_string");// on ne peux récupérer que le texte de la classe

			req->bind(":matiere_string",std::string(matiere_string));
			req->bind(":classe_string",std::string(classe_string));
			req->bind(":matricule",wxAtoi(evenement.GetText()));
			req->fetch();
		
			matiere_tmp=req->getColumn_int(0);
			classe_tmp =req->getColumn_int(1);
			
			req->closeCursor();
			Frame_ajout_modification_membre(liste_membres,bdd,wxAtoi(evenement.GetText()),matiere_tmp,classe_tmp);
		}	
		else
		{
			Frame_ajout_modification_membre(liste_membres,bdd,wxAtoi(evenement.GetText()));
		}
		liste_membres->afficher_liste(*(new wxCommandEvent()));
	}
}

void Frame_admin::onSupprimer_id_selectionne(wxListEvent &evenement)
{
	requete_sql* req;
	int classe_tmp,matiere_tmp,matricule_tmp=wxAtoi(evenement.GetText());
	wxString matiere_string,classe_string;
	bool effacer_login_centralise=true;
			
	if(evenement.GetIndex()!=wxNOT_FOUND)
	{
		if(wxMessageBox(_T("Voulez vous vraiment supprimer ce membre ?"),_T("Supprimer un membre"),wxYES_NO)==wxNO)
			return ;
		
		if(liste_membres->ongletProfs_selected())
		{
			matiere_string=liste_membres->getListCtrl()->GetItemText(evenement.GetIndex(),2);//on récupère le texte dans la cellule (séléction,2)
			classe_string=liste_membres->getListCtrl()->GetItemText(evenement.GetIndex(),3);
			
			req=bdd->prepare("SELECT profs.matiere, profs.classe FROM profs			\
								JOIN classes  ON classes.id=profs.classe			\
								JOIN matieres ON matieres.id_matiere=profs.matiere  \
								WHERE profs.id=:matricule 							\
									AND matieres.nom=:matiere_string				\
									AND classes.nom=:classe_string");// on ne peux récupérer que le texte de la classe

			req->bind(":matiere_string",std::string(matiere_string));
			req->bind(":classe_string",std::string(classe_string));
			req->bind(":matricule",matricule_tmp);
			req->fetch();
		
			matiere_tmp=req->getColumn_int(0);
			classe_tmp =req->getColumn_int(1);
			
			req->closeCursor();
			
			this->supprimer_prof(matricule_tmp,classe_tmp,matiere_tmp);
			
			req=bdd->prepare("SELECT count(id) from profs WHERE id=:matricule");
			req->bind(":matricule",matricule_tmp);
			req->fetch();
			if(req->getColumn_int(0)<1) effacer_login_centralise=false;
		}	
		else if(liste_membres->ongletEleves_selected())
		{
			req=bdd->prepare("SELECT classe FROM eleves WHERE id=:matricule");//and eleve
			req->bind(":matricule",matricule);
			req->fetch();
			classe_tmp=req->getColumn_int(0);
			req->closeCursor();
			
			this->supprimer_eleve(matricule_tmp,classe_tmp);
		}
		else
		{
			req=bdd->prepare("DELETE FROM admins WHERE id=:matricule");
			req->bind(":matricule",matricule_tmp);
			req->fetch();
			req->closeCursor();
		}
		
		if(effacer_login_centralise)
		{
			req=bdd->prepare("DELETE FROM login_centralise WHERE matricule=:matricule");
			req->bind(":matricule",matricule_tmp);
			req->fetch();
			req->closeCursor();
		}
		liste_membres->afficher_liste(*(new wxCommandEvent()));
		
	}
}

void Frame_admin::onClick_hors_bareme(wxCommandEvent &evenement)
{
	if(input_checkbox__notes_hors_bareme->IsChecked()) bdd->exec("UPDATE reglages SET notes_hors_bareme=1");
	else bdd->exec("UPDATE reglages SET notes_hors_bareme=0");
}

void Frame_admin::onChange_arrondi(wxCommandEvent &evenement)
{
	int valeur=10;
	if(input_radio__arrondi_cent->GetValue())		valeur=100;
	else if(input_radio__arrondi_dix->GetValue())	valeur=10;
	else if(input_radio__arrondi_demi->GetValue())	valeur=2;
	else if(input_radio__arrondi_un->GetValue()) 	valeur=1;
	else wxMessageBox("erreur !");
	
	requete_sql* req=bdd->prepare("UPDATE reglages SET precision=?;");
	req->bind(1,valeur);
	req->fetch();
	
	req->closeCursor();
}
// -------------


void Frame_admin::supprimer_prof(int id, int classe, int matiere)
{
	int count;
	requete_sql* req;
	req=bdd->prepare("SELECT count(profs.id) FROM profs WHERE id=:matricule AND classe=:classe");//and eleve
	req->bind(":matricule",id);
	req->bind(":classe",classe);
	req->fetch();
	count=req->getColumn_int(0);
	req->closeCursor();
				
	if(count==1)
	{
		req=bdd->prepare("SELECT count(eleves.id) FROM eleves WHERE classe=:classe");
		req->bind(":classe",classe);
		req->fetch();
		count=req->getColumn_int(0);
		req->closeCursor();
	
		if(count==0)
		{
			//supprimer la classe / supprimer les notes
			req=bdd->prepare("DELETE FROM classes WHERE id=:classe");
			req->bind(":classe",classe);
			req->fetch();
			req->closeCursor();
			
			req=bdd->prepare("DELETE FROM notes WHERE id=:classe");
			req->bind(":classe",classe);
			req->fetch();
			req->closeCursor();
		}
	}
	
	req=bdd->prepare("SELECT count(id) FROM profs WHERE matiere=:matiere");
	req->bind(":matiere",matiere);
	req->fetch();
	count=req->getColumn_int(0);
	req->closeCursor();
	
	if(count==1)//supprimer la matiere / supprimer les notes
	{
		req=bdd->prepare("DELETE FROM matieres WHERE id_matiere=:matiere");
		req->bind(":matiere",matiere);
		req->fetch();
		req->closeCursor();
		
		req=bdd->prepare("DELETE FROM notes WHERE id_matiere=:matiere");
		req->bind(":matiere",matiere);
		req->fetch();
		req->closeCursor();
		
		req=bdd->prepare("DELETE FROM commentaires WHERE id_matiere=:matiere");
		req->bind(":matiere",matiere);
		req->fetch();
		req->closeCursor();
	}
	
	req=bdd->prepare("DELETE FROM profs WHERE id=:matricule AND matiere=:matiere AND classe=:classe");
	req->bind(":matricule",id);
	req->bind(":matiere",matiere);
	req->bind(":classe",classe);
	req->fetch();
	req->closeCursor();
}



void Frame_admin::supprimer_eleve(int id,int classe)
{
	requete_sql* req;
	int count;

	req=bdd->prepare("SELECT count(eleves.id) FROM eleves WHERE classe=:classe");//and eleve
	req->bind(":classe",classe);
	req->fetch();
	count=req->getColumn_int(0);
	req->closeCursor();
				
	if(count==1)
	{
		req=bdd->prepare("SELECT count(profs.id) FROM profs WHERE classe=:classe");
		req->bind(":classe",classe);
		req->fetch();
		count=req->getColumn_int(0);
		req->closeCursor();
	
		if(count==0)
		{
			//supprimer la classe / supprimer les notes
			req=bdd->prepare("DELETE FROM classes WHERE id=:classe");
			req->bind(":classe",classe);
			req->fetch();
			req->closeCursor();
			
			req=bdd->prepare("DELETE FROM notes WHERE id=:classe");
			req->bind(":classe",classe);
			req->fetch();
			req->closeCursor();
		}
	}
	
	req=bdd->prepare("DELETE FROM eleves WHERE id=:matricule");
	req->bind(":matricule",id);
	req->fetch();
	req->closeCursor();
	
	
	req=bdd->prepare("DELETE FROM notes WHERE id_eleve=:matricule");
	req->bind(":matricule",id);
	req->fetch();
	req->closeCursor();
	
	req=bdd->prepare("DELETE FROM commentaires WHERE id_eleve=:matricule");
	req->bind(":matricule",id);
	req->fetch();
	req->closeCursor();
	
	req=bdd->prepare("DELETE FROM commentaires WHERE id_eleve=:matricule");
	req->bind(":matricule",id);
	req->fetch();
	req->closeCursor();
}