
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
	std::vector<std::wstring> filter_list;
	std::vector<std::wstring> select_list;
	std::vector<std::wstring> search_list_f;
	std::vector<std::wstring> filter_list_f;
	std::vector<std::wstring> select_list_f;

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
	afx_msg void OnBnClickedButtonClear2();
	afx_msg void OnBnClickedButtonClear3();
	afx_msg void OnBnClickedButtonConvert();
	afx_msg void OnBnClickedButtonSaveFolder();
	CButton m_save_same_path;
	CComboBox m_save_format;
	CButton m_check_rename_index;
	int m_index = 1;
};
