
#include "ConfigOptions.hpp"
#include "ProgressDialog.hpp"

void BitTorrentOptions::onFilterImport(UINT, int, HWND hWnd)
{
	CSSFileDialog dlgOpen(TRUE, NULL, NULL, OFN_HIDEREADONLY, L"eMule ipfilter.dat. (*.dat)|*.dat|", m_hWnd);
	
	if (dlgOpen.DoModal() == IDOK) 
	{
		ProgressDialog progDlg(L"Importing IP filters...", bind(
			&hal::BitTorrent::ip_filter_import_dat, &hal::bittorrent(), path(hal::to_str(dlgOpen.m_ofn.lpstrFile)), _1, true));
		progDlg.DoModal();
	}
}	

