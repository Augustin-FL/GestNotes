#ifndef HEADERS_INCLUS_IMPRIMER_BULETIN
	#define HEADERS_INCLUS_IMPRIMER_BULETIN
	
	#include <wx/wxhtml.h>
	#include <wx/wfstream.h> 	//FileOutputStream


	
	
	#include "bdd.h"

	class Frame_imprimer_buletins;
	
	
	class Frame_imprimer_buletins : public wxFrame
	{
		public:
			Frame_imprimer_buletins(wxWindow* parent_arg, connexion_bdd*& bdd_arg);
			~Frame_imprimer_buletins(){}
			wxString generer_html5();

			void onEnregistrer(wxCommandEvent& evenement);
			void onImprimer(wxCommandEvent& evenement);

		private:
			wxWindow* parent;
			connexion_bdd* bdd;
			wxHtmlWindow* fenetre_html;
	};
	
#endif