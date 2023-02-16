// -----------------------------------------------------------------------------------
//    wstring.cpp - support for delphi widestrings in c++
//                (WideString)
// $Rev: 108085 $
//
// Copyright(c) 1995-2022 Embarcadero Technologies, Inc.
//              All rights reserved                      
// -----------------------------------------------------------------------------------
#include <System.hpp>
#include <System.Internal.StrHlpr.hpp>

#if defined(_Windows) || defined(_WIN64)
  #include <Windows.hpp>
#endif

#include <System.SyncObjs.hpp>
#include <System.SysUtils.hpp>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <wchar.h>

#include <wstring.h>
#include <utilcls.h>

#if defined(__ANDROID__)
  #include <WideCharUtils.h>
#endif

#define STR_CAST_(type, arg) const_cast<type>(arg)

namespace System
{

#if !defined(_DELPHI_NEXTGEN)

#if !defined(WIDESTRING_USE_COM_API)
  template <typename CH>
  int WideCharLen(const CH* src)
  {
    int len = 0;
    if (src)
    {
      while (*src++)
        ++len;
    }
    return len;
  }
#endif

  static int UTF32ToUTF16(const char32_t* src, WideChar* dst, int len)
  {
    int count = 0;
    while ((len != 0) && *src) {
      char32_t ch = *src++;
      if (ch < 0x0000FFFF) {
        count++;
        if (dst)
          *dst++ = (ch & 0x0000FFFF);
      }
      else if (ch < 0x0010FFFF) {
        count += 2;
        if (dst) {
          ch -= 0x10000;
          *dst++ = (ch >> 10)  | 0xD800;
          *dst++ = (ch & 0x3FF)| 0xDC00;
        }
      } else {
        count++;
        if (dst)
          *dst++ = 0x0000FFFD;
      }
      if (len > 0)
        len--;
    }
    return count;
  }

#if defined(WIDECHAR_IS_CHAR16)
  #if defined(__ANDROID__)
  // NOTE: vswprintf does not work on Android/bionic currently
  //    See https://code.google.com/p/android/issues/detail?id=20567
  //        https://groups.google.com/forum/#!topic/android-ndk/fBqGZDOIn7E
  static int vsnwprintf(WideString& dst, const wchar_t* fmt, va_list paramList)
  {
    UTF8String _fmt8(fmt);
    const char* pFmt = _fmt8.c_str();

    UTF8String _buf;
    int _size = 16;
    _buf.SetLength(_size);
    char *pBuf = static_cast<char*>(const_cast<void*>(_buf.data()));

    int count = vsnprintf(pBuf, _size+1, pFmt, paramList);
    if (!count)
    {
      dst.SetLength(0);
      return 0;
    }
    
    if (count < 0)
      return count;
    
    if (count > _size)
    {
      _size = count;
      _buf.SetLength(_size);
      pBuf = static_cast<char*>(const_cast<void*>(_buf.data()));
      count = vsnprintf(pBuf, _size+1, pFmt, paramList);
    }
    else if (count < _size)
    {
      _buf.SetLength(count);
    }

    if (!count)
    {
      dst.SetLength(0);
    }
    else if (count > 0)
    {
      dst = _buf;
      count = dst.Length();
    }
    return count;
  }
  #else
  static int vsnwprintf(TAPtr<wchar_t>& _buf, const wchar_t* fmt, va_list paramList)
  {
    int _size = 16;
    _buf = new wchar_t[_size];
#if defined(__linux) && defined(__x86_64)
    va_list temp;
    va_copy(temp, paramList);
#endif
    int count = vswprintf(&_buf[0], _size, fmt, paramList);
    while (count < 0)
    {
      _size <<= 1;
      _buf = new wchar_t[_size];
#if defined(__linux) && defined(__x86_64)
      va_copy(paramList, temp);
#endif
      count = vswprintf(&_buf[0], _size, fmt, paramList);
    }
    return count;
  }
  #endif
#endif
  

