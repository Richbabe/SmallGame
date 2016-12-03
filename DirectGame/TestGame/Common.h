#pragma once

#include "stdafx.h"



// wchar_t* CharToWchar(const char* c)
// {
// 	wchar_t *m_wchar;
// 	int len = MultiByteToWideChar(CP_ACP, 0, c, strlen(c), NULL, 0);
// 	m_wchar = new wchar_t[len + 1];
// 	MultiByteToWideChar(CP_ACP, 0, c, strlen(c), m_wchar, len);
// 	m_wchar[len] = '\0';
// 	return m_wchar;
// }