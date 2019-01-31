// /d/hmy/shimen.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "ʯ��");
        set("long", "
    �ߵ�һ����ʯ��ǰ��ֻ�����Կ������д��֣������ǡ��ĳ���¡�����
���ǡ�����Ӣ����������Ͽ���

                "HIR"��   ��   ��   ��"NOR"

�ĸ�����֡�\n");
	set("outdoors", "��ľ��");
	set("exits", ([
	"eastdown" : __DIR__"shijie2",
]));
	set("objects", ([ 
	  __DIR__"npc/jiabu" : 1,
]));

	setup();
}
void init()
{
        add_action("do_say", "say");
}

int do_say(string arg)
{

        if( !arg || arg=="" ) return 0;

        if( arg=="�����ĳ���£�һͳ����"
        ||  arg=="������ּӢ���������Ų�")
        {
                write("ֻ���ֲ�˵�������š����Ǳ����ֵܰɣ�������ɡ�\n");
                message("vision", "�ǵ���ʯ�Ż������˿�����һ�����½�ͽ˵�������������\n", this_player());
                set("exits/westup", __DIR__"ryping");

                remove_call_out("close");
                call_out("close", 5, this_object());

                return 1;
        }
}

void close(object room)
{
        message("vision","ֻ���Ǵ�ʯ��ƹ�ع����ˡ�\n", room);
        room->delete("exits/westup");
}

int valid_leave(object me, string dir)
{
	mapping myfam;
	myfam = (mapping)me->query("family");

	if ((!myfam || myfam["family_name"] != "�������") && dir == "westup" &&
		objectp(present("jia bu", environment(me))))
	   return notify_fail("�ֲ��ȵ���վס���㲻��������̵��ӣ��������ڡ�\n");
		
        return ::valid_leave(me, dir);
}
