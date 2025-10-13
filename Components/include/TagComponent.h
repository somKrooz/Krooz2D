#pragma once
#include "Types.h"


namespace Krooz2D
{	
	struct TagComponent
	{
		private:
		string _tagname = "kroozDefault";

		public:
		TagComponent(const char* name){
			_tagname = name;
		}

		string& GetTag(){
			return _tagname;
		}
	};
} 