  WideString WideString::StringOfChar(WideChar ch, int count)
  {
    return System::StringOfChar(ch, count);     
  }

  WideString::WideString(const char* src) : Data(0)
  {
#ifdef __ANDROID__
    // The Android startup sequence is such that global C++ objects cannot use
    // Delphi code as the .ctor section is executed before "System.main_app_entry"
    // is invoked, which means that "System.DelphiActivity" is not initialized yet.
    // So, to allow global UnicodeString instances, such as ...
    //
    //  System::String str("I am a global variable");
    //
    //  ... we will go directly to ICU. Ultimately the Delphi Unit Initialization
    // sequence should be updated to tolerate calls from C++ global objects. Or the
    // C++ startup code should initialize Delphi units early enough so that C++
    // global objects can safely access Delphi code.
    //
    WideBuffer wbuff(src);
    *this = reinterpret_cast<WideChar*>(wbuff.c_str());
#else    
    System::Internal::Strhlpr::WideFromPChar(*this, const_cast<char*>(src));
#endif
  }

#if defined(WIDESTRING_IS_BSTR)
  WideString::WideString(const WideString& src)
  {
    Data = src.Data ? ::SysAllocStringLen(src.Data, src.Length()) : 0;
  }
#else
  WideString::WideString(const WideString& src) : Data(0)
  {
    System::Internal::Strhlpr::WideAssign(*this, const_cast<WideString&>(src));
  }
#endif

#if defined(WIDESTRING_IS_BSTR)
  WideString::WideString(const UnicodeString& src)
  {
    Data = src.data() ? ::SysAllocStringLen(reinterpret_cast<const wchar_t*>(src.data()),
                                            src.Length()) : 0;
  }
#else
  WideString::WideString(const UnicodeString& src) : Data(0)
  {
    System::Internal::Strhlpr::WideFromUnicode(*this, const_cast<UnicodeString&>(src));
  }
#endif

  WideString::WideString(const WideChar* src, int len) : Data(0)
  {
    if (src && (len > 0))
    {
#if defined(WIDESTRING_IS_BSTR)
      Data = ::SysAllocStringLen(src, len);
#else
      SetLength(len);
      memcpy(Data, src, len * sizeof(WideChar));
#endif
    }
  }

#if !defined(WIDECHAR_IS_CHAR16)
  WideString::WideString(const char16_t* src, int numChar16/*= -1*/) : Data(0)
  {
    if (src)
    {
#if defined(WIDESTRING_IS_BSTR)
      if (numChar16 > 0)
        Data = ::SysAllocStringLen((wchar_t*)src, numChar16);
      else
        Data = ::SysAllocString((wchar_t*)src);
#else
      if (numChar16 < 0)
        numChar16 = WideCharLen(src);
      SetLength(numChar16);
      memcpy(Data, src, numChar16 * sizeof(WideChar));
#endif
    }
  }
#endif  

  WideString::WideString(const char32_t* src, int numChar32/*= -1*/) : Data(0)
  {
    if (src && (numChar32 != 0))
    {
      int len = UTF32ToUTF16(src, 0, numChar32);
      SetLength(len);
      UTF32ToUTF16(src, Data, numChar32);
    }
  }

  WideString::WideString(const char* src, int len) : Data(0)
  {
    AnsiString str(src, len);
    System::Internal::Strhlpr::WideFromAnsi(*this, *PRawByteString(&str));
  }


  WideString::WideString(const WideChar* src) : Data(0)
  {
    if (src && *src)
    {
#if defined(WIDESTRING_IS_BSTR)
      Data = ::SysAllocString(src);
#else
      int len = WideCharLen(src);
      SetLength(len);
      memcpy(Data, src, len * sizeof(WideChar));
#endif
    }
  }

#if !defined(WIDECHAR_IS_WCHAR)
  WideString::WideString(const wchar_t* src) : Data(0)
  {
    // Note: we assume the following:
    // 1) wchar_t uses UCS4 encoding
    // 2) WideChar uses UCS2 encoding
    // 3) it's permissible to "squish" character values that are too
    // large.
    //
    // These are the same assumptions made by System::UCS4StringToWideString
    int len = wcslen(src);
    SetLength(len);
    for (int i = 0; i < len; ++i)
      Data[i] = static_cast<WideChar>(src[i]);
  }

