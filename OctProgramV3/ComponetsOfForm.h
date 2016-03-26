#pragma once

namespace OCTProgram
{
	using namespace System;
	using namespace System::IO;
	ref class ComboBoxItem
	{
	private: 
		String^ m_Text;
		String^ m_Value;
	public:
		ComboBoxItem(String^ text,String^ value);
		~ComboBoxItem();
		String^ Text();
		String^ Value();
		virtual String^ ToString() override;
	};
}
