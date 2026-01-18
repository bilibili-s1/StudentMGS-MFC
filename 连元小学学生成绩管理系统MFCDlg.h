
// 连元小学学生成绩管理系统MFCDlg.h: 头文件
//

#pragma once


// C连元小学学生成绩管理系统MFCDlg 对话框
class C连元小学学生成绩管理系统MFCDlg : public CDialogEx
{
// 构造
public:
	C连元小学学生成绩管理系统MFCDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdit1Name();
	CEdit m_edit_show;
	CString m_edit_str;
	CComboBox m_ComBoxText;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnEnChangeEdit2();
	CEdit m_show_id;
	afx_msg void OnEnChangeEdit2Id();
	CEdit m_show_chinese;
	CEdit m_show_maths;
	CEdit m_show_english;
	afx_msg void OnCbnSelchangeCombo2();
	CComboBox m_ComBoxText_class;
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButton4Delete();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1Insert();
	afx_msg void OnBnClickedRadio2SearchOrDelete();
	afx_msg void OnEnChangeEdit3Chinese();
	afx_msg void OnBnClickedRadio1Inseart();
	afx_msg void OnStnClickedStatic10();
	afx_msg void OnStnClickedStatic11();
	CStatic m_static11_result_show;
	afx_msg void OnBnClickedButton20Helps();
};
