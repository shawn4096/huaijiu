#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�ɿ�");
        set("long", @LONG
��ǰ���������ޱߵ�ãã�󺣣���ˮ���������һ�˽���һ�˵س����߻�
����һ����ȥ��ֻ������Ÿ�ں����Ϸ��裬ż��Ҳ�ɼ���Զ���з�Ӱ�ӹ���
�����ǵ��㵺Ψһ����ͣ�������ĵط�������Ķ������߶���ɳ̲����������
һ�����֡�
LONG
        );

        set("exits", ([
"north" : __DIR__"haitan1",
        ]));
		  set("objects", ([
   __DIR__"npc/chuanfu" :1,
	]));
	set("no_fight",1);
        set("outdoors", "���㵺");
        set("coor/x",490);
  set("coor/y",420);
   set("coor/z",0);
   setup();
        
}

int valid_leave(object me, string dir)
{

        if ( dir == "north")
           return notify_fail(CYN"�����ɿ��ˣ��͸Ͻ��뿪�ɡ�\n"NOR);

        return ::valid_leave(me, dir);
}
