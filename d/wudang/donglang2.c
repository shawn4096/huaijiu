// Room: donglang2.c  ��������

#include <ansi.h>


inherit ROOM;

void create()
{
    set("short", "��������");
    set("long", @LONG
������һ��ľ�ƽṹ�������ϣ��ϱ���������ݣ��ſڶ�����һ��ǣ�
�ϱߵ�����(menpai1)�����ģ����ߵ�(menpai2)�ǰ׵ġ�
LONG
    );
        set("exits", ([
            "east" : __DIR__"chufang",
            "south":__DIR__"xiuxishi1",
            "north" :__DIR__"xiuxishi2",
            "west" : __DIR__"xiaolu1",
    ]));
        set("objects",([
                "/kungfu/class/wudang/yu" : 1,
        ]));
                                                    
        set("item_desc",([
           "menpai1"        :   HIB"          Ǭ\n"NOR,
           "menpai2"        :   HIW"          ��\n"NOR,

    ]));

        set("coor/x",-10);
  set("coor/y",-80);
   set("coor/z",100);
   setup();
}


int valid_leave(object me, string dir)
{
        if (me->query("family/family_name") != "�䵱��" &&
            present("yu lianzhou", environment(me)) &&
	    (dir =="south" || dir =="north" || dir=="east"))
           return notify_fail("��������ס���ȥ·����ȭ�������䵱���Ӳ������ڡ�\n");

        if ((me->query("gender") =="����") && dir =="north" )
           return notify_fail("��ѧ������ȥ͵�����˵Ĺ뷿ô?!\n");
        if ((me->query("gender") == "Ů��") && dir == "south") 
           return notify_fail("Ů���˼һ��ǲ�Ҫ����ȥ�ĺã�����Ͳ������ż��ˡ�\n");
                
        return ::valid_leave(me, dir);
}

