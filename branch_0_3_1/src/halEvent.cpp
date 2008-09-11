
//         Copyright E�in O'Callaghan 2006 - 2008.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "stdAfx.hpp"
#include "Halite.hpp"

#include <iostream>
#include <fstream>
#include <iterator>
#include <iomanip>
#include <map>
#include <algorithm>
#include <string>
#include <vector>

#include <libtorrent/file.hpp>
#include <libtorrent/hasher.hpp>
#include <libtorrent/entry.hpp>
#include <libtorrent/bencode.hpp>
#include <libtorrent/session.hpp>
#include <libtorrent/ip_filter.hpp>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/peer_connection.hpp>

#define HAL_EVENT_IMPL_UNIT
#include "halEvent.hpp"

namespace hal
{

static boost::shared_ptr<event_impl> s_event_impl;

struct event_impl
{
	mutable mutex_t mutex_;
	boost::signal<void (boost::shared_ptr<EventDetail>)> event_signal_;
};

event_logger::event_logger()
{
	if (!s_event_impl)
		s_event_impl.reset(new event_impl());

	pimpl_ = s_event_impl;
}

event_logger::~event_logger()
{}

boost::signals::connection event_logger::attach(boost::function<void (boost::shared_ptr<EventDetail>)> fn)
{
	mutex_t::scoped_lock l(pimpl_->mutex_);
	return pimpl_->event_signal_.connect(fn);
}

void event_logger::dettach(const boost::signals::connection& c)
{
	mutex_t::scoped_lock l(pimpl_->mutex_);
	pimpl_->event_signal_.disconnect(c);
}

void event_logger::post(boost::shared_ptr<EventDetail> e)
{
	mutex_t::scoped_lock l(pimpl_->mutex_);
	if (e->level() > hal::event_logger::debug || halite().logDebug())
		pimpl_->event_signal_(e);
}
	
std::wstring event_logger::eventLevelToStr(eventLevel event)
{
	switch (event)
	{
	case debug:
		return hal::app().res_wstr(HAL_EVENTDEBUG);
	case info:
		return hal::app().res_wstr(HAL_EVENTINFO);
	case warning:
		return hal::app().res_wstr(HAL_EVENTWARNING);
	case critical:
		return hal::app().res_wstr(HAL_EVENTCRITICAL);
	case fatal:
		return hal::app().res_wstr(HAL_EVENTCRITICAL);
	default:
		return hal::app().res_wstr(HAL_EVENTNONE);
	}
}

} // namespace hal
