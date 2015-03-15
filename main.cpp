#include <wx/wx.h>
#include <wx/statline.h>

class App_GestNote : public wxApp
{
	public :
		
	virtual bool OnInit();
	
};
DECLARE_APP(App_GestNote);


class Frame_login : public wxFrame
{
    public:
        Frame_login(const wxString& title) : wxFrame(NULL, wxID_ANY, title)
		{
				wxPanel *panelAffichage = new wxPanel(this, -1);// Création du panel d'affichage
				wxBoxSizer *sizer_intermed = new wxBoxSizer(wxVERTICAL); // Création du wxBoxSizer intermédiaire  
				wxStaticBoxSizer *cadre = new wxStaticBoxSizer(wxVERTICAL, panelAffichage, _T("Informations : ")); // Création du wxStaticBoxSizer pour le cadre
				wxFlexGridSizer *grille = new wxFlexGridSizer(4, 2, 5, 5);// Création du wxFlexGridSizer
    
                wxStaticText *labelNom = new wxStaticText(panelAffichage, -1, _T("Nom :")); // wxStaticText pour le nom
                grille->Add(labelNom, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);
            
                wxTextCtrl *txtNom = new wxTextCtrl(panelAffichage, -1, _T("")); // wxTextCtrl pour le nom
                grille->Add(txtNom, 0, wxEXPAND);
               
                wxStaticText *labelPrenom = new wxStaticText(panelAffichage, -1, _T("aaaaaaaaa :")); // wxStaticText pour le prénom
                grille->Add(labelPrenom, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);
               
                wxTextCtrl *txtPrenom = new wxTextCtrl(panelAffichage, -1, _T(""));
                grille->Add(txtPrenom, 0, wxEXPAND); // wxTextCtrl pour le prénom
          
                wxStaticText *labelDate = new wxStaticText(panelAffichage, -1, _T("Date de naissance :")); // wxStaticText pour la date de naissance
                grille->Add(labelDate, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);
        
                wxTextCtrl *txtDate = new wxTextCtrl(panelAffichage, -1, _T(""));  // wxTextCtrl pour la date de naissance
                grille->Add(txtDate, 0, wxEXPAND);
      
                wxStaticText *labelComm = new wxStaticText(panelAffichage, -1, _T("Commentaires :"));// wxStaticText pour les commentaires
                grille->Add(labelComm, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);
     
                wxTextCtrl *txtComm = new wxTextCtrl(panelAffichage, -1, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
                grille->Add(txtComm, 0, wxEXPAND);// wxTextCtrl pour les commentaires
   
				cadre->Add(grille, 1, wxALL | wxEXPAND, 5);// Ajout de la grille au wxStaticBoxSizer
            
				grille->AddGrowableCol(1);// La deuxième colonne est extensible
				grille->AddGrowableRow(3);  // La quatrième ligne également

				sizer_intermed->Add(cadre, 1, wxALL | wxEXPAND, 5); // Ajout du wxStaticBoxSizer au sizer intermédiaire
      
				wxStaticLine *ligneHoriz = new wxStaticLine(panelAffichage, -1);  // Création de la ligne de séparation horizontale et ajout au sizer intermédiaire
				sizer_intermed->Add(ligneHoriz, 0, wxALL | wxEXPAND, 5);

				wxBoxSizer *sizer_boutons = new wxBoxSizer(wxHORIZONTAL); // Création du wxBoxSizer pour les boutons
   
				wxButton *btnValider = new wxButton(panelAffichage, -1, _T("Valider")); // Création du bouton "Valider"
				sizer_boutons->Add(btnValider, 0);

				sizer_boutons->AddSpacer(5);// Ajout d'un espace entre les deux boutons
    
				wxButton *btnAnnuler = new wxButton(panelAffichage, -1, _T("Annuler"));// Création du bouton "Annuler"
				sizer_boutons->Add(btnAnnuler, 0);

				sizer_intermed->Add(sizer_boutons, 0, wxALIGN_RIGHT | wxALL, 5);  // Ajout du sizer des boutons au sizer intermédiaire
				panelAffichage->SetSizer(sizer_intermed); // Affectation du sizer intermédiaire au wxPanel
			
		}
		
        virtual ~Frame_login(){};
};

IMPLEMENT_APP(App_GestNote);


bool App_GestNote::OnInit()
{
	Frame_login *login=new Frame_login(_T("GestNote"));
	login->Show();
 
    return true;
}

