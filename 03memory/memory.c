#include <ntddk.h>

VOID DriverUnload(PDRIVER_OBJECT driver) {
  DbgPrint("first : Our Driver is unload.\n");
}

NTSTATUS DriverEntry(PDRIVER_OBJECT driver, PUNICODE_STRING regPath) {
  NTSTATUS status;
  UNICODE_STRING dst = {0};
  UNICODE_STRING src = RTL_CONSTANT_STRING(L"source string..");

#if DBG
  _asm int 3
#endif
#define MEM_TAG 'MyTt'
  dst.Buffer = (PWCHAR)ExAllocatePoolWithTag(NonPagedPool, src.Length, MEM_TAG);
  //NonPagedPool == 锁定内存，永远存在真实内存上，不被分配到硬盘的交换内存
  // PagedPool：分页内存 即交换内存swap
  //要分配的内存长度
  //分配的内存的内存标识 用于检测内存泄漏问题
  if (dst.Buffer == NULL){
    status = STATUS_INSUFFICIENT_RESOURCES;
  }
  dst.Length = dst.MaximumLength = src.Length;
  RtlCopyUnicodeString(&dst, &src);

  ExFreePool(dst.Buffer);
  dst.Buffer = NULL;
  dst.Length = dst.MaximumLength = 0;
  //ExFreePool 不能释放栈内内存 比如 src，否则将立即蓝屏
  //驱动卸载
  DbgPrint("first : DriverEntry\n");
  driver->DriverUnload = DriverUnload;

  return STATUS_SUCCESS;
}
