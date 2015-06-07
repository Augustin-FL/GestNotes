#ifndef HEADERS_INCLUS_ELEVE
	#define HEADERS_INCLUS_ELEVE
	
	#include <map>
	#include <wx/wx.h>
	#include <wx/listctrl.h> 	//listcrl et dataviewListCtrl
	
	#include "imprimer_bulletin.h"
	
	#include "main.h"
	#include "admin.h"
	#include "professeur.h"
	#include "eleve.h"
	
	class Frame_eleve : public Frame_principale
	{
		public:
			Frame_eleve(Frame_login* parent,int &matricule,connexion_bdd*& bdd);
			void OnClick_imprimer_buletin(wxCommandEvent &evenement);

		private:
			wxButton *bouton_modifier,*bouton_imprimer_buletin;
			Frame_imprimer_buletins *frame_imprimer_buletin;

	};
	
#endif