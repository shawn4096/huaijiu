#include <ansi.h>

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "�鳡");
        set("long",@long
���߽��鳡�����������������ֵģ������ﶼ������ģ�����ǰ����һ
λ˵��������������ȥ����ʮ�꣬��������һ����壬���ھ۾������˵��
����---����ҽ�������Ҳ�𽥱���������������������е����ǲ�ʱ�ķ���
��̾�ͺȲ�����ʱ��ʱ��ͭ��������ȥ��
long);
 set("item_desc", ([
    "door" :
"����һ��ͨ�����õ�Сľ�š�\n"
]));
set("objects",([
__DIR__"npc/gongzige" : 1,
]));
set("exits",([
"enter" : __DIR__"houtang",
"south" : __DIR__"xidajie2",
]));
set("no_clean_up", 0);
create_door("enter", "С��", "out", DOOR_CLOSED);
set("coor/x",90);
  set("coor/y",-200);
   set("coor/z",0);
   setup();
}
