
// 连元小学学生成绩管理系统MFCDlg.cpp: 实现文件
//
#include <sqlite3.h>
#include <vector>
#include <ctime>
#include <iomanip>
#include <string>
#include "class.h"
#include "grade.h"
#include "sqlite_api.h"
#include "school.h"
#include "student.h"
#include "pch.h"
#include "framework.h"
#include "连元小学学生成绩管理系统MFC.h"
#include "连元小学学生成绩管理系统MFCDlg.h"
#include "afxdialogex.h"
#include <atlconv.h>  

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C连元小学学生成绩管理系统MFCDlg 对话框



C连元小学学生成绩管理系统MFCDlg::C连元小学学生成绩管理系统MFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_DIALOG, pParent)
	, m_edit_str(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C连元小学学生成绩管理系统MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1_NAME, m_edit_show);
	DDX_Text(pDX, IDC_EDIT1_NAME, m_edit_str);
	DDX_Control(pDX, IDC_COMBO1, m_ComBoxText);
	DDX_Control(pDX, IDC_EDIT2_ID, m_show_id);
	DDX_Control(pDX, IDC_EDIT3_CHINESE, m_show_chinese);
	DDX_Control(pDX, IDC_EDIT4_MATHS, m_show_maths);
	DDX_Control(pDX, IDC_EDIT5_ENGLISH, m_show_english);
	DDX_Control(pDX, IDC_COMBO2, m_ComBoxText_class);
	DDX_Control(pDX, IDC_STATIC_11, m_static11_result_show);
}

BEGIN_MESSAGE_MAP(C连元小学学生成绩管理系统MFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C连元小学学生成绩管理系统MFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C连元小学学生成绩管理系统MFCDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1_NAME, &C连元小学学生成绩管理系统MFCDlg::OnEnChangeEdit1Name)
	ON_CBN_SELCHANGE(IDC_COMBO1, &C连元小学学生成绩管理系统MFCDlg::OnCbnSelchangeCombo1)
	ON_EN_CHANGE(IDC_EDIT2_ID, &C连元小学学生成绩管理系统MFCDlg::OnEnChangeEdit2Id)
	ON_CBN_SELCHANGE(IDC_COMBO2, &C连元小学学生成绩管理系统MFCDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &C连元小学学生成绩管理系统MFCDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON4_DELETE, &C连元小学学生成绩管理系统MFCDlg::OnBnClickedButton4Delete)
	ON_BN_CLICKED(IDC_RADIO1_INSERT, &C连元小学学生成绩管理系统MFCDlg::OnBnClickedRadio1Insert)
	ON_BN_CLICKED(IDC_RADIO2_SEARCH_OR_DELETE, &C连元小学学生成绩管理系统MFCDlg::OnBnClickedRadio2SearchOrDelete)
	ON_EN_CHANGE(IDC_EDIT3_CHINESE, &C连元小学学生成绩管理系统MFCDlg::OnEnChangeEdit3Chinese)
	ON_STN_CLICKED(IDC_STATIC_10, &C连元小学学生成绩管理系统MFCDlg::OnStnClickedStatic10)
	ON_STN_CLICKED(IDC_STATIC_11, &C连元小学学生成绩管理系统MFCDlg::OnStnClickedStatic11)
	ON_BN_CLICKED(IDC_BUTTON20_HELPS, &C连元小学学生成绩管理系统MFCDlg::OnBnClickedButton20Helps)
END_MESSAGE_MAP()
vector<CStudent> StudentVector;
CSqlite_api sql;
sqlite3* db = NULL;
int rc = SQLITE_ERROR;

// C连元小学学生成绩管理系统MFCDlg 消息处理程序

BOOL C连元小学学生成绩管理系统MFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	rc = sqlite3_open("james_student++.db", &db);
	if (rc == SQLITE_ERROR) {
		MessageBox(_T("数据库打开失败!\n请退出重试!"));
		sqlite3_log(sqlite3_errcode(db), "open failed\n");
	}
	    rc=sql.creat_table(db);
		//if (rc == SQLITE_ERROR) {
		//	MessageBox(_T("table build faild:please try to continue"));
		//}
	
		rc=sql.initialize(db,StudentVector);
		if (rc==SQLITE_ERROR) {
			MessageBox(_T("初始化失败:请退出重试"));
		}
		/*else {
			MessageBox(_T("初始化成功"));
		}*/

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C连元小学学生成绩管理系统MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
CStudent student;
int num = time(nullptr) / 8;

