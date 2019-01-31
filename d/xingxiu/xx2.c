// Room: /d/xingxiu/xx2.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "���޺�");
        set("long", @LONG
���������޺�����Բ�����ﶼ��һ���޼ʵĺ��������󣬵���
�����˳�֮Ϊ��������Ҳ��������ʪ�����深ֳ���������޵��ӳ���
�˲�׽���棬�Ա�����֮�á�����ͨ�����޺������������һ��С
�������Ե�׺��Щ���ܡ�����ϡ�٣��������޺���һ����ˡ����ɵ�
�����Ļ�ŭ�ţ�������С����
LONG
        );
        set("objects", ([                
                __DIR__"npc/chuchen" : 1,
        ]) );

        set("exits", ([
             "southeast" : __DIR__"xx1",
             "west" : __DIR__"xx3",
             "enter" : __DIR__"cangku",
        ]));

        set("outdoors", "xingxiuhai");
        set("yushi_count", 1);
        set("coor/x",-310);
  set("coor/y",180);
   set("coor/z",0);
   setup();
}

void init()
{
   	object me = this_player();
  
   	if( me->query("family/family_name") == "������" && me->query("xx_points") > 10
      	&& (random(30) == me->query("kar")) && query("yushi_count") >= 1 && !me->query_temp("yushi_get")){
      		write("�㿴�������и�����һ"WHT"��"NOR"���������ŷ���ԭ����һС����ʯ��\n");
      		me->set_temp("yushi_get", 1);
      		new(MISC_D("yushi"))->move(me);
      		add("yushi_count", -1);
      	}
}

int valid_leave(object me, string dir)
{   
        if( me->query("family/family_name") != "������" && dir == "enter")
//        && objectp(present("chuchen zi", environment(me))))
            return notify_fail("���洫��һ�ɷǳ����ĵ���ζ����һ�ž����£����������ɽ����\n");
        
        return ::valid_leave(me, dir);
}
