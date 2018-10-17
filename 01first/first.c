#include <ntddk.h>

VOID DriverUnload(PDRIVER_OBJECT driver) {
  DbgPrint("first : Our Driver is unload.\n");
}

NTSTATUS DriverEntry(PDRIVER_OBJECT driver, PUNICODE_STRING regPath) {
  UNICODE_STRING str = RTL_CONSTANT_STRING(L"first : this is UNICODE_STRING!\n");
#if DBG
  _asm int 3
#endif
  DbgPrint("first : DriverEntry\n");
  DbgPrint("%wZ", str);
  driver->DriverUnload = DriverUnload;
  return STATUS_SUCCESS;
}
