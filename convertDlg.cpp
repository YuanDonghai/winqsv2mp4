
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
	DDX_Control(pDX, IDC_FAILED_LIST2, m_failed_list);
	DDX_Control(pDX, IDC_CHECK_SAME_PATH, m_save_same_path);
	DDX_Control(pDX, IDC_COMBO_FORMAT2, m_save_format);
	DDX_Control(pDX, IDC_COMBO_CV, m_cv_format);
	DDX_Control(pDX, IDC_COMBO_CRF, m_crf_format);
	DDX_Control(pDX, IDC_COMBO_CA, m_ca_format);
	DDX_Control(pDX, IDC_COMBO_BA, m_ba_format);
	DDX_Control(pDX, IDC_CHECK_RENAME, m_check_rename_index);
	DDX_Control(pDX, IDC_CHECK_RENAME2, m_with_aqi_name);
	DDX_Control(pDX, IDC_CHECK_SHOW_NAME, m_show_name);
}

BEGIN_MESSAGE_MAP(CconvertDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
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

	ON_BN_CLICKED(IDC_BUTTON_CLEAR4, &CconvertDlg::OnBnClickedButtonClear4)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CconvertDlg::OnBnClickedButtonBack)

	ON_BN_CLICKED(IDC_BUTTON1, &CconvertDlg::OnBnClickedButton1)
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
	m_cv_format.SetCurSel(1);
	m_crf_format.SetCurSel(0);
	m_ca_format.SetCurSel(0);
	m_ba_format.SetCurSel(0);
	m_show_name.SetCheck(1);
	SetTimer(1, 1000, NULL);


	cur_task.status_p = &convert_status;
	cur_task.cur_task_status = 0;

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
	std::wstring aqydname, aqyvname;

	for (int i = 0; i < search_list.size(); i++)
	{
		if (search_list[i].length() >= f_format.length())
		{
			if (f_format == search_list[i].substr(search_list[i].length() - f_format.length()))
			{
				if (m_show_name.GetCheck())
				{
					if (0 == get_aqy_file_v_name_with_path(search_list_f[i], f_format, aqydname, aqyvname))
					{
						filter_list.push_back(aqyvname + L"." + f_format);
					}
					else
					{
						filter_list.push_back(search_list[i]);
					}
				}
				else
				{
					filter_list.push_back(search_list[i]);
				}

				filter_list_f.push_back(search_list_f[i]);
			}
		}

	}

	if (filter_list.size() > 0)
	{

		for (int i = 0; i < filter_list.size(); i++)
		{
			//pListBox->AddString(filter_list[i].c_str()); // 添加数据
			if (m_show_name.GetCheck())
			{
				//wfname.replace(aiqy_f_name.length() - i_f.length(), i_f.length(), L"qiyicfg");
				//read_aqi_file_vedio_name()
			}
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





void CconvertDlg::OnBnClickedButtonConvert()
{
	// TODO: 在此添加控件通知处理程序代码

	switch (convert_status)
	{
	case 0:
		if (select_list_f.size() > 0)
		{
			if (!m_save_same_path.GetCheck())
			{
				if (SaveFolder.GetLength() == 0)
				{
					AfxMessageBox(L"选择存储路径");
					OnBnClickedButtonSaveFolder();
				}
				if (SaveFolder.GetLength() == 0)
				{
					AfxMessageBox(L"未配置存储路径");
				}
				else
				{
					if (SaveFolder.GetAt(SaveFolder.GetLength() - 1) != '\\')
					{
						SaveFolder = SaveFolder + L"\\";
						convert_status = 1;
						GetDlgItem(IDC_BUTTON_CONVERT)->SetWindowTextW(L"STOP");
					}
				}
			}
		}
		break;

	case 1:
		if (select_list_f.size() > 0)
		{
			convert_status = 2;
			GetDlgItem(IDC_BUTTON_CONVERT)->SetWindowTextW(L"CONVERT");
		}
		break;
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
	//std::string command = "ffmpeg -i " + std::string(infname) + " -c:v libx264 -crf 30 -c:a aac -strict experimental -b:a 192k " + std::string(outfname);
	std::string command = "./ffmpeg.exe -i " + std::string(infname) + "-c:v h264_qsv -crf 30 -c:a aac -strict experimental -b:a 192k " + std::string(outfname);
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

void CconvertDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 1:
		if (convert_status == 1)// start convert
		{
			if (cur_task.cur_task_status != 1)
			{
				if (cur_task.cur_task_status == 2)
				{
					if (select_list_f.size() >= 1)
					{
						select_list.erase(select_list.begin());
						select_list_f.erase(select_list_f.begin());
						UpdateSelectedList();
					}

				}
				if (cur_task.cur_task_status == 3)
				{
					if (select_list_f.size() >= 1)
					{
						fail_list.push_back(select_list[0]);
						fail_list_f.push_back(select_list_f[0]);
						select_list.erase(select_list.begin());
						select_list_f.erase(select_list_f.begin());

						UpdateSelectedList();
						UpdateFailedList();
					}

				}
				if (select_list_f.size() == 0)
				{
					UpdateSelectedList();
					convert_status = 0;
					GetDlgItem(IDC_BUTTON_CONVERT)->SetWindowTextW(L"CONVERT");
					cur_task.cur_task_status = 0;
					return;
				}
				std::wstring infname, outfname, midfname;
				std::wstring aiqy_name, aiqy_f_name, aiqy_d_name;
				//std::string infname_s, outfname_s;
				CString str_i_f, str_o_f;
				std::wstring i_f, o_f, m_f;

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



				for (int i = 0; i < 1; i++)
				{
					if (m_save_same_path.GetCheck())
					{
						infname = select_list_f[i];
						outfname = select_list_f[i];
						midfname = select_list_f[i];

						/*
						if (m_check_rename_index.GetCheck())
						{


								outfname.replace(0, outfname.length() - i_f.length() - 1, IntToWstring(m_index++));


						}

						if (m_with_aqi_name.GetCheck())
						{
							aiqy_f_name = infname;
							aiqy_f_name.replace(aiqy_f_name.length() - i_f.length(), i_f.length(), L"qiyicfg");
							read_aqi_file_vedio_name(aiqy_f_name, aiqy_d_name, aiqy_f_name);
							aiqy_f_name.replace(0, aiqy_d_name.length()+1, L"");
							outfname = aiqy_f_name + L".mp3";

						}
						*/
						if (m_show_name.GetCheck())
						{
							std::wstring::size_type pos = outfname.rfind(L'\\');
							outfname = outfname.substr(0, pos + 1) + select_list[i];
						}

						outfname.replace(outfname.length() - i_f.length(), i_f.length(), o_f);



						midfname.replace(midfname.length() - i_f.length(), i_f.length(), L"flv");
						outfname = SaveFolder.GetString() + outfname;
						//midfname = SaveFolder.GetString() + midfname;
					}
					else
					{
						infname = select_list_f[i];
						outfname = select_list[i];
						midfname = select_list[i];
						/*
						if (m_check_rename_index.GetCheck())
						{
							outfname.replace(0, outfname.length() - i_f.length() - 1, IntToWstring(m_index++));
						}
						if (m_with_aqi_name.GetCheck())
						{
							aiqy_f_name = infname;
							aiqy_f_name.replace(aiqy_f_name.length() - i_f.length(), i_f.length(), L"qiyicfg");
							read_aqi_file_vedio_name(aiqy_f_name, aiqy_d_name, aiqy_f_name);
							aiqy_f_name.replace(0, aiqy_d_name.length() + 1, L"");
							outfname = aiqy_f_name + L".mp3";

						}
						*/

						outfname.replace(outfname.length() - i_f.length(), i_f.length(), o_f);


						//outfname.replace(outfname.length() - i_f.length(), i_f.length(), o_f);
						midfname.replace(midfname.length() - i_f.length(), i_f.length(), L"flv");
						//SaveFolder = SaveFolder + L"\\";
						outfname = SaveFolder.GetString() + outfname;
						midfname = SaveFolder.GetString() + midfname;
					}

					int size = WideCharToMultiByte(CP_UTF8, 0, infname.c_str(), -1, nullptr, 0, nullptr, nullptr);
					std::string infname_s(size, 0);
					WideCharToMultiByte(CP_UTF8, 0, infname.c_str(), -1, &infname_s[0], size, nullptr, nullptr);
					cur_task.infname = infname_s;

					if (m_show_name.GetCheck() && !m_save_same_path.GetCheck())
					{
						size = WideCharToMultiByte(CP_ACP, 0, midfname.c_str(), -1, nullptr, 0, nullptr, nullptr);
						std::string midfname_s(size, 0);
						WideCharToMultiByte(CP_ACP, 0, midfname.c_str(), -1, &midfname_s[0], size, nullptr, nullptr);
						cur_task.midname = midfname_s;
					}
					else
					{
						size = WideCharToMultiByte(CP_UTF8, 0, midfname.c_str(), -1, nullptr, 0, nullptr, nullptr);
						std::string midfname_s(size, 0);
						WideCharToMultiByte(CP_UTF8, 0, midfname.c_str(), -1, &midfname_s[0], size, nullptr, nullptr);
						cur_task.midname = midfname_s;
					}


					if (m_show_name.GetCheck())
					{
						size = WideCharToMultiByte(CP_ACP, 0, outfname.c_str(), -1, nullptr, 0, nullptr, nullptr);
						std::string outfname_s(size, 0);
						WideCharToMultiByte(CP_ACP, 0, outfname.c_str(), -1, &outfname_s[0], size, nullptr, nullptr);
						cur_task.outfname = outfname_s;
					}
					else
					{
						size = WideCharToMultiByte(CP_UTF8, 0, outfname.c_str(), -1, nullptr, 0, nullptr, nullptr);
						std::string outfname_s(size, 0);
						WideCharToMultiByte(CP_UTF8, 0, outfname.c_str(), -1, &outfname_s[0], size, nullptr, nullptr);
						cur_task.outfname = outfname_s;
					}
					
					CString temp;
					std::wstring temp2;
					nSel = m_cv_format.GetCurSel();
					if (nSel != CB_ERR)
					{

						m_cv_format.GetLBText(nSel, temp); // 根据索引获取文本	
						temp2 = temp.GetString();
						size = WideCharToMultiByte(CP_UTF8, 0, temp2.c_str(), -1, nullptr, 0, nullptr, nullptr);
						WideCharToMultiByte(CP_UTF8, 0, temp2.c_str(), -1, &cur_task.cv[0], size, nullptr, nullptr);
					}
					nSel = m_crf_format.GetCurSel();
					if (nSel != CB_ERR)
					{

						m_crf_format.GetLBText(nSel, temp); // 根据索引获取文本	
						temp2 = temp.GetString();
						size = WideCharToMultiByte(CP_UTF8, 0, temp2.c_str(), -1, nullptr, 0, nullptr, nullptr);
						WideCharToMultiByte(CP_UTF8, 0, temp2.c_str(), -1, &cur_task.crf[0], size, nullptr, nullptr);
					}
					nSel = m_ca_format.GetCurSel();
					if (nSel != CB_ERR)
					{

						m_ca_format.GetLBText(nSel, temp); // 根据索引获取文本	
						temp2 = temp.GetString();
						size = WideCharToMultiByte(CP_UTF8, 0, temp2.c_str(), -1, nullptr, 0, nullptr, nullptr);
						WideCharToMultiByte(CP_UTF8, 0, temp2.c_str(), -1, &cur_task.ca[0], size, nullptr, nullptr);
					}
					nSel = m_ba_format.GetCurSel();
					if (nSel != CB_ERR)
					{

						m_ba_format.GetLBText(nSel, temp); // 根据索引获取文本	
						temp2 = temp.GetString();
						size = WideCharToMultiByte(CP_UTF8, 0, temp2.c_str(), -1, nullptr, 0, nullptr, nullptr);
						WideCharToMultiByte(CP_UTF8, 0, temp2.c_str(), -1, &cur_task.ba[0], size, nullptr, nullptr);
					}

					cur_task.cur_task_status = 1;
				}
				pThread = AfxBeginThread(ConvertThread, (LPVOID)&cur_task);
				if (pThread == NULL)
				{
					AfxThrowMemoryException(); // 如果无法创建线程，则抛出异常  
				}

			}

		}
		if (convert_status == 2)
		{
			if (cur_task.cur_task_status != 1)
			{
				convert_status = 0;
			}

		}
		break;
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

UINT ConvertThread(LPVOID pParam)
{
	// 在这里编写线程的代码  
	// pParam 可以用来传递数据给线程  
	convert_task* th_task = (convert_task*)pParam;

	std::string infname_s = th_task->infname;
	std::string midfname_s = th_task->midname;
	std::string outfname_s = th_task->outfname;

	remove(outfname_s.c_str());
	extract_media(infname_s.c_str(), midfname_s.c_str());

	int ret = cmd_convert(midfname_s.c_str(), outfname_s.c_str(), th_task->cv.c_str(), th_task->crf.c_str(), th_task->ca.c_str(), th_task->ba.c_str());

	remove(midfname_s.c_str());
	if (ret == 0)
	{
		th_task->cur_task_status = 2;
	}
	else
	{
		th_task->cur_task_status = ret;
	}

	return 0; // 线程函数的返回值将被用作线程的退出代码  
}

int cmd_convert(std::string infname, std::string outfname, std::string cv, std::string crf, std::string ca, std::string ba)
{
	std::string command;
	if (cv == "copy")
	{
		command = "ffmpeg -i \"" + std::string(infname) + "\" -c:v copy  -c:a copy \"" + std::string(outfname) + "\"";
	}
	else
	{
		command = "ffmpeg -i \"" + std::string(infname) + "\" -c:v " + std::string(cv) + " -crf " + std::string(crf) \
			+ " -c:a " + std::string(ca) + " -b:a " + std::string(ba) + " \"" + std::string(outfname) + "\"";
	}

	// 构建FFmpeg命令
	//ffmpeg -i input.flv -c:v libx264 -crf 23 -c:a aac -strict experimental -b:a 192k output.mp4
	//std::string command = "ffmpeg -i " + std::string(infname) + " " + std::string(outfname)
	// std::string command = "ffmpeg -i " + std::string(infname) + " -c:v libx264 -crf 30 -c:a aac -strict experimental -b:a 192k " + std::string(outfname);
	//std::string command = "ffmpeg -i " + std::string(infname) + " -c:v copy  -c:a copy " + std::string(outfname);
	//std::string command = "ffmpeg -i " + std::string(infname) + "-c:v h264_qsv -crf 23 -c:a aac -strict experimental -b:a 192k " + std::string(outfname);
	//-c:v h264_qsv
	// 执行命令
	int ret = std::system(command.c_str());
	//Sleep(10000);

	//int ret = 0;
	if (ret == 0) {
		std::cout << "转换成功" << std::endl;
		return 0;
	}
	else {
		std::cout << "转换失败，错误码：" << ret << std::endl;
		return 3;
	}
}

void CconvertDlg::UpdateSelectedList()
{
	m_selected_list.ResetContent();
	for (int i = 0; i < select_list.size(); i++)
	{
		m_selected_list.InsertString(-1, select_list[i].c_str());
	}
}

void CconvertDlg::OnLbnSelchangeSearchList()
{
	// TODO: 在此添加控件通知处理程序代码
}




void CconvertDlg::OnBnClickedButtonClear4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_failed_list.ResetContent();
	fail_list.clear();
	fail_list_f.clear();
	//	UpdateSelectedList();
	UpdateFailedList();
}
void CconvertDlg::UpdateFailedList()
{
	m_failed_list.ResetContent();
	for (int i = 0; i < fail_list.size(); i++)
	{
		m_failed_list.InsertString(-1, fail_list[i].c_str());
	}
}

void CconvertDlg::OnBnClickedButtonBack()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < fail_list.size(); i++) {

		select_list.push_back(fail_list[i]);
		select_list_f.push_back(fail_list_f[i]);
	}
	m_failed_list.ResetContent();
	fail_list.clear();
	fail_list_f.clear();
	UpdateSelectedList();
	UpdateFailedList();
}

int hex_char_to_int(char c) {
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'a' && c <= 'f') return c - 'a' + 10;
	if (c >= 'A' && c <= 'F') return c - 'A' + 10;
	return -1;
}

