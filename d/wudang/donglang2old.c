// Room: donglang2.c  ��������
// by shang 97/6


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
            "south":__DIR__"xiuxishimen",
            "north" :__DIR__"xiuxishiwomen",
            "west" : __DIR__"xiaolu1",
    ]));
                                                    
        set("item_desc",([
           "menpai1"        :    "Ǭ",
           "menpai2"        :    "��",

    ]));

        setup();
}


int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam = (mapping)me->query("gender");

        if ((myfam["gender_name"] =="����") && dir =="north" )
           return notify_fail("��ѧ������ȥ͵�����˵Ĺ뷿ô?!\n");
        if ((myfam["gender_name"] == "Ů��") && dir == "south") 
           return notify_fail("Ů���˼һ��ǲ�Ҫ����ȥ�ĺã�����Ͳ������ż��ˡ�\n");
                
        return ::valid_leave(me, dir);
}


