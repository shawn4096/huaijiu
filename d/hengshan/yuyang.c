// Room: /d/hengshan/yuyang.c
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "��������");
        set("long", @LONG
�����ͱ��¶��ϣ���ʯ���ۣ�ɢ�����£�����������£�����
���У������ڳԲݵ���ֻ������Ǻ͡��𼦱����������ĺ�ɽʤ��
���������ơ���
LONG);
        set("exits", ([ /* sizeof() == 4 */
           "westdown"    : __DIR__"beiyuedian",
        ]));
        set("outdoors", "��ɽ");
        set("no_clean_up", 0);
        set("coor/x",90);
  set("coor/y",120);
   set("coor/z",80);
   setup();
}