  WideString::WideString(const wchar_t* src, int len) : Data(0)
  {
    // Note: See 'note' above
    SetLength(len);
    for (int i = 0; i < len; ++i)
      Data[i] = static_cast<WideChar>(src[i]);
  }
  
  WideString::WideString(const wchar_t  src) : Data(0)
  {
    // Note: See 'note' above
    SetLength(1);
    Data[0] = static_cast<WideChar>(src);
  }    
#endif

  static WideString IntFmt("%d");
  static WideString UintFmt("%u");
  static WideString FltFmt("%g");

  WideString::WideString(const WideChar src)
    : Data(0)
  {
    WideChar buf[2];
    buf[0] = src;
    buf[1] = 0;
    *this = buf;
  }

  WideString::WideString(char src)
    : Data(0)
  {
    char buf[2];
    buf[0] = src;
    buf[1] = 0;
    *this = buf;
  }

  WideString::WideString(short src)
    : Data(0)
  {
    TVarRec r(src);
    Sysutils::WideFmtStr(*this, IntFmt, &r, 0);
  }

  WideString::WideString(unsigned short src)
    : Data(0)
  {
    TVarRec r(src);
    Sysutils::WideFmtStr(*this, UintFmt, &r, 0);
  }

  WideString::WideString(int src)
    : Data(0)
  {
    TVarRec r(src);
    Sysutils::WideFmtStr(*this, IntFmt, &r, 0);
  }

  WideString::WideString(unsigned int src)
    : Data(0)
  {
    TVarRec r(src);
    Sysutils::WideFmtStr(*this, UintFmt, &r, 0);
  }

  WideString::WideString(long src)
    : Data(0)
  {
    TVarRec r(src);
    Sysutils::WideFmtStr(*this, IntFmt, &r, 0);
  }

  WideString::WideString(unsigned long src)
    : Data(0)
  {
    TVarRec r(src);
    Sysutils::WideFmtStr(*this, UintFmt, &r, 0);
  }

  WideString::WideString(__int64 src)
    : Data(0)
  {
    TVarRec r(src);
    Sysutils::WideFmtStr(*this, IntFmt, &r, 0);
  }

  WideString::WideString(unsigned __int64 src)
    : Data(0)
  {
    *this = UnicodeString(src);
  }

  WideString::WideString(float src)
    : Data(0)
  {
#if defined(__clang__)  
    TVarRec r(static_cast<long double>(src));
#else
    TVarRec r(src);
#endif    
    Sysutils::WideFmtStr(*this, FltFmt, &r, 0);
  }

  WideString::WideString(double src)
    : Data(0)
  {
#if defined(__clang__)  
    TVarRec r(static_cast<long double>(src));
#else
    TVarRec r(src);
#endif    
    Sysutils::WideFmtStr(*this, FltFmt, &r, 0);
  }

  WideString::WideString(long double src)
    : Data(0)
  {
    TVarRec r(src);
    Sysutils::WideFmtStr(*this, FltFmt, &r, 0);
  }

  WideString::~WideString()
  {
    if (Data)
    {
      System::Internal::Strhlpr::WideFree(*this);
    }
  }


  WideString& WideString::operator=(const WideString& src)
  {
    System::Internal::Strhlpr::WideAssign(*this, const_cast<WideString&>(src));
    return *this;
  }

#ifdef WIDESTRING_IS_BSTR
  WideString& WideString::operator=(BSTR src)
  {
    if (Data) {
      ::SysFreeString(Data);
    }
    Data = (src && *src) ? ::SysAllocString(src) : 0;
    return *this;
  }

  void WideString::Attach(BSTR src)
  {
    // Must Detach what's there before Attaching new BSTR
    //
    _ASSERTE(Data == 0);
    Data = src;
  }

