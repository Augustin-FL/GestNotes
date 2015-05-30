#include "main.h"


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
	
	liste_appreciations->AppendTextColumn(_T("Matricule"),     wxDATAVIEW_CELL_INERT	,wxCOL_WIDTH_AUTOSIZE);
	liste_appreciations->AppendTextColumn(_T("Élèves"),  	   wxDATAVIEW_CELL_INERT	,wxCOL_WIDTH_AUTOSIZE);
	liste_appreciations->AppendTextColumn(_T("Classes"),  	   wxDATAVIEW_CELL_INERT	,wxCOL_WIDTH_AUTOSIZE);
	liste_appreciations->AppendTextColumn(_T("Appréciations"), wxDATAVIEW_CELL_EDITABLE);// 
	
	ordre_colonne1=1;
	ordre_colonne2=0;
	ordre_colonne3=0;
	
	this->Afficher_liste(*new wxDataViewEvent());
	
	menu_fichier->Insert(1,wxID_HIGHEST+2, _T("Liste Des Utilisateurs"),	 _T("Afficher la liste des membres de GestNotes"));
	
	fenetre->SetSizer(sizer_principal);

	button_ajouter->Bind(					wxEVT_BUTTON,			&Frame_admin::onAjouter,			this);
	input_checkbox__afficher_buletins->Bind(wxEVT_CHECKBOX, 		&Frame_admin::onCheck_Buletins,		this);
	button_modifier->Bind(					wxEVT_BUTTON,			&Frame_admin::onModifier,			this);
	button_supprimer->Bind(					wxEVT_BUTTON,			&Frame_admin::onSupprimer,			this);
	input_radio__arrondi_cent->Bind(		wxEVT_RADIOBUTTON,		&Frame_admin::onChange_arrondi,		this);
	input_radio__arrondi_dix->Bind(			wxEVT_RADIOBUTTON,		&Frame_admin::onChange_arrondi,		this);
	input_radio__arrondi_demi->Bind(		wxEVT_RADIOBUTTON,		&Frame_admin::onChange_arrondi,		this);
	input_radio__arrondi_un->Bind(			wxEVT_RADIOBUTTON,		&Frame_admin::onChange_arrondi,		this);
	input_checkbox__notes_hors_bareme->Bind(wxEVT_CHECKBOX,			&Frame_admin::onClick_hors_bareme,	this);
	input_checkbox__autoriser_modif_notes->Bind(wxEVT_CHECKBOX,		&Frame_admin::onCheck_Modif_notes,	this);
	//liste_appreciations->Bind(wxEVT_DATAVIEW_COLUMN_HEADER_CLICK,	&Frame_admin::onChanger_ordre,		this);
	liste_appreciations->Bind(wxEVT_DATAVIEW_ITEM_VALUE_CHANGED,	&Frame_admin::onChange_commentaires,this);
	liste_appreciations->Bind(wxEVT_DATAVIEW_ITEM_ACTIVATED,		&Frame_admin::onDbclick_commentaires,this);
	
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
	//this->Afficher_liste(*new wxDataViewEvent());
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
	liste_membres=new Frame_afficher_liste_membres(this,bdd,0);
}

void Frame_admin::onSupprimer(wxCommandEvent &evenement)
{
	liste_membres=new Frame_afficher_liste_membres(this,bdd,2);	
}

