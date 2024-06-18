
// convertDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "convert.h"
#include "convertDlg.h"
#include "afxdialogex.h"

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


// CconvertDlg 对话框



CconvertDlg::CconvertDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONVERT_DIALOG, pParent)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CconvertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FORMAT, m_combo_format);
	DDX_Control(pDX, IDC_SEARCH_LIST, m_list_filter);
	DDX_Control(pDX, IDC_SELECT_LIST, m_selected_list);
	DDX_Control(pDX, IDC_CHECK_SAME_PATH, m_save_same_path);
	DDX_Control(pDX, IDC_COMBO_FORMAT2, m_save_format);
	DDX_Control(pDX, IDC_CHECK_RENAME, m_check_rename_index);

}

BEGIN_MESSAGE_MAP(CconvertDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SRC_FILE, &CconvertDlg::OnBnClickedButtonSrcFile)
	ON_BN_CLICKED(IDC_BUTTON2, &CconvertDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CconvertDlg::OnBnClickedButtonClear)

	ON_LBN_DBLCLK(IDC_SEARCH_LIST, &CconvertDlg::OnLbnDblclkSearchList)
	ON_BN_CLICKED(IDC_BUTTON_SELECT, &CconvertDlg::OnBnClickedButtonSelect)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR2, &CconvertDlg::OnBnClickedButtonClear2)

	ON_BN_CLICKED(IDC_BUTTON_CONVERT, &CconvertDlg::OnBnClickedButtonConvert)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_FOLDER, &CconvertDlg::OnBnClickedButtonSaveFolder)
END_MESSAGE_MAP()


// CconvertDlg 消息处理程序

BOOL CconvertDlg::OnInitDialog()
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

	m_combo_format.SetCurSel(0);
	m_save_format.SetCurSel(0);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CconvertDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CconvertDlg::OnPaint()
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
HCURSOR CconvertDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CconvertDlg::OnBnClickedButtonSrcFile()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fileDialog(TRUE, _T("txt"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
		_T("所有文件 (*.*)|*.*||"), this);

	if (fileDialog.DoModal() == IDOK)
	{
		// 获取用户选择的文件路径 
		CString filePath = fileDialog.GetPathName();
		search_list_f.push_back(filePath.GetString());
		CString filename = fileDialog.GetFileName();
		search_list.push_back(filename.GetString());
		
		int nSel = m_combo_format.GetCurSel();
		if (nSel != CB_ERR)
		{
			CString str;
			m_combo_format.GetLBText(nSel, str); // 根据索引获取文本
			filter_list.clear();
			filter_list_f.clear();
			m_list_filter.ResetContent();
			FilterFiles(str.GetString());
		}
		else
		{
			AfxMessageBox(_T("没有选中任何格式"));
		}
	}
}


void CconvertDlg::OnBnClickedButton2()
{
	BROWSEINFO bi = { 0 };
	TCHAR pszPath[MAX_PATH] = { 0 };
	LPITEMIDLIST pidl = NULL;

	// 设置浏览信息  
	bi.hwndOwner = this->m_hWnd; // 使用对话框的句柄作为拥有者  
	bi.pidlRoot = NULL; // 从桌面开始浏览  
	bi.pszDisplayName = pszPath;
	bi.lpszTitle = _T("请选择文件夹");
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE; // 只返回文件夹  
	bi.lpfn = NULL; // 不使用回调函数  
	bi.lParam = 0; // 传递给回调函数的参数  

	// 显示文件夹浏览对话框  
	pidl = SHBrowseForFolder(&bi);

	if (pidl != NULL)
	{
		// 将ITEMIDLIST转换为路径  
		if (SHGetPathFromIDListW(pidl, pszPath))
		{
			// 将路径保存到成员变量中  
			SelectFolder = pszPath;
			SaveFolder = pszPath;
			// 更新UI或进行其他操作  
			//AfxMessageBox(_T("你选择了文件夹: ") + SelectFolder);
		}

		// 释放ITEMIDLIST内存  
		CoTaskMemFree(pidl);
	}
	search_list.clear();
	search_list_f.clear();
	ListFilesInDirectory(SelectFolder.GetString());
	int nSel = m_combo_format.GetCurSel();
	if (nSel != CB_ERR)
	{
		CString str;
		m_combo_format.GetLBText(nSel, str); // 根据索引获取文本
		filter_list.clear();
		filter_list_f.clear();
		m_list_filter.ResetContent();
		FilterFiles(str.GetString());
	}
	else
	{
		AfxMessageBox(_T("没有选中任何格式"));
	}
	
}


void CconvertDlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list_filter.ResetContent();
}

