#include <common.h>

void MM_Scrapbook_Init(void)
{
    OVR_230.scrapbookState = 0;

    // change checkered flag
    TitleFlag_SetDrawOrder(1);

    // clear gamepad input (for menus)
    MENUBOX_ClearInput();
}