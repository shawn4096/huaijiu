//���շ�

inherit ROOM;
#include <ansi.h>

void create()
{
   set("short", HIR "���շ�" NOR);
    set("long", 
"�������"HIG"��ɽ���շ�"NOR"��������һվ,�㲻����һ��:\n"
"          ���������,ǧɽĺѩ,ֻӰ��˭ȥ?\n"
"�ĸо�,�����м���ʯͷ,���������ʿƽʱ���������ĵط�!\n"
);
  set("outdoors", "��ɽ");
         set("no_fight", 1);
        set("exits",([
    "west":__DIR__"fengchantai",
]));
        setup();
}