void C连元小学学生成绩管理系统MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C连元小学学生成绩管理系统MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void C连元小学学生成绩管理系统MFCDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString namecs;
	CString idcs, cChinese, cMaths, cEnglish;

	int index_grade = m_ComBoxText.GetCurSel();
	CString cGrade;
	m_ComBoxText.GetLBText(index_grade, cGrade);
	std::string sGrade = CT2A(cGrade.GetString());
	int grade = std::stoi(sGrade);

	int index_class = m_ComBoxText_class.GetCurSel();
	CString cClass;
	m_ComBoxText_class.GetLBText(index_class, cClass);
	std::string sClass = CT2A(cClass.GetString());
	int iClass = std::stoi(sClass);


	m_edit_show.GetWindowTextW(namecs);
	m_show_id.GetWindowTextW(idcs);
	m_show_chinese.GetWindowTextW(cChinese);
	m_show_maths.GetWindowTextW(cMaths);
	m_show_english.GetWindowTextW(cEnglish);

	std::string name = CT2A(namecs.GetString());
	std::string ids= CT2A(idcs.GetString());
	if (ids == "") {
		MessageBox(_T("请输入学号!"));
		return;
	}
	int id = std::stoi(ids);
	std::string chineses = CT2A(cChinese.GetString());
	if (chineses == "") {
		MessageBox(_T("请输入语文成绩!"));
		return;
	}
	int chinese = std::stoi(chineses);
	std::string mathss = CT2A(cMaths.GetString());
	if (mathss == "") {
		MessageBox(_T("请输入数学成绩!"));
		return;
	}
	int maths= std::stoi(mathss);
	std::string englishs = CT2A(cEnglish.GetString());
	if (englishs == "") {
		MessageBox(_T("请输入英语成绩!"));
		return;
	}
	int english = std::stoi(englishs);
	student.set_ch(chinese);
	student.set_ms(maths);
	student.set_en(english);
	student.set_id(id);
	student.set_name(name);
	student.set_grade(grade);
	student.set_cla(iClass);

	for (int i = 0; i < StudentVector.size(); i++) {
		if (StudentVector[i].get_gra() == student.get_gra()) {
			if (StudentVector[i].get_cla() == student.get_cla()) {
				if (StudentVector[i].get_id() == student.get_id()) {
					StudentVector.erase(StudentVector.begin() + i);
					sql.sql_delete(db,student.get_gra(),student.get_cla(), student.get_id());

				}

			}
		}
	}

	StudentVector.push_back(student);
	rc=sql.insert_sql(db, grade, iClass, name, id, chinese, maths, english);
	if (rc == SQLITE_ERROR) {
		MessageBox(_T("数据插入失败！\n " ));

	}
	else {
		MessageBox(_T("数据插入成功！\n "));
	}

}

void C连元小学学生成绩管理系统MFCDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("学生成绩管理系统\n\n版本:1.1.0 beta3\n作者:James"));
}

void C连元小学学生成绩管理系统MFCDlg::OnEnChangeEdit1Name()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码;


}

void C连元小学学生成绩管理系统MFCDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	
}

void C连元小学学生成绩管理系统MFCDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void C连元小学学生成绩管理系统MFCDlg::OnEnChangeEdit2Id()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void C连元小学学生成绩管理系统MFCDlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
}

//void C连元小学学生成绩管理系统MFCDlg::OnBnClickedButton0()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	int close = MessageBox(L"是否退出？", L"提示", MB_YESNO | MB_ICONQUESTION);
//	if (close == IDYES)
//	{
//		CDialogEx::OnCancel();
//	}
//}
//
//void C连元小学学生成绩管理系统MFCDlg::OnBnClickedButton3()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}