void serialized_unicode_to_utf16(const char* serialized_unicode, int len, char* ch_out)
{
	wchar_t* utf16_str = (wchar_t*)malloc(len + 1);
	int i = 0;
	int j = 0;
	int k = 0;
	char hex_digits[5] = { 0 };

	for (i = 0; i < len; i++)
	{
		if (strncmp(&serialized_unicode[i], "\\u", 2) != 0)
		{
			utf16_str[j++] = (wchar_t)serialized_unicode[i];
		}
		else
		{
			strncpy_s(hex_digits, &serialized_unicode[i + 2], 4);
			uint32_t code_point = 0;
			for (int k = 0; k < 4; k++)
			{
				int digit = hex_char_to_int(hex_digits[k]);
				if (digit == -1) {
					fprintf(stderr, "Invalid hex digit in serialized Unicode string\n");
					return;
				}
				code_point = (code_point << 4) | digit;
			}

			utf16_str[j++] = (wchar_t)code_point;
			i = i + 5;
		}
	}
	utf16_str[j++] = L'\0';

	int size = WideCharToMultiByte(CP_ACP, 0, utf16_str, -1, nullptr, 0, nullptr, nullptr);
	std::string str_temp(size, 0);
	WideCharToMultiByte(CP_ACP, 0, utf16_str, -1, &str_temp[0], size, nullptr, nullptr);
	memcpy(ch_out, str_temp.c_str(), str_temp.length());
	free(utf16_str);
}
//void read_aqi_file_vedio_name(const char* fname, char* dir_name, char* v_name)
int read_aqi_file_vedio_name(std::wstring wfname, std::wstring& dirname, std::wstring& vname)
{
	FILE* file;
	char line[4096];
	char temp_out[4096];

	int size = WideCharToMultiByte(CP_UTF8, 0, wfname.c_str(), -1, nullptr, 0, nullptr, nullptr);
	std::string sfname(size, 0);
	WideCharToMultiByte(CP_UTF8, 0, wfname.c_str(), -1, &sfname[0], size, nullptr, nullptr);
	// 打开文件，使用 "r" 模式表示读取  

	fopen_s(&file, sfname.c_str(), "r");
	if (file == NULL) {
		perror("无法打开文件");
		return 1;
	}

	// 按行读取文件内容  
	while (fgets(line, sizeof(line), file) != NULL) {
		// 打印读取到的行  
		if (strncmp(line, "_a_t", 4) == 0)
		{
			memset(temp_out, 0, 4096);
			serialized_unicode_to_utf16(&line[5], strlen(line) - 6, temp_out);
			dirname = gbk_to_wstring(temp_out);
			//memcpy(dir_name, &line[5], strlen(line) - 6);
		}
		if (strncmp(line, "text", 4) == 0)
		{
			memset(temp_out, 0, 4096);
			serialized_unicode_to_utf16(&line[5], strlen(line) - 6, temp_out);
			vname = gbk_to_wstring(temp_out);
		}
		printf("%s", line);
	}

	// 检查是否到达文件末尾之外的EOF  
	if (feof(file) && ferror(file)) {
		perror("读取文件时出错");
	}

	// 关闭文件  
	fclose(file);

	return 0;
}

