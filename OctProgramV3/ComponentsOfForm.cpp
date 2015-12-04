#include "stdafx.h"
#include "ComponetsOfForm.h"
namespace OCTProgram
{
	ComboBoxItem::ComboBoxItem(String^ text,String^ value)
	{
		this->m_Text = text;
		this->m_Value = value;
	}
	ComboBoxItem::~ComboBoxItem()
	{}
	String^ ComboBoxItem::Text()
	{
		return this->m_Text;
	}
	String^ ComboBoxItem::Value()
	{
		return this->m_Value;
	}
	String^ ComboBoxItem::ToString()
	{
		return this->m_Text;
	}
}