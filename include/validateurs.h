#ifndef HEADERS_INCLUS_VALIDATEURS
	#define HEADERS_INCLUS_VALIDATEURS
	
	#include <wx/wx.h>
	#include <wx/regex.h>		//regexp
	
	class wxTextRegexpValidator : public wxTextValidator//Classe permettant un wxValidator via regexp
	{
		protected:
		   wxRegEx m_regEx;
		   wxString m_regexp_texte;

		public:
		   wxTextRegexpValidator(wxString regexp, wxString* valeur = NULL);
		   ~wxTextRegexpValidator(){}

		   wxObject* Clone() const;

		   virtual bool TransferToWindow();
		   virtual bool TransferFromWindow();
	};

	
#endif