void CconvertDlg::ListFilesInDirectory(const std::wstring& path)
{
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	std::wstring search_path = path + L"\\*";

	HANDLE hFind = FindFirstFile(search_path.c_str(), &ffd);
	if (hFind == INVALID_HANDLE_VALUE) {
		std::cerr << "Error finding files: " << GetLastError() << std::endl;
		return;
	}

	while (1)
	{
		if (ffd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY && wcscmp(ffd.cFileName, L".") != 0 && wcscmp(ffd.cFileName, L"..") != 0)
		{
			std::wcout << "[dir]" << path + L"\\" + ffd.cFileName << std::endl;
			std::wstring next_search_path = path + L"\\" + ffd.cFileName;
			ListFilesInDirectory(next_search_path);
		}
		if (wcscmp(ffd.cFileName, L".") == 0 || wcscmp(ffd.cFileName, L"..") == 0)
		{
			std::wcout << "[...]" << path + L"\\" + ffd.cFileName << std::endl;
		}

		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
		{
			std::wcout << "[archive]" << path + L"\\" + ffd.cFileName << std::endl;
			search_list.push_back(ffd.cFileName);
			search_list_f.push_back(path + L"\\" + ffd.cFileName);
			
		}

		if (FindNextFile(hFind, &ffd) == 0)
		{
			break;
		}
	}

	FindClose(hFind);
}

void CconvertDlg::FilterFiles(const std::wstring& f_format)
{
	filter_list.clear();
	for(int i=0;i<search_list.size();i++)
	{
		if (search_list[i].length() >= f_format.length())
		{
			if (f_format == search_list[i].substr(search_list[i].length() - f_format.length()))
			{
				filter_list.push_back(search_list[i]);
				filter_list_f.push_back(search_list_f[i]);
			}
		}
		
	}
	if (filter_list.size() > 0)
	{
		
			for (int i = 0; i < filter_list.size(); i++)
			{
				//pListBox->AddString(filter_list[i].c_str()); // 添加数据  
				m_list_filter.InsertString(-1, filter_list[i].c_str());
			}			

	
	}
	
}

bool CconvertDlg::CheckSelectedList(const std::wstring& f_format)
{
	for (int i = 0; i < select_list_f.size(); i++)
	{
		if (f_format == select_list_f[i])
		{
			return true;
		}
	}
	return false;
}
void CconvertDlg::OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CconvertDlg::OnLbnDblclkSearchList()
{
	// TODO: 在此添加控件通知处理程序代码
	int nSel = m_list_filter.GetCurSel();
	if (nSel != LB_ERR) // 确保获取到了有效的索引（LB_ERR 表示没有选中任何项）  
	{
		if (false == CheckSelectedList(filter_list_f[nSel]))
		{
			select_list.push_back(filter_list[nSel]);
			select_list_f.push_back(filter_list_f[nSel]);
			m_selected_list.InsertString(-1, filter_list[nSel].c_str());
		}
				
	}
	

}


void CconvertDlg::OnBnClickedButtonSelect()
{
	// TODO: 在此添加控件通知处理程序代码
	int count = m_list_filter.GetSelCount();
	if (count > 0)
	{
		int* indices = new int[count]; // 分配内存来存储选中的项的索引  
		m_list_filter.GetSelItems(count, indices); // 获取选中的项的索引  

		// 遍历选中的项并获取它们的文本  
		for (int i = 0; i < count; i++)
		{
			if (false == CheckSelectedList(filter_list_f[indices[i]]))
			{
				select_list.push_back(filter_list[indices[i]]);
				select_list_f.push_back(filter_list_f[indices[i]]);
				m_selected_list.InsertString(-1, filter_list[indices[i]].c_str());
			}
		}

		delete[] indices; // 释放之前分配的内存  
	}
	else
	{
		AfxMessageBox(_T("没有选中任何项"));
	}
}


void CconvertDlg::OnBnClickedButtonClear2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_selected_list.ResetContent();
	select_list.clear();
	select_list_f.clear();
}


