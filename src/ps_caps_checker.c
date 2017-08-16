#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <d3d9.h>

int main(int argc, char const *argv[])
{
    HWND    wnd       = NULL;
    HRESULT hr        = E_FAIL;
    int     exit_code = 1;

    IDirect3D9            *d3d    = NULL;
    IDirect3DDevice9      *device = NULL;
    D3DPRESENT_PARAMETERS  d3dpp;
    D3DCAPS9 capabilities;
    D3DADAPTER_IDENTIFIER9 identifier;

    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed   = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

    ZeroMemory(&capabilities, sizeof(&capabilities));

    d3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (!d3d) {
        printf("IDirect3D9 interface creation failed :<\n");
        goto cleanup;
    }

    wnd = CreateWindow(L"static", L"Testing D3D9", WS_CAPTION,
                       CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                       NULL, NULL, NULL, NULL);
    if (!wnd) {
        printf("Window creation failed :<\n");
        goto cleanup;
    }

    hr = d3d->lpVtbl->CreateDevice(d3d, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
                                   wnd, D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                   &d3dpp, &device);
    if (FAILED(hr)) {
        printf("Device Creation failed :<\n");
        goto cleanup;
    }

    hr = device->lpVtbl->GetDeviceCaps(device, &capabilities);
    if (FAILED(hr)) {
        printf("Getting capabilities failed :<\n");
        goto cleanup;
    }

    hr = d3d->lpVtbl->GetAdapterIdentifier(d3d, D3DADAPTER_DEFAULT, 0, &identifier);
    if (FAILED(hr)) {
        printf("Getting adapter identifier failed :<\n");
        goto cleanup;
    }

    printf("Device: %s, ID: %d\n\n", identifier.Description,
           capabilities.MasterAdapterOrdinal);
    printf("PixelShaderVersion: %d.%d\n\n", D3DSHADER_VERSION_MAJOR(capabilities.PixelShaderVersion),
           D3DSHADER_VERSION_MINOR(capabilities.PixelShaderVersion));
    printf("Caps: %ld, DynamicFlowControlDepth: %d\nNumTemps: %d, StaticFlowControlDepth: %d\nNumInstructionSlots: %d\n",
           capabilities.PS20Caps.Caps, capabilities.PS20Caps.DynamicFlowControlDepth, capabilities.PS20Caps.NumTemps,
           capabilities.PS20Caps.StaticFlowControlDepth, capabilities.PS20Caps.NumInstructionSlots);

    exit_code = 0;

cleanup:
    if (device) {
        IDirect3DDevice9_Release(device);
    }
    if (wnd) {
        DestroyWindow(wnd);
    }
    if (d3d) {
        IDirect3D9_Release(d3d);
    }

    return exit_code;
}
