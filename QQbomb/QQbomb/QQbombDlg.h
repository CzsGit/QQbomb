
// QQbombDlg.h : ͷ�ļ�
//

#pragma once


// CQQbombDlg �Ի���
class CQQbombDlg : public CDialogEx
{
// ����
public:
	CQQbombDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_QQBOMB_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	HWND m_hFindWnd;
	int m_index;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void SetClipboardWord(wchar_t word);
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_Content;
	CString m_Name;
};
