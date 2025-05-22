#include <genesis.h>
#include <resources.h>

int main()
{
    VDP_loadTileSet(bgtile.tileset, 1, DMA);
    VDP_setTileMapXY(BG_B, 1, 2, 2);

    // VDP_drawText("Some new and improved text", 4, 6);
    while(1)
    {
        
        SYS_doVBlankProcess();
    }
    return (0);
}
