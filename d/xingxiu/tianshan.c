// room: /d/xingxiu/tianshan
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "��ɽɽ·");
        set("long","
��������ɽ��´��ɽ���ɽ�ϴ������������ɪɪ�������������
��ɽ�������ԣ��������ѩˮ��ȣ����ط��֣��̳���һƬ��ԭ����ԭ
�Ϸ����Ⱥ��ӣ�һ�Զ�������Ů�����˶������������Գ���
------------------"WHT"��ɽ��ʱ�رգ�"NOR"----------------------\n");

        set("exits", ([
           "southeast" : "/d/hj/senlin1",
        ]));

        set("outdoors", "tianshan");

        set("objects", ([
                __DIR__"npc/hkid" : 1,
                __DIR__"npc/hgirl" : 1,
                __DIR__"npc/yang" : 3,
        ]));

        set("coor/x",-320);
  set("coor/y",120);
   set("coor/z",0);
   setup();
}