  BSTR WideString::Detach()
  {
    BSTR bstr = Data;
    Data = 0;
    return bstr;
  }

  void WideString::Empty()
  {
    if (Data)
    {
      ::SysFreeString(Data);
      Data = 0;
    }
  }
#else  
  WideString& WideString::operator =(const char16_t* rhs)
  {
    WideString temp(rhs);
    this->swap(temp);
    return *this;
  }
#endif

  WideString& WideString::operator+=(const WideString& src)
  {
    System::Internal::Strhlpr::WideAppend(*this, STR_CAST_(WideString&, src));
    return *this;
  }

  bool WideString::operator==(const WideString& rhs) const
  {
    return System::Internal::Strhlpr::WideEqual(const_cast<WideString&>(*this), const_cast<WideString&>(rhs));
  }

  bool WideString::operator!=(const WideString& rhs) const
  {
    return !(System::Internal::Strhlpr::WideEqual(const_cast<WideString&>(*this), const_cast<WideString&>(rhs)));
  }

  bool WideString::operator<(const WideString& rhs) const
  {
    return System::Internal::Strhlpr::WideLess(const_cast<WideString&>(*this), const_cast<WideString&>(rhs));
  }

  bool WideString::operator>(const WideString& rhs) const
  {
    return System::Internal::Strhlpr::WideGreater(const_cast<WideString&>(*this), const_cast<WideString&>(rhs));
  }

  bool WideString::operator<=(const WideString& rhs) const
  {
    return !(System::Internal::Strhlpr::WideGreater(const_cast<WideString&>(*this), const_cast<WideString&>(rhs)));
  }

  bool WideString::operator>=(const WideString& rhs) const
  {
    return !(System::Internal::Strhlpr::WideLess(const_cast<WideString&>(*this), const_cast<WideString&>(rhs)));
  }

#ifdef WIDESTRING_IS_BSTR
  bool WideString::operator==(const BSTR w) const 
  { 
    return operator==(WideString(w));
  }

  bool WideString::operator!=(const BSTR w) const 
  { 
    return operator!=(WideString(w));
  }

  bool WideString::operator<(const BSTR w) const 
  { 
    return operator<(WideString(w));
  }

  bool WideString::operator>(const BSTR w) const 
  { 
    return operator>(WideString(w));
  }

  bool WideString::operator<=(const BSTR w) const 
  { 
    return operator<=(WideString(w));
  }

  bool WideString::operator>=(const BSTR w) const 
  { 
    return operator>=(WideString(w));
  }

  bool operator ==(const BSTR w, const WideString& rhs)
  { 
    return rhs.operator==(WideString(w));
  };

  bool operator !=(const BSTR w, const WideString& rhs)
  { 
    return rhs.operator!=(WideString(w));
  };

  bool operator < (const BSTR w, const WideString& rhs)
  { 
    return rhs.operator>(WideString(w));
  };

  bool operator > (const BSTR w, const WideString& rhs)
  { 
    return rhs.operator<(WideString(w));
  };

  bool operator <=(const BSTR w, const WideString& rhs)
  { 
    return rhs.operator>=(WideString(w));
  };

  bool operator >=(const BSTR w, const WideString& rhs)
  { 
    return rhs.operator<=(WideString(w));
  };
#else
  bool WideString::operator==(const char16_t* w) const 
  { 
    return operator==(WideString(w));
  }

  bool WideString::operator!=(const char16_t* w) const 
  { 
    return operator!=(WideString(w));
  }

  bool WideString::operator<(const char16_t* w) const 
  { 
    return operator<(WideString(w));
  }

  bool WideString::operator>(const char16_t* w) const 
  { 
    return operator>(WideString(w));
  }

  bool WideString::operator<=(const char16_t* w) const 
  { 
    return operator<=(WideString(w));
  }

  bool WideString::operator>=(const char16_t* w) const 
  { 
    return operator>=(WideString(w));
  }

