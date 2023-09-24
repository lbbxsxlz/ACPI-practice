#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>

EFI_STATUS EFIAPI GetResolution(
    IN EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop
)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN SizeOfInfo = 0;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;

    /* show the all screen resolution ratio supported */
    for (UINTN i = 0; i < Gop->Mode->MaxMode; i++)
    {
        Status = Gop->QueryMode(
            Gop,/*this pointer*/
            i,
            &SizeOfInfo,
            &Info
        );

        if(EFI_ERROR(Status))
        {
            Print(L"Failed to invoke Gop->Querymode.\n");
            return Status;
        }

        Print(L"Gop->Mode %d, H = %d, V = %d.\n",
        i,
        Info->HorizontalResolution,
        Info->VerticalResolution);
    }

    return Status;
}

EFI_STATUS EFIAPI GraphicBlt(
    IN EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop,
    IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL *bltBuffer,
    IN EFI_GRAPHICS_OUTPUT_BLT_OPERATION operation,
    IN  UINTN                            SourceX,
    IN  UINTN                            SourceY,
    IN  UINTN                            DestinationX,
    IN  UINTN                            DestinationY,
    IN  UINTN                            Width,
    IN  UINTN                            Height,
    IN  UINTN                            Delta
)
{
    return Gop->Blt(Gop, bltBuffer, operation,
        SourceX, SourceY,
        DestinationX, DestinationY,
        Width, Height, Delta);
}

EFI_STATUS
EFIAPI
UefiMain(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN NoHandles = 0;
    EFI_HANDLE *Buffer = NULL;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop = NULL;

    Status = gBS->LocateHandleBuffer(
        ByProtocol,
        &gEfiGraphicsOutputProtocolGuid,
        NULL,
        &NoHandles,
        &Buffer
    );

    Print(L"Return Status of gBS->LocateHandleBuffer = %d.\n", Status);

    if(EFI_ERROR(Status))
    {
        Print(L"Failed to invoke gbs->LoacateHandleBuffer.\n");
        return Status;
    }

    Print(L"NoHandles = %d.\n", NoHandles);

    Status = gBS->OpenProtocol(
        Buffer[0],
        &gEfiGraphicsOutputProtocolGuid,
        (VOID **)&Gop,
        ImageHandle,
        NULL,
        EFI_OPEN_PROTOCOL_GET_PROTOCOL
    );

    Print(L"Return Status of gBS->OpenProtocol = %d.\n", Status);

    if(EFI_ERROR(Status))
    {
        Print(L"Failed to invoke gbs->OpenProtocol.\n");
        return Status;
    }

    Status = GetResolution(Gop);
    if(EFI_ERROR(Status))
    {
        Print(L"Failed to invoke GetResolution.\n");
        return Status;
    }

    /* set the resolution ratio */
    /* 22 : 1920 * 1080 */
    /* 28 : 2560 * 1440*/
    Status = Gop->SetMode(Gop, 28);
    if(EFI_ERROR(Status))
    {
        Print(L"Failed to Setmode.\n");
        return Status;
    }

    EFI_GRAPHICS_OUTPUT_BLT_PIXEL auqamarin = {127, 255, 170, 0};

    Status = GraphicBlt(Gop, &auqamarin, EfiBltVideoFill,
        0, 0, 0, 0, 256, 128, 0);

    if(EFI_ERROR(Status))
    {
        Print(L"Failed to Blt.\n");
        return Status;
    }

    EFI_GRAPHICS_OUTPUT_BLT_PIXEL Orange = {255, 165, 0, 0};

    Status = GraphicBlt(Gop, &Orange, EfiBltVideoFill,
        0, 0, 0, 256, 256, 128, 0);

    if(EFI_ERROR(Status))
    {
        Print(L"Failed to Blt.\n");
        return Status;
    }

    /* Copy region */
    Status = GraphicBlt(Gop, &auqamarin, EfiBltVideoToVideo,
        0, 0, 256, 256, 256, 128, 0);

    if(EFI_ERROR(Status))
    {
        Print(L"Failed to Blt.\n");
        return Status;
    }

    EFI_GRAPHICS_OUTPUT_BLT_PIXEL Gold = {255, 215, 0, 0};

    EFI_PHYSICAL_ADDRESS frameStart = Gop->Mode->FrameBufferBase
                                   + Gop->Mode->Info->PixelsPerScanLine * 128 * 4;

    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *VideoHandle = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)frameStart;

    UINTN NoPixels = Gop->Mode->Info->PixelsPerScanLine * 128;

    for(UINTN i = 0; i < NoPixels; i++)
    {
        *VideoHandle = Gold;
        VideoHandle++;
    }
    return Status;
}