void C连元小学学生成绩管理系统MFCDlg::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	m_static11_result_show.SetWindowTextW(_T(" "));
	GetDlgItem(IDC_EDIT1_NAME)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT3_CHINESE)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT4_MATHS)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT5_ENGLISH)->SetWindowTextW(_T(""));
	CString namecs;
	CString idcs, cChinese, cMaths, cEnglish;

	int index_grade = m_ComBoxText.GetCurSel();
	CString cGrade;
	m_ComBoxText.GetLBText(index_grade, cGrade);
	std::string sGrade = CT2A(cGrade.GetString());
	int grade = std::stoi(sGrade);

	int index_class = m_ComBoxText_class.GetCurSel();
	CString cClass;
	m_ComBoxText_class.GetLBText(index_class, cClass);
	std::string sClass = CT2A(cClass.GetString());
	int iClass = std::stoi(sClass);

	m_show_id.GetWindowTextW(idcs);
	std::string ids = CT2A(idcs.GetString());
	if (ids == "") {
		MessageBox(_T("请输入学号!"));
		return;
	}
	int id = std::stoi(ids);
	
	bool bfound = false;
	
	
	for (auto it = StudentVector.begin(); it != StudentVector.end(); ++it) {
		if (it->get_gra() == grade) {
			if (it->get_cla() == iClass) {
				if (it->get_id() == id) {
					bfound = true;
					m_static11_result_show.SetWindowTextW(_T("查询成功!"));
					CString csName= CString(it->get_name().c_str());
					GetDlgItem(IDC_EDIT1_NAME)->SetWindowTextW(csName);
					SetDlgItemInt(IDC_EDIT3_CHINESE,it->get_ch());
					SetDlgItemInt(IDC_EDIT4_MATHS, it->get_ms());
					SetDlgItemInt(IDC_EDIT5_ENGLISH, it->get_en());



				}
			}
		}
	}
	if (!bfound) {
		m_static11_result_show.SetWindowTextW(_T("查无此人!"));
	}

}

void C连元小学学生成绩管理系统MFCDlg::OnBnClickedButton4Delete()
{
	// TODO: 在此添加控件通知处理程序代码
	m_static11_result_show.SetWindowTextW(_T(" "));
	GetDlgItem(IDC_EDIT1_NAME)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT3_CHINESE)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT4_MATHS)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT5_ENGLISH)->SetWindowTextW(_T(""));
	CString namecs;
	CString idcs, cChinese, cMaths, cEnglish;
	int index_grade = m_ComBoxText.GetCurSel();
	CString cGrade;
	m_ComBoxText.GetLBText(index_grade, cGrade);
	std::string sGrade = CT2A(cGrade.GetString());
	int grade = std::stoi(sGrade);

	int index_class = m_ComBoxText_class.GetCurSel();
	CString cClass;
	m_ComBoxText_class.GetLBText(index_class, cClass);
	std::string sClass = CT2A(cClass.GetString());
	int iClass = std::stoi(sClass);

	m_show_id.GetWindowTextW(idcs);
	std::string ids = CT2A(idcs.GetString());
	if (ids == "") {
		MessageBox(_T("请输入学号!"));
		return;
	}
	int id = std::stoi(ids);
	bool bfound=false;
	student.set_id(id);
	student.set_grade(grade);
	student.set_cla(iClass);
	for (int i = 0; i < StudentVector.size(); i++) {
		if (StudentVector[i].get_gra() == student.get_gra()) {
			if (StudentVector[i].get_cla() == student.get_cla()) {
				if (StudentVector[i].get_id() == student.get_id()) {
					bfound = true;
					StudentVector.erase(StudentVector.begin() + i);
					rc=sql.sql_delete(db, student.get_gra(), student.get_cla(), student.get_id());

				}

			}
		}
	}
	if (!bfound) {
		m_static11_result_show.SetWindowTextW(_T("查无此人!"));
	}
}



void C连元小学学生成绩管理系统MFCDlg::OnBnClickedRadio1Insert()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_BUTTON4_DELETE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SEARCH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT1_NAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT3_CHINESE)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT4_MATHS)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT5_ENGLISH)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_10)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_11)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT1_NAME)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT2_ID)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT3_CHINESE)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT4_MATHS)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT5_ENGLISH)->SetWindowTextW(_T(""));
}

void C连元小学学生成绩管理系统MFCDlg::OnBnClickedRadio2SearchOrDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_BUTTON4_DELETE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_SEARCH)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT1_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT3_CHINESE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT4_MATHS)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT5_ENGLISH)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_10)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_11)->ShowWindow(SW_SHOW);
	m_static11_result_show.SetWindowTextW(_T(" "));
	GetDlgItem(IDC_EDIT1_NAME)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT2_ID)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT3_CHINESE)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT4_MATHS)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT5_ENGLISH)->SetWindowTextW(_T(""));

}

void C连元小学学生成绩管理系统MFCDlg::OnEnChangeEdit3Chinese()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void C连元小学学生成绩管理系统MFCDlg::OnStnClickedStatic10()
{
	// TODO: 在此添加控件通知处理程序代码
}

void C连元小学学生成绩管理系统MFCDlg::OnStnClickedStatic11()
{
	// TODO: 在此添加控件通知处理程序代码
}

void C连元小学学生成绩管理系统MFCDlg::OnBnClickedButton20Helps()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("帮助:\n\n1:如果遇到显示参数错误,请用如下方法输入:\n     1、下拉框请用弹出的下拉框选择,无需手动输入\n     2、请确认所有能输入的框都填写完毕"));
}
