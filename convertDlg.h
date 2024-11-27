
// convertDlg.h: 头文件
//

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <ShlObj.h>

#pragma comment(lib, "Shell32.lib") 

#include "qsv2flv.h"
#include <sstream>  

#include <locale> 
#include <iomanip>

struct convert_task {
	int* status_p;
	std::string infname;
	std::string midname;
	std::string outfname;
	int cur_task_status;
	std::string cv;
	std::string crf;
	std::string ca;
	std::string ba;
};
// CconvertDlg 对话框
class CconvertDlg : public CDialogEx
{
// 构造
public:
	CconvertDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONVERT_DIALOG };
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

	CString SelectFolder;
	CString SaveFolder;

	std::vector<std::wstring> search_list;
	std::vector<std::wstring> search_list_aqyname;
	std::vector<std::wstring> filter_list;
	std::vector<std::wstring> select_list;
	std::vector<std::wstring> fail_list;
	std::vector<std::wstring> search_list_f;
	std::vector<std::wstring> filter_list_f;
	std::vector<std::wstring> select_list_f;
	std::vector<std::wstring> fail_list_f;


	void ListFilesInDirectory(const std::wstring& path);
	void FilterFiles(const std::wstring& f_format);
	bool CheckSelectedList(const std::wstring& f_format);

	void cmd_convert(std::string infname, std::string outfname);
	std::wstring IntToWstring(int value);
public:
	afx_msg void OnBnClickedButtonSrcFile();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLbnDblclkSearchList();
	CComboBox m_combo_format;
	CListBox m_list_filter;
	afx_msg void OnBnClickedButtonSelect();
	CListBox m_selected_list;
	CListBox m_failed_list;
	afx_msg void OnBnClickedButtonClear2();


	afx_msg void OnBnClickedButtonConvert();
	afx_msg void OnBnClickedButtonSaveFolder();
	CButton m_save_same_path;
	CComboBox m_save_format;
	CComboBox m_cv_format;
	CComboBox m_crf_format;
	CComboBox m_ca_format;
	CComboBox m_ba_format;
	CButton m_check_rename_index;
	int m_index = 1;
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	int convert_status = 0;
	CWinThread* pThread;
	convert_task cur_task;

	void UpdateSelectedList();
	void UpdateFailedList();
	afx_msg void OnLbnSelchangeSearchList();
	CListBox m_list_failed;
	//afx_msg void OnBnClickedButtonClear4();
	afx_msg void OnBnClickedButtonClear4();
	afx_msg void OnBnClickedButtonBack();


	CButton m_with_aqi_name;
	CButton m_show_name;
	afx_msg void OnBnClickedButton1();
};

UINT ConvertThread(LPVOID pParam);
int cmd_convert(std::string infname, std::string outfname, std::string cv, std::string crf, std::string ca, std::string ba);
int hex_char_to_int(char c);
void serialized_unicode_to_utf16(const char* serialized_unicode, int len, char* ch_out);
int read_aqi_file_vedio_name(std::wstring wfname, std::wstring& dirname, std::wstring& vname);
std::wstring gbk_to_wstring(const char* utf8Str);
int get_aqy_file_v_name_with_path(std::wstring wfname, std::wstring if_name, std::wstring& dirname, std::wstring& vname);