void Frame_admin::onModifier(wxCommandEvent &evenement)
{
	liste_membres=new Frame_afficher_liste_membres(this,bdd,1);
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
		//this->Afficher_liste(*new wxDataViewEvent());
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

void Frame_admin::Afficher_liste(wxDataViewEvent &evenement)
{
	std::string texte_req="SELECT eleves.id AS id,eleves.nom AS nom,eleves.prenom AS prenom, classes.nom AS classe, 0 AS pas_dappreciation, commentaires.commentaire AS commentaire,classes.id AS id_classe FROM commentaires JOIN eleves ON commentaires.id_eleve=eleves.id JOIN classes ON classes.id=eleves.classe WHERE id_matiere=-1 UNION SELECT eleves.id AS id,eleves.nom AS nom,eleves.prenom AS prenom, classes.nom AS classe, 1 AS pas_dappreciation, '' AS commentaire, classes.id AS id_classe FROM eleves JOIN classes ON classes.id=eleves.classe";
	
	if(ordre_colonne3!=0) texte_req+=" ORDER BY commentaire";
	else if(ordre_colonne2!=0) texte_req+=" ORDER BY nom";
	else if(ordre_colonne3!=0) texte_req+=" ORDER BY id_classe";
	else texte_req+=" ORDER BY id";
	
	if(ordre_colonne4==-1 || ordre_colonne3==-1 || ordre_colonne2==-1 || ordre_colonne1==-1) texte_req+=" DESC";
	
	wxVector<wxVariant> ligne;//wxWidgets à besoin d'un vecteur pour créer une ligne. Ce vecteurs doit contenir les champs des colonnes de cette ligne
	std::map<int,int> liste_eleve;
	liste_appreciations->DeleteAllItems();
	liste_eleve.clear();
	for(int i=0;i<4;i++) ligne.push_back(wxVariant(""));//on crée une ligne avec que des colonnes vides
    
	
	while(bdd->exec(texte_req))
	{
		if(liste_eleve.find(bdd->getColumn_int(0))==liste_eleve.end())
		{
			ligne[0]=wxVariant(wxString::Format("%d",bdd->getColumn_int(0)));//on effectue l'ajout de la ligne
			
			liste_appreciations->AppendItem(ligne);
			liste_eleve[bdd->getColumn_int(0)]=liste_appreciations->GetItemCount()-1;			
		}
	
		liste_appreciations->SetTextValue(std::string(bdd->getColumn_text(2))+" "+std::string(bdd->getColumn_text(1)),liste_eleve[bdd->getColumn_int(0)],1);//le nom d'un élève
		liste_appreciations->SetTextValue(std::string(bdd->getColumn_text(3)),liste_eleve[bdd->getColumn_int(0)],2);//La classe
	
		if(bdd->getColumn_int(4)==0) liste_appreciations->SetTextValue(std::string(bdd->getColumn_text(5)),liste_eleve[bdd->getColumn_int(0)],3);// l'appréciation, si il y en a une		
	}
}


void Frame_admin::onChange_commentaires(wxDataViewEvent &evenement)
{
	if(evenement.GetColumn()!=3) return ;
	
	liste_appreciations->GetSelectedRow();
	
	int id_tmp=wxAtoi(liste_appreciations->GetTextValue(liste_appreciations->GetSelectedRow(),0));
	bool deja_en_bdd=false;
	
	std::string appreciation=std::string(liste_appreciations->GetTextValue(liste_appreciations->GetSelectedRow(),3)),texte_req;
	
	requete_sql* req=bdd->prepare("SELECT count(*) from commentaires WHERE id_eleve=:id_eleve AND id_matiere=-1");
	req->bind(":id_eleve",id_tmp);
	req->fetch();
	deja_en_bdd=(req->getColumn_int(0)==0)?false:true;
	req->closeCursor();
	
	if(deja_en_bdd && appreciation.empty()) texte_req="DELETE FROM commentaires WHERE id_eleve=:id_eleve AND id_matiere=-1";
	else if(!deja_en_bdd && !appreciation.empty()) texte_req="INSERT INTO commentaires VALUES (-1,:id_eleve,:commentaire)";
	else if(!appreciation.empty()) texte_req="UPDATE commentaires SET commentaire=:commentaire WHERE id_eleve=:id_eleve AND id_matiere=-1";
	else return ;

	req=bdd->prepare(texte_req);
	req->bind(":id_eleve",id_tmp);
	if(!appreciation.empty())  req->bind(":commentaire",appreciation);
	
	req->fetch();
	req->closeCursor();
}

void Frame_admin::onChanger_ordre(wxDataViewEvent &evenement)
{
	int col = evenement.GetColumn();
	
	if(col==0) 
	{
		ordre_colonne2=0;
		ordre_colonne3=0;
		ordre_colonne4=0;
		if(ordre_colonne1!=1) ordre_colonne1=1;
		else ordre_colonne1=-1;
	}
	else if(col==1)
	{	
		ordre_colonne1=0;
		ordre_colonne3=0;
		ordre_colonne4=0;
		if(ordre_colonne2!=1) ordre_colonne2=1;
		else ordre_colonne2=-1;
	}
	else if(col==1)
	{
		ordre_colonne1=0;
		ordre_colonne2=0;
		ordre_colonne4=0;
		if(ordre_colonne3!=1) ordre_colonne3=1;
		else ordre_colonne3=-1;
	}
	else 
	{
		ordre_colonne1=0;
		ordre_colonne2=0;
		ordre_colonne3=0;
		if(ordre_colonne4!=1)ordre_colonne4=1;
		else ordre_colonne4=-1;
	}
	
	this->Afficher_liste(*new wxDataViewEvent());
}


void Frame_admin::onDbclick_commentaires(wxDataViewEvent &evenement)
{
	if(evenement.GetColumn()!=3) return ;
		
	wxDataViewItem item=liste_appreciations->GetCurrentItem();
	wxDataViewColumn *colonne=evenement.GetDataViewColumn();
	
	liste_appreciations->EditItem(item,colonne);
}