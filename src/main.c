#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <d3d9.h>

int main(int argc, char const *argv[])
{
    HWND    wnd;
    HRESULT hr;

    IDirect3D9            *d3d    = NULL;
    IDirect3DDevice9      *device = NULL;
    D3DPRESENT_PARAMETERS  d3dpp;
    D3DCAPS9 capabilities;

    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed   = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

    ZeroMemory(&capabilities, sizeof(&capabilities));

    d3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (!d3d) {
        printf("IDirect3D9 interface creation failed :<\n");
        return 1;
    }

    wnd = CreateWindow(L"static", L"Testing D3D9", WS_CAPTION,
                       CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                       NULL, NULL, NULL, NULL);
    if (!wnd) {
        printf("Window creation failed :<\n");
        return 1;
    }

    hr = d3d->lpVtbl->CreateDevice(d3d, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
                                   wnd, D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                   &d3dpp, &device);
    if (FAILED(hr)) {
        printf("Device Creation failed :<\n");
        IDirect3D9_Release(d3d);
        DestroyWindow(wnd);
        return 1;
    }

    hr = device->lpVtbl->GetDeviceCaps(device, &capabilities);
    if (FAILED(hr)) {
        printf("Getting capabilities failed :<\n");
        device->lpVtbl->Release(device);
        d3d->lpVtbl->Release(d3d);
        DestroyWindow(wnd);
        return 1;
    }

    printf("Caps: %ld, DynamicFlowControlDepth: %d\nNumTemps: %d, StaticFlowControlDepth: %d\nNumInstructionSlots: %d\n",
           capabilities.PS20Caps.Caps, capabilities.PS20Caps.DynamicFlowControlDepth, capabilities.PS20Caps.NumTemps,
           capabilities.PS20Caps.StaticFlowControlDepth, capabilities.PS20Caps.NumInstructionSlots);

    return 0;
}