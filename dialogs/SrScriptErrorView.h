#ifndef __SRSCRIPTERRORVIEW_H
#define __SRSCRIPTERRORVIEW_H


class CSrScriptView;


class CSrScriptErrorView : public CFormView 
{
	DECLARE_DYNCREATE(CSrScriptErrorView);

protected:
	CSrScriptView*	m_pScriptView;
	bool			m_HasDblClick;

	HACCEL			m_hAccelerator;


protected:

	CSrScriptErrorView();
	virtual ~CSrScriptErrorView();

public:

	void ClearErrors (void);
	void AddError    (CSrScriptError* pError);
	void AddErrors   (CSrScriptErrorArray& Errors);
	void AddMessage  (const char* pString, ...);

	void SetErrorText (const char* pString);

	CSrScriptError* FindErrorFromLine (const int Line);

	void SetScriptView (CSrScriptView* pView) { m_pScriptView = pView; }

	enum { IDD = IDD_SCRIPTERROR_VIEW };
	CRichEditCtrl	m_ErrorText;
  
public:
	virtual void OnInitialUpdate();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDblclkErrortext(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMsgfilterErrortext(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu (CWnd* pWnd, CPoint Point);
	afx_msg void OnErrorbarCopy();
	afx_msg void OnUpdateErrorbarCopy(CCmdUI *pCmdUI);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnErrorCopy();
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);

	DECLARE_MESSAGE_MAP();

};


#endif
