// Room: /d/hengshan/tongyuangu.c
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "ͨԪ��");
        set("long", @LONG
ͨԪ�ȹ´����Է��£��ഫΪ�Ź��ϳ���ǰ�޵�֮����������
���� "ͨԪ" ������Ҳ�ͳ���ͨԪ�ȡ�
LONG);
        set("exits", ([ /* sizeof() == 4 */
           "eastup"  : __DIR__"guolaoling",
        ]));
        set("outdoors", "��ɽ");
        set("no_clean_up", 0);
        set("coor/x",70);
  set("coor/y",100);
   set("coor/z",40);
   setup();
}

