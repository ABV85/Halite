

#include <boost/foreach.hpp>
#include <tinyxml.h>

#include "wtl_app.hpp"
#include "logger.hpp"
#include "string_conv.hpp"
#include "ini.hpp"

#define foreach BOOST_FOREACH

namespace hal 
{

class ini_impl
{
public:
	ini_impl(std::string filename) :
		working_file_(app().exe_path().branch_path()/filename),
		xml_(working_file_.string())
	{}
	
	void load_data()
	{
		if (!xml_.LoadFile())
		{
			generate_default_file();
		}
	}
	
	void save_data()
	{		
		xml_.SaveFile(working_file_.string());
	}
	
	bool save(boost::filesystem::path location, std::string data)
	{
		tinyxml::node* data_node = get_data_node(location);
		
		// Should have correct node		
		
		return true;
	}

	bool save(boost::filesystem::path location, tinyxml::node* data)
	{
		tinyxml::node* data_node = get_data_node(location);
		
		data_node->Clear();
		data_node->LinkEndChild(data);
		
		return true;
	}
	
	tinyxml::node* load(boost::filesystem::path location)
	{
		tinyxml::node* data_node = get_data_node(location);
		
		tinyxml::node* data = data_node->FirstChild();
		
		if (data)
			return data->Clone();
		else
			return 0;
	}

private:
	void generate_default_file()
	{
		xml_.LinkEndChild(new tinyxml::declaration("1.0", "", ""));
		
		xml_.LinkEndChild(new tinyxml::element("ini"));
	}
	
	tinyxml::node* get_data_node(boost::filesystem::path location)
	{
		tinyxml::node* data_node = xml_.FirstChild("ini");
		
		if (!data_node)
		{
			data_node = new tinyxml::element("ini");
			xml_.LinkEndChild(data_node);
		}
		
		foreach (std::string elem, location)
		{
			tinyxml::node* child_node = data_node->FirstChild(elem);
			
			if (!child_node)
			{
				child_node = new tinyxml::element(elem);
				data_node->LinkEndChild(child_node);
			}
			
			data_node = child_node;
		}
		
		return data_node;
	}
	
	boost::filesystem::path working_file_;
	tinyxml::document xml_;
};

ini_file::ini_file(std::string filename) :
	pimpl(new ini_impl(filename))
{}

void ini_file::load_data()
{
	pimpl->load_data();
}

void ini_file::save_data()
{
	pimpl->save_data();
}

bool ini_file::save(boost::filesystem::path location, std::string data)
{
	return pimpl->save(location, data);
}

bool ini_file::save(boost::filesystem::path location, tinyxml::node* data)
{
	return pimpl->save(location, data);
}

tinyxml::node* ini_file::load(boost::filesystem::path location)
{
	return pimpl->load(location);
}

ini_file& ini()
{
	static ini_file ini("Halite.xml");
	return ini;
}

}
