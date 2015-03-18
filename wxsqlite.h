#ifndef WX_SQLITE_H
#define WX_SQLITE_H

#pragma warning( disable : 4101 4786)

#include <wx/thread.h>
#include <wx/string.h>
#include <wx/datetime.h>
#include <wx/hashmap.h>

#if defined(__GNUG__) && !defined(__APPLE__)
    #pragma interface "wxsqlite.h"
#endif

const char *wxSQLiteVersion();

typedef struct sqlite sqlite;
typedef struct sqlite_vm sqlite_vm;
class wxSQLiteException;

class wxSQLiteDatabase
{
private:
    friend class wxSQLiteDatabaseLocker;
	sqlite              *db;
    wxCriticalSection   csDB;

public:
	int			m_lastIErr;
	wxString	m_lastErr;

	wxSQLiteDatabase(wxString fname = wxT(""));
	~wxSQLiteDatabase();

	bool Open(wxString fname);
	bool Close();

	bool Ok() const {return db != NULL;};

	bool TableExists(wxString tableName);
	void BeginTransaction();
	void Commit();
	void Rollback();
	int LastInsertRowId();
};


class wxSQLiteQueryBase
{
public:
	WX_DECLARE_STRING_HASH_MAP(int, ColNamesMap);

protected:
	wxSQLiteDatabase& db;


	ColNamesMap colNames;

	wxSQLiteQueryBase(wxSQLiteDatabase& db);
	void InitCols(const char **pazColNames, int ncols);

public:
    int         m_lastIErr;
	wxString    m_lastErr;

	int GetFieldIndex(wxString fieldName);		// returns -1 if not found

    class TField
    {
    private:
        const char *data;

    public:
        TField(const char *data) : data(data) {}

        const char * AsChar() const;
        wxString AsString() const;
        long AsLong() const;
        bool AsBool() const;
        wxDateTime AsDate() const;
    };
};

class wxSQLiteQuery : public wxSQLiteQueryBase
{
private:
    sqlite_vm	*pVm;
	int			ncol;
	const char	**pazValue;
	const char	**pazColName;

public:
	wxSQLiteQuery(wxSQLiteDatabase& db);
	~wxSQLiteQuery();

	void Close();
    void Prepare(const char *sqlstr, va_list args);
    void Prepare(const char *sqlstr, ...);
    void Exec();
	void Execute(const char *sqlstr, ...);

    void Bind(int idx, const char *value, int len = -1, bool copy = false);

	bool eof() const;
	bool Fetch();
	void Terminate();

    int NumFields() const;
    const char *GetFieldName(int fieldIdx);
    TField Fields(int fieldIdx);
	TField FieldByName(wxString fieldName);	// raise exception if not found

protected:
    void Reset();
};

class wxSQLiteQueryResult : public wxSQLiteQueryBase
{
private:
    char    **result;
    int     nrow;
    int     ncolumn;

public:
	wxSQLiteQueryResult(wxSQLiteDatabase& db);
	~wxSQLiteQueryResult();

	bool Execute(const char *sql, ...);
    int NumChanges();

    int NumRows();
    int NumCols();

    char *GetFieldName(int fieldIdx);
    TField Fields(int rowIdx, int fieldIdx);
	TField FieldByName(int rowIdx, wxString fieldName);	// raise exception if not found
};


class wxSQLiteException
{
public:
	int			m_ierr;
	wxString	m_err;

	wxSQLiteException(wxString err = wxT(""), int ierr = 0) : m_err(err), m_ierr(ierr) {}
	
	wxSQLiteException(const wxSQLiteDatabase& db) :
		m_err(db.m_lastErr),  m_ierr(db.m_lastIErr) {}

	wxSQLiteException(const wxSQLiteQueryBase& q) : 
		m_err(q.m_lastErr),  m_ierr(q.m_lastIErr) {}

	inline operator const wxString& ()  const {return m_err;}
};


#endif