  bool operator ==(const char16_t* w, const WideString& rhs)
  { 
    return rhs.operator==(WideString(w));
  };

  bool operator !=(const char16_t* w, const WideString& rhs)
  { 
    return rhs.operator!=(WideString(w));
  };

  bool operator < (const char16_t* w, const WideString& rhs)
  { 
    return rhs.operator>(WideString(w));
  };

  bool operator > (const char16_t* w, const WideString& rhs)
  { 
    return rhs.operator<(WideString(w));
  };

  bool operator <=(const char16_t* w, const WideString& rhs)
  { 
    return rhs.operator>=(WideString(w));
  };

  bool operator >=(const char16_t* w, const WideString& rhs)
  { 
    return rhs.operator<=(WideString(w));
  };
  
#endif

  WideString WideString::operator+(const WideString& rhs) const
  {
    return System::Internal::Strhlpr::WideCat(STR_CAST_(WideString&, *this), STR_CAST_(WideString&, rhs));
  }

  int WideString::Length() const
  {
    return System::Internal::Strhlpr::WideLength(STR_CAST_(WideString&, *this));
  }

  WideString WideString::Format(const WideString& format, const TVarRec *args, int size)
  {
    return Sysutils::WideFormat(format, args, size);
  }

  WideString WideString::FormatFloat(const WideString& format, const long double& value)
  {
    return WideString(Sysutils::FormatFloat(format, value).c_str());
  }


#if defined (_Windows)
  
#undef vprintf
#undef printf
#undef sprintf

  int __cdecl WideString::vprintf(const wchar_t* format, va_list paramList)
  {
#if !defined(WIDECHAR_IS_CHAR16)  
    int size = vsnwprintf(NULL, 0, format, paramList);
    SetLength(size);
    return size ? vsnwprintf(Data, size + 1, format, paramList) : 0;
#else
    //TAPtr<wchar_t> _buf;
    //int size = vsnwprintf(_buf, format, paramList);
#endif    
  }

  int __cdecl WideString::cat_vprintf(const wchar_t* format, va_list paramList)
  {
#if !defined(WIDECHAR_IS_CHAR16)  
    int size = vsnwprintf(NULL, 0, format, paramList);

    if (!size)
      return 0;

    int len = Length();
    SetLength(len + size);
    return vsnwprintf(Data + len, size + 1, format, paramList);
#else
    //TAPtr<wchar_t> _buf;
    //int size = vsnwprintf(_buf, format, paramList);

    //if (!size)
    //  return 0;

    //int len = Length();
    //SetLength(len + size);
#endif    
  }

  int __cdecl WideString::printf(const wchar_t* format, ...)
  {
    int rc;
    va_list paramList;
    va_start(paramList, format);
    rc = vprintf(format, paramList);
    va_end(paramList);
    return rc;
  }

  WideString& __cdecl WideString::sprintf(const wchar_t* format, ...)
  {
    va_list paramList;
    va_start(paramList, format);
    vprintf(format, paramList);
    va_end(paramList);
    return *this;
  }

  int __cdecl WideString::cat_printf(const wchar_t* format, ...)
  {
    int rc;
    va_list paramList;
    va_start(paramList, format);
    rc = cat_vprintf(format, paramList);
    va_end(paramList);
    return rc;
  }

  WideString& __cdecl WideString::cat_sprintf(const wchar_t* format, ...)
  {
    va_list paramList;
    va_start(paramList, format);
    cat_vprintf(format, paramList);
    va_end(paramList);
    return *this;
  }
#endif // _Windows
  
  WideString WideString::FloatToStrF(long double value, TStringFloatFormat format, int precision, int digits)
  {
    return WideString(Sysutils::FloatToStrF(value, Sysutils::TFloatFormat(format), precision, digits).c_str());
  }

  WideString WideString::IntToHex(int value, int digits)
  {
    return WideString(Sysutils::IntToHex(value, digits).c_str());
  }

  WideString WideString::CurrToStr(Currency value)
  {
    return WideString(Sysutils::CurrToStr(value).c_str());
  }

  WideString WideString::CurrToStrF(Currency value, TStringFloatFormat format, int digits)
  {
    return WideString(Sysutils::CurrToStrF(value, Sysutils::TFloatFormat(format), digits).c_str());
  }

  void WideString::Insert(const WideString& src, int index)
  {
    System::Internal::Strhlpr::WideInsert(*this, STR_CAST_(WideString&, src), index);
  }

  void WideString::Delete(int index, int count)
  {
    System::Internal::Strhlpr::WideDelete(*this, index, count);
  }

  void WideString::SetLength(int newLength) // newLength: wchar_t count
  {
    System::Internal::Strhlpr::WideSetLength(*this, newLength);
  }

  int WideString::Pos(const WideString& subStr) const
  {
    return System::Internal::Strhlpr::WidePos(STR_CAST_(WideString&, *this), STR_CAST_(WideString&, subStr));
  }

  WideString WideString::LowerCase() const
  {
    return Sysutils::WideLowerCase(*this);
  }

  WideString WideString::UpperCase() const
  {
    return Sysutils::WideUpperCase(*this);
  }

  WideString WideString::Trim() const
  {
    return WideString(Sysutils::Trim(*this).c_str());
  }

  WideString WideString::TrimLeft() const
  {
    return WideString(Sysutils::TrimLeft(*this).c_str());
  }

  WideString WideString::TrimRight() const
  {
    return WideString(Sysutils::TrimRight(*this).c_str());
  }

  WideString WideString::SubString(int index, int count) const
  {
    return System::Internal::Strhlpr::WideCopy(STR_CAST_(WideString&, *this), index, count);
  }

  int WideString::ToInt() const
  {
    return Sysutils::StrToInt(*this);
  }

  int WideString::ToIntDef(int defaultValue) const
  {
    return Sysutils::StrToIntDef(*this, defaultValue);
  }

  double WideString::ToDouble() const
  {
    #pragma option push -w-8071
    return Sysutils::StrToFloat(*this);
    #pragma option pop
  }

  bool WideString::IsDelimiter(const WideString& delimiters, int index) const
  {
    return Sysutils::IsDelimiter(UnicodeString(delimiters), UnicodeString(*this), index);
  }

  bool WideString::IsPathDelimiter(int index) const
  {
    return Sysutils::IsPathDelimiter(*this, index);
  }

  int WideString::LastDelimiter(const WideString& delimiters) const
  {
    return Sysutils::LastDelimiter(UnicodeString(delimiters), UnicodeString(*this));
  }

#ifdef WIDESTRING_IS_BSTR
  BSTR WideString::Copy(BSTR src)
  {
    return (src) ? ::SysAllocStringLen(src, ::SysStringLen(src)) : 0;
  }
#endif

#if !defined(WIDECHAR_IS_WCHAR)

  wchar_t* WideString::Copy(wchar_t *dst, int sz) const
  {
    if (!dst || sz == -1)
    {
      sz = Length() + 1;
      dst = new wchar_t[sz];
    }
    else
    {
      int len = Length();
      if (sz > len + 1)
        sz = len + 1;
    }
    for (int i = 0; i < sz - 1; ++i)
      dst[i] = Data[i];
    dst[sz] = 0;
    return dst;
  }
#else
  wchar_t* WideString::Copy(wchar_t *dst, int sz) const
  {
    if (!dst || sz == -1)
    {
      sz = Length() + 1;
      dst = new wchar_t[sz];
    }
    memcpy(dst, Data, sz);
    return dst;
  }
#endif

  const WideChar* WideString::FirstChar() const
  {
    return Data;
  }

  const WideChar* WideString::LastChar() const
  {
    return Data ? Sysutils::AnsiStrLastChar(Data) : 0;
  }

  WideChar* WideString::FirstChar() 
  {
    return Data;
  }

  WideChar* WideString::LastChar()
  {
    return Data ? Sysutils::AnsiStrLastChar(Data) : 0;
  }

