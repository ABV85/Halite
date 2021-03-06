
//         Copyright E�in O'Callaghan 2006 - 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "halEvent.hpp"
#include "HaliteWindow.hpp"
#include "HaliteListView.hpp"

#include <boost/archive/xml_woarchive.hpp>
#include <boost/archive/xml_wiarchive.hpp>

template <class TBase>
class CHaliteDialogBase
{
	typedef CHaliteDialogBase<TBase> this_class_t;
	
public:
	CHaliteDialogBase(HaliteWindow& haliteWindow) :
		haliteWindow_(haliteWindow),
		sc_block_(connection_)
	{		
		connection_ = haliteWindow.connectUiUpdate(bind(&this_class_t::handleUiUpdate, this, _1));
		sc_block_.block();
	}
	
	BEGIN_MSG_MAP_EX(this_class_t)
		MSG_WM_SHOWWINDOW(OnShow)
//		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()
	
	void OnShow(BOOL show, int flags)
	{
		if (show)
		{
			sc_block_.unblock();
		}
		else
		{
			sc_block_.block();
		}
		
		SetMsgHandled(false);
	}
	
	void InitializeHalDialogBase()
	{
		TBase* pT = static_cast<TBase*>(this);	
		OnShow(pT->IsWindowVisible(), 0);
	}
	
	HaliteListViewCtrl& torrentsList() 
	{ 
		return haliteWindow_.torrentsList(); 
	}
	
	void requestUiUpdate()
	{
		haliteWindow_.issueUiUpdate();
	}
	
	#define logical_xor !=0==!
	
	void handleUiUpdate(const hal::torrent_details_manager& tD)
	{
		try
		{

		TBase* pT = static_cast<TBase*>(this);
		
		hal::torrent_details_ptr focused = tD.focused_torrent();
		
		if ((focusedTorrent_ logical_xor focused) ||
				(focused && focusedTorrent_->name() != focused->name()))
		{
			pT->focusChanged(focusedTorrent_ = focused);
			
			if (focusedTorrent_)
			{
			//	HAL_DEV_MSG(hal::wform(L"HaliteDialogBase::handleUiUpdate(%1%)") 
			//		% hal::to_wstr_shim(focusedTorrent_->name()));
			}
		}
		else
			focusedTorrent_ = focused;
	
		pT->uiUpdate(tD);

		} HAL_GENERIC_FN_EXCEPTION_CATCH(L"HaliteDialogBase::handleUiUpdate()")
	}

	void uiUpdate(const hal::torrent_details_manager& tD)
	{}	
	
	void focusChanged(const hal::torrent_details_ptr pT)
	{}
	
	const hal::torrent_details_ptr focused_torrent() { return focusedTorrent_; }
	
	template<typename T>
	BOOL SetDlgItemInfo(int nID, T info)
	{
		std::wostringstream oss;
		oss << info;
		TBase* pT = static_cast<TBase*>(this);
		return pT->SetDlgItemText(nID, oss.str().c_str());
	}
	
protected:
	hal::torrent_details_ptr focusedTorrent_;

private:
	HaliteWindow& haliteWindow_;
	boost::signals2::scoped_connection connection_;
	boost::signals2::shared_connection_block sc_block_;
};

