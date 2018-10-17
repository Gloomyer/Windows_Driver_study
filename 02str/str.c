#include <ntddk.h>
#include <ntstrsafe.h>

VOID DriverUnload(PDRIVER_OBJECT driver) {
  DbgPrint("first : Our Driver is unload.\n");
}

NTSTATUS DriverEntry(PDRIVER_OBJECT driver, PUNICODE_STRING regPath) {
  UNICODE_STRING str = { 0 };
  UNICODE_STRING str1;
  UNICODE_STRING str2 = {0};
  UNICODE_STRING dst1;
  UNICODE_STRING src1 = RTL_CONSTANT_STRING(L"My source string.");

  WCHAR dst_buf1[256];
  WCHAR strBuf[128] = { 0 };

  NTSTATUS status;
  UNICODE_STRING dst2;
  WCHAR dst_buf2[256];
  UNICODE_STRING src2 = RTL_CONSTANT_STRING(L"My source string...");

  WCHAR dst_buf3[512] = { 0 };
  UNICODE_STRING dst3;
  UNICODE_STRING file_path3 = RTL_CONSTANT_STRING(L"\\??\\d:\\Develop\\WinDDK\\7600.16385.1\\inc\\ddk\\cifs.h");
  USHORT file_size3 = 1024;

#if DBG
  _asm int 3
#endif

  //驱动卸载
  DbgPrint("first : DriverEntry\n");
  driver->DriverUnload = DriverUnload;


  //字符串初始化的3种方式
  //str.Buffer = strBuf;
  //wcscpy(str.Buffer, L"My first string!");
  //str.Length = str.MaximumLength = wcslen(L"My first string!") * sizeof(WCHAR);
  //DbgPrint("%wZ", str);

  str1.Buffer = L"My first string!";
  str1.Length = str1.MaximumLength = wcslen(L"My first string!") * sizeof(WCHAR);
  DbgPrint("%wZ", str1);

  RtlInitUnicodeString(&str2, L"My first string!");
  DbgPrint("%wZ", str2);

  //字符串拷贝
  RtlInitEmptyUnicodeString(&dst1, dst_buf1, 256 * sizeof(WCHAR));
  RtlCopyUnicodeString(&dst1, &src1);
  DbgPrint("%wZ", dst1);

  //字符串连接
  RtlInitEmptyUnicodeString(&dst2, dst_buf2, 256 * sizeof(WCHAR));
  RtlCopyUnicodeString(&dst2, &src2);
  DbgPrint("%wZ", dst2);
  status = RtlAppendUnicodeToString(&dst2, L"my second string!");
  DbgPrint("%wZ  %d", dst2, status);
  //status 成功返回 STATUS_SUCCESS 如果缓存区大小不够 返回 STATUS_BUFFER_TOOL_SMALL
  status = RtlAppendUnicodeStringToString(&dst2, &str);
  DbgPrint("%wZ  %d", dst2, status);
  //RtlAppendUnicodeStringToString:连接两个UNICODE_STRING


  //字符串涉及非字符串的连接
  RtlInitEmptyUnicodeString(&dst3, dst_buf3, 512 * sizeof(WCHAR));
  status = RtlStringCbPrintfW(dst3.Buffer, 512 * sizeof(WCHAR), L"file path = %wZ file size = %d \r\n", &file_path3, file_size3);
  dst3.Length = wcslen(dst3.Buffer) * sizeof(WCHAR);
  DbgPrint("%wZ  %d", dst3, status);
  //RtlStringCbPrintfW 字符串缓冲区不足也可以连接，但是会返回STATUS_BUFFER_OVERFLOW






  return STATUS_SUCCESS;
}