  WideString& WideString::swap(WideString& other)
  {
    Data = reinterpret_cast<System::WideChar*>(
          System::Syncobjs::TInterlocked::Exchange(reinterpret_cast<void*&>(other.Data), 
                                                   reinterpret_cast<void*>(Data)));
    return *this;
  }

  void to_string(WideString &str, bool src)
  {
    str = System::Sysutils::BoolToStr(src);
  }
  
  void to_string(WideString &str, char ch)
  {
    str = WideString(ch);
  }

  void to_string(WideString &str, signed char ch)
  {
    str = System::Sysutils::IntToStr(static_cast<signed int>(ch));
  }

  void to_string(WideString &str, unsigned char ch)
  {
    str = System::Sysutils::UIntToStr(static_cast<unsigned int>(ch));
  }

  void to_string(WideString &str, short src)
  {
    str = System::Sysutils::IntToStr(static_cast<signed int>(src));
  }

  void to_string(WideString &str, unsigned short src)
  {
    str = System::Sysutils::UIntToStr(static_cast<unsigned int>(src));
  }

  void to_string(WideString &str, int src)
  {
    str = System::Sysutils::IntToStr(src);
  }

  void to_string(WideString &str, unsigned int src)
  {
    str = System::Sysutils::UIntToStr(src);
  }

  void to_string(WideString &str, long src)
  {
    str = System::Sysutils::IntToStr(static_cast<__int64>(src));
  }

  void to_string(WideString &str, unsigned long src)
  {
    str = System::Sysutils::UIntToStr(static_cast<unsigned __int64>(src));
  }

  void to_string(WideString &str, wchar_t src)
  {
    str = System::StringOfChar(static_cast<WideChar>(src), 1);
  }

  void to_string(WideString &str, long long src)
  {
    str = System::Sysutils::IntToStr(static_cast<__int64>(src));
  }

  void to_string(WideString &str, unsigned long long src)
  {
    str = System::Sysutils::UIntToStr(static_cast<unsigned __int64>(src));
  }

  void to_string(WideString &str, float src)
  {
    str = System::Sysutils::FloatToStr(src);
  }
  void to_string(WideString &str, float src, const Sysutils::TFormatSettings &settings)
  {
    str = System::Sysutils::FloatToStr(src, settings);
  }

  void to_string(WideString &str, double src)
  {
    str = System::Sysutils::FloatToStr(src);
  }
  void to_string(WideString &str, double src, const Sysutils::TFormatSettings &settings)
  {
    str = System::Sysutils::FloatToStr(src, settings);
  }

  void to_string(WideString &str, long double src)
  {
    str = System::Sysutils::FloatToStr(src);
  }
  void to_string(WideString &str, long double src, const Sysutils::TFormatSettings &settings)
  {
    str = System::Sysutils::FloatToStr(src, settings);
  }

  bool from_string(const WideString &str, bool &value)
  {
    return System::Sysutils::TryStrToBool(str, value);
  }

  bool from_string(const WideString &str, Extended &value)
  {
    return System::Sysutils::TryStrToFloat(str, value);
  }
  bool from_string(const WideString &str, const Sysutils::TFormatSettings &settings, Extended &value)
  {
    return System::Sysutils::TryStrToFloat(str, value, settings);
  }

  bool from_string(const WideString &str, int &value)
  {
    return System::Sysutils::TryStrToInt(str, value);
  }

  bool from_string(const WideString &str, long long &value)
  {
    return System::Sysutils::TryStrToInt64(str, value);
  }

  bool from_string(const WideString &str, unsigned int &value)
  {
    return System::Sysutils::TryStrToUInt(str, value);
  }

  bool from_string(const WideString &str, unsigned long long &value)
  {
    return System::Sysutils::TryStrToUInt64(str, value);
  }  
  
#else
  // In _DELPHI_NEXTGEN mode, there's no WideString support
  // This is a dummy impl using UnicodeString
  WideString::WideString(): Data(0) 
  {}
  
  WideString::~WideString()
  {
  }  
#endif  

} // namespace System