void CconvertDlg::OnBnClickedButtonClear3()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CconvertDlg::OnBnClickedButtonConvert()
{
	// TODO: 在此添加控件通知处理程序代码\

	std::wstring infname, outfname,midfname;
	//std::string infname_s, outfname_s;
	CString str_i_f, str_o_f;
	std::wstring i_f, o_f,m_f;
	
	//m_f = "flv";
	int nSel = m_combo_format.GetCurSel();
	if (nSel != CB_ERR)
	{

		m_combo_format.GetLBText(nSel, str_i_f); // 根据索引获取文本	
		i_f = str_i_f.GetString();
	}

	nSel = m_save_format.GetCurSel();
	if (nSel != CB_ERR)
	{

		m_save_format.GetLBText(nSel, str_o_f); // 根据索引获取文本	
		o_f = str_o_f.GetString();
	}
	
	SaveFolder = SaveFolder + L"\\";
	for (int i = 0; i < select_list_f.size(); i++)
	{
		if (m_save_same_path.GetCheck())
		{
			infname = select_list_f[i];
			outfname = select_list_f[i];
			midfname = select_list_f[i];

			if (m_check_rename_index.GetCheck())
			{
				outfname.replace(0,outfname.length() - i_f.length()-1, IntToWstring(m_index++));
			}
			
			outfname.replace(outfname.length() - i_f.length(), i_f.length(), o_f);
			
			

			midfname.replace(outfname.length() - i_f.length(), i_f.length(), L"flv");
		}
		else
		{
			infname = select_list_f[i];
			outfname = select_list[i];
			midfname = select_list[i];
			if (m_check_rename_index.GetCheck())
			{
				outfname.replace(0, outfname.length() - i_f.length() - 1, IntToWstring(m_index++));				
			}
			
			outfname.replace(outfname.length() - i_f.length(), i_f.length(), o_f);
			

			//outfname.replace(outfname.length() - i_f.length(), i_f.length(), o_f);
			midfname.replace(outfname.length() - i_f.length(), i_f.length(), L"flv");
			//SaveFolder = SaveFolder + L"\\";
			outfname = SaveFolder.GetString()+ outfname;
			midfname = SaveFolder.GetString() +  midfname;
		}
		int size = WideCharToMultiByte(CP_UTF8, 0, infname.c_str(), -1, nullptr, 0, nullptr, nullptr);
		std::string infname_s(size, 0);
		WideCharToMultiByte(CP_UTF8, 0, infname.c_str(), -1, &infname_s[0], size, nullptr, nullptr);


		size = WideCharToMultiByte(CP_UTF8, 0,midfname.c_str(), -1, nullptr, 0, nullptr, nullptr);
		std::string midfname_s(size, 0);
		WideCharToMultiByte(CP_UTF8, 0, midfname.c_str(), -1, &midfname_s[0], size, nullptr, nullptr);

		size = WideCharToMultiByte(CP_UTF8, 0, outfname.c_str(), -1, nullptr, 0, nullptr, nullptr);
		std::string outfname_s(size, 0);
		WideCharToMultiByte(CP_UTF8, 0, outfname.c_str(), -1, &outfname_s[0], size, nullptr, nullptr);
		

		remove(outfname_s.c_str());
		extract_media(infname_s.c_str(), midfname_s.c_str());

		cmd_convert(midfname_s.c_str(), outfname_s.c_str());
		remove(midfname_s.c_str());
	}
	
}


void CconvertDlg::OnBnClickedButtonSaveFolder()
{
	// TODO: 在此添加控件通知处理程序代码
	BROWSEINFO bi = { 0 };
	TCHAR pszPath[MAX_PATH] = { 0 };
	LPITEMIDLIST pidl = NULL;

	// 设置浏览信息  
	bi.hwndOwner = this->m_hWnd; // 使用对话框的句柄作为拥有者  
	bi.pidlRoot = NULL; // 从桌面开始浏览  
	bi.pszDisplayName = pszPath;
	bi.lpszTitle = _T("请选择文件夹");
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE; // 只返回文件夹  
	bi.lpfn = NULL; // 不使用回调函数  
	bi.lParam = 0; // 传递给回调函数的参数  

	// 显示文件夹浏览对话框  
	pidl = SHBrowseForFolder(&bi);

	if (pidl != NULL)
	{
		// 将ITEMIDLIST转换为路径  
		if (SHGetPathFromIDListW(pidl, pszPath))
		{
			// 将路径保存到成员变量中  			
			SaveFolder = pszPath;
			// 更新UI或进行其他操作  
			//AfxMessageBox(_T("你选择了文件夹: ") + SelectFolder);
		}

		// 释放ITEMIDLIST内存  
		CoTaskMemFree(pidl);
	}
}

void CconvertDlg::cmd_convert(std::string infname, std::string outfname)
{

	// 构建FFmpeg命令
	//ffmpeg -i input.flv -c:v libx264 -crf 23 -c:a aac -strict experimental -b:a 192k output.mp4
	//std::string command = "ffmpeg -i " + std::string(infname) + " " + std::string(outfname)
	std::string command = "ffmpeg -i " + std::string(infname) + " -c:v libx264 -crf 30 -c:a aac -strict experimental -b:a 192k " + std::string(outfname);
	//std::string command = "ffmpeg -i " + std::string(infname) + "-c:v h264_qsv -crf 23 -c:a aac -strict experimental -b:a 192k " + std::string(outfname);
	//-c:v h264_qsv
	// 执行命令
	int ret = std::system(command.c_str());

	if (ret == 0) {
		std::cout << "转换成功" << std::endl;
	}
	else {
		std::cout << "转换失败，错误码：" << ret << std::endl;
	}


}

std::wstring CconvertDlg::IntToWstring(int value) {

	std::wstringstream wss;

	wss.imbue(std::locale("")); // 设置本地化设置，以便正确显示数字（例如，逗号作为千位分隔符）  

	//wss << value;
	wss << std::setw(2) << std::setfill(L'0') << value;

	return wss.str();

}