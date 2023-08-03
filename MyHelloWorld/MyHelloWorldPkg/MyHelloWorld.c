#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    Print(L"Hello, World!\n");
    Print(L"Welcome to the New world of UEFI!\n");
    return EFI_SUCCESS;
}