std::wstring gbk_to_wstring(const char* utf8Str) {
	if (utf8Str == nullptr) {
		throw std::invalid_argument("Input string is nullptr");
	}

	int utf8Len = static_cast<int>(strlen(utf8Str));
	int wcharLen = MultiByteToWideChar(CP_ACP, 0, utf8Str, utf8Len, nullptr, 0);

	if (wcharLen == 0) {
		throw std::runtime_error("MultiByteToWideChar failed to get buffer size");
	}

	std::wstring wstr(wcharLen, L'\0');
	MultiByteToWideChar(CP_ACP, 0, utf8Str, utf8Len, &wstr[0], wcharLen);

	return wstr;
}

int get_aqy_file_v_name_with_path(std::wstring wfname, std::wstring if_name, std::wstring& dirname, std::wstring& vname)
{
	int res = 0;
	std::wstring aqyfname = wfname;
	aqyfname.replace(aqyfname.length() - if_name.length(), if_name.length(), L"qiyicfg");
	res = read_aqi_file_vedio_name(aqyfname, dirname, vname);
	if (res == 0)
	{
		vname.replace(0, dirname.length() + 1, L"");
	}
	if (dirname.length() == 0 || vname.length() == 0)
	{
		return 1;
	}
	return res;
}

void CconvertDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int count = filter_list.size();
	for (int i = 0; i < count; i++)
	{
			select_list.push_back(filter_list[i]);
			select_list_f.push_back(filter_list_f[i]);
			m_selected_list.InsertString(-1, filter_list[i].c_str());
	
	}
	